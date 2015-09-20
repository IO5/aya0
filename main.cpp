#include<fstream>
#include<iostream>

#include<cstdio>
#include<cassert>


// (*) include lexical analyser header
#include "lexer"

#include "types.h"
#include "error.h"

#include "parser.h"

#include "vm/vm.h"

using namespace AYA;

#ifndef     ENCODING_NAME
#    define ENCODING_NAME (0x0)
#endif

int main(int argc, char** argv)
{
    VM vm;
    vm.setParserInput(&std::cin);
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
