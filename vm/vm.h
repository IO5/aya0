#ifndef VM_H_INCLUDED
#define VM_H_INCLUDED

#include "function_call.h"

#include "gc.h"
#include "eval_stack.h"
#include "object_factory.h"
#include "io_manager.h"
#include "file_manager.h"

#include "closure.h"

#include "../error.h"
#include "../bind.h"

#include "parser.h"

#include <atomic>

namespace quex { class lexer; };

namespace AYA
{
    class VM
    {
        friend class IOManager;
        friend class FunctionBuilder;
        friend class GarbageCollector;
        friend class BuiltIn;
    public:
        VM();
        ~VM();

        int run();
        const FunctionPrototype* parse(const STRING_T& input, const std::vector<IDENT_T>& args = std::vector<IDENT_T>());
        void printResult();
        void setParserInput(std::istream*);
        void interrupt() { halt.store(true); };
        void clearStack();

        EvalStack::CCallFrame& callFrame()
        {
            return evalStack.cCallFrame;
        }

        void setIntVariable(const IDENT_T& var, INT_T val) { globalEnv->set(var, INT(val)); }
        void setRealVariable(const IDENT_T& var, REAL_T val) { globalEnv->set(var, REAL(val)); }
        void setStringVariable(const IDENT_T& var, STRING_T val) { globalEnv->set(var, objectFactory.makeString(val)); }
        void setCFuncVariable(const IDENT_T& var, Bind val) { globalEnv->set(var, BIND(val)); }
        void setFuncVariable(const IDENT_T& var, const FunctionPrototype* val) { globalEnv->set(var, objectFactory.makeClosure(val, globalEnv)); }

        GarbageCollector gc;
        IOManager io;
        FileManager files;

        int maxRecursionDepth = 100;

        ObjectFactory objectFactory;
    protected:
        pEnvironment globalEnv;
        EvalStack evalStack;
        FunctionCall* activeFunction;
        quex::lexer* qlex;
        std::istream* parserInput;

        void mark();
        void _run();
        void _load(const FunctionPrototype* proto)
        {
            if(activeFunction == NULL)
            {
                //TODO TODO TODO
                activeFunction = new FunctionCall(objectFactory.makeClosure(proto, globalEnv), NULL);
                activeFunction->enter(evalStack, 0, NIL());
            }
            else
            {
                throw RuntimeError("Unable to load function. Call stack is not empty.");
            }
        }

    private:
        std::atomic_bool halt;

        // helpers
        int test(const Variant&);
        int getType(const Variant&);
        int getBuildInType(const Variant&);
        const STRING_T& getStr(const Variant&);

        void call(uint8_t f);
        void construct(uint8_t f);

        void binOp(uint8_t f);
        void unOp(uint8_t f);

        void createList(uint8_t f);
        void createDict(uint8_t f);
        void loadCollection();
        void storeCollection();
    };

}
#endif // VM_H_INCLUDED
