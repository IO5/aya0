#ifndef FOR_NODE_H_INCLUDED
#define FOR_NODE_H_INCLUDED

#include "../vm/function_prototype.h"
#include "node.h"

namespace AYA
{
    class ForNode : public Node
    {
    protected:
        STRING_T ident;
        Node* list;
        BlockNode* block;
    public:
        ForNode(Node* _ident, Node* _list, BlockNode* _block)
        {
            assert(dynamic_cast<IdentNode*>(_ident));
            ident = (static_cast<IdentNode*>(_ident))->ident;
            delete _ident;
            list = _list;
            block = _block;
        }

        ~ForNode()
        {
            delete list;
            delete block;
        }

        void gen(FunctionBuilder& target)
        {
            target.addInst(Inst::SENTER);
            target.addInst(Inst::DECL, target.addConst(ident));

            list->gen(target);

            target.addInst(Inst::LBOOL, 0);

            size_t loopStartIdx = target.current();
            size_t iterIdx = target.addInst(Inst::NOP);

            target.addInst(Inst::STORE, target.addConst(ident));

            block->gen(target);
            target.addInst(Inst::JMP, (loopStartIdx - 1) - target.current());
            target.at(iterIdx) = Inst(Inst::ITER, target.current() - iterIdx - 1);

            target.addInst(Inst::SLEAVE);
        }
    };
}

#endif // FOR_NODE_H_INCLUDED
