#ifndef RETURN_NODE_H_INCLUDED
#define RETURN_NODE_H_INCLUDED

#include "../vm/function_prototype.h"
#include "node.h"

namespace AYA
{
    class ReturnNode : public Node
    {
        Node* expr;
    public:
        ReturnNode(Node* _expr)
        :
            expr(_expr)
        {
            assert(expr);
        }

        ~ReturnNode()
        {
            delete expr;
        }

        void gen(FunctionBuilder& target)
        {
            expr->gen(target);

            target.addInst(Inst::RET);
        }
    };
}

#endif // LOOP_NODE_H_INCLUDED
