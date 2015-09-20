#include "object_factory.h"
#include "vm.h"
#include "built_in.h"

namespace AYA
{
    ObjectFactory::ObjectFactory(VM& _target)
    :
	target(_target.gc)
    {
        createDefaultDef();
    }

    ObjectFactory::~ObjectFactory()
    {
        delete OBJECT_DEF;
        delete TYPE_OBJECT_DEF;
        delete FUNCTION_OBJECT_DEF;
        delete STRING_OBJECT_DEF;
        delete LIST_OBJECT_DEF;
    }

    int illegalConstr(VM* state)
    {
        AYA_setErrorMsg(state, "Cannot construct an object of this type this way");
        return -1;
    }

    int ObjectFactory::objectConstr(VM* state)
    {
        AYA::Variant& arg = state->callFrame().frameBottom()[0];
        if (!arg.isREF() || getBuildInType(arg.value.ref) != BType::TYPE)
        {
            AYA_setErrorMsg(state, "Invalid constructor argument");
            return -1;
        }
        TypeObject* def = static_cast<TypeObject*>(arg.value.ref);

        *(state->callFrame().frameBottom()) = REF(state->objectFactory.makeObject(def));
        return 0;
    }

    void ObjectFactory::createDefaultDef()
    {
        TYPE_OBJECT_DEF = new TypeObject(NULL, NULL);
        // point to itself
        TYPE_OBJECT_DEF->def = TYPE_OBJECT_DEF;

        OBJECT_DEF = new TypeObject(TYPE_OBJECT_DEF, NULL);

        // point to parent (Object doesn't have one, it's on top of the hierarchy)
        TYPE_OBJECT_DEF->parent = OBJECT_DEF;

        FUNCTION_OBJECT_DEF     = new TypeObject(TYPE_OBJECT_DEF, OBJECT_DEF);
        STRING_OBJECT_DEF       = new TypeObject(TYPE_OBJECT_DEF, OBJECT_DEF);
        LIST_OBJECT_DEF         = new TypeObject(TYPE_OBJECT_DEF, OBJECT_DEF);
        DICT_OBJECT_DEF         = new TypeObject(TYPE_OBJECT_DEF, OBJECT_DEF);

        #define _SET_SHARED_VARS(DEF, name) \
        (DEF)->setShared("type", REF(DEF), NULL); \
        (DEF)->setShared("typename", REF(new StringObject(STRING_OBJECT_DEF, (name))), NULL); \
        (DEF)->setShared("__new__", BIND(illegalConstr), NULL);

        _SET_SHARED_VARS(OBJECT_DEF, "Object");
        _SET_SHARED_VARS(TYPE_OBJECT_DEF, "Type");
        _SET_SHARED_VARS(FUNCTION_OBJECT_DEF, "Function");
        _SET_SHARED_VARS(STRING_OBJECT_DEF, "String");
        _SET_SHARED_VARS(LIST_OBJECT_DEF, "List");
        _SET_SHARED_VARS(LIST_OBJECT_DEF, "Dict");

        OBJECT_DEF->setShared("__new__", BIND(objectConstr), NULL);

        STRING_OBJECT_DEF->setShared("+", BIND(BuiltIn::strConcat), NULL);
        STRING_OBJECT_DEF->setShared("==", BIND(BuiltIn::strComp), NULL);
        STRING_OBJECT_DEF->setShared("||", BIND(BuiltIn::strLen), NULL);

        LIST_OBJECT_DEF->setShared("+", BIND(BuiltIn::listConcat), NULL);
        LIST_OBJECT_DEF->setShared("==", BIND(BuiltIn::listComp), NULL);
        LIST_OBJECT_DEF->setShared("||", BIND(BuiltIn::listLen), NULL);
    }

    Object* ObjectFactory::makeObject(TypeObject* def)
    {
        if(def == NULL)
            def = OBJECT_DEF;

        Object* p = new Object(def);
        target.registerObj(p, sizeof(*p));
        return p;
    }

    TypeObject* ObjectFactory::makeType(const STRING_T& name, TypeObject* parent, TypeObject* def)
    {
        if (def == NULL)
            def = TYPE_OBJECT_DEF;

        if (parent == NULL)
            parent = OBJECT_DEF;

        TypeObject* p = new TypeObject(def, parent);
        p->setShared("type", REF(p), &target);
        p->setShared("typename", REF(makeString(name)), &target);

        target.registerObj(p, sizeof(*p) + p->shareVar.size());

        return p;
    }

    Closure* ObjectFactory::makeClosure(const FunctionPrototype* proto, const pEnvironment& env, TypeObject* def)
    {
        if(def == NULL)
            def = FUNCTION_OBJECT_DEF;

        return new(target) Closure(def, proto, env);
    }

    StringObject* ObjectFactory::makeString(const STRING_T& init, TypeObject* def)
    {
        if(def == NULL)
            def = STRING_OBJECT_DEF;

        StringObject* p = new StringObject(def, init);
        target.registerObj(p, sizeof(*p) + init.size());
        return p;
    }

    ListObject* ObjectFactory::makeList(std::vector<Variant>&& init, TypeObject* def)
    {
        if(def == NULL)
            def = LIST_OBJECT_DEF;

        ListObject* p = new ListObject(def, std::move(init));
        target.registerObj(p, sizeof(*p) + init.capacity());

        return p;
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
        else if(def == LIST_OBJECT_DEF)
        {
            return BType::LIST;
        }
        else if(def == DICT_OBJECT_DEF)
        {
            return BType::DICT;
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
