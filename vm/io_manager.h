#ifndef IOMANAGER_H
#define IOMANAGER_H

#include "../types.h"

#include <iostream>

namespace AYA
{
    class VM;

    class IOManager
    {
        std::istream* ins;
        std::ostream* outs;
        std::ostream* errs;
    public:
        IOManager(std::istream* i = &std::cin,
                  std::ostream* o = &std::cout,
                  std::ostream* e = &std::cerr)
        :
            ins(i), outs(o), errs(e)
        {}

        void setInput(std::istream* i)
        { ins = i; }
        void setOutput(std::ostream* o)
        { outs = o; }
        void setErrOutput(std::ostream* e)
        { errs = e; }
        std::istream* getInput()
        { return ins; }
        std::ostream* getOutput()
        { return outs; }
        std::ostream* getErrOutput()
        { return errs; }

        void write(const STRING_T& str);
        void writeErr(const STRING_T& str);
        STRING_T read();
        STRING_T read(size_t n);
        STRING_T readLine();
    };
}

#endif // IOMANAGER_H
