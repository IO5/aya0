#include "object_factory.h"

#include "vm.h"

namespace AYA
{
    ObjectFactory::ObjectFactory(VM* _target)
    {
        assert(_target);

        target = &(_target->gc);
    }

    // TODO
    // bind to gc (everywhere)
    void ObjectFactory::createDefaultDef()
    {
        TYPE_OBJECT_DEF = new TypeObject(NULL, "Type", NULL);
        // point to itself
        TYPE_OBJECT_DEF->def = TYPE_OBJECT_DEF;

        OBJECT_DEF = new TypeObject(TYPE_OBJECT_DEF, "Object", NULL);

        // point to parent (Object doesn't have one, it's on top of the hierarchy)
        TYPE_OBJECT_DEF->parent = OBJECT_DEF;

        FUNCTION_OBJECT_DEF     = new TypeObject(TYPE_OBJECT_DEF, "Function", OBJECT_DEF);
        STRING_OBJECT_DEF       = new TypeObject(TYPE_OBJECT_DEF, "String", OBJECT_DEF);
    }

    Object* ObjectFactory::makeObject(TypeObject* def)
    {
        if(def == NULL)
            def = OBJECT_DEF;

        // TODO
        // bind to gc
        return new Object(def);
    }

    TypeObject* ObjectFactory::makeType(const STRING_T& name, TypeObject* parent, TypeObject* def)
    {
        if(def == NULL)
            def = TYPE_OBJECT_DEF;

        return new TypeObject(def, name, parent);
    }

    Closure* ObjectFactory::makeClosure(const FunctionPrototype* proto, const pEnvironment& env, TypeObject* def)
    {
        if(def == NULL)
            def = FUNCTION_OBJECT_DEF;

        return new Closure(def, proto, env);
    }

    StringObject* ObjectFactory::makeString(const STRING_T& init, TypeObject* def)
    {
        if(def == NULL)
            def = STRING_OBJECT_DEF;

        return new StringObject(def, init);
    }

    Object* ObjectFactory::copy(const Object* original)
    {
        // TODO
        // bind to gc
        return original->clone();
    }

    int ObjectFactory::getType(const Object* o)
    {
        assert(o);

        auto def = o->def;

        if(def == OBJECT_DEF)
        {
            return BType::OBJ;
        }
        else if(def == TYPE_OBJECT_DEF)
        {
            return BType::TYPE;
        }
        else if(def == FUNCTION_OBJECT_DEF)
        {
            return BType::FUNC;
        }
        else if(def == STRING_OBJECT_DEF)
        {
            return BType::STR;
        }
        else
        {
            return BType::USR;
        }
    }

    int ObjectFactory::getBuildInType(const Object* o)
    {
        assert(o);

        return o->getBuildInType();
    }
}
