#ifndef LOGICALOP_NODE_H_INCLUDED
#define LOGICALOP_NODE_H_INCLUDED

#include "../vm/function_prototype.h"
#include "node.h"

namespace AYA
{
    template<bool AND>
    class LogicalOpNode : public Node
    {
        Node* left;
        Node* right;
    public:
        LogicalOpNode(Node* _left, Node* _right)
        {
            left = _left;
            right = _right;

            assert(left && right);
        }

        ~LogicalOpNode()
        {
            delete left;
            delete right;
        }

        void gen(FunctionBuilder& target)
        {
            left->gen(target);

            size_t idx =  target.addInst(Inst::NOP);

            right->gen(target);

            // relative jump
            if(AND)
                target.at(idx) = Inst(Inst::AND, target.current() - idx - 1);
            else
                target.at(idx) = Inst(Inst::OR, target.current() - idx - 1);
        }
    };

    typedef LogicalOpNode<true> AndNode;
    typedef LogicalOpNode<false> OrNode;
}

#endif // LOGICALOP_NODE_H_INCLUDED
