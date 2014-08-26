#ifndef IOMANAGER_H
#define IOMANAGER_H

#include "../types.h"

#include <cstdio>

namespace AYA
{
    class VM;

    class IOManager
    {
    public:
        void write(const STRING_T& str);
    //private:
        template<char>
        static int printValues(VM*);
        static int print(VM* state);
        static int puts(VM* state);
    };
}

#endif // IOMANAGER_H
