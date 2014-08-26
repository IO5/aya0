#ifndef FUNCTION_CALL_H_INCLUDED
#define FUNCTION_CALL_H_INCLUDED

#include "closure.h"
#include "eval_stack.h"

namespace AYA
{
    class FunctionCall
    {
    public:
        FunctionCall(Closure* c, FunctionCall* caller)
        :
            _PC(0),
            closure(c),
            _caller(caller),
            env(c->env)
        {}

        void enter(EvalStack& evalStack, size_t argCount, bool selfCall)
        {
            newScope();
            // load arguments
            size_t i = 0;

            if(selfCall)
            {
                env->set("self", evalStack.peek(argCount));
                ++i;
            }

            auto& args = closure->proto->arguments;
            while ( (i < argCount) && (i < args.size()) )
            {
                env->set(args[i], evalStack.peek(argCount-i));

                ++i;
            }

            while (i < args.size())
            {
                env->set(args[i], NIL());

                ++i;
            }

            evalStack.pop(argCount);
        }

        // not really needed
        ~FunctionCall()
        {
            leaveScope();
        }

        /// Getters
        uint32_t& PC()
        {
            return _PC;
        }

        FunctionCall* caller()
        {
            return _caller;
        }

        const InstCode& code()
        {
            return closure->proto->code;
        }

        const ValueList& constTable()
        {
            return closure->proto->constTable;
        }

        pEnvironment environment()
        {
            return env;
        }

         // Enter new scope
        pEnvironment newScope()
        {
            pEnvironment newEnv(new Environment(env));
            env = newEnv;
            return env;
        }

        // Leave scope
        pEnvironment leaveScope()
        {
            // has a parent?
            assert(env->parent());

            env = env->parent();
            return env;
        }


        void mark() const
        {
            closure->mark();
            if(_caller)
                _caller->mark();

            env->mark();
        }

    protected:
        // Program Counter
        uint32_t _PC;
        Closure* closure;
        FunctionCall* _caller;
        pEnvironment env;
    };
}


#endif // FUNCTION_CALL_H_INCLUDED
