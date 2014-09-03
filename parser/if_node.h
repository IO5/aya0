#ifndef IF_NODE_H_INCLUDED
#define IF_NODE_H_INCLUDED

#include "../vm/function_prototype.h"
#include "node.h"

namespace AYA
{
    class IfNode : public Node
    {
        Node* cond;
        BlockNode* block;
        Node* elseBlock;
    public:
        IfNode(Node* _cond, BlockNode* _block, Node* _elseBlock)
        :
            cond(_cond),
            block(_block),
            elseBlock(_elseBlock)
        {
            assert(cond && block);
        }

        ~IfNode()
        {
            delete cond;
            delete block;
            delete elseBlock;
        }

        void gen(FunctionBuilder& target)
        {
            target.addInst(Inst::SENTER);

            cond->gen(target);

            size_t elseJmpIdx = target.addInst(Inst::NOP);

            block->gen(target);

            //add jump past "else" if else is non-empty
            if(elseBlock)
            {
                size_t endJmpIdx = target.addInst(Inst::NOP);

                target.at(elseJmpIdx) = Inst(Inst::JMPF, target.current() - elseJmpIdx - 1);

                elseBlock->gen(target);

                target.at(endJmpIdx) = Inst(Inst::JMP, target.current() - endJmpIdx - 1);
            }
            else
                target.at(elseJmpIdx) = Inst(Inst::JMPF, target.current() - elseJmpIdx - 1);

            target.addInst(Inst::SLEAVE);
        }
    };
}

#endif // IF_NODE_H_INCLUDED
