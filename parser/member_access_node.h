#ifndef MEMBER_ACCESS_NODE_H_INCLUDED
#define MEMBER_ACCESS_NODE_H_INCLUDED

#include "node.h"

namespace AYA
{
    class MemberAccessNode : public Node
    {
        Node* expr;
        STRING_T ident;
        friend class AssignNode;
    public:
        MemberAccessNode(Node* _expr, Node* _ident)
        :
            expr(_expr)
        {
            assert(_expr);
            assert(dynamic_cast<IdentNode*>(_ident));
            ident = std::move((static_cast<IdentNode*>(_ident))->ident);

            delete _ident;
        }

        ~MemberAccessNode()
        {
            delete expr;
        }

        void gen(FunctionBuilder& target)
        {
            expr->gen(target);
            target.addInst(Inst::LOADM, target.addConst(ident));
        }
    };
}

#endif // MEMBER_ACCESS_NODE_H_INCLUDED
