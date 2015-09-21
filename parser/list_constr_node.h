#ifndef LIST_CONSTR_NODE_H_INCLUDED
#define LIST_CONSTR_NODE_H_INCLUDED

#include "node.h"
#include "../vm/function_prototype.h"

namespace AYA
{
    class ListConstrNode : public Node
    {
        NodeList<>* exprs;
    public:
        ListConstrNode(NodeList<>* exprs_) : exprs(exprs_)
        {}

        ~ListConstrNode()
        {
            if (exprs)
            {
                for (auto expr : *exprs)
                    delete expr;
                delete exprs;
            }
        }

        void gen(FunctionBuilder& target)
        {
            if (exprs)
                for (auto expr : *exprs)
                    expr->gen(target);
            target.addInst(Inst::LISTC, exprs ? exprs->size() : 0);
        }
    };
}

#endif // LIST_CONSTR_NODE_H_INCLUDED
