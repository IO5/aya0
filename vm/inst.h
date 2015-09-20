#ifndef INST_H_INCLUDED
#define INST_H_INCLUDED

#include <cstdint>

#define OPCODES(DO) \
    DO(NOP) \
    DO(POP) \
    DO(LOAD) \
    DO(STORE) \
    /*MEMBER ACCESS*/ \
    DO(LOADM) \
    DO(STOREM) \
    /*COLLECTION ACCESS*/ \
    DO(LOADC) \
    DO(STOREC) \
    /*SCOPES*/\
    DO(SENTER) \
    DO(SLEAVE) \
    DO(DECL) \
    /*OPERATORS*/\
    DO(BINOP) \
    DO(UNOP) \
    /*FLOW CONTROL*/\
    DO(JMP) \
    DO(JMPT) \
    DO(JMPF) \
    DO(OR) \
    DO(AND) \
    DO(CALL) \
    DO(RET) \
    /*LOAD NIL*/\
    DO(LNIL) \
    /*LOAD BOOLEAN*/\
    DO(LBOOL) \
    /*LOAD CONSTANT*/\
    DO(LCONST) \
    /*CONSTRUCT*/\
    DO(CLOSURE) \
    DO(LISTC) \
    DO(DICTC) \
    /*FOR*/\
    DO(ITER)

#define STRINGIFY(x) #x,

#define ENUM(x) x,

class Inst
{
    uint8_t code;
    int16_t opr;
public:
    enum
    {
        OPCODES(ENUM)
    };

    static const char** name;

    Inst(uint8_t op)
    {
        code = op;
    }

    Inst(uint8_t op, int16_t _opr)
    {
        code = op;
        opr = _opr;
    }

    inline uint8_t opcode() const
    {
        return code;
    }

    inline int16_t operand() const
    {
        return opr;
    }
};

#endif // INST_H_INCLUDED
