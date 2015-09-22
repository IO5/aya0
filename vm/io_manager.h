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
    };
}

#endif // IOMANAGER_H
