#ifndef FUNC_NODE_H_INCLUDED
#define FUNC_NODE_H_INCLUDED

#include "../vm/function_prototype.h"
#include "ident_node.h"

namespace AYA
{
    /// Function definition / closure creation
    class FuncNode : public Node
    {
        NodeList<IdentNode>* args;
        BlockNode* block;
    public:
        FuncNode(NodeList<IdentNode>* _args, BlockNode* _block)
        :
            args(_args),
            block(_block)
        {
            assert(block);
        }

        ~FuncNode()
        {
            if(args)
            {
                for(auto arg : *args)
                    delete arg;
                delete args;
            }

            delete block;
        }

        void gen(FunctionBuilder& target)
        {
            //subtarget
            FunctionBuilder sub = target.getChild();

            if(args)
            {
                for(IdentNode* arg : *args)
                    sub.addArg(arg->ident);
            }

            // generate for subtarget
            block->gen(sub);

            // function must end with return
            sub.addInst(Inst::LNIL); // TODO this can be done better
            sub.addInst(Inst::RET);

            Variant result(sub.getResult());

            target.addInst(Inst::CLOSURE, target.addConst(result));
        }
    };
}

#endif // FUNC_NODE_H_INCLUDED
