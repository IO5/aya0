#ifndef VARIANT_H_INCLUDED
#define VARIANT_H_INCLUDED

#include "../types.h"

#include "../bind.h"

namespace AYA
{
    struct Object;
    struct FunctionPrototype;

    union Value
    {
        INT_T   integer;
        REAL_T  real;
        Object* ref;
        Bind    cfunc;
        FunctionPrototype* proto;
    };

    struct Variant
    {
        Value value;
        uint8_t tag;

//        enum
//        {
//            /// Tags:
//            NIL = 0,
//
//            /// Numbers
//            NUMBER = 0b10,
//            INT = 0b10,
//            REAL = 0b11,
//
//            /// ManagedMemory objects
//            MANAGED = 0b100,
//            /// *Objects
//            REF = 0b100,
//            /// *FunctionPrototypes
//            PROTO = 0b101,
//
//            /// Function bindings
//            CFUNC = 0b1000
//        };

        Variant()
        {
            tag = BType::NIL;
        }
        Variant(Object* ref)
        {
            tag = BType::REF;
            value.ref = ref;
        }
        Variant(INT_T i)
        {
            tag = BType::INT;
            value.integer = i;
        }
        Variant(REAL_T r)
        {
            tag = BType::REAL;
            value.real = r;
        }
        Variant(Bind b)
        {
            tag = BType::CFUNC;
            value.cfunc = b;
        }
        Variant(FunctionPrototype* p)
        {
            tag = BType::PROTO;
            value.proto = p;
        }

        bool operator==(const Variant& v) const
        {
            if(tag == v.tag)
            {
                switch(tag)
                {
                    case BType::NIL:
                        return true;
                    case BType::INT:
                        return value.integer  == v.value.integer;
                    case BType::REAL:
                        return value.real     == v.value.real;
                    case BType::REF:
                        return value.ref      == v.value.ref;
                    case BType::CFUNC:
                        return value.cfunc    == v.value.cfunc;
                    case BType::PROTO:
                        return value.proto    == v.value.proto;
                }
            }
            return false;
        }

        bool operator!=(const Variant& v) const
        {
            return !operator==(v);
        }

        bool isNIL() const
        {
            return tag == BType::NIL;
        }
        bool isINT() const
        {
            return tag == BType::INT;
        }
        bool isREAL() const
        {
            return tag == BType::REAL;
        }
        bool isREF() const
        {
            return tag == BType::REF;
        }
        bool isCFUNC() const
        {
            return tag == BType::CFUNC;
        }
        bool isPROTO() const
        {
            return tag == BType::PROTO;
        }

        //Defined in object.h
        void mark() const;

        #define NIL()   AYA::Variant()
        #define INT(x)  AYA::Variant((AYA::INT_T)(x))
        #define REAL(x) AYA::Variant((AYA::REAL_T)(x))
        #define REF(x)  AYA::Variant(x)

        #define BIND(x) AYA::Variant((Bind)x)
    };
}
#endif // VARIANT_H_INCLUDED
