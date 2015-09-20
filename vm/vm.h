#ifndef VM_H_INCLUDED
#define VM_H_INCLUDED

#include "function_call.h"

#include "gc.h"
#include "eval_stack.h"
#include "object_factory.h"
#include "io_manager.h"

#include "closure.h"

#include "../error.h"
#include "parser.h"

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
        void printResult();
        void setParserInput(std::istream*);
        void interrupt();

        EvalStack::CCallFrame& callFrame()
        {
            return evalStack.cCallFrame;
        }

        GarbageCollector gc;
        IOManager io;

    //protected:
        ObjectFactory objectFactory;
        pEnvironment globalEnv;
    protected:
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
        bool halt;

        void clearStack();

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
        void loadCollection();
        void storeCollection();
    };

}
#endif // VM_H_INCLUDED
