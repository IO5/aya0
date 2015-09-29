#ifndef LIST_OBJECT_H_INCLUDED
#define LIST_OBJECT_H_INCLUDED

#include "object.h"

namespace AYA
{
    class ListObject : public Object
    {
        friend class ObjectFactory;
    protected:
        ListObject(TypeObject* definition, std::vector<Variant>&& init)
        :
            Object(definition),
            content(std::move(init))
        {}

        ListObject(const ListObject& o)
        :
            Object(o),
            content(o.content)
        {}

        // TODO add to gc
        ListObject* clone() const
        {
            return new ListObject(*this);
        }

        int getBuildInType() const
        {
            return BType::LIST;
        }
    public:
        void mark() const
        {
            if(!marker)
            {
                Object::mark();
                for (auto& v : content)
                        v.mark();
            }
        }

        std::vector<Variant> content;
    };
}

#endif // LIST_OBJECT_H_INCLUDED
