#ifndef ASSIGN_NODE_H_INCLUDED
#define ASSIGN_NODE_H_INCLUDED

#include "../vm/function_prototype.h"
#include "var_node.h"

namespace AYA
{
    class AssignNode : public Node
    {
        STRING_T ident;
	Node* expr;
    public:
        AssignNode(Node* left, Node* right)
	{
	    VarNode* vn = dynamic_cast<VarNode*>(left);

            assert(vn);

	    ident = std::move(vn->ident);

	    expr = right;
	}

	~AssignNode()
	{
            delete expr;
	}

        void gen(FunctionBuilder& target)
        {
	    expr->gen(target);
            target.addInst(Inst::STORE, target.addConst(ident));
        }
    };
}

#endif // ASSIGN_NODE_H_INCLUDED
