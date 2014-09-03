#ifndef BINOP_NODE_H_INCLUDED
#define BINOP_NODE_H_INCLUDED

#include "../vm/function_prototype.h"
#include "node.h"

namespace AYA
{
    template<char op>
    class BinOpNode : public Node
    {
        Node* left;
        Node* right;
    public:
        BinOpNode(Node* _left, Node* _right)
        :
            left(_left),
            right(_right)
        {
            assert(left && right);
        }

        ~BinOpNode()
        {
            delete left;
            delete right;
        }

        void gen(FunctionBuilder& target)
        {
            left->gen(target);
            right->gen(target);
            target.addInst(Inst::BINOP, op);
        }
    };
}

#endif // BINOP_NODE_H_INCLUDED
