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

//int main()
//{
//    Parser par;
//    TOKEN_T t0;
//    //par.parse(TOKEN_T)
//
//    VM vm;
//
//    auto& f = vm.objectFactory;
//
//
//    FunctionBuilder a(vm);
//    a.addArg("i");
//    a.addInst(Inst::LOAD,   a.addConst("i"));
//    a.addInst(Inst::RET);
//
//
//    FunctionBuilder b(vm);
//
//    b.addInst(Inst::LBOOL,  5);
//    b.addInst(Inst::STORE,   b.addConst("i"));
//    b.addInst(Inst::LOAD,   b.addConst("i"));
//
//    size_t w1 = b.addInst(Inst::NOP);
//
//    b.addInst(Inst::LOAD,   b.addConst("i"));
//    b.addInst(Inst::LCONST, b.addConst("*"));
//    b.addInst(Inst::LCONST, b.addConst(REAL(2.5)));
//    b.addInst(Inst::LCONST, b.addConst("="));
//
//    b.addInst(Inst::LOAD,   b.addConst("i"));
//    b.addInst(Inst::CLOSURE, b.addConst(Variant((FunctionPrototype*)a.getResult())));
//    b.addInst(Inst::STORE,   b.addConst("f"));
//    b.addInst(Inst::LOAD,   b.addConst("f"));
//    b.addInst(Inst::CALL,   1);
//
//    b.addInst(Inst::LCONST, b.addConst(REAL(2.5)));
//    b.addInst(Inst::BINOP,  '*');
//
//    b.addInst(Inst::LCONST, b.addConst("\n"));
//
//    b.addInst(Inst::LCONST, b.addConst(BIND(vm.io.print)));
//    b.addInst(Inst::CALL,   6);
//
//    b.addInst(Inst::LBOOL,  -1);
//    b.addInst(Inst::BINOP,  '+');
//
//    b.addInst(Inst::STORE,  b.addConst("i"));
//    b.addInst(Inst::LOAD,   b.addConst("i"));
//
//    b.addInst(Inst::JMP, (w1 - 1) - b.current() );
//    b.at(w1) = Inst(Inst::JMPF, b.current() - w1 - 1);
//
//    b.addInst(Inst::LBOOL,  1);
//    b.addInst(Inst::LBOOL,  2);
//    b.addInst(Inst::LBOOL,  3);
//    b.addInst(Inst::LOAD,   b.addConst("f"));
//    b.addInst(Inst::CALL,   3);
//    b.addInst(Inst::LCONST, b.addConst(BIND(vm.io.print)));
//    b.addInst(Inst::CALL,   1);
//
//    b.addInst(Inst::RET);
//
//    vm.load(b.getResult());
//    vm.run();
//
//    return 0;
//}

#ifndef     ENCODING_NAME
#    define ENCODING_NAME (0x0)
#endif

int main(int argc, char** argv)
{
    using namespace std;

    quex::Token*       token_p = 0x0;
    // (*) create the lexical analyser
    //     1st arg: input file, default = 'example.txt'
    //     2nd arg: input character encoding name, 0x0 --> no codec conversion
    quex::lexer    qlex(argc == 1 ? "test2.sbx" : argv[1], ENCODING_NAME);

    Parser par;

    try
    {
        do
        {
            // (*) get next token from the token stream
            qlex.receive(&token_p);

            //cerr<<token_p->type_id_name()<<'\n';
            par.parse(token_p);
        }while( token_p->type_id() != TK_EOS );
    }
    catch(ParseError err)
    {
        cerr << err.what() << endl;
    }

    return 0;
}
