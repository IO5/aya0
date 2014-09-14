#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include "variant.h"
#include "inst.h"
#include "symbol_table.h"
#include "gc.h"

#include "../bind.h"


#include <vector>

namespace AYA
{
    class TypeObject;

    class Object : public ManagedMemory
    {
        friend class ObjectFactory;
    protected:
        explicit Object(TypeObject* definition)
        :
            def(definition)
        {}

        Object(const Object& o)
        :
            def(o.def),
            instVar(o.instVar)
        {}

        // make sure all derived classes override those:
        virtual Object* clone() const
        {
            return new Object(*this);
        }

        virtual int getBuildInType() const
        {
            return BType::OBJ;
        }

    public:
        virtual ~Object()
        {}

        virtual void mark() const;

        /// Load member
        const Variant* get(const IDENT_T& key);
        /// Load member - Read Only (no copy)
        const Variant* getReadOnly(const IDENT_T& key);
        /// Store member
        void set(const IDENT_T& key, const Variant& val);

    protected:
        /// Type definition
        TypeObject* def;
        /// Instance variables
        class InstVar : public SymbolTable
        {
            friend class Object;
        } instVar;
    };


    class TypeObject : public Object
    {
        friend class ObjectFactory;
    protected:
        TypeObject(TypeObject* _def, const STRING_T& name, TypeObject* _parent)
        :
            Object(_def),
            parent(_parent),
            constructor(NULL)
        {
            //TODO
            //instVar["name"] = name;
        }

        TypeObject(const TypeObject& o)
        :
            Object(o),
            parent(o.parent)
        {}

        TypeObject* clone() const
        {
            return new TypeObject(*this);
        }

        int getBuildInType() const
        {
            return BType::TYPE;
        }

    public:
        void mark() const
        {
            if(!marker)
            {
                Object::mark();
                shareVar.mark();
            }
        }

        /// Load shared
        const Variant* getShared(const IDENT_T& key);

        typedef Object* (*Constructor)(VM* target);
    protected:
        TypeObject* parent;

        Constructor constructor;

        /// Read-only variables shared between instances of defined type
        class ShareVar : public SymbolTable
        {
            friend class TypeObject;
        } shareVar;
    };

    inline void Object::mark() const
    {
        if(!marker)
        {
            marker = true;
            def->mark();
            //TODO
            instVar.mark();
        }
    }


    /// Load member
    inline const Variant* Object::get(const IDENT_T& key)
    {
        if(!instVar.empty())
        {
            Variant* p = instVar.find(key);

            //Found
            if(p)
                return p;
        }

        //Not found -> copy
        const Variant* tmp = def->getShared(key);

        if(tmp)
            return instVar.insert(key, *tmp);
        else
            return NULL;
    }

    /// Load member - Read Only (no copy, unsafe)
    inline const Variant* Object::getReadOnly(const IDENT_T& key)
    {
        if(!instVar.empty())
        {
            Variant* p = instVar.find(key);

            //Found
            if(p)
                return p;
        }

        //Not found
        return def->getShared(key);
    }

    /// Store member
    inline void Object::set(const IDENT_T& key, const Variant& val)
    {
        instVar.insert(key, val);
    }

    /// Load shared
    inline const Variant* TypeObject::getShared(const IDENT_T& key)
    {
        if(!shareVar.empty())
        {
            Variant* p = shareVar.find(key);

            //Found
            if(p)
                return p;
        }

        //Not found
        if(parent)
            return parent->getShared(key);
        else
            return NULL;
    }

    inline void Variant::mark() const
    {
        if(tag == BType::REF)
            value.ref->mark();
    }
}

#endif // OBJECT_H_INCLUDED
