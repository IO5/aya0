%token_type {AYA::Node*}

//%extra_argument { MyStruct *target }

%token_prefix TK_

%name Lemon

%start_symbol chunk

%left OR.
%left AND.
%left EQ NEQ.
%nonassoc L G LEQ GEQ.
%nonassoc RANGEOP.
%left PLUS MINUS.
%left MUL DIV MOD.
%right NOT.
%right EXP.

%include
{
    #include "types.h"
    #include "error.h"

    #include <cassert> //wtf lemon, include your own shit

	#include "lparser.h"

    #include "lexer"
    #include "parser/lit_node.h"
    #include "parser/binop_node.h"
    #include "parser/unop_node.h"
    #include "parser/logicalop_node.h"


    #ifdef DEBUG
        #include <iostream>
    #endif // DEBUG

    using namespace AYA;
}

%syntax_error
{
    throw AYA::ParseError("syntax error");
}

chunk       ::= TERMINATION UNINITIALIZED WARNING.

//start
chunk       ::= block EOS.

block       ::= stat_list.

stat_list   ::= stat.
stat_list   ::= stat_list NL stat.
stat_list   ::= stat_list SCOLON stat.


//stat
stat(S)     ::= .    { S=NULL; }
stat(S)     ::= exp(E). { S=E; }
stat(S)     ::= DO block END. { S; }

stat        ::= var_list ASSIG exp_list.

stat        ::= LOCAL ident_list var_init.
stat        ::= GLOBAL ident_list var_init.

var_init    ::= .
var_init    ::= ASSIG exp_list.

stat        ::= functioncall.

stat        ::= WHILE exp DO block END.

stat        ::= REPEAT block UNTIL exp.

stat        ::= FOR ident_list IN exp_list DO block END.

//TODO REDO
stat        ::= IF exp THEN block elseif else END.
elseif      ::= .
elseif      ::= ELSEIF exp THEN block.
else        ::= .
else        ::= ELSE block.

stat        ::= RETURN exp_list.

stat        ::= NEXT.
stat        ::= BREAK.


// func definition
stat        ::= DEF func_ident func_body.
stat        ::= LOCAL DEF IDENT func_body.
func_ident  ::= IDENT member_list. //[':' IDENT]

function    ::= DEF func_body.
func_body   ::= PL PR block END.
func_body   ::= PL ident_list PR block END.


exp(E)      ::= PL exp(A) PR. { E = A; }
exp(E)      ::= function(A). { E = A; }

//literals
exp(E)      ::= NIL. { E = new NilLitNode(); }
exp(E)      ::= FALSE. { E = new BoolLitNode(false); }
exp(E)      ::= TRUE. { E = new BoolLitNode(true); }

exp(E)      ::= INT(A). { E = A; }
exp(E)      ::= REAL(A). { E = A; }
exp(E)      ::= STRING(A). { E = A; }


exp(E)      ::= PIPE exp(A) PIPE. { E = new UnOpNode<'|'>(A); }

exp(E)      ::= exp(A) OR exp(B).  { E = new OrNode(A, B); }
exp(E)      ::= exp(A) AND exp(B). { E = new AndNode(A, B); }

exp(E)      ::= exp(A) L exp(B).   { E = new BinOpNode<'<'>(A, B); }
exp(E)      ::= exp(A) G exp(B).   { E = new BinOpNode<'>'>(A, B); }
exp(E)      ::= exp(A) LEQ exp(B). { E = new BinOpNode<'<'+'='>(A, B); }
exp(E)      ::= exp(A) GEQ exp(B). { E = new BinOpNode<'>'+'='>(A, B); }
exp(E)      ::= exp(A) NEQ exp(B). { E = new BinOpNode<'!'>(A, B); }
exp(E)      ::= exp(A) EQ exp(B).  { E = new BinOpNode<'='>(A, B); }

exp         ::= exp RANGEOP exp.

exp(E)      ::= exp(A) PLUS exp(B).     { E = new BinOpNode<'+'>(A, B); }
exp(E)      ::= exp(A) MINUS exp(B).    { E = new BinOpNode<'-'>(A, B); }

exp(E)      ::= exp(A) MUL exp(B) . { E = new BinOpNode<'*'>(A, B); }
exp(E)      ::= exp(A) DIV exp(B) . { E = new BinOpNode<'/'>(A, B); }
exp(E)      ::= exp(A) MOD exp(B) . { E = new BinOpNode<'%'>(A, B); }

exp(E)      ::= exp(A) EXP exp(B) . { E = new BinOpNode<'^'>(A, B); }

exp(E)     ::= NOT exp(A). { E = new UnOpNode<'!'>(A); }
exp(E)     ::= MINUS exp(A). [NOT] { E = new UnOpNode<'-'>(A); }

exp     ::= var.
//

member_list ::= .
member_list ::= member_list member.
member      ::= DOT IDENT.

//

var_list ::= var.
var_list ::= var_list COMMA var.

var ::= IDENT.

exp_list ::= exp.
exp_list ::= exp_list COMMA exp.

ident_list ::= IDENT.
ident_list ::= ident_list COMMA IDENT.

functioncall ::= IDENT PL PR. // TODO
