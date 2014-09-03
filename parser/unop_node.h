#ifndef UNOP_NODE_H_INCLUDED
#define UNOP_NODE_H_INCLUDED

#include "../vm/function_prototype.h"
#include "node.h"

namespace AYA
{
    template<char op>
    class UnOpNode : public Node
    {
        Node* operand;
    public:
        UnOpNode(Node* _operand)
        {
            operand = _operand;

            assert(operand);
        }

        ~UnOpNode()
        {
            delete operand;
        }

        void gen(FunctionBuilder& target)
        {
            operand->gen(target);
            target.addInst(Inst::UNOP, op);
        }
    };
}

#endif // UNOP_NODE_H_INCLUDED
