#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include "../vm/function_prototype.h"

namespace AYA
{
    class FunctionBuilder;

    class Node
    {
    public:
        virtual ~Node() {}

        virtual void gen(FunctionBuilder& target) =0; //Code gen
    };
}

#endif // NODE_H_INCLUDED
