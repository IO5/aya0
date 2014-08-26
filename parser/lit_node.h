#ifndef LIT_NODE_H_INCLUDED
#define LIT_NODE_H_INCLUDED

#include "node.h"

namespace AYA
{
    struct NilLitNode : public Node
    {
        void gen(FunctionBuilder& target)
        {
            target.addInst(Inst::LNIL);
        }
    };

    struct BoolLitNode : public Node
    {
        const INT_T value;
        BoolLitNode(INT_T val)
        :
            value(val)
        {}

        void gen(FunctionBuilder& target)
        {
            target.addInst(Inst::LBOOL, value);
        }
    };

    struct IntLitNode : public Node
    {
        const INT_T value;
        IntLitNode(INT_T val)
        :
            value(val)
        {}

        void gen(FunctionBuilder& target)
        {
            target.addInst(Inst::LCONST, target.addConst(INT(value)));
            //TODO
            //add LBOOL option whenever possible
        }
    };

    struct RealLitNode : public Node
    {
        const REAL_T value;
        RealLitNode(REAL_T val)
        :
            value(val)
        {}

        void gen(FunctionBuilder& target)
        {
            target.addInst(Inst::LCONST, target.addConst(REAL(value)));
        }
    };

    struct StringLitNode : public Node
    {
        const STRING_T value;
        StringLitNode(const STRING_T& val)
        :
            value(val)
        {}

        void gen(FunctionBuilder& target)
        {
            target.addInst(Inst::LCONST, target.addConst(value));
        }
    };
}

#endif // LIT_NODE_H_INCLUDED
