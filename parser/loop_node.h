#ifndef LOOP_NODE_H_INCLUDED
#define LOOP_NODE_H_INCLUDED

#include "../vm/function_prototype.h"
#include "node.h"

namespace AYA
{
    class LoopNode : public Node
    {
    protected:
        Node* cond;
        BlockNode* block;
    public:
        LoopNode(Node* _cond, BlockNode* _block)
        {
            cond = _cond;
            block = _block;
        }

        ~LoopNode()
        {
            delete cond;
            delete block;
        }
    };

    class RepeatNode : public LoopNode
    {
        using LoopNode::LoopNode;

        void gen(FunctionBuilder& target)
        {
            target.addInst(Inst::SENTER);
            size_t startIdx = target.current();

            block->gen(target);

            cond->gen(target);

            target.addInst(Inst::JMPF, (startIdx - 1) - target.current());

            target.addInst(Inst::SLEAVE);
        }
    };

    class WhileNode : public LoopNode
    {
        using LoopNode::LoopNode;

        void gen(FunctionBuilder& target)
        {
            target.addInst(Inst::SENTER);

            size_t condIdx = target.current();

            cond->gen(target);

            size_t jmpIdx = target.addInst(Inst::NOP);

            block->gen(target);

            target.addInst(Inst::JMP, (condIdx - 1) - target.current());
            target.at(jmpIdx) = Inst(Inst::JMPF, target.current() - jmpIdx - 1);

            target.addInst(Inst::SLEAVE);
        }
    };
}

#endif // LOOP_NODE_H_INCLUDED
