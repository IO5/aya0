%token_type {AYA::Node*}

%extra_argument { AYA::Node** currentNode }

%token_prefix TK_

%name Lemon

%start_symbol chunk

%left OR.
%left AND.
%left EQ NEQ.
%nonassoc L G LEQ GEQ.
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
    #include "parser/member_access_node.h"
    #include "parser/index_access_node.h"
    #include "parser/stat_node.h"
    #include "parser/block_node.h"
    #include "parser/loop_node.h"
    #include "parser/if_node.h"
    #include "parser/return_node.h"
    #include "parser/func_node.h"
    #include "parser/call_node.h"
    #include "parser/decl_node.h"
    #include "parser/list_constr_node.h"
    #include "parser/dict_constr_node.h"
    #include "parser/for_node.h"
    #include "parser/class_node.h"

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

stat(S)     ::= LOCAL IDENT(I). { S = new DeclNode(I, NULL); }
stat(S)     ::= LOCAL IDENT(I) ASSIG exp(E). { S = new DeclNode(I, E); }


//stat        ::= LOCAL ident_list var_init.
//stat        ::= GLOBAL ident_list var_init.
//
//var_init    ::= .
//var_init    ::= ASSIG exp_list.

stat(S)     ::= WHILE exp(C) DO block(B) END. { S = new WhileNode(C, B); }

stat(S)     ::= REPEAT block(B) UNTIL exp(C). { S = new RepeatNode(C, B); }

stat(S)     ::= FOR IDENT(I) IN exp(E) DO block(B) END. { S = new ForNode(I, E, B); }

stat(S)     ::= IF exp(C) THEN block(B) else(E) END. { S = new IfNode(C, B, E); }
else(S)     ::= . { S = NULL; }
else(S)     ::= ELSE block(B). { S = B; }
else(S)     ::= ELSEIF exp(C) THEN block(B) else(E). { S = new IfNode(C, B, E); }

//stat(S)     ::= RETURN exp_list.
stat(S)     ::= RETURN exp(E). { S = new ReturnNode(E); }

stat        ::= NEXT. //TODO
stat        ::= BREAK. //TODO

%type class_body { std::vector<std::pair<Node*, Node*> >* }
stat(S)         ::= CLASS IDENT(I) class_body(B). { S = new ClassNode(I, NULL, B); }
stat(S)         ::= CLASS IDENT(I) PL exp(E) PR class_body(B). { S = new ClassNode(I, E, B); }
class_body(CB)  ::= END . { CB = new std::vector<std::pair<Node*, Node*> >(); }
class_body(CB)  ::= NL class_body(B) . { CB = B; }
class_body(CB)  ::= SCOLON class_body(B) . { CB = B; }
class_body(CB)  ::= NL DEF IDENT(I) func_body(F) class_body(B) . { CB = B; B->push_back(std::make_pair(I, F)); }
class_body(CB)  ::= SCOLON DEF IDENT(I) func_body(F) class_body(B) . { CB = B; B->push_back(std::make_pair(I, F)); }
class_body(CB)  ::= NL IDENT(I) ASSIG exp(E) class_body(B) . { CB = B; B->push_back(std::make_pair(I, E)); }
class_body(CB)  ::= SCOLON IDENT(I) ASSIG exp(E) class_body(B) . { CB = B; B->push_back(std::make_pair(I, E)); }

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

stat(S)     ::= DEF func_ident(I) func_body(B). { S = new AssignNode(I, B); }
stat(S)     ::= LOCAL DEF IDENT(I) func_body(B). { S = new DeclNode(I, B); }
func_ident(FI)  ::= IDENT(I). { FI = new VarNode(I); }
func_ident(FI)  ::= func_ident(F) DOT IDENT(I). { FI = new MemberAccessNode(F, I); }
//func_ident  ::= IDENT member_list. //[':' IDENT]

function(F)     ::= DEF func_body(B). { F = B; }
func_body(F)    ::= PL PR block(B) END. { F = new FuncNode(NULL, B); }
func_body(F)    ::= PL ident_list(ARGS) PR block(B) END. { F = new FuncNode(ARGS, B); }

functioncall(C) ::= prefixexp(E) PL PR. { C = new CallNode(E, NULL); } // TODO
functioncall(C) ::= prefixexp(E) PL exp_list(EL) PR. { C = new CallNode(E, EL); } // TODO

prefixexp(E) ::= var(V). { E = V; }
prefixexp(E) ::= functioncall(C). { E = C; }
prefixexp(E) ::= PL exp(A) PR. { E = A; }

prefixexp(E) ::= STRING(A). { E = A; } // so I can do "abc".abc()

//constructors
prefixexp(E)      ::= SBL SBR. { E = new ListConstrNode(NULL); }
prefixexp(E)      ::= SBL exp_list(L) SBR. { E = new ListConstrNode(L); }
prefixexp(E)      ::= CBL CBR. { E = new DictConstrNode(NULL); }
prefixexp(E)      ::= CBL dict_list(L) CBR. { E = new DictConstrNode(L); }

exp(E)      ::= prefixexp(P). { E = P; }
exp(E)      ::= function(F). { E = F; }

//literals
exp(E)      ::= NIL. { E = new NilLitNode(); }
exp(E)      ::= FALSE. { E = new BoolLitNode(false); }
exp(E)      ::= TRUE. { E = new BoolLitNode(true); }

exp(E)      ::= INT(A). { E = A; }
exp(E)      ::= REAL(A). { E = A; }
//exp(E)      ::= STRING(A). { E = A; } // moved to prefixexp

%type dict_list { NodeDictList* }
dict_list(DL) ::= exp(L) COLON exp(R). { DL = new NodeDictList(); DL->push_back(std::make_pair(L, R)); }
dict_list(DL) ::= dict_list(D) COMMA exp(L) COLON exp(R). { DL = D; DL->push_back(std::make_pair(L, R)); }


//operations
exp(E)      ::= PIPE exp(A) PIPE. { E = new UnOpNode<'|'>(A); }

exp(E)      ::= exp(A) OR exp(B).  { E = new OrNode(A, B); }
exp(E)      ::= exp(A) AND exp(B). { E = new AndNode(A, B); }

exp(E)      ::= exp(A) L exp(B).   { E = new BinOpNode<'<'>(A, B); }
exp(E)      ::= exp(A) G exp(B).   { E = new BinOpNode<'>'>(A, B); }
exp(E)      ::= exp(A) LEQ exp(B). { E = new BinOpNode<'<'+'='>(A, B); }
exp(E)      ::= exp(A) GEQ exp(B). { E = new BinOpNode<'>'+'='>(A, B); }
exp(E)      ::= exp(A) NEQ exp(B). { E = new BinOpNode<'!'>(A, B); }
exp(E)      ::= exp(A) EQ exp(B).  { E = new BinOpNode<'='>(A, B); }

exp(E)      ::= exp(A) PLUS exp(B).     { E = new BinOpNode<'+'>(A, B); }
exp(E)      ::= exp(A) MINUS exp(B).    { E = new BinOpNode<'-'>(A, B); }

exp(E)      ::= exp(A) MUL exp(B). { E = new BinOpNode<'*'>(A, B); }
exp(E)      ::= exp(A) DIV exp(B). { E = new BinOpNode<'/'>(A, B); }
exp(E)      ::= exp(A) MOD exp(B). { E = new BinOpNode<'%'>(A, B); }

exp(E)      ::= exp(A) EXP exp(B). { E = new BinOpNode<'^'>(A, B); }

exp(E)     ::= NOT exp(A). { E = new UnOpNode<'!'>(A); }
exp(E)     ::= MINUS exp(A). [NOT] { E = new UnOpNode<'-'>(A); }

//var_list ::= var.
//var_list ::= var_list COMMA var.

var(V) ::= IDENT(I). { V = new VarNode(I); }
var(V) ::= prefixexp(E) DOT IDENT(I). { V = new MemberAccessNode(E, I); }
var(V) ::= prefixexp(E) SBL exp(IDX) SBR. { V = new IndexAccessNode(E, IDX); }

%type exp_list { NodeList<>* }
exp_list(EL) ::= exp(E). { EL = new NodeList<>(); EL->push_back(E); }
exp_list(EL) ::= exp_list(L) COMMA exp(E). { EL = L; EL->push_back(E); }
