#ifndef DICT_OBJECT_H_INCLUDED
#define DICT_OBJECT_H_INCLUDED

#include "object.h"
#include <unordered_map>

namespace AYA
{
    //typedef std::unordered_map<Variant, Variant> Dict;
    typedef int Dict;

    class DictObject : public Object
    {
        friend class ObjectFactory;
    protected:
        DictObject(TypeObject* definition, Dict&& init)
        :
            Object(definition),
            content(std::move(init))
        {}

        DictObject(const DictObject& o)
        :
            Object(o),
            content(o.content)
        {}

        // TODO add to gc
        DictObject* clone() const
        {
            return new DictObject(*this);
        }

        int getBuildInType() const
        {
            return BType::DICT;
        }
    public:
        void mark() const
        {
            Object::mark();
        }

        Dict content;
    };
}

#endif // DICT_OBJECT_H_INCLUDED
