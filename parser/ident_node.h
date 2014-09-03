#ifndef IDENT_NODE_H_INCLUDED
#define IDENT_NODE_H_INCLUDED

#include "node.h"

namespace AYA
{
    struct IdentNode : public Node
    {
        const STRING_T ident;
        IdentNode(const STRING_T& val)
        :
            ident(val)
        {}

        void gen(FunctionBuilder& target)
        {
            // ugly
            assert(false);
        }
    };
}

#endif // IDENT_NODE_H_INCLUDED
