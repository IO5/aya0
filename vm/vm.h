#ifndef VM_H_INCLUDED
#define VM_H_INCLUDED

#include "function_call.h"

#include "gc.h"
#include "eval_stack.h"
#include "object_factory.h"
#include "io_manager.h"

#include "closure.h"

#include "../error.h"

namespace AYA
{
    class VM
    {
        friend class IOManager;
        friend class FunctionBuilder;

        friend class Parser;
        friend class BuiltIn;
    public:
        VM()
        :
            gc(this),
            objectFactory(*this),
            globalEnv(new Environment(NULL)),
            activeFunction(NULL)
        {
        }

        void run();
        void interrupt();

        void load(const FunctionPrototype* proto)
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

        void mark();

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

    private:
        bool halt;

        // helpers
        int test(const Variant&);
        int getType(const Variant&);
        int getBuildInType(const Variant&);
        const STRING_T& getStr(const Variant&);

        void call(uint8_t f);

        void binOp(uint8_t f);
        void unOp(uint8_t f);

        void createList(uint8_t f);
        void loadCollection();
        void storeCollection();
    };

}
#endif // VM_H_INCLUDED
