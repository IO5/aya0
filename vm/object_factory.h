#ifndef OBJECT_FACTORY_H_INCLUDED
#define OBJECT_FACTORY_H_INCLUDED

#include "object.h"
#include "closure.h"
#include "string_object.h"
#include "list_object.h"
#include "dict_object.h"

namespace AYA
{
    class VM;
    class GarbageCollector;

    class ObjectFactory
    {
    public:
        ObjectFactory(VM& _target);
        ~ObjectFactory();

        Object*         makeObject  (TypeObject* def = NULL);
        TypeObject*     makeType    (const STRING_T& name, TypeObject* parent = NULL, TypeObject* def = NULL);
        Closure*        makeClosure (const FunctionPrototype* proto, const pEnvironment& env, TypeObject* def = NULL);
        StringObject*   makeString  (const STRING_T& init = "", TypeObject* def = NULL);
        ListObject*     makeList    (std::vector<Variant>&& init, TypeObject* def = NULL);
        DictObject*     makeDict    (Dict&& init, TypeObject* def = NULL);

        Object*         copy(const Object* original);
        int             getType(const Object*);
        static int      getBuildInType(const Object*);

    protected:
        friend class VM;

        void createDefaultDef();

        GarbageCollector& target;

        TypeObject* OBJECT_DEF          = NULL;
        TypeObject* TYPE_OBJECT_DEF     = NULL;
        TypeObject* FUNCTION_OBJECT_DEF = NULL;
        TypeObject* STRING_OBJECT_DEF   = NULL;
        TypeObject* LIST_OBJECT_DEF     = NULL;
        TypeObject* DICT_OBJECT_DEF     = NULL;

        static int objectConstr(VM* state);
        static size_t dictHash(const Variant& v);
        static bool dictComp(const Variant& a, const Variant& b);
    };
}

#endif // OBJECT_FACTORY_H_INCLUDED
