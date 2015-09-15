%token_type {AYA::Node*}

%extra_argument { AYA::Node** currentNode }

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
    #include "parser/assign_node.h"
    #include "parser/var_node.h"
    #include "parser/member_access.h"
    #include "parser/stat_node.h"
    #include "parser/block_node.h"
    #include "parser/loop_node.h"
    #include "parser/if_node.h"
    #include "parser/return_node.h"
    #include "parser/func_node.h"
    #include "parser/call_node.h"
    #include "parser/decl_node.h"

    #ifdef DEBUG
        #include <iostream>
    #endif // DEBUG

    using namespace AYA;
}

%syntax_error
{
    throw AYA::ParseError("syntax error");
}

chunk       ::= TERMINATION UNINITIALIZED WARNING DOT.

//start
chunk(C)    ::= block(B) EOS. { *currentNode = C = B; }

%type stat_list { NodeList<>* }
%type block { BlockNode* }
block(B)    ::= stat_list(L). { B = new BlockNode(L);  }

stat_list(SL) ::= stat(S). { SL = new NodeList<>(); if(S){ SL->push_back(S); }  }
stat_list(SL) ::= stat_list(L) NL stat(S). { SL = L;  if(S){ SL->push_back(S); }  }
stat_list(SL) ::= stat_list(L) SCOLON stat(S). { SL = L;  if(S){ SL->push_back(S); }  }


//stat
stat(S)     ::= .    { S = NULL; }
stat(S)     ::= exp(E). { S = new StatNode(E); }
stat(S)     ::= DO block(B) END. { S = B; B->createScope(); }

//stat        ::= var_list ASSIG exp_list.
stat(S)     ::= var(V) ASSIG exp(E). { S = new AssignNode(V, E); }
stat(S)     ::= GLOBAL IDENT(I) ASSIG exp(E). { S = new AssignNode(new VarNode(I), E); }
stat(S)     ::= GLOBAL IDENT. { S = NULL; }

stat(S)     ::= LOCAL IDENT(I). { S = new DeclNode(I, NULL); }
stat(S)     ::= LOCAL IDENT(I) ASSIG exp(E). { S = new DeclNode(I, E); }


//stat        ::= LOCAL ident_list var_init.
//stat        ::= GLOBAL ident_list var_init.
//
//var_init    ::= .
//var_init    ::= ASSIG exp_list.

stat(S)     ::= WHILE exp(C) DO block(B) END. { S = new WhileNode(C, B); }

stat(S)     ::= REPEAT block(B) UNTIL exp(C). { S = new RepeatNode(C, B); }

stat        ::= FOR ident_list IN exp_list DO block END.

stat(S)     ::= IF exp(C) THEN block(B) else(E) END. { S = new IfNode(C, B, E); }
else(S)     ::= . { S = NULL; }
else(S)     ::= ELSE block(B). { S = B; }
else(S)     ::= ELSEIF exp(C) THEN block(B) else(E). { S = new IfNode(C, B, E); }

//stat(S)     ::= RETURN exp_list.
stat(S)     ::= RETURN exp(E). { S = new ReturnNode(E); }

stat        ::= NEXT.
stat        ::= BREAK.

// func definition
%type ident_list { NodeList<IdentNode>* }
ident_list(IL) ::= IDENT(I).
{
    IL = new NodeList<IdentNode>();

    assert(dynamic_cast<IdentNode*>(I));
    IL->push_back(static_cast<IdentNode*>(I));

}
ident_list(IL) ::= ident_list(L) COMMA IDENT(I).
{
    IL = L;

    assert(dynamic_cast<IdentNode*>(I));
    IL->push_back(static_cast<IdentNode*>(I));
}

//stat(S)     ::= DEF func_ident func_body. { S; }
stat(S)     ::= DEF IDENT(I) func_body(B). { S = new AssignNode(new VarNode(I), B); }
stat        ::= LOCAL DEF IDENT func_body.
//func_ident  ::= IDENT member_list. //[':' IDENT]

function(F)     ::= DEF func_body(B). { F = B; }
func_body(F)    ::= PL PR block(B) END. { F = new FuncNode(NULL, B); }
func_body(F)    ::= PL ident_list(ARGS) PR block(B) END. { F = new FuncNode(ARGS, B); }

functioncall(C) ::= prefixexp(E) PL PR. { C = new CallNode(E, NULL); } // TODO
functioncall(C) ::= prefixexp(E) PL exp_list(EL) PR. { C = new CallNode(E, EL); } // TODO

prefixexp(E) ::= var(V). { E = V; }
prefixexp(E) ::= functioncall(C). { E = C; }
prefixexp(E) ::= PL exp(A) PR. { E = A; }

exp(E)      ::= prefixexp(P). { E = P; }
exp(E)      ::= function(F). { E = F; }

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

exp(E)      ::= exp(A) MUL exp(B). { E = new BinOpNode<'*'>(A, B); }
exp(E)      ::= exp(A) DIV exp(B). { E = new BinOpNode<'/'>(A, B); }
exp(E)      ::= exp(A) MOD exp(B). { E = new BinOpNode<'%'>(A, B); }

exp(E)      ::= exp(A) EXP exp(B). { E = new BinOpNode<'^'>(A, B); }

exp(E)     ::= NOT exp(A). { E = new UnOpNode<'!'>(A); }
exp(E)     ::= MINUS exp(A). [NOT] { E = new UnOpNode<'-'>(A); }


//member_list ::= .
//member_list ::= member_list member.
//member      ::= DOT IDENT.


//var_list ::= var.
//var_list ::= var_list COMMA var.

var(V) ::= IDENT(I). { V = new VarNode(I); }
var(V) ::= prefixexp(E) DOT IDENT(I). { V = new MemberAccessNode(E, I); }

%type exp_list { NodeList<>* }
exp_list(EL) ::= exp(E). { EL = new NodeList<>(); EL->push_back(E); }
exp_list(EL) ::= exp_list(L) COMMA exp(E). { EL = L; EL->push_back(E); }
