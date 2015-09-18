#ifndef BIND_H_INCLUDED
#define BIND_H_INCLUDED

#include "types.h"

namespace AYA
{
    struct Variant;
    class VM;

    enum ERR
    {
        ARG_COUNT_MISMATCH = -1,
        ARG_TYPE_MISMATCH = -2
    };

    typedef int (*Bind)(VM* state);
}

extern "C"
{
    int AYA_assertArgCount(AYA::VM* state, size_t argCount);

    int AYA_assertMinArgCount(AYA::VM* state, size_t argCount);

    int AYA_getArgCount(AYA::VM* state);

    int8_t AYA_getArgType(AYA::VM* state, size_t index);

    int AYA_isNilArg(AYA::VM* state, size_t index);

    int AYA_getIntArg(AYA::VM* state, size_t index, AYA::INT_T* result);

    int AYA_getRealArg(AYA::VM* state, size_t index, AYA::REAL_T* result);

    int AYA_getStrArg(AYA::VM* state, size_t index, const char** result);

    void AYA_setErrorMsg(AYA::VM* state, const char* msg);

    void AYA_setNilResult(AYA::VM* state);

    void AYA_setIntResult(AYA::VM* state, AYA::INT_T result);

    void AYA_setRealResult(AYA::VM* state, AYA::REAL_T result);

    void AYA_setStrResult(AYA::VM* state, const char* result);
}


#endif // BIND_H_INCLUDED
