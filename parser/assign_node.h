#ifndef ASSIGN_NODE_H_INCLUDED
#define ASSIGN_NODE_H_INCLUDED

#include "var_node.h"
#include "member_access_node.h"
#include "index_access_node.h"

namespace AYA
{
    class AssignNode : public Node
    {
        Node* expr;
        Node* var;
        enum { VAR_NODE, MEMBER_NODE, INDEX_NODE } variant;
    public:
        AssignNode(Node* left, Node* right)
        {
            assert(left && right);
            assert(dynamic_cast<VarNode*>(left) || dynamic_cast<MemberAccessNode*>(left)
                    || dynamic_cast<IndexAccessNode*>(left));

            if (dynamic_cast<VarNode*>(left))
                variant = VAR_NODE;
            else if (dynamic_cast<MemberAccessNode*>(left))
                variant = MEMBER_NODE;
            else
                variant = INDEX_NODE;

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
            else if (variant == MEMBER_NODE)
            {
                MemberAccessNode* memb = static_cast<MemberAccessNode*>(var);
                memb->expr->gen(target);
                expr->gen(target);
                target.addInst(Inst::STOREM, target.addConst(memb->ident));
            }
            else
            {
                IndexAccessNode* indx = static_cast<IndexAccessNode*>(var);
                indx->collection->gen(target);
                indx->index->gen(target);
                expr->gen(target);
                target.addInst(Inst::STOREC);
            }
        }
    };
}

#endif // ASSIGN_NODE_H_INCLUDED
