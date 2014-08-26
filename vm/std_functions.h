#ifndef STD_FUNCTIONS_H_INCLUDED
#define STD_FUNCTIONS_H_INCLUDED

#include "vm.h"

#include <cmath>

namespace AYA
{
    // --------------- Binary Operation ---------------
    template<typename T>
    inline void binOpTemplate(EvalStack& evalStack)
    {
        Variant a = evalStack.pop();
        Variant& b = evalStack.peek();

        if(b.isINT())
        {
            if(a.isINT())
            {
                b.value.integer = T::op(b.value.integer, a.value.integer);
                return;
            }
            else if(a.isREAL())
            {
                b.value.real = T::op((REAL_T)b.value.integer, a.value.real);
                b.tag = BType::REAL;
                return;
            }
        }
        else if(b.isREAL())
        {
            if(a.isINT())
            {
                b.value.real = T::op(b.value.real, (REAL_T)a.value.integer);
                return;
            }
            else if(a.isREAL())
            {
                b.value.real = T::op(b.value.real, a.value.real);
                return;
            }
        }

        throw RuntimeError("Type mismatch");
    }

    #define make_binOP(NAME, CODE) \
        struct NAME \
        { \
            template<typename T> \
            static T op(T a, T b) \
            { \
                CODE; \
            } \
        }; \

    make_binOP(Add, return a+b);
    make_binOP(Sub, return a-b);
    make_binOP(Mul, return a*b);
    make_binOP(Pow, return (T)pow(a,b));

    make_binOP(Eq,      return a==b);
    make_binOP(NEq,     return a!=b);
    make_binOP(Less,    return a<b);
    make_binOP(LessEq,  return a<=b);
    make_binOP(Great,   return a>b);
    make_binOP(GreatEq, return a<=b);

    inline void Div(EvalStack& evalStack)
    {
        Variant a = evalStack.pop();
        Variant& b = evalStack.peek();

        if(a.isINT())
        {
            if(a.value.integer != 0)
            {
                if(b.isINT())
                {
                    b.value.integer /= a.value.integer;
                    return;
                }
                else if(b.isREAL())
                {
                    b.value.real /= (REAL_T)a.value.integer;
                    return;
                }
            }
            else
                throw RuntimeError("Division by 0");
        }
        else if(a.isREAL())
        {
            if(a.value.real != 0)
            {
                if(b.isINT())
                {
                    b.value.real = (REAL_T)b.value.integer / a.value.real;
                    b.tag = BType::REAL;
                    return;
                }
                else if(b.isREAL())
                {
                    b.value.real /= a.value.real;
                    return;
                }
            }
            else
                throw RuntimeError("Division by 0");
        }

        throw RuntimeError("Type mismatch");
    }

    inline void Mod(EvalStack& evalStack)
    {
        Variant a = evalStack.pop();
        Variant& b = evalStack.peek();

        if(a.isINT())
        {
            if(a.value.integer != 0)
            {
                if(b.isINT())
                {
                    b.value.integer %= a.value.integer;
                    return;
                }
                else if(b.isREAL())
                {
                    b.value.real = fmod(b.value.real, (REAL_T)a.value.integer);
                    return;
                }
            }
            else
                throw RuntimeError("Division by 0");
        }
        else if(a.isREAL())
        {
            if(a.value.real != 0)
            {
                if(b.isINT())
                {
                    b.value.real = fmod((REAL_T)b.value.integer, a.value.real);
                    b.tag = BType::REAL;
                    return;
                }
                else if(b.isREAL())
                {
                    b.value.real = fmod(b.value.real, a.value.real);
                    return;
                }
            }
            else
                throw RuntimeError("Division by 0");
        }

        throw RuntimeError("Type mismatch");
    }

    // --------------- Object Methods ---------------
//    int to_s(VM* state)
//    {
//
//    }
}

#endif // STD_FUNCTIONS_H_INCLUDED
