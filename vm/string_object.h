#ifndef STRING_OBJECT_H_INCLUDED
#define STRING_OBJECT_H_INCLUDED

#include "object.h"

namespace AYA
{
    class StringObject : public Object
    {
        friend class ObjectFactory;
    protected:
        StringObject(TypeObject* definition, const STRING_T& init)
        :
            Object(definition),
            content(init)
        {}

        StringObject(const StringObject& o)
        :
            Object(o),
            content(o.content)
        {}

        // TODO add to gc
        StringObject* clone() const
        {
            return new StringObject(*this);
        }

        int getBuildInType() const
        {
            return BType::STR;
        }
    public:
        void mark() const
        {
            Object::mark();
        }

        const STRING_T content;
    };
}

#endif // STRING_OBJECT_H_INCLUDED
