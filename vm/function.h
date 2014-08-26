#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED

#include "closure.h"

namespace AYA
{
    class Function
    {
        friend class VM;
    public:
        Function(Closure* f, Function* _caller)
        : caller(_caller), prototype(f), PC(0) {}

        typedef Closure::InstList InstList;

    protected:
        Function* caller;
        Closure* prototype;

        const InstList& code()
        {
            return prototype->code;
        }

        const std::vector<Variant>& constTable()
        {
            return prototype->constTable;
        }
        /// Program Counter
        uint32_t PC;
    };
}

#endif // FUNCTION_H_INCLUDED
