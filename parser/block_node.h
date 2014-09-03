#ifndef BLOCK_NODE_H_INCLUDED
#define BLOCK_NODE_H_INCLUDED

#include "../vm/function_prototype.h"
#include "node.h"

#include <vector>

namespace AYA
{
    class BlockNode : public Node
    {
        NodeList<>* statements;
        bool _createScope;
    public:
        BlockNode(NodeList<>* list)
        :
            statements(list),
            _createScope(false)
        {
            assert(list);
        }

        ~BlockNode()
        {
            for(auto stat : *statements)
                delete stat;

            delete statements;
        }

        void createScope()
        {
            _createScope = true;
        }

        void gen(FunctionBuilder& target)
        {
            if(_createScope)
            target.addInst(Inst::SENTER);

            for(auto stat : *statements)
                stat->gen(target);

            if(_createScope)
                target.addInst(Inst::SLEAVE);
        }
    };
}

#endif // BLOCK_NODE_H_INCLUDED
