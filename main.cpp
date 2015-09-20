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
    vm.run();

    return 0;
}
