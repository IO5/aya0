#include <fstream>
#include <sstream>
#include <iostream>

#include "vm/vm.h"

using namespace AYA;

int main(int argc, char** argv)
{
    VM vm;

    if (argc == 2)
    {
        return vm.runFile(argv[1]);
    }

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
        vm.gc.collect();
    }

    return 0;
}
