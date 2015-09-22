#include <fstream>
#include <iostream>

#include <cassert>

#include "vm/vm.h"

using namespace AYA;

int main(int argc, char** argv)
{
    VM vm;
    vm.setParserInput(&std::cin);
    vm.files.addToWhitelist(boost::filesystem::current_path());
    while (true)
    {
        std::cout << "AYA> " << std::flush;
        int result = vm.run();
        if (result == 0)
        {
            std::cout << "=> " << std::flush;
            vm.printResult();
            std::cout << std::endl;
        }
    }

    return 0;
}
