#ifndef CLOSURE_H_INCLUDED
#define CLOSURE_H_INCLUDED

#include "object.h"
#include "environment.h"
#include "function_prototype.h"

namespace AYA
{
    class Closure : public Object
    {
        friend class ObjectFactory;
        friend class FunctionCall;

        Closure(TypeObject* _def, const FunctionPrototype* _proto, const pEnvironment& _env)
        :
            Object(_def),
            proto(_proto),
            env(_env)
        { }

        Closure(const Closure& o)
        :
            Object(o),
            proto(o.proto),
            env(o.env)
        {}

        Closure* clone() const
        {
            return new Closure(*this);
        }

        int getBuildInType() const
        {
            return BType::FUNC;
        }
    public:
        void mark() const
        {
            Object::mark();
            if(!marker)
            {
                proto->mark();
                env->mark();
            }
        }

    protected:
        const FunctionPrototype* proto;
        pEnvironment env;
    };
    typedef Closure FunctionObject;
}

#endif // CLOSURE_H_INCLUDED
