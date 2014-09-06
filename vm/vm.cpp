#include "vm.h"
#include "std_functions.h"

namespace AYA
{
    void VM::run()
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
                    evalStack.pop();
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
                        evalStack.push( NIL() );

                    break;
                }

                case Inst::STORE:
                {
                    auto& str = getStr(constTable[inst.operand()]);
                    env->set( str, evalStack.pop() );
                    break;
                }

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

                // 1 argument, self-call
                uint8_t operand = 1 | (1 << 7);
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
                binOpTemplate<Eq>(evalStack);
                break;

            case '!':
                binOpTemplate<NEq>(evalStack);
                break;

            case '<':
                binOpTemplate<Less>(evalStack);
                break;

            // lol (for the record: '<'|'+' would be more readable but unfortunately results in '=')
            case '<'+'=':
                binOpTemplate<LessEq>(evalStack);
                break;

            case '>':
                binOpTemplate<Great>(evalStack);
                break;

            case '>'+'=':
                binOpTemplate<GreatEq>(evalStack);
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

            if(func)
            {
                evalStack.push(*func);

                // 2 arguments, self-call
                uint8_t operand = 2 | (1 << 7);
                call(operand);
            }
            else
            {
                throw RuntimeError("Could not find an overloaded operator \'" + s + "\'");
            }
        }
    }


    // Call

    void VM::call(uint8_t operand)
    {
        Variant v = evalStack.pop();
        uint8_t argCount = operand & ~(1 << 7);
        uint8_t self = operand >> 7;

        if(v.isCFUNC())
        {
            // C call
            Bind cFunc = v.value.cfunc;

            int status;
            auto& frame = evalStack.prepareCallFrame(argCount, self);

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

            newCall->enter(evalStack, argCount, self);

            activeFunction = newCall;
        }
        else
            throw RuntimeError("Unable to call, type mismatch.");
    }
}
