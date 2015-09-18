#include "io_manager.h"

#include "vm.h"

#include "boost/format.hpp"

namespace AYA
{
    using boost::format;
    using boost::io::group;

    void IOManager::write(const STRING_T& str)
    {
        printf("%s", str.c_str());
    }
}
