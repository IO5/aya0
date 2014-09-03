#ifndef VAR_NODE_H_INCLUDED
#define VAR_NODE_H_INCLUDED

#include "../vm/function_prototype.h"
#include "node.h"

namespace AYA
{
    class VarNode : public Node
    {
        friend class AssignNode;

        STRING_T ident;
    public:
        VarNode(const STRING_T& _ident)
        :
            ident(_ident)
        {}

        void gen(FunctionBuilder& target)
        {
            target.addInst(Inst::LOAD, target.addConst(ident));
        }
    };
}

#endif // VAR_NODE_H_INCLUDED
