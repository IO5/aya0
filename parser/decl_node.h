#ifndef DECL_NODE_H_INCLUDED
#define DECL_NODE_H_INCLUDED

#include "../vm/function_prototype.h"
#include "assign_node.h"

namespace AYA
{
    class DeclNode : public Node
    {
        STRING_T ident;
        AssignNode* assignment;
    public:
        DeclNode(Node* _ident, Node* _expr)
        {
            assert(dynamic_cast<IdentNode*>(_ident));
            ident = (static_cast<IdentNode*>(_ident))->ident;

            if (_expr)
            {
                assignment = new AssignNode(new VarNode(_ident), _expr);
            }
            else
            {
                assignment = NULL;
                // in the opposite case AssignNode already did the cleanup
                delete _ident;
            }
        }

        ~DeclNode()
        {
            delete assignment;
        }

        void gen(FunctionBuilder& target)
        {
            target.addInst(Inst::DECL, target.addConst(ident));

            if(assignment)
                assignment->gen(target);
        }
    };
}

#endif // DECL_NODE_H_INCLUDED
