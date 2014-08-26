#ifndef OBJECT_FACTORY_H_INCLUDED
#define OBJECT_FACTORY_H_INCLUDED

#include "object.h"
#include "closure.h"
#include "string_object.h"

namespace AYA
{
    class VM;
    class GarbageCollector;

    class ObjectFactory
    {
    public:
        ObjectFactory(VM* _target);

        void createDefaultDef();

        Object*         makeObject  (TypeObject* def = NULL);
        TypeObject*     makeType    (const STRING_T& name, TypeObject* parent = NULL, TypeObject* def = NULL);
        Closure*        makeClosure (const FunctionPrototype* proto, const pEnvironment& env, TypeObject* def = NULL);
        StringObject*   makeString  (const STRING_T& init = "", TypeObject* def = NULL);

        Object*         copy(const Object* original);
        int             getType(const Object*);
        int             getBuildInType(const Object*);

    protected:
        GarbageCollector* target;

        TypeObject* OBJECT_DEF;
        TypeObject* TYPE_OBJECT_DEF;
        TypeObject* FUNCTION_OBJECT_DEF;
        TypeObject* STRING_OBJECT_DEF;
    };
}

#endif // OBJECT_FACTORY_H_INCLUDED
