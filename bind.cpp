#include "bind.h"
#include "vm/vm.h"

#include "vm/string_object.h"

extern "C"
{
    int AYA_assertArgCount(AYA::VM* state, size_t argCount)
    {
        return argCount == state->callFrame().argCount();
    }

    int AYA_assertMinArgCount(AYA::VM* state, size_t argCount)
    {
        return argCount >= state->callFrame().argCount();
    }

    int AYA_getArgCount(AYA::VM* state)
    {
        return state->callFrame().argCount();
    }

    int8_t AYA_getArgType(AYA::VM* state, size_t index)
    {
        AYA::Variant* args = state->callFrame().frameBottom();
        return args[index].tag;
    }

    int AYA_isNilArg(AYA::VM* state, size_t index)
    {
        AYA::Variant* args = state->callFrame().frameBottom();

        return args[index].isNIL();
    }

    int AYA_getIntArg(AYA::VM* state, size_t index, AYA::INT_T* result)
    {
        AYA::Variant& arg = state->callFrame().frameBottom()[index];

        if(arg.isINT())
        {
            if(result)
                *result = arg.value.integer;
            return true;
        }
        else
            return false;
    }

    int AYA_getRealArg(AYA::VM* state, size_t index, AYA::REAL_T* result)
    {
        AYA::Variant& arg = state->callFrame().frameBottom()[index];

        if(arg.isREAL())
        {
            if(result)
                *result = arg.value.real;
            return true;
        }
        else
            return false;
    }

    int AYA_getStrArg(AYA::VM* state, size_t index, const char** result)
    {
        AYA::Variant& arg = state->callFrame().frameBottom()[index];

        if(arg.isREF() && state->objectFactory.getType(arg.value.ref) == AYA::BType::STR)
        {
            AYA::StringObject* str = static_cast<AYA::StringObject*>(arg.value.ref);
            if(result)
                *result = str->content.c_str();
            return true;
        }
        else
            return false;
    }

    void AYA_setErrorMsg(AYA::VM* state, const char* msg)
    {
        state->callFrame().setErrorMsg(msg);
    }

    void AYA_setNilResult(AYA::VM* state)
    {
        *(state->callFrame().frameBottom()) = NIL();
    }

    void AYA_setIntResult(AYA::VM* state, AYA::INT_T result)
    {
        *(state->callFrame().frameBottom()) = INT(result);
    }

    void AYA_setRealResult(AYA::VM* state, AYA::REAL_T result)
    {
        *(state->callFrame().frameBottom()) = REAL(result);
    }

    void AYA_setStrResult(AYA::VM* state, const char* result)
    {
        auto str = state->objectFactory.makeString(AYA::STRING_T(result));
        *(state->callFrame().frameBottom()) = REF(str);
    }
}
