#include "vm.h"
#include "std_functions.h"
#include "built_in.h"

#include "lexer"
#include "parser.h"

#ifndef     ENCODING_NAME
#    define ENCODING_NAME (0x0)
#endif

#include<iostream> //TODO change to io manager

namespace AYA
{
    VM::~VM()
    {
        delete activeFunction;
        delete qlex;
    }

    VM::VM() :
        gc(this),
        objectFactory(*this),
        globalEnv(new Environment(NULL)),
        activeFunction(NULL),
        // NULL pointer = use raw memory
        qlex( new quex::lexer((QUEX_TYPE_CHARACTER*)NULL, ENCODING_NAME)),
        parserInput(NULL)
    {
        gc.setMemoryLimit(GarbageCollector::NO_LIMIT);

        Object* stdlib = objectFactory.makeObject();
        globalEnv->set("std", REF(stdlib));
        stdlib->set("object", REF(objectFactory.OBJECT_DEF), &gc);
        stdlib->set("type", REF(objectFactory.TYPE_OBJECT_DEF), &gc);
        stdlib->set("function", REF(objectFactory.FUNCTION_OBJECT_DEF), &gc);
        stdlib->set("string", REF(objectFactory.STRING_OBJECT_DEF), &gc);
        stdlib->set("list", REF(objectFactory.LIST_OBJECT_DEF), &gc);
        //stdlib->set("dict_type", REF(objectFactory.DICT_OBJECT_DEF), &gc);

        globalEnv->set("print", BIND(BuiltIn::print));
        globalEnv->set("puts",  BIND(BuiltIn::puts));
    }

    void VM::printResult()
    {
        BuiltIn::printValue(this, evalStack.lastExpr);
    }

    void VM::setParserInput(std::istream* is)
    {
        parserInput = is;
    }

    void VM::clearStack()
    {
        evalStack.clear();
        delete activeFunction;
        activeFunction = NULL;
    }

    int VM::run()
    {
        if (!parserInput)
        {
            return -1;
        }

        quex::Token token;
        (void)qlex->token_p_switch(&token);

        qlex->buffer_fill_region_prepare();

        // Read a line from standard input
        parserInput->getline((char*)qlex->buffer_fill_region_begin(),
                    qlex->buffer_fill_region_size());

        if( parserInput->gcount() == 0 ) {
            return 0;
        }

        // Inform about number of read characters. Note, that getline
        // writes a terminating zero, which has not to be part of the
        // buffer content.
        qlex->buffer_fill_region_finish(parserInput->gcount() - 1);

        try
        {
            Parser parser(*this);

            // Loop until the 'EOS' token arrives
            do {
                (void)qlex->receive();
                parser.parse(&token);
            } while( token.type_id() != TK_EOS );

            const FunctionPrototype* proto = parser.generateCode();
            _load(proto);

            _run();
        }
        catch(ParseError err)
        {
            std::cerr << err.what() << std::endl;
            clearStack();
            while( token.type_id() != TK_EOS )
                (void)qlex->receive();
            return -1;
        }
        catch(RuntimeError err)
        {
            std::cerr << "Error: " << err.what() << std::endl;
            clearStack();
            return -1;
        }

        clearStack();
        return 0;
    }

    void VM::_run()
    {
        halt = false;

        while(activeFunction != NULL)
        {
            while(!halt)
            {
                uint32_t&     PC = activeFunction->PC();
                auto&       code = activeFunction->code();
                auto& constTable = activeFunction->constTable();
                auto         env = activeFunction->environment();

                assert(PC < code.size());

                Inst inst = code[PC];

                //std::cerr<<Inst::name[inst.opcode()]<<'\n';

                ++PC;

                Variant tmp;

                switch(inst.opcode())
                {
                case Inst::NOP:
                    break;

                case Inst::POP:
                    evalStack.lastExpr = evalStack.pop();
                    break;

                case Inst::LNIL:
                    evalStack.push(NIL());
                    break;

                case Inst::LBOOL:
                    evalStack.push(INT(inst.operand()));
                    break;

                case Inst::LCONST:
                    evalStack.push(constTable[inst.operand()]);
                    break;

                case Inst::LOAD:
                {
                    auto& str = getStr(constTable[inst.operand()]);
                    const Variant* v = env->get( str );
                    if(v)
                        evalStack.push( *v );
                    else
                        throw RuntimeError("Variable \"" + str + "\" is undeclared");

                    break;
                }

                case Inst::STORE:
                {
                    auto& str = getStr(constTable[inst.operand()]);
                    env->set( str, evalStack.pop() );
                    break;
                }

                case Inst::LOADM:
                {
                    auto& str = getStr(constTable[inst.operand()]);
                    Variant& obj = evalStack.self = evalStack.pop();
                    if (!obj.isREF())
                        throw RuntimeError("Type error: not an object");

                    const Variant* v = obj.value.ref->get( str );
                    if(v)
                        evalStack.push( *v );
                    else
                        throw RuntimeError("Member variable \"" + str + "\" is undeclared");

                    break;
                }

                case Inst::STOREM:
                {
                    auto& str = getStr(constTable[inst.operand()]);
                    Variant& obj = evalStack.peek(2);
                    if (!obj.isREF())
                        throw RuntimeError("Type error: not an object");

                    if (!gc.isRegistered(obj.value.ref) || str == "type" || str == "__new__")
                        throw RuntimeError("Cannot modify an immutable object");

                    obj.value.ref->set( str, evalStack.peek(), &gc );
                    evalStack.pop(2);
                    break;
                }

                case Inst::LOADC:
                    loadCollection();
                    break;

                case Inst::STOREC:
                    storeCollection();
                    break;

                case Inst::JMP:
                    PC += inst.operand();
                    break;

                case Inst::JMPT:
                    if(test(evalStack.pop()))
                        PC += inst.operand();

                    break;

                case Inst::JMPF:
                    if(!test(evalStack.pop()))
                        PC += inst.operand();

                    break;

                case Inst::ITER:
                {
                    Variant& v1 = evalStack.peek(1);
                    Variant& v2 = evalStack.peek(2);
                    // no code allowing such situation should be generated
                    assert (v1.isINT() && getBuildInType(v2) == BType::LIST);

                    INT_T& it = v1.value.integer;
                    auto& list = static_cast<ListObject*>(v2.value.ref)->content;

                    // fetch next element
                    if ((size_t)it < list.size()) {
                        evalStack.push(list[it]);
                        ++it;
                    }
                    // clean up
                    else
                    {
                        evalStack.pop(2);
                        PC += inst.operand();
                    }
                    break;
                }

                /// Lazy evaluated OR
                case Inst::OR:
                    if(test(evalStack.peek()))
                        PC += inst.operand();
                    else
                        evalStack.pop();

                    break;

                /// Lazy evaluated AND
                case Inst::AND:
                    if(!test(evalStack.peek()))
                        PC += inst.operand();
                    else
                        evalStack.pop();

                    break;

                case Inst::UNOP:
                    unOp(inst.operand());
                    break;

                case Inst::BINOP:
                    binOp(inst.operand());
                    break;

                case Inst::CALL:
                    if(getBuildInType(evalStack.peek()) == BType::TYPE)
                        construct(inst.operand());
                    else
                        call(inst.operand());
                    break;

                case Inst::RET:
                    goto RETURN;
                    break;

                case Inst::CLOSURE:
                {
                    Variant v = constTable[inst.operand()];
                    assert(v.isPROTO());
                    Closure* c = objectFactory.makeClosure(v.value.proto, env);
                    evalStack.push(REF(c));
                    break;
                }

                case Inst::LISTC:
                    createList(inst.operand());
                    break;

                case Inst::DICTC:
                    createDict(inst.operand());
                    break;

                // Type constructor
                case Inst::TYPEC:
                {
                    auto& ident = getStr(constTable[inst.operand()]);
                    Variant baseClass = evalStack.pop();
                    TypeObject* type;
                    if (baseClass == NIL())
                        type = objectFactory.makeType(ident);
                    else
                        type = objectFactory.makeType(ident, static_cast<TypeObject*>(baseClass.value.ref));

                    evalStack.push(REF(type));
                    env->set( ident, REF(type) );

                    break;
                }
                // Store member function definition in type
                case Inst::STORET:
                {
                    auto& ident = getStr(constTable[inst.operand()]);
                    Variant& v = evalStack.peek(2);
                    TypeObject* type = static_cast<TypeObject*>(v.value.ref);
                    type->setShared( ident, evalStack.pop(), &gc );
                    break;
                }

                case Inst::SENTER:
                    activeFunction->enterScope();
                    break;

                case Inst::SLEAVE:
                    activeFunction->leaveScope();
                    break;

                case Inst::DECL:
                {
                    auto& str = getStr(constTable[inst.operand()]);
                    env->declareLocal(str);
                    break;
                }

                default:
                    throw RuntimeError("VM has encounter an unknown instruction.");
                }
            }

            // leave aya func
            RETURN:

            FunctionCall* oldCall = activeFunction;
            activeFunction = activeFunction->caller();

            delete oldCall;
        }
    }

    void VM::mark()
    {
        //globalEnv->mark();
        if(activeFunction)
            activeFunction->mark();
    }

    /// Test for true
    int VM::test(const Variant& v)
    {
        // 0, nil -> false, every other number -> true
        if(v.isNIL())
        {
            return false;
        }
        else if(v.isINT())
        {
            return v.value.integer;
        }
        else if(v.isREAL())
        {
            return (INT_T)v.value.real;
        }
        else
            throw RuntimeError("Type mismatch");
    }

    int VM::getType(const Variant& v)
    {
        if(v.tag != BType::REF)
            return v.tag;
        else
        {
            assert(v.value.ref);
            return objectFactory.getType(v.value.ref);
        }
    }

    int VM::getBuildInType(const Variant& v)
    {
        if(v.tag != BType::REF)
            return v.tag;
        else
        {
            assert(v.value.ref);
            return objectFactory.getBuildInType(v.value.ref);
        }

    }

    const STRING_T& VM::getStr(const Variant& v)
    {
        assert(getBuildInType(v) == BType::STR);

        StringObject* str = static_cast<StringObject*>(v.value.ref);
        return str->content;
    }

    inline void VM::unOp(uint8_t op)
    {
        Variant& v = evalStack.peek();

        // primitive type
        if(!v.isREF())
        {
            if(v.isINT() || v.isREAL())
            {
                switch(op)
                {
                case '-':
                    if(v.isINT())
                        v.value.integer = -v.value.integer;
                    else
                        v.value.real = -v.value.real;
                    break;

                case '!':
                    if(v.isREAL())
                        v.value.integer = !v.value.integer;
                    else
                        v.value.real = !v.value.real;
                    break;

                case '|':
                    throw RuntimeError("Could not find an overloaded operator ||");
                    break;
                default:
                    assert(false);
                }
            }
            else
                throw RuntimeError("Type mismatch");
        }
        // object
        else
        {
            Object* obj = v.value.ref;

            assert(obj);

            // char -> string
            STRING_T s;
            if(op == '|')
                s = "||";
            else
                s += op;


            const Variant* func = obj->getReadOnly(s);

            if(func)
            {
                evalStack.push(*func);

                // 1 argument
                uint8_t operand = 1;
                call(operand);
            }
            else
            {
                throw RuntimeError("Could not find an overloaded operator \'" + s + "\'");
            }
        }
    }

    inline void VM::binOp(uint8_t op)
    {
        Variant& v = evalStack.peek(2);

        // primitive type
        if(!v.isREF())
        {
            switch(op)
            {
            case '+':
                binOpTemplate<Add>(evalStack);
                break;

            case '-':
                binOpTemplate<Sub>(evalStack);
                break;

            case '*':
                binOpTemplate<Mul>(evalStack);
                break;

            case '/':
                Div(evalStack);
                break;

            case '%':
                Mod(evalStack);
                break;

            case '^':
                binOpTemplate<Pow>(evalStack);
                break;

            case '=':
                Eq(evalStack);
                break;

            case '!':
                NEq(evalStack);
                break;

            case '<':
                compareTemplate<Less>(evalStack);
                break;

            // lol (for the record: '<'|'+' would be more readable but unfortunately results in '=')
            case '<'+'=':
                compareTemplate<LessEq>(evalStack);
                break;

            case '>':
                compareTemplate<Great>(evalStack);
                break;

            case '>'+'=':
                compareTemplate<GreatEq>(evalStack);
                break;

            default:
                assert(false);
            }
        }
        // object
        else
        {
            Object* obj = v.value.ref;

            assert(obj);

            // char -> string
            STRING_T s(1, op);

            switch(op)
            {
            case '=':
                s = "==";
                break;

            case '<'+'=':
                s = "<=";
                break;

            case '>'+'=':
                s = ">=";
                break;
            }

            const Variant* func = obj->getReadOnly(s);

            if (func)
            {
                evalStack.push(*func);

                // 2 arguments
                uint8_t operand = 2;
                call(operand);
            }
            //compare references
            else if (op == '!' || op == '=')
            {
                Variant v2 = evalStack.pop();
                INT_T result = (v == v2);
                if (op == '!')
                    result = !result;

                evalStack.pop();
                evalStack.push(INT(result));
            }
            else
            {
                throw RuntimeError("Could not find an overloaded operator \'" + s + "\'");
            }
        }
    }

    // Constructor hacky hack hack
    void VM::construct(uint8_t argCount)
    {
        Variant &v = evalStack.peek();
        TypeObject* type = static_cast<TypeObject*>(v.value.ref);
        evalStack.push(*(type->getShared("__new__")));
        call(1); //returns new object

        Variant obj = evalStack.self = evalStack.peek();
        if (!obj.isREF())
            throw RuntimeError("Type error: not an object");

        const Variant* init = obj.value.ref->get( "init" );
        if(init)
        {
            int initType = getBuildInType(*init);
            if(initType != BType::CFUNC && initType != BType::FUNC)
                throw RuntimeError("Invalid \"init\" function");

            // take obj aside
            evalStack.pop();
            evalStack.push( *init );
            call(argCount);
            evalStack.push( REF(obj) );
        }
    }

    // Call
    void VM::call(uint8_t argCount)
    {
        Variant v = evalStack.pop();

        if(v.isCFUNC())
        {
            // C call
            Bind cFunc = v.value.cfunc;

            int status;
            auto& frame = evalStack.prepareCallFrame(argCount, evalStack.self);

            status = cFunc(this);

            if(status < 0)
                throw RuntimeError(frame.errorMsg());

            evalStack.clearCallFrame();
        }
        else if(v.isREF() && getBuildInType(v) == BType::FUNC)
        {
            // enter aya func
            Closure* c = static_cast<Closure*>(v.value.ref);

            FunctionCall* newCall = new FunctionCall(c, activeFunction);

            newCall->enter(evalStack, argCount, evalStack.self);

            activeFunction = newCall;
        }
        else
            throw RuntimeError("Unable to call, type mismatch.");

        evalStack.self = NIL();
    }

    void VM::createList(uint8_t listLen)
    {
        std::vector<Variant> list(listLen);

        int i = listLen;
        for (auto& element : list)
            element = evalStack.peek(i--);
        evalStack.pop(listLen);

        evalStack.push(
                       REF(objectFactory.makeList(std::move(list)))
                       );
    }

    void VM::createDict(uint8_t dictSize)
    {
        DictObject* dict = objectFactory.makeDict();

        for (auto i = 0; i < dictSize; ++i)
        {
            Variant val = evalStack.pop();
            Variant key = evalStack.pop();
            if ( getType(key) != BType::INT
                && getType(key) != BType::REAL
                && getBuildInType(key) != BType::STR )
            {
                throw RuntimeError("Type error: dictionary key must be hashable");
            }
            dict->content[key] = val;
        }

        gc.updateObj(dict, sizeof(Variant)*dictSize*2);
        evalStack.push(REF(dict));
    }

    void VM::loadCollection()
    {
        Variant index = evalStack.pop();
        Variant collection = evalStack.pop();
        if (collection.isREF())
        {
            if (getType(collection) == BType::LIST)
            {
                if (getType(index) != BType::INT)
                    throw RuntimeError("Type error: list index must be an integer");

                ListObject* list = static_cast<ListObject*>(collection.value.ref);
                INT_T i = index.value.integer;
                if (i < 0)
                    i += list->content.size();
                if (i < 0 || i >= (INT_T)list->content.size())
                    throw RuntimeError("Index out of bounds");

                evalStack.push(list->content[i]);
            }
            else if (getType(collection) == BType::DICT)
            {
                if ( getType(index) != BType::INT
                    && getType(index) != BType::REAL
                    && getBuildInType(index) != BType::STR )
                {
                    throw RuntimeError("Type error: dictionary key must be hashable");
                }

                Dict& dict = static_cast<DictObject*>(collection.value.ref)->content;
                if (dict.find(index) == dict.end())
                    throw RuntimeError("Key not found");

                evalStack.push(dict[index]);
            }
            else
            {
                throw RuntimeError("Type error: not a collection");
            }
        }
        else
        {
            throw RuntimeError("Type error: not a collection");
        }
    }

    void VM::storeCollection()
    {
        Variant value = evalStack.pop();
        Variant index = evalStack.pop();
        Variant collection = evalStack.pop();
        if (collection.isREF())
        {
            if (getType(collection) == BType::LIST)
            {
                if (getType(index) != BType::INT)
                    throw RuntimeError("Type error: list index must be an integer");

                ListObject* list = static_cast<ListObject*>(collection.value.ref);
                INT_T i = index.value.integer;
                if (i < 0)
                    i += list->content.size();
                if (i < 0 || i >= (INT_T)list->content.size())
                    throw RuntimeError("Index out of bounds");

                list->content[i] = value;
            }
            else if (getType(collection) == BType::DICT)
            {
                if ( getType(index) != BType::INT
                    && getType(index) != BType::REAL
                    && getBuildInType(index) != BType::STR )
                {
                    throw RuntimeError("Type error: dictionary key must be hashable");
                }

                Dict& dict = static_cast<DictObject*>(collection.value.ref)->content;
                if (dict.find(index) == dict.end())
                    gc.updateObj(collection.value.ref, sizeof(Variant)*2);

                dict[index] = value;
            }
            else
            {
                throw RuntimeError("Type error: not a collection");
            }
        }
        else
        {
            throw RuntimeError("Type error: not a collection");
        }
    }
}
