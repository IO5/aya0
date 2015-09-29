#ifndef DICT_CONSTR_NODE_H_INCLUDED
#define DICT_CONSTR_NODE_H_INCLUDED


#include "node.h"
#include "../vm/function_prototype.h"

namespace AYA
{
    typedef std::vector<std::pair<Node*, Node*> > NodeDictList;

    class DictConstrNode : public Node
    {
        NodeDictList* exprs;
    public:
        DictConstrNode(NodeDictList* exprs_) : exprs(exprs_)
        {}

        ~DictConstrNode()
        {
            if (exprs)
            {
                for (auto& expr : *exprs)
                {
                    delete expr.first;
                    delete expr.second;
                }
                delete exprs;
            }
        }

        void gen(FunctionBuilder& target)
        {
            if (exprs)
            {
                for (auto& expr : *exprs)
                {
                    expr.first->gen(target);
                    expr.second->gen(target);
                }
            }
            target.addInst(Inst::DICTC, exprs ? exprs->size() : 0);
        }
    };
}
#endif // DICT_CONSTR_NODE_H_INCLUDED
