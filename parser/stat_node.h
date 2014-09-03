#ifndef STAT_NODE_H_INCLUDED
#define STAT_NODE_H_INCLUDED

#include "../vm/function_prototype.h"
#include "node.h"

// Statement Node

namespace AYA
{
    class StatNode : public Node
    {
	Node* expr;
    public:
        StatNode(Node* _expr)
	{
	    expr = _expr;
	}

	~StatNode()
	{
            delete expr;
	}

        void gen(FunctionBuilder& target)
        {
	    expr->gen(target);
            target.addInst(Inst::POP);
        }
    };
}

#endif // STAT_NODE_H_INCLUDED
