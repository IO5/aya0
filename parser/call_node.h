#ifndef CALL_NODE_H_INCLUDED
#define CALL_NODE_H_INCLUDED

#include "../vm/function_prototype.h"
#include "node.h"

namespace AYA
{
    /// Function call
    class CallNode : public Node
    {
        Node* expr;
        NodeList<>* args;
    public:
        CallNode(Node* _expr, NodeList<>* _args)
        :
            expr(_expr),
            args(_args)
        {
            assert(expr);
        }

        ~CallNode()
        {
            delete expr;

            if(args)
            {
                for(auto arg : *args)
                    delete arg;

                delete args;
            }
        }

        void gen(FunctionBuilder& target)
        {
            if(args)
            {
                for(auto arg : *args)
                    arg->gen(target);
            }

            expr->gen(target);

            // args size or 0 if args is NULL
            target.addInst(Inst::CALL, args ? args->size() : 0);
        }
    };
}

#endif // CALL_NODE_H_INCLUDED
