#ifndef ASSIGN_NODE_H_INCLUDED
#define ASSIGN_NODE_H_INCLUDED

#include "../vm/function_prototype.h"
#include "var_node.h"
#include "member_access.h"

namespace AYA
{
    class AssignNode : public Node
    {
        Node* expr;
        Node* var;
        enum { VAR_NODE, MEMBER_NODE } variant;
    public:
        AssignNode(Node* left, Node* right)
        {
            assert(left && right);
            assert(dynamic_cast<VarNode*>(left) || dynamic_cast<MemberAccessNode*>(left));

            if (dynamic_cast<VarNode*>(left))
                variant = VAR_NODE;
            else
                variant = MEMBER_NODE;

            var = left;
            expr = right;
        }

        ~AssignNode()
        {
            delete expr;
        }

        void gen(FunctionBuilder& target)
        {
            if (variant == VAR_NODE)
            {
                expr->gen(target);
                STRING_T &ident = (static_cast<VarNode*>(var))->ident;
                target.addInst(Inst::STORE, target.addConst(ident));
            }
            else
            {
                MemberAccessNode* memb = static_cast<MemberAccessNode*>(var);
                memb->expr->gen(target);
                expr->gen(target);
                target.addInst(Inst::STOREM, target.addConst(memb->ident));
            }
        }
    };
}

#endif // ASSIGN_NODE_H_INCLUDED
