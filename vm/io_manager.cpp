#include "io_manager.h"

#include "vm.h"

namespace AYA
{
    void IOManager::write(const STRING_T& str)
    {
        if(!outs->good())
            throw RuntimeError("output stream is in invalid state");
        *outs << str;
    }

    void IOManager::writeErr(const STRING_T& str)
    {
       if(!errs->good())
            throw RuntimeError("error output stream is in invalid state");
        *errs << str;
    }

    STRING_T IOManager::read()
    {
        if(!ins->good())
            throw RuntimeError("input stream is in invalid state");
        STRING_T str;
        *ins >> str;
        return str;
    }

    STRING_T IOManager::read(size_t num)
    {
        if(!ins->good())
            throw RuntimeError("input stream is in invalid state");
        char buf[num+1];
        ins->read(buf, num);
        buf[ins->gcount()] = '\0';
        return STRING_T(buf);
    }

    STRING_T IOManager::readLine()
    {
        if(!ins->good())
            throw RuntimeError("input stream is in invalid state");
        char buf[256];
        ins->getline(buf, 256);
        return STRING_T(buf);
    }
}
