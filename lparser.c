/* Driver template for the LEMON parser generator.
** The author disclaims copyright to this source code.
*/
/* First off, code is included that follows the "include" declaration
** in the input grammar file. */
#include <stdio.h>
#line 22 "lparser.y"

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
#line 45 "lparser.c"
/* Next is all token values, in a form suitable for use by makeheaders.
** This section will be null unless lemon is run with the -m switch.
*/
/* 
** These constants (all generated automatically by the parser generator)
** specify the various kinds of tokens (terminals) that the parser
** understands. 
**
** Each symbol here is a terminal symbol in the grammar.
*/
/* Make sure the INTERFACE macro is defined.
*/
#ifndef INTERFACE
# define INTERFACE 1
#endif
/* The next thing included is series of defines which control
** various aspects of the generated parser.
**    YYCODETYPE         is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 terminals
**                       and nonterminals.  "int" is used otherwise.
**    YYNOCODE           is a number of type YYCODETYPE which corresponds
**                       to no legal terminal or nonterminal number.  This
**                       number is used to fill in empty slots of the hash 
**                       table.
**    YYFALLBACK         If defined, this indicates that one or more tokens
**                       have fall-back values which should be used if the
**                       original value of the token will not parse.
**    YYACTIONTYPE       is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 rules and
**                       states combined.  "int" is used otherwise.
**    LemonTOKENTYPE     is the data type used for minor tokens given 
**                       directly to the parser from the tokenizer.
**    YYMINORTYPE        is the data type used for all minor tokens.
**                       This is typically a union of many types, one of
**                       which is LemonTOKENTYPE.  The entry in the union
**                       for base tokens is called "yy0".
**    YYSTACKDEPTH       is the maximum depth of the parser's stack.  If
**                       zero the stack is dynamically sized using realloc()
**    LemonARG_SDECL     A static variable declaration for the %extra_argument
**    LemonARG_PDECL     A parameter declaration for the %extra_argument
**    LemonARG_STORE     Code to store %extra_argument into yypParser
**    LemonARG_FETCH     Code to extract %extra_argument from yypParser
**    YYNSTATE           the combined number of states.
**    YYNRULE            the number of rules in the grammar
**    YYERRORSYMBOL      is the code number of the error symbol.  If not
**                       defined, then do no error processing.
*/
#define YYCODETYPE unsigned char
#define YYNOCODE 77
#define YYACTIONTYPE unsigned short int
#define LemonTOKENTYPE AYA::Node*
typedef union {
  int yyinit;
  LemonTOKENTYPE yy0;
  NodeList<IdentNode>* yy69;
  std::vector<std::pair<Node*, Node*> >* yy88;
  NodeList<>* yy115;
  NodeDictList* yy129;
  BlockNode* yy132;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define LemonARG_SDECL  AYA::Node** currentNode ;
#define LemonARG_PDECL , AYA::Node** currentNode 
#define LemonARG_FETCH  AYA::Node** currentNode  = yypParser->currentNode 
#define LemonARG_STORE yypParser->currentNode  = currentNode 
#define YYNSTATE 188
#define YYNRULE 83
#define YY_NO_ACTION      (YYNSTATE+YYNRULE+2)
#define YY_ACCEPT_ACTION  (YYNSTATE+YYNRULE+1)
#define YY_ERROR_ACTION   (YYNSTATE+YYNRULE)

/* The yyzerominor constant is used to initialize instances of
** YYMINORTYPE objects to zero. */
static const YYMINORTYPE yyzerominor = { 0 };

/* Define the yytestcase() macro to be a no-op if is not already defined
** otherwise.
**
** Applications can choose to define yytestcase() in the %include section
** to a macro that can assist in verifying code coverage.  For production
** code the yytestcase() macro should be turned off.  But it is useful
** for testing.
*/
#ifndef yytestcase
# define yytestcase(X)
#endif


/* Next are the tables used to determine what action to take based on the
** current state and lookahead token.  These tables are used to implement
** functions that take a state number and lookahead value and return an
** action integer.  
**
** Suppose the action integer is N.  Then the action is determined as
** follows
**
**   0 <= N < YYNSTATE                  Shift N.  That is, push the lookahead
**                                      token onto the stack and goto state N.
**
**   YYNSTATE <= N < YYNSTATE+YYNRULE   Reduce by rule N-YYNSTATE.
**
**   N == YYNSTATE+YYNRULE              A syntax error has occurred.
**
**   N == YYNSTATE+YYNRULE+1            The parser accepts its input.
**
**   N == YYNSTATE+YYNRULE+2            No such action.  Denotes unused
**                                      slots in the yy_action[] table.
**
** The action table is constructed as a single large table named yy_action[].
** Given state S and lookahead X, the action is computed as
**
**      yy_action[ yy_shift_ofst[S] + X ]
**
** If the index value yy_shift_ofst[S]+X is out of range or if the value
** yy_lookahead[yy_shift_ofst[S]+X] is not equal to X or if yy_shift_ofst[S]
** is equal to YY_SHIFT_USE_DFLT, it means that the action is not in the table
** and that yy_default[S] should be used instead.  
**
** The formula above is for computing the action when the lookahead is
** a terminal symbol.  If the lookahead is a non-terminal (as occurs after
** a reduce action) then the yy_reduce_ofst[] array is used in place of
** the yy_shift_ofst[] array and YY_REDUCE_USE_DFLT is used in place of
** YY_SHIFT_USE_DFLT.
**
** The following are the tables generated in this section:
**
**  yy_action[]        A single table containing all actions.
**  yy_lookahead[]     A table containing the lookahead for each entry in
**                     yy_action.  Used to detect hash collisions.
**  yy_shift_ofst[]    For each state, the offset into yy_action for
**                     shifting terminals.
**  yy_reduce_ofst[]   For each state, the offset into yy_action for
**                     shifting non-terminals after a reduce.
**  yy_default[]       Default action for each state.
*/
#define YY_ACTTAB_COUNT (844)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    28,  138,   98,   97,   29,  185,  139,  271,   35,   34,
 /*    10 */    33,   32,   31,    8,   30,  137,  123,  164,  100,   23,
 /*    20 */     6,    1,  117,   18,   20,   11,   10,  188,   19,  156,
 /*    30 */   155,  113,   46,  186,   51,   56,  176,   13,    9,   12,
 /*    40 */   133,  170,  169,  168,  167,  166,   28,   41,   81,  179,
 /*    50 */    29,  180,  144,   47,  121,  171,  178,   99,  103,    8,
 /*    60 */    98,   97,  123,  164,  100,   23,    6,   61,  117,   47,
 /*    70 */    20,  120,  174,  136,   19,  156,  155,  113,   46,   44,
 /*    80 */    51,  134,  176,   13,  172,   12,  124,  170,  169,  168,
 /*    90 */   167,  166,  189,   41,  182,   50,   48,   37,   38,   45,
 /*   100 */    42,   40,   39,   36,   35,   34,   33,   32,   31,   14,
 /*   110 */    30,   33,   32,   31,   26,   30,   98,   97,   50,   48,
 /*   120 */    37,   38,   45,   42,   40,   39,   36,   35,   34,   33,
 /*   130 */    32,   31,  184,   30,   49,   50,   48,   37,   38,   45,
 /*   140 */    42,   40,   39,   36,   35,   34,   33,   32,   31,   30,
 /*   150 */    30,  271,  271,  271,  271,   36,   35,   34,   33,   32,
 /*   160 */    31,  177,   30,   50,   48,   37,   38,   45,   42,   40,
 /*   170 */    39,   36,   35,   34,   33,   32,   31,  163,   30,   37,
 /*   180 */    38,   45,   42,   40,   39,   36,   35,   34,   33,   32,
 /*   190 */    31,   43,   30,   50,   48,   37,   38,   45,   42,   40,
 /*   200 */    39,   36,   35,   34,   33,   32,   31,  122,   30,   25,
 /*   210 */    45,   42,   40,   39,   36,   35,   34,   33,   32,   31,
 /*   220 */   165,   30,   50,   48,   37,   38,   45,   42,   40,   39,
 /*   230 */    36,   35,   34,   33,   32,   31,   24,   30,   81,  179,
 /*   240 */     3,   15,  108,   64,  160,  171,  178,   99,  102,   27,
 /*   250 */    22,   50,   48,   37,   38,   45,   42,   40,   39,   36,
 /*   260 */    35,   34,   33,   32,   31,   61,   30,  116,   21,  159,
 /*   270 */   162,  158,  152,   54,    7,  109,   50,   48,   37,   38,
 /*   280 */    45,   42,   40,   39,   36,   35,   34,   33,   32,   31,
 /*   290 */    63,   30,  112,   62,   17,   16,  142,  141,  145,    5,
 /*   300 */   186,   50,   48,   37,   38,   45,   42,   40,   39,   36,
 /*   310 */    35,   34,   33,   32,   31,  114,   30,   61,   50,   48,
 /*   320 */    37,   38,   45,   42,   40,   39,   36,   35,   34,   33,
 /*   330 */    32,   31,  151,   30,  161,  110,    4,  273,   50,   48,
 /*   340 */    37,   38,   45,   42,   40,   39,   36,   35,   34,   33,
 /*   350 */    32,   31,  111,   30,   58,   57,   72,  179,  104,  146,
 /*   360 */   153,   59,  148,  171,  178,   99,  150,  101,  143,  273,
 /*   370 */   154,  149,  147,    2,  273,   50,   48,   37,   38,   45,
 /*   380 */    42,   40,   39,   36,   35,   34,   33,   32,   31,   28,
 /*   390 */    30,  273,  273,   29,  273,  273,  273,  273,  273,  272,
 /*   400 */   135,  105,  183,   85,  131,  273,  164,  187,   85,  131,
 /*   410 */   171,  178,   99,  273,  273,  171,  178,   99,  273,  273,
 /*   420 */   273,   46,  181,   65,  273,  176,   13,  273,   12,  273,
 /*   430 */   170,  169,  168,  167,  166,   28,   41,  273,  273,   29,
 /*   440 */   273,  273,  273,  273,  273,  273,  107,  105,  183,   85,
 /*   450 */   131,   28,  164,   86,  179,   29,  171,  178,   99,  273,
 /*   460 */   171,  178,   99,  273,  273,  273,  273,   46,  164,   65,
 /*   470 */   273,  176,   13,  175,   12,  273,  170,  169,  168,  167,
 /*   480 */   166,  273,   41,   46,  273,   65,  273,  176,   13,  273,
 /*   490 */    12,  173,  170,  169,  168,  167,  166,  273,   41,   48,
 /*   500 */    37,   38,   45,   42,   40,   39,   36,   35,   34,   33,
 /*   510 */    32,   31,   28,   30,  273,  273,   29,  273,   84,  179,
 /*   520 */   132,  105,  183,   85,  131,  171,  178,   99,  273,  164,
 /*   530 */   171,  178,   99,  140,   85,  131,  273,  273,  273,  273,
 /*   540 */   273,  171,  178,   99,   46,  273,   65,  273,  176,   13,
 /*   550 */   273,   12,  273,  170,  169,  168,  167,  166,  273,   41,
 /*   560 */   119,  105,  183,   85,  131,  118,  105,  183,   85,  131,
 /*   570 */   171,  178,   99,  273,  273,  171,  178,   99,  115,  105,
 /*   580 */   183,   85,  131,   60,  105,  183,   85,  131,  171,  178,
 /*   590 */    99,   87,  179,  171,  178,   99,   80,  179,  171,  178,
 /*   600 */    99,  273,  273,  171,  178,   99,  157,  105,  183,   85,
 /*   610 */   131,   55,  105,  183,   85,  131,  171,  178,   99,  273,
 /*   620 */   273,  171,  178,   99,  106,  105,  183,   85,  131,  273,
 /*   630 */    75,  179,  273,  273,  171,  178,   99,  171,  178,   99,
 /*   640 */    88,  179,  273,   74,  179,  273,  273,  171,  178,   99,
 /*   650 */   171,  178,   99,   83,  179,  273,   89,  179,  273,  273,
 /*   660 */   171,  178,   99,  171,  178,   99,  273,  273,   73,  179,
 /*   670 */   273,   93,  179,  273,  273,  171,  178,   99,  171,  178,
 /*   680 */    99,   92,  179,  273,  273,  273,   91,  179,  171,  178,
 /*   690 */    99,   90,  179,  171,  178,   99,   94,  179,  171,  178,
 /*   700 */    99,   96,  179,  171,  178,   99,   95,  179,  171,  178,
 /*   710 */    99,  273,  273,  171,  178,   99,  130,  179,  273,  129,
 /*   720 */   179,  273,  273,  171,  178,   99,  171,  178,   99,  128,
 /*   730 */   179,  273,  273,  127,  179,  273,  171,  178,   99,  273,
 /*   740 */   171,  178,   99,  126,  179,  273,  125,  179,  273,  273,
 /*   750 */   171,  178,   99,  171,  178,   99,   82,  179,  273,   71,
 /*   760 */   179,  273,  273,  171,  178,   99,  171,  178,   99,   79,
 /*   770 */   179,  273,   78,  179,  273,  273,  171,  178,   99,  171,
 /*   780 */   178,   99,   70,  179,  273,   77,  179,  273,  273,  171,
 /*   790 */   178,   99,  171,  178,   99,   69,  179,  273,   68,  179,
 /*   800 */   273,  273,  171,  178,   99,  171,  178,   99,   76,  179,
 /*   810 */   273,   67,  179,  273,  273,  171,  178,   99,  171,  178,
 /*   820 */    99,   53,  179,  273,   52,  179,  273,  273,  171,  178,
 /*   830 */    99,  171,  178,   99,   66,  179,  273,  273,  273,  273,
 /*   840 */   273,  171,  178,   99,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    11,   18,   22,   23,   15,   28,   17,    9,   10,   11,
 /*    10 */    12,   13,   14,   24,   16,   19,   27,   28,   29,   30,
 /*    20 */    31,   44,   33,   43,   35,   22,   23,    0,   39,   40,
 /*    30 */    41,   42,   43,   68,   45,   70,   47,   48,   44,   50,
 /*    40 */    46,   52,   53,   54,   55,   56,   11,   58,   64,   65,
 /*    50 */    15,   44,   28,   46,   28,   71,   72,   73,   74,   24,
 /*    60 */    22,   23,   27,   28,   29,   30,   31,   43,   33,   46,
 /*    70 */    35,   45,   49,   20,   39,   40,   41,   42,   43,   46,
 /*    80 */    45,   21,   47,   48,   51,   50,   20,   52,   53,   54,
 /*    90 */    55,   56,    0,   58,   25,    1,    2,    3,    4,    5,
 /*   100 */     6,    7,    8,    9,   10,   11,   12,   13,   14,   43,
 /*   110 */    16,   12,   13,   14,   48,   16,   22,   23,    1,    2,
 /*   120 */     3,    4,    5,    6,    7,    8,    9,   10,   11,   12,
 /*   130 */    13,   14,   28,   16,   26,    1,    2,    3,    4,    5,
 /*   140 */     6,    7,    8,    9,   10,   11,   12,   13,   14,   16,
 /*   150 */    16,    5,    6,    7,    8,    9,   10,   11,   12,   13,
 /*   160 */    14,   44,   16,    1,    2,    3,    4,    5,    6,    7,
 /*   170 */     8,    9,   10,   11,   12,   13,   14,   28,   16,    3,
 /*   180 */     4,    5,    6,    7,    8,    9,   10,   11,   12,   13,
 /*   190 */    14,   57,   16,    1,    2,    3,    4,    5,    6,    7,
 /*   200 */     8,    9,   10,   11,   12,   13,   14,   28,   16,   26,
 /*   210 */     5,    6,    7,    8,    9,   10,   11,   12,   13,   14,
 /*   220 */    58,   16,    1,    2,    3,    4,    5,    6,    7,    8,
 /*   230 */     9,   10,   11,   12,   13,   14,   26,   16,   64,   65,
 /*   240 */    37,   38,   20,   28,   25,   71,   72,   73,   74,   57,
 /*   250 */    32,    1,    2,    3,    4,    5,    6,    7,    8,    9,
 /*   260 */    10,   11,   12,   13,   14,   43,   16,   28,   34,   25,
 /*   270 */    49,   25,   25,   28,   24,   28,    1,    2,    3,    4,
 /*   280 */     5,    6,    7,    8,    9,   10,   11,   12,   13,   14,
 /*   290 */    28,   16,   45,   28,   26,   26,   25,   25,   28,   24,
 /*   300 */    68,    1,    2,    3,    4,    5,    6,    7,    8,    9,
 /*   310 */    10,   11,   12,   13,   14,   66,   16,   43,    1,    2,
 /*   320 */     3,    4,    5,    6,    7,    8,    9,   10,   11,   12,
 /*   330 */    13,   14,   25,   16,   68,   28,   36,   76,    1,    2,
 /*   340 */     3,    4,    5,    6,    7,    8,    9,   10,   11,   12,
 /*   350 */    13,   14,   45,   16,   68,   68,   64,   65,   69,   68,
 /*   360 */    67,   44,   67,   71,   72,   73,   67,   75,   66,   76,
 /*   370 */    67,   67,   67,   36,   76,    1,    2,    3,    4,    5,
 /*   380 */     6,    7,    8,    9,   10,   11,   12,   13,   14,   11,
 /*   390 */    16,   76,   76,   15,   76,   76,   76,   76,   76,   60,
 /*   400 */    61,   62,   63,   64,   65,   76,   28,   63,   64,   65,
 /*   410 */    71,   72,   73,   76,   76,   71,   72,   73,   76,   76,
 /*   420 */    76,   43,   44,   45,   76,   47,   48,   76,   50,   76,
 /*   430 */    52,   53,   54,   55,   56,   11,   58,   76,   76,   15,
 /*   440 */    76,   76,   76,   76,   76,   76,   61,   62,   63,   64,
 /*   450 */    65,   11,   28,   64,   65,   15,   71,   72,   73,   76,
 /*   460 */    71,   72,   73,   76,   76,   76,   76,   43,   28,   45,
 /*   470 */    76,   47,   48,   49,   50,   76,   52,   53,   54,   55,
 /*   480 */    56,   76,   58,   43,   76,   45,   76,   47,   48,   76,
 /*   490 */    50,   51,   52,   53,   54,   55,   56,   76,   58,    2,
 /*   500 */     3,    4,    5,    6,    7,    8,    9,   10,   11,   12,
 /*   510 */    13,   14,   11,   16,   76,   76,   15,   76,   64,   65,
 /*   520 */    61,   62,   63,   64,   65,   71,   72,   73,   76,   28,
 /*   530 */    71,   72,   73,   63,   64,   65,   76,   76,   76,   76,
 /*   540 */    76,   71,   72,   73,   43,   76,   45,   76,   47,   48,
 /*   550 */    76,   50,   76,   52,   53,   54,   55,   56,   76,   58,
 /*   560 */    61,   62,   63,   64,   65,   61,   62,   63,   64,   65,
 /*   570 */    71,   72,   73,   76,   76,   71,   72,   73,   61,   62,
 /*   580 */    63,   64,   65,   61,   62,   63,   64,   65,   71,   72,
 /*   590 */    73,   64,   65,   71,   72,   73,   64,   65,   71,   72,
 /*   600 */    73,   76,   76,   71,   72,   73,   61,   62,   63,   64,
 /*   610 */    65,   61,   62,   63,   64,   65,   71,   72,   73,   76,
 /*   620 */    76,   71,   72,   73,   61,   62,   63,   64,   65,   76,
 /*   630 */    64,   65,   76,   76,   71,   72,   73,   71,   72,   73,
 /*   640 */    64,   65,   76,   64,   65,   76,   76,   71,   72,   73,
 /*   650 */    71,   72,   73,   64,   65,   76,   64,   65,   76,   76,
 /*   660 */    71,   72,   73,   71,   72,   73,   76,   76,   64,   65,
 /*   670 */    76,   64,   65,   76,   76,   71,   72,   73,   71,   72,
 /*   680 */    73,   64,   65,   76,   76,   76,   64,   65,   71,   72,
 /*   690 */    73,   64,   65,   71,   72,   73,   64,   65,   71,   72,
 /*   700 */    73,   64,   65,   71,   72,   73,   64,   65,   71,   72,
 /*   710 */    73,   76,   76,   71,   72,   73,   64,   65,   76,   64,
 /*   720 */    65,   76,   76,   71,   72,   73,   71,   72,   73,   64,
 /*   730 */    65,   76,   76,   64,   65,   76,   71,   72,   73,   76,
 /*   740 */    71,   72,   73,   64,   65,   76,   64,   65,   76,   76,
 /*   750 */    71,   72,   73,   71,   72,   73,   64,   65,   76,   64,
 /*   760 */    65,   76,   76,   71,   72,   73,   71,   72,   73,   64,
 /*   770 */    65,   76,   64,   65,   76,   76,   71,   72,   73,   71,
 /*   780 */    72,   73,   64,   65,   76,   64,   65,   76,   76,   71,
 /*   790 */    72,   73,   71,   72,   73,   64,   65,   76,   64,   65,
 /*   800 */    76,   76,   71,   72,   73,   71,   72,   73,   64,   65,
 /*   810 */    76,   64,   65,   76,   76,   71,   72,   73,   71,   72,
 /*   820 */    73,   64,   65,   76,   64,   65,   76,   76,   71,   72,
 /*   830 */    73,   71,   72,   73,   64,   65,   76,   76,   76,   76,
 /*   840 */    76,   71,   72,   73,
};
#define YY_SHIFT_USE_DFLT (-24)
#define YY_SHIFT_COUNT (139)
#define YY_SHIFT_MIN   (-23)
#define YY_SHIFT_MAX   (501)
static const short yy_shift_ofst[] = {
 /*     0 */   -11,   35,   35,   35,   35,   35,   35,   35,   35,   35,
 /*    10 */    35,   35,  440,  424,  378,  501,  501,  501,  501,  501,
 /*    20 */   501,  501,  501,  501,  501,  501,  501,  501,  501,  501,
 /*    30 */   501,  501,  501,  501,  501,  501,  501,  501,  501,  501,
 /*    40 */   501,  501,  501,  501,  501,  501,  501,  501,  501,  501,
 /*    50 */   501,   24,   94,   94,  -20,  203,  222,   38,   38,   38,
 /*    60 */   203,  -23,  274,  274,  274,  274,  337,  317,  300,  275,
 /*    70 */   250,  221,  192,  162,  134,  117,  374,  374,  374,  374,
 /*    80 */   374,  374,  374,  374,  374,  374,  497,  176,  146,  146,
 /*    90 */   205,  205,  146,  146,   -2,   99,   99,  307,  247,   66,
 /*   100 */    26,   33,   23,    7,   -6,    3,  272,  271,  270,  269,
 /*   110 */   268,  265,  262,  245,  246,  244,  234,  239,  218,  219,
 /*   120 */   215,  210,  183,  179,  149,  133,  133,  133,  133,  133,
 /*   130 */   133,  108,   69,  104,   92,   60,   27,   53,   -4,  -17,
};
#define YY_REDUCE_USE_DFLT (-36)
#define YY_REDUCE_COUNT (65)
#define YY_REDUCE_MIN   (-35)
#define YY_REDUCE_MAX   (770)
static const short yy_reduce_ofst[] = {
 /*     0 */   339,  563,  550,  545,  522,  517,  504,  499,  459,  385,
 /*    10 */   470,  344,  292,  174,  -16,  770,  760,  757,  747,  744,
 /*    20 */   734,  731,  721,  718,  708,  705,  695,  692,  682,  679,
 /*    30 */   669,  665,  655,  652,  642,  637,  632,  627,  622,  617,
 /*    40 */   607,  604,  592,  589,  579,  576,  566,  532,  527,  454,
 /*    50 */   389,  -35,  305,  304,  303,  302,  291,  299,  295,  293,
 /*    60 */   249,  289,  287,  286,  266,  232,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   194,  194,  194,  194,  194,  194,  194,  194,  194,  194,
 /*    10 */   194,  194,  271,  271,  271,  271,  271,  271,  271,  271,
 /*    20 */   271,  271,  271,  271,  271,  271,  271,  271,  271,  271,
 /*    30 */   271,  271,  271,  271,  271,  271,  271,  271,  271,  271,
 /*    40 */   271,  271,  271,  271,  271,  271,  271,  271,  271,  271,
 /*    50 */   271,  271,  271,  271,  271,  206,  271,  271,  271,  271,
 /*    60 */   206,  271,  271,  271,  271,  271,  271,  271,  271,  271,
 /*    70 */   271,  271,  271,  271,  271,  271,  209,  203,  201,  198,
 /*    80 */   270,  269,  246,  247,  197,  195,  249,  250,  251,  252,
 /*    90 */   256,  255,  254,  253,  257,  259,  258,  271,  271,  239,
 /*   100 */   271,  271,  271,  271,  271,  190,  271,  271,  271,  271,
 /*   110 */   271,  271,  271,  271,  271,  271,  271,  271,  271,  271,
 /*   120 */   271,  200,  199,  271,  271,  265,  264,  263,  262,  261,
 /*   130 */   260,  231,  271,  271,  271,  271,  271,  271,  271,  271,
 /*   140 */   193,  227,  228,  208,  224,  225,  222,  218,  216,  219,
 /*   150 */   217,  215,  214,  213,  212,  211,  210,  207,  205,  204,
 /*   160 */   202,  223,  268,  267,  266,  248,  245,  244,  243,  242,
 /*   170 */   241,  240,  238,  237,  236,  235,  234,  233,  232,  231,
 /*   180 */   230,  229,  196,  191,  221,  220,  226,  192,
};

/* The next table maps tokens into fallback tokens.  If a construct
** like the following:
** 
**      %fallback ID X Y Z.
**
** appears in the grammar, then ID becomes a fallback token for X, Y,
** and Z.  Whenever one of the tokens X, Y, or Z is input to the parser
** but it does not parse, the type of the token is changed to ID and
** the parse is retried before an error is thrown.
*/
#ifdef YYFALLBACK
static const YYCODETYPE yyFallback[] = {
};
#endif /* YYFALLBACK */

/* The following structure represents a single element of the
** parser's stack.  Information stored includes:
**
**   +  The state number for the parser at this level of the stack.
**
**   +  The value of the token stored at this level of the stack.
**      (In other words, the "major" token.)
**
**   +  The semantic value stored at this level of the stack.  This is
**      the information used by the action routines in the grammar.
**      It is sometimes called the "minor" token.
*/
struct yyStackEntry {
  YYACTIONTYPE stateno;  /* The state-number */
  YYCODETYPE major;      /* The major token value.  This is the code
                         ** number for the token at this stack level */
  YYMINORTYPE minor;     /* The user-supplied minor token value.  This
                         ** is the value of the token  */
};
typedef struct yyStackEntry yyStackEntry;

/* The state of the parser is completely contained in an instance of
** the following structure */
struct yyParser {
  int yyidx;                    /* Index of top element in stack */
#ifdef YYTRACKMAXSTACKDEPTH
  int yyidxMax;                 /* Maximum value of yyidx */
#endif
  int yyerrcnt;                 /* Shifts left before out of the error */
  LemonARG_SDECL                /* A place to hold %extra_argument */
#if YYSTACKDEPTH<=0
  int yystksz;                  /* Current side of the stack */
  yyStackEntry *yystack;        /* The parser's stack */
#else
  yyStackEntry yystack[YYSTACKDEPTH];  /* The parser's stack */
#endif
};
typedef struct yyParser yyParser;

#ifndef NDEBUG
#include <stdio.h>
static FILE *yyTraceFILE = 0;
static char *yyTracePrompt = 0;
#endif /* NDEBUG */

#ifndef NDEBUG
/* 
** Turn parser tracing on by giving a stream to which to write the trace
** and a prompt to preface each trace message.  Tracing is turned off
** by making either argument NULL 
**
** Inputs:
** <ul>
** <li> A FILE* to which trace output should be written.
**      If NULL, then tracing is turned off.
** <li> A prefix string written at the beginning of every
**      line of trace output.  If NULL, then tracing is
**      turned off.
** </ul>
**
** Outputs:
** None.
*/
void LemonTrace(FILE *TraceFILE, char *zTracePrompt){
  yyTraceFILE = TraceFILE;
  yyTracePrompt = zTracePrompt;
  if( yyTraceFILE==0 ) yyTracePrompt = 0;
  else if( yyTracePrompt==0 ) yyTraceFILE = 0;
}
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing shifts, the names of all terminals and nonterminals
** are required.  The following table supplies these names */
static const char *const yyTokenName[] = { 
  "$",             "OR",            "AND",           "EQ",          
  "NEQ",           "L",             "G",             "LEQ",         
  "GEQ",           "RANGEOP",       "PLUS",          "MINUS",       
  "MUL",           "DIV",           "MOD",           "NOT",         
  "EXP",           "TERMINATION",   "UNINITIALIZED",  "WARNING",     
  "DOT",           "EOS",           "NL",            "SCOLON",      
  "DO",            "END",           "ASSIG",         "GLOBAL",      
  "IDENT",         "LOCAL",         "WHILE",         "REPEAT",      
  "UNTIL",         "FOR",           "IN",            "IF",          
  "THEN",          "ELSE",          "ELSEIF",        "RETURN",      
  "NEXT",          "BREAK",         "CLASS",         "PL",          
  "PR",            "DEF",           "COMMA",         "STRING",      
  "SBL",           "SBR",           "CBL",           "CBR",         
  "NIL",           "FALSE",         "TRUE",          "INT",         
  "REAL",          "COLON",         "PIPE",          "error",       
  "chunk",         "block",         "stat_list",     "stat",        
  "exp",           "var",           "else",          "class_body",  
  "func_body",     "ident_list",    "func_ident",    "function",    
  "functioncall",  "prefixexp",     "exp_list",      "dict_list",   
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "chunk ::= TERMINATION UNINITIALIZED WARNING DOT",
 /*   1 */ "chunk ::= block EOS",
 /*   2 */ "block ::= stat_list",
 /*   3 */ "stat_list ::= stat",
 /*   4 */ "stat_list ::= stat_list NL stat",
 /*   5 */ "stat_list ::= stat_list SCOLON stat",
 /*   6 */ "stat ::=",
 /*   7 */ "stat ::= exp",
 /*   8 */ "stat ::= DO block END",
 /*   9 */ "stat ::= var ASSIG exp",
 /*  10 */ "stat ::= GLOBAL IDENT ASSIG exp",
 /*  11 */ "stat ::= GLOBAL IDENT",
 /*  12 */ "stat ::= LOCAL IDENT",
 /*  13 */ "stat ::= LOCAL IDENT ASSIG exp",
 /*  14 */ "stat ::= WHILE exp DO block END",
 /*  15 */ "stat ::= REPEAT block UNTIL exp",
 /*  16 */ "stat ::= FOR IDENT IN exp DO block END",
 /*  17 */ "stat ::= IF exp THEN block else END",
 /*  18 */ "else ::=",
 /*  19 */ "else ::= ELSE block",
 /*  20 */ "else ::= ELSEIF exp THEN block else",
 /*  21 */ "stat ::= RETURN exp",
 /*  22 */ "stat ::= NEXT",
 /*  23 */ "stat ::= BREAK",
 /*  24 */ "stat ::= CLASS IDENT class_body",
 /*  25 */ "stat ::= CLASS IDENT PL exp PR class_body",
 /*  26 */ "class_body ::= NL END",
 /*  27 */ "class_body ::= SCOLON END",
 /*  28 */ "class_body ::= NL DEF IDENT func_body class_body",
 /*  29 */ "class_body ::= SCOLON DEF IDENT func_body class_body",
 /*  30 */ "class_body ::= NL IDENT ASSIG exp class_body",
 /*  31 */ "class_body ::= SCOLON IDENT ASSIG exp class_body",
 /*  32 */ "ident_list ::= IDENT",
 /*  33 */ "ident_list ::= ident_list COMMA IDENT",
 /*  34 */ "stat ::= DEF func_ident func_body",
 /*  35 */ "stat ::= LOCAL DEF IDENT func_body",
 /*  36 */ "func_ident ::= IDENT",
 /*  37 */ "func_ident ::= func_ident DOT IDENT",
 /*  38 */ "function ::= DEF func_body",
 /*  39 */ "func_body ::= PL PR block END",
 /*  40 */ "func_body ::= PL ident_list PR block END",
 /*  41 */ "functioncall ::= prefixexp PL PR",
 /*  42 */ "functioncall ::= prefixexp PL exp_list PR",
 /*  43 */ "prefixexp ::= var",
 /*  44 */ "prefixexp ::= functioncall",
 /*  45 */ "prefixexp ::= PL exp PR",
 /*  46 */ "prefixexp ::= STRING",
 /*  47 */ "prefixexp ::= SBL SBR",
 /*  48 */ "prefixexp ::= SBL exp_list SBR",
 /*  49 */ "prefixexp ::= CBL CBR",
 /*  50 */ "prefixexp ::= CBL dict_list CBR",
 /*  51 */ "exp ::= prefixexp",
 /*  52 */ "exp ::= function",
 /*  53 */ "exp ::= NIL",
 /*  54 */ "exp ::= FALSE",
 /*  55 */ "exp ::= TRUE",
 /*  56 */ "exp ::= INT",
 /*  57 */ "exp ::= REAL",
 /*  58 */ "dict_list ::= exp COLON exp",
 /*  59 */ "dict_list ::= dict_list COMMA exp COLON exp",
 /*  60 */ "exp ::= PIPE exp PIPE",
 /*  61 */ "exp ::= exp OR exp",
 /*  62 */ "exp ::= exp AND exp",
 /*  63 */ "exp ::= exp L exp",
 /*  64 */ "exp ::= exp G exp",
 /*  65 */ "exp ::= exp LEQ exp",
 /*  66 */ "exp ::= exp GEQ exp",
 /*  67 */ "exp ::= exp NEQ exp",
 /*  68 */ "exp ::= exp EQ exp",
 /*  69 */ "exp ::= exp RANGEOP exp",
 /*  70 */ "exp ::= exp PLUS exp",
 /*  71 */ "exp ::= exp MINUS exp",
 /*  72 */ "exp ::= exp MUL exp",
 /*  73 */ "exp ::= exp DIV exp",
 /*  74 */ "exp ::= exp MOD exp",
 /*  75 */ "exp ::= exp EXP exp",
 /*  76 */ "exp ::= NOT exp",
 /*  77 */ "exp ::= MINUS exp",
 /*  78 */ "var ::= IDENT",
 /*  79 */ "var ::= prefixexp DOT IDENT",
 /*  80 */ "var ::= prefixexp SBL exp SBR",
 /*  81 */ "exp_list ::= exp",
 /*  82 */ "exp_list ::= exp_list COMMA exp",
};
#endif /* NDEBUG */


#if YYSTACKDEPTH<=0
/*
** Try to increase the size of the parser stack.
*/
static void yyGrowStack(yyParser *p){
  int newSize;
  yyStackEntry *pNew;

  newSize = p->yystksz*2 + 100;
  pNew = realloc(p->yystack, newSize*sizeof(pNew[0]));
  if( pNew ){
    p->yystack = pNew;
    p->yystksz = newSize;
#ifndef NDEBUG
    if( yyTraceFILE ){
      fprintf(yyTraceFILE,"%sStack grows to %d entries!\n",
              yyTracePrompt, p->yystksz);
    }
#endif
  }
}
#endif

/* 
** This function allocates a new parser.
** The only argument is a pointer to a function which works like
** malloc.
**
** Inputs:
** A pointer to the function used to allocate memory.
**
** Outputs:
** A pointer to a parser.  This pointer is used in subsequent calls
** to Lemon and LemonFree.
*/
void *LemonAlloc(void *(*mallocProc)(size_t)){
  yyParser *pParser;
  pParser = (yyParser*)(*mallocProc)( (size_t)sizeof(yyParser) );
  if( pParser ){
    pParser->yyidx = -1;
#ifdef YYTRACKMAXSTACKDEPTH
    pParser->yyidxMax = 0;
#endif
#if YYSTACKDEPTH<=0
    pParser->yystack = NULL;
    pParser->yystksz = 0;
    yyGrowStack(pParser);
#endif
  }
  return pParser;
}

/* The following function deletes the value associated with a
** symbol.  The symbol can be either a terminal or nonterminal.
** "yymajor" is the symbol code, and "yypminor" is a pointer to
** the value.
*/
static void yy_destructor(
  yyParser *yypParser,    /* The parser */
  YYCODETYPE yymajor,     /* Type code for object to destroy */
  YYMINORTYPE *yypminor   /* The object to be destroyed */
){
  LemonARG_FETCH;
  switch( yymajor ){
    /* Here is inserted the actions which take place when a
    ** terminal or non-terminal is destroyed.  This can happen
    ** when the symbol is popped from the stack during a
    ** reduce or during error processing or when a parser is 
    ** being destroyed before it is finished parsing.
    **
    ** Note: during a reduce, the only symbols destroyed are those
    ** which appear on the RHS of the rule, but which are not used
    ** inside the C code.
    */
    default:  break;   /* If no destructor action specified: do nothing */
  }
}

/*
** Pop the parser's stack once.
**
** If there is a destructor routine associated with the token which
** is popped from the stack, then call it.
**
** Return the major token number for the symbol popped.
*/
static int yy_pop_parser_stack(yyParser *pParser){
  YYCODETYPE yymajor;
  yyStackEntry *yytos = &pParser->yystack[pParser->yyidx];

  if( pParser->yyidx<0 ) return 0;
#ifndef NDEBUG
  if( yyTraceFILE && pParser->yyidx>=0 ){
    fprintf(yyTraceFILE,"%sPopping %s\n",
      yyTracePrompt,
      yyTokenName[yytos->major]);
  }
#endif
  yymajor = yytos->major;
  yy_destructor(pParser, yymajor, &yytos->minor);
  pParser->yyidx--;
  return yymajor;
}

/* 
** Deallocate and destroy a parser.  Destructors are all called for
** all stack elements before shutting the parser down.
**
** Inputs:
** <ul>
** <li>  A pointer to the parser.  This should be a pointer
**       obtained from LemonAlloc.
** <li>  A pointer to a function used to reclaim memory obtained
**       from malloc.
** </ul>
*/
void LemonFree(
  void *p,                    /* The parser to be deleted */
  void (*freeProc)(void*)     /* Function used to reclaim memory */
){
  yyParser *pParser = (yyParser*)p;
  if( pParser==0 ) return;
  while( pParser->yyidx>=0 ) yy_pop_parser_stack(pParser);
#if YYSTACKDEPTH<=0
  free(pParser->yystack);
#endif
  (*freeProc)((void*)pParser);
}

/*
** Return the peak depth of the stack for a parser.
*/
#ifdef YYTRACKMAXSTACKDEPTH
int LemonStackPeak(void *p){
  yyParser *pParser = (yyParser*)p;
  return pParser->yyidxMax;
}
#endif

/*
** Find the appropriate action for a parser given the terminal
** look-ahead token iLookAhead.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
*/
static int yy_find_shift_action(
  yyParser *pParser,        /* The parser */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
  int stateno = pParser->yystack[pParser->yyidx].stateno;
 
  if( stateno>YY_SHIFT_COUNT
   || (i = yy_shift_ofst[stateno])==YY_SHIFT_USE_DFLT ){
    return yy_default[stateno];
  }
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
  if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
    if( iLookAhead>0 ){
#ifdef YYFALLBACK
      YYCODETYPE iFallback;            /* Fallback token */
      if( iLookAhead<sizeof(yyFallback)/sizeof(yyFallback[0])
             && (iFallback = yyFallback[iLookAhead])!=0 ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE, "%sFALLBACK %s => %s\n",
             yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[iFallback]);
        }
#endif
        return yy_find_shift_action(pParser, iFallback);
      }
#endif
#ifdef YYWILDCARD
      {
        int j = i - iLookAhead + YYWILDCARD;
        if( 
#if YY_SHIFT_MIN+YYWILDCARD<0
          j>=0 &&
#endif
#if YY_SHIFT_MAX+YYWILDCARD>=YY_ACTTAB_COUNT
          j<YY_ACTTAB_COUNT &&
#endif
          yy_lookahead[j]==YYWILDCARD
        ){
#ifndef NDEBUG
          if( yyTraceFILE ){
            fprintf(yyTraceFILE, "%sWILDCARD %s => %s\n",
               yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[YYWILDCARD]);
          }
#endif /* NDEBUG */
          return yy_action[j];
        }
      }
#endif /* YYWILDCARD */
    }
    return yy_default[stateno];
  }else{
    return yy_action[i];
  }
}

/*
** Find the appropriate action for a parser given the non-terminal
** look-ahead token iLookAhead.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
*/
static int yy_find_reduce_action(
  int stateno,              /* Current state number */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
#ifdef YYERRORSYMBOL
  if( stateno>YY_REDUCE_COUNT ){
    return yy_default[stateno];
  }
#else
  assert( stateno<=YY_REDUCE_COUNT );
#endif
  i = yy_reduce_ofst[stateno];
  assert( i!=YY_REDUCE_USE_DFLT );
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
#ifdef YYERRORSYMBOL
  if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
    return yy_default[stateno];
  }
#else
  assert( i>=0 && i<YY_ACTTAB_COUNT );
  assert( yy_lookahead[i]==iLookAhead );
#endif
  return yy_action[i];
}

/*
** The following routine is called if the stack overflows.
*/
static void yyStackOverflow(yyParser *yypParser, YYMINORTYPE *yypMinor){
   LemonARG_FETCH;
   yypParser->yyidx--;
#ifndef NDEBUG
   if( yyTraceFILE ){
     fprintf(yyTraceFILE,"%sStack Overflow!\n",yyTracePrompt);
   }
#endif
   while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
   /* Here code is inserted which will execute if the parser
   ** stack every overflows */
   LemonARG_STORE; /* Suppress warning about unused %extra_argument var */
}

/*
** Perform a shift action.
*/
static void yy_shift(
  yyParser *yypParser,          /* The parser to be shifted */
  int yyNewState,               /* The new state to shift in */
  int yyMajor,                  /* The major token to shift in */
  YYMINORTYPE *yypMinor         /* Pointer to the minor token to shift in */
){
  yyStackEntry *yytos;
  yypParser->yyidx++;
#ifdef YYTRACKMAXSTACKDEPTH
  if( yypParser->yyidx>yypParser->yyidxMax ){
    yypParser->yyidxMax = yypParser->yyidx;
  }
#endif
#if YYSTACKDEPTH>0 
  if( yypParser->yyidx>=YYSTACKDEPTH ){
    yyStackOverflow(yypParser, yypMinor);
    return;
  }
#else
  if( yypParser->yyidx>=yypParser->yystksz ){
    yyGrowStack(yypParser);
    if( yypParser->yyidx>=yypParser->yystksz ){
      yyStackOverflow(yypParser, yypMinor);
      return;
    }
  }
#endif
  yytos = &yypParser->yystack[yypParser->yyidx];
  yytos->stateno = (YYACTIONTYPE)yyNewState;
  yytos->major = (YYCODETYPE)yyMajor;
  yytos->minor = *yypMinor;
#ifndef NDEBUG
  if( yyTraceFILE && yypParser->yyidx>0 ){
    int i;
    fprintf(yyTraceFILE,"%sShift %d\n",yyTracePrompt,yyNewState);
    fprintf(yyTraceFILE,"%sStack:",yyTracePrompt);
    for(i=1; i<=yypParser->yyidx; i++)
      fprintf(yyTraceFILE," %s",yyTokenName[yypParser->yystack[i].major]);
    fprintf(yyTraceFILE,"\n");
  }
#endif
}

/* The following table contains information about every rule that
** is used during the reduce.
*/
static const struct {
  YYCODETYPE lhs;         /* Symbol on the left-hand side of the rule */
  unsigned char nrhs;     /* Number of right-hand side symbols in the rule */
} yyRuleInfo[] = {
  { 60, 4 },
  { 60, 2 },
  { 61, 1 },
  { 62, 1 },
  { 62, 3 },
  { 62, 3 },
  { 63, 0 },
  { 63, 1 },
  { 63, 3 },
  { 63, 3 },
  { 63, 4 },
  { 63, 2 },
  { 63, 2 },
  { 63, 4 },
  { 63, 5 },
  { 63, 4 },
  { 63, 7 },
  { 63, 6 },
  { 66, 0 },
  { 66, 2 },
  { 66, 5 },
  { 63, 2 },
  { 63, 1 },
  { 63, 1 },
  { 63, 3 },
  { 63, 6 },
  { 67, 2 },
  { 67, 2 },
  { 67, 5 },
  { 67, 5 },
  { 67, 5 },
  { 67, 5 },
  { 69, 1 },
  { 69, 3 },
  { 63, 3 },
  { 63, 4 },
  { 70, 1 },
  { 70, 3 },
  { 71, 2 },
  { 68, 4 },
  { 68, 5 },
  { 72, 3 },
  { 72, 4 },
  { 73, 1 },
  { 73, 1 },
  { 73, 3 },
  { 73, 1 },
  { 73, 2 },
  { 73, 3 },
  { 73, 2 },
  { 73, 3 },
  { 64, 1 },
  { 64, 1 },
  { 64, 1 },
  { 64, 1 },
  { 64, 1 },
  { 64, 1 },
  { 64, 1 },
  { 75, 3 },
  { 75, 5 },
  { 64, 3 },
  { 64, 3 },
  { 64, 3 },
  { 64, 3 },
  { 64, 3 },
  { 64, 3 },
  { 64, 3 },
  { 64, 3 },
  { 64, 3 },
  { 64, 3 },
  { 64, 3 },
  { 64, 3 },
  { 64, 3 },
  { 64, 3 },
  { 64, 3 },
  { 64, 3 },
  { 64, 2 },
  { 64, 2 },
  { 65, 1 },
  { 65, 3 },
  { 65, 4 },
  { 74, 1 },
  { 74, 3 },
};

static void yy_accept(yyParser*);  /* Forward Declaration */

/*
** Perform a reduce action and the shift that must immediately
** follow the reduce.
*/
static void yy_reduce(
  yyParser *yypParser,         /* The parser */
  int yyruleno                 /* Number of the rule by which to reduce */
){
  int yygoto;                     /* The next state */
  int yyact;                      /* The next action */
  YYMINORTYPE yygotominor;        /* The LHS of the rule reduced */
  yyStackEntry *yymsp;            /* The top of the parser's stack */
  int yysize;                     /* Amount to pop the stack */
  LemonARG_FETCH;
  yymsp = &yypParser->yystack[yypParser->yyidx];
#ifndef NDEBUG
  if( yyTraceFILE && yyruleno>=0 
        && yyruleno<(int)(sizeof(yyRuleName)/sizeof(yyRuleName[0])) ){
    fprintf(yyTraceFILE, "%sReduce [%s].\n", yyTracePrompt,
      yyRuleName[yyruleno]);
  }
#endif /* NDEBUG */

  /* Silence complaints from purify about yygotominor being uninitialized
  ** in some cases when it is copied into the stack after the following
  ** switch.  yygotominor is uninitialized when a rule reduces that does
  ** not set the value of its left-hand side nonterminal.  Leaving the
  ** value of the nonterminal uninitialized is utterly harmless as long
  ** as the value is never used.  So really the only thing this code
  ** accomplishes is to quieten purify.  
  **
  ** 2007-01-16:  The wireshark project (www.wireshark.org) reports that
  ** without this code, their parser segfaults.  I'm not sure what there
  ** parser is doing to make this happen.  This is the second bug report
  ** from wireshark this week.  Clearly they are stressing Lemon in ways
  ** that it has not been previously stressed...  (SQLite ticket #2172)
  */
  /*memset(&yygotominor, 0, sizeof(yygotominor));*/
  yygotominor = yyzerominor;


  switch( yyruleno ){
  /* Beginning here are the reduction cases.  A typical example
  ** follows:
  **   case 0:
  **  #line <lineno> <grammarfile>
  **     { ... }           // User supplied code
  **  #line <lineno> <thisfile>
  **     break;
  */
      case 1: /* chunk ::= block EOS */
#line 68 "lparser.y"
{ *currentNode = yygotominor.yy0 = yymsp[-1].minor.yy132; }
#line 1067 "lparser.c"
        break;
      case 2: /* block ::= stat_list */
#line 72 "lparser.y"
{ yygotominor.yy132 = new BlockNode(yymsp[0].minor.yy115);  }
#line 1072 "lparser.c"
        break;
      case 3: /* stat_list ::= stat */
#line 74 "lparser.y"
{ yygotominor.yy115 = new NodeList<>(); if(yymsp[0].minor.yy0){ yygotominor.yy115->push_back(yymsp[0].minor.yy0); }  }
#line 1077 "lparser.c"
        break;
      case 4: /* stat_list ::= stat_list NL stat */
      case 5: /* stat_list ::= stat_list SCOLON stat */ yytestcase(yyruleno==5);
#line 75 "lparser.y"
{ yygotominor.yy115 = yymsp[-2].minor.yy115;  if(yymsp[0].minor.yy0){ yygotominor.yy115->push_back(yymsp[0].minor.yy0); }  }
#line 1083 "lparser.c"
        break;
      case 6: /* stat ::= */
      case 18: /* else ::= */ yytestcase(yyruleno==18);
#line 79 "lparser.y"
{ yygotominor.yy0 = NULL; }
#line 1089 "lparser.c"
        break;
      case 7: /* stat ::= exp */
#line 80 "lparser.y"
{ yygotominor.yy0 = new StatNode(yymsp[0].minor.yy0); }
#line 1094 "lparser.c"
        break;
      case 8: /* stat ::= DO block END */
#line 81 "lparser.y"
{ yygotominor.yy0 = yymsp[-1].minor.yy132; yymsp[-1].minor.yy132->createScope(); }
#line 1099 "lparser.c"
        break;
      case 9: /* stat ::= var ASSIG exp */
#line 84 "lparser.y"
{ yygotominor.yy0 = new AssignNode(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1104 "lparser.c"
        break;
      case 10: /* stat ::= GLOBAL IDENT ASSIG exp */
#line 85 "lparser.y"
{ yygotominor.yy0 = new AssignNode(new VarNode(yymsp[-2].minor.yy0), yymsp[0].minor.yy0); }
#line 1109 "lparser.c"
        break;
      case 11: /* stat ::= GLOBAL IDENT */
#line 86 "lparser.y"
{ yygotominor.yy0 = new AssignNode(new VarNode(yymsp[0].minor.yy0), new NilLitNode()); }
#line 1114 "lparser.c"
        break;
      case 12: /* stat ::= LOCAL IDENT */
#line 88 "lparser.y"
{ yygotominor.yy0 = new DeclNode(yymsp[0].minor.yy0, NULL); }
#line 1119 "lparser.c"
        break;
      case 13: /* stat ::= LOCAL IDENT ASSIG exp */
#line 89 "lparser.y"
{ yygotominor.yy0 = new DeclNode(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1124 "lparser.c"
        break;
      case 14: /* stat ::= WHILE exp DO block END */
#line 98 "lparser.y"
{ yygotominor.yy0 = new WhileNode(yymsp[-3].minor.yy0, yymsp[-1].minor.yy132); }
#line 1129 "lparser.c"
        break;
      case 15: /* stat ::= REPEAT block UNTIL exp */
#line 100 "lparser.y"
{ yygotominor.yy0 = new RepeatNode(yymsp[0].minor.yy0, yymsp[-2].minor.yy132); }
#line 1134 "lparser.c"
        break;
      case 16: /* stat ::= FOR IDENT IN exp DO block END */
#line 102 "lparser.y"
{ yygotominor.yy0 = new ForNode(yymsp[-5].minor.yy0, yymsp[-3].minor.yy0, yymsp[-1].minor.yy132); }
#line 1139 "lparser.c"
        break;
      case 17: /* stat ::= IF exp THEN block else END */
#line 104 "lparser.y"
{ yygotominor.yy0 = new IfNode(yymsp[-4].minor.yy0, yymsp[-2].minor.yy132, yymsp[-1].minor.yy0); }
#line 1144 "lparser.c"
        break;
      case 19: /* else ::= ELSE block */
#line 106 "lparser.y"
{ yygotominor.yy0 = yymsp[0].minor.yy132; }
#line 1149 "lparser.c"
        break;
      case 20: /* else ::= ELSEIF exp THEN block else */
#line 107 "lparser.y"
{ yygotominor.yy0 = new IfNode(yymsp[-3].minor.yy0, yymsp[-1].minor.yy132, yymsp[0].minor.yy0); }
#line 1154 "lparser.c"
        break;
      case 21: /* stat ::= RETURN exp */
#line 110 "lparser.y"
{ yygotominor.yy0 = new ReturnNode(yymsp[0].minor.yy0); }
#line 1159 "lparser.c"
        break;
      case 24: /* stat ::= CLASS IDENT class_body */
#line 116 "lparser.y"
{ yygotominor.yy0 = new ClassNode(yymsp[-1].minor.yy0, NULL, yymsp[0].minor.yy88); }
#line 1164 "lparser.c"
        break;
      case 25: /* stat ::= CLASS IDENT PL exp PR class_body */
#line 117 "lparser.y"
{ yygotominor.yy0 = new ClassNode(yymsp[-4].minor.yy0, yymsp[-2].minor.yy0, yymsp[0].minor.yy88); }
#line 1169 "lparser.c"
        break;
      case 26: /* class_body ::= NL END */
      case 27: /* class_body ::= SCOLON END */ yytestcase(yyruleno==27);
#line 118 "lparser.y"
{ yygotominor.yy88 = new std::vector<std::pair<Node*, Node*> >(); }
#line 1175 "lparser.c"
        break;
      case 28: /* class_body ::= NL DEF IDENT func_body class_body */
      case 29: /* class_body ::= SCOLON DEF IDENT func_body class_body */ yytestcase(yyruleno==29);
#line 120 "lparser.y"
{ yygotominor.yy88 = yymsp[0].minor.yy88; yymsp[0].minor.yy88->push_back(std::make_pair(yymsp[-2].minor.yy0, yymsp[-1].minor.yy0)); }
#line 1181 "lparser.c"
        break;
      case 30: /* class_body ::= NL IDENT ASSIG exp class_body */
      case 31: /* class_body ::= SCOLON IDENT ASSIG exp class_body */ yytestcase(yyruleno==31);
#line 122 "lparser.y"
{ yygotominor.yy88 = yymsp[0].minor.yy88; yymsp[0].minor.yy88->push_back(std::make_pair(yymsp[-3].minor.yy0, yymsp[-1].minor.yy0)); }
#line 1187 "lparser.c"
        break;
      case 32: /* ident_list ::= IDENT */
#line 128 "lparser.y"
{
    yygotominor.yy69 = new NodeList<IdentNode>();

    assert(dynamic_cast<IdentNode*>(yymsp[0].minor.yy0));
    yygotominor.yy69->push_back(static_cast<IdentNode*>(yymsp[0].minor.yy0));

}
#line 1198 "lparser.c"
        break;
      case 33: /* ident_list ::= ident_list COMMA IDENT */
#line 136 "lparser.y"
{
    yygotominor.yy69 = yymsp[-2].minor.yy69;

    assert(dynamic_cast<IdentNode*>(yymsp[0].minor.yy0));
    yygotominor.yy69->push_back(static_cast<IdentNode*>(yymsp[0].minor.yy0));
}
#line 1208 "lparser.c"
        break;
      case 34: /* stat ::= DEF func_ident func_body */
#line 143 "lparser.y"
{ yygotominor.yy0 = new AssignNode(yymsp[-1].minor.yy0, yymsp[0].minor.yy0); }
#line 1213 "lparser.c"
        break;
      case 35: /* stat ::= LOCAL DEF IDENT func_body */
#line 144 "lparser.y"
{ yygotominor.yy0 = new DeclNode(yymsp[-1].minor.yy0, yymsp[0].minor.yy0); }
#line 1218 "lparser.c"
        break;
      case 36: /* func_ident ::= IDENT */
      case 78: /* var ::= IDENT */ yytestcase(yyruleno==78);
#line 145 "lparser.y"
{ yygotominor.yy0 = new VarNode(yymsp[0].minor.yy0); }
#line 1224 "lparser.c"
        break;
      case 37: /* func_ident ::= func_ident DOT IDENT */
      case 79: /* var ::= prefixexp DOT IDENT */ yytestcase(yyruleno==79);
#line 146 "lparser.y"
{ yygotominor.yy0 = new MemberAccessNode(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1230 "lparser.c"
        break;
      case 38: /* function ::= DEF func_body */
      case 43: /* prefixexp ::= var */ yytestcase(yyruleno==43);
      case 44: /* prefixexp ::= functioncall */ yytestcase(yyruleno==44);
      case 46: /* prefixexp ::= STRING */ yytestcase(yyruleno==46);
      case 51: /* exp ::= prefixexp */ yytestcase(yyruleno==51);
      case 52: /* exp ::= function */ yytestcase(yyruleno==52);
      case 56: /* exp ::= INT */ yytestcase(yyruleno==56);
      case 57: /* exp ::= REAL */ yytestcase(yyruleno==57);
#line 149 "lparser.y"
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
#line 1242 "lparser.c"
        break;
      case 39: /* func_body ::= PL PR block END */
#line 150 "lparser.y"
{ yygotominor.yy0 = new FuncNode(NULL, yymsp[-1].minor.yy132); }
#line 1247 "lparser.c"
        break;
      case 40: /* func_body ::= PL ident_list PR block END */
#line 151 "lparser.y"
{ yygotominor.yy0 = new FuncNode(yymsp[-3].minor.yy69, yymsp[-1].minor.yy132); }
#line 1252 "lparser.c"
        break;
      case 41: /* functioncall ::= prefixexp PL PR */
#line 153 "lparser.y"
{ yygotominor.yy0 = new CallNode(yymsp[-2].minor.yy0, NULL); }
#line 1257 "lparser.c"
        break;
      case 42: /* functioncall ::= prefixexp PL exp_list PR */
#line 154 "lparser.y"
{ yygotominor.yy0 = new CallNode(yymsp[-3].minor.yy0, yymsp[-1].minor.yy115); }
#line 1262 "lparser.c"
        break;
      case 45: /* prefixexp ::= PL exp PR */
#line 158 "lparser.y"
{ yygotominor.yy0 = yymsp[-1].minor.yy0; }
#line 1267 "lparser.c"
        break;
      case 47: /* prefixexp ::= SBL SBR */
#line 163 "lparser.y"
{ yygotominor.yy0 = new ListConstrNode(NULL); }
#line 1272 "lparser.c"
        break;
      case 48: /* prefixexp ::= SBL exp_list SBR */
#line 164 "lparser.y"
{ yygotominor.yy0 = new ListConstrNode(yymsp[-1].minor.yy115); }
#line 1277 "lparser.c"
        break;
      case 49: /* prefixexp ::= CBL CBR */
#line 165 "lparser.y"
{ yygotominor.yy0 = new DictConstrNode(NULL); }
#line 1282 "lparser.c"
        break;
      case 50: /* prefixexp ::= CBL dict_list CBR */
#line 166 "lparser.y"
{ yygotominor.yy0 = new DictConstrNode(yymsp[-1].minor.yy129); }
#line 1287 "lparser.c"
        break;
      case 53: /* exp ::= NIL */
#line 172 "lparser.y"
{ yygotominor.yy0 = new NilLitNode(); }
#line 1292 "lparser.c"
        break;
      case 54: /* exp ::= FALSE */
#line 173 "lparser.y"
{ yygotominor.yy0 = new BoolLitNode(false); }
#line 1297 "lparser.c"
        break;
      case 55: /* exp ::= TRUE */
#line 174 "lparser.y"
{ yygotominor.yy0 = new BoolLitNode(true); }
#line 1302 "lparser.c"
        break;
      case 58: /* dict_list ::= exp COLON exp */
#line 181 "lparser.y"
{ yygotominor.yy129 = new NodeDictList(); yygotominor.yy129->push_back(std::make_pair(yymsp[-2].minor.yy0, yymsp[0].minor.yy0)); }
#line 1307 "lparser.c"
        break;
      case 59: /* dict_list ::= dict_list COMMA exp COLON exp */
#line 182 "lparser.y"
{ yygotominor.yy129 = yymsp[-4].minor.yy129; yygotominor.yy129->push_back(std::make_pair(yymsp[-2].minor.yy0, yymsp[0].minor.yy0)); }
#line 1312 "lparser.c"
        break;
      case 60: /* exp ::= PIPE exp PIPE */
#line 186 "lparser.y"
{ yygotominor.yy0 = new UnOpNode<'|'>(yymsp[-1].minor.yy0); }
#line 1317 "lparser.c"
        break;
      case 61: /* exp ::= exp OR exp */
#line 188 "lparser.y"
{ yygotominor.yy0 = new OrNode(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1322 "lparser.c"
        break;
      case 62: /* exp ::= exp AND exp */
#line 189 "lparser.y"
{ yygotominor.yy0 = new AndNode(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1327 "lparser.c"
        break;
      case 63: /* exp ::= exp L exp */
#line 191 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'<'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1332 "lparser.c"
        break;
      case 64: /* exp ::= exp G exp */
#line 192 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'>'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1337 "lparser.c"
        break;
      case 65: /* exp ::= exp LEQ exp */
#line 193 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'<'+'='>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1342 "lparser.c"
        break;
      case 66: /* exp ::= exp GEQ exp */
#line 194 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'>'+'='>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1347 "lparser.c"
        break;
      case 67: /* exp ::= exp NEQ exp */
#line 195 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'!'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1352 "lparser.c"
        break;
      case 68: /* exp ::= exp EQ exp */
#line 196 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'='>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1357 "lparser.c"
        break;
      case 70: /* exp ::= exp PLUS exp */
#line 200 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'+'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1362 "lparser.c"
        break;
      case 71: /* exp ::= exp MINUS exp */
#line 201 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'-'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1367 "lparser.c"
        break;
      case 72: /* exp ::= exp MUL exp */
#line 203 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'*'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1372 "lparser.c"
        break;
      case 73: /* exp ::= exp DIV exp */
#line 204 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'/'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1377 "lparser.c"
        break;
      case 74: /* exp ::= exp MOD exp */
#line 205 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'%'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1382 "lparser.c"
        break;
      case 75: /* exp ::= exp EXP exp */
#line 207 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'^'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1387 "lparser.c"
        break;
      case 76: /* exp ::= NOT exp */
#line 209 "lparser.y"
{ yygotominor.yy0 = new UnOpNode<'!'>(yymsp[0].minor.yy0); }
#line 1392 "lparser.c"
        break;
      case 77: /* exp ::= MINUS exp */
#line 210 "lparser.y"
{ yygotominor.yy0 = new UnOpNode<'-'>(yymsp[0].minor.yy0); }
#line 1397 "lparser.c"
        break;
      case 80: /* var ::= prefixexp SBL exp SBR */
#line 217 "lparser.y"
{ yygotominor.yy0 = new IndexAccessNode(yymsp[-3].minor.yy0, yymsp[-1].minor.yy0); }
#line 1402 "lparser.c"
        break;
      case 81: /* exp_list ::= exp */
#line 220 "lparser.y"
{ yygotominor.yy115 = new NodeList<>(); yygotominor.yy115->push_back(yymsp[0].minor.yy0); }
#line 1407 "lparser.c"
        break;
      case 82: /* exp_list ::= exp_list COMMA exp */
#line 221 "lparser.y"
{ yygotominor.yy115 = yymsp[-2].minor.yy115; yygotominor.yy115->push_back(yymsp[0].minor.yy0); }
#line 1412 "lparser.c"
        break;
      default:
      /* (0) chunk ::= TERMINATION UNINITIALIZED WARNING DOT */ yytestcase(yyruleno==0);
      /* (22) stat ::= NEXT */ yytestcase(yyruleno==22);
      /* (23) stat ::= BREAK */ yytestcase(yyruleno==23);
      /* (69) exp ::= exp RANGEOP exp */ yytestcase(yyruleno==69);
        break;
  };
  yygoto = yyRuleInfo[yyruleno].lhs;
  yysize = yyRuleInfo[yyruleno].nrhs;
  yypParser->yyidx -= yysize;
  yyact = yy_find_reduce_action(yymsp[-yysize].stateno,(YYCODETYPE)yygoto);
  if( yyact < YYNSTATE ){
#ifdef NDEBUG
    /* If we are not debugging and the reduce action popped at least
    ** one element off the stack, then we can push the new element back
    ** onto the stack here, and skip the stack overflow test in yy_shift().
    ** That gives a significant speed improvement. */
    if( yysize ){
      yypParser->yyidx++;
      yymsp -= yysize-1;
      yymsp->stateno = (YYACTIONTYPE)yyact;
      yymsp->major = (YYCODETYPE)yygoto;
      yymsp->minor = yygotominor;
    }else
#endif
    {
      yy_shift(yypParser,yyact,yygoto,&yygotominor);
    }
  }else{
    assert( yyact == YYNSTATE + YYNRULE + 1 );
    yy_accept(yypParser);
  }
}

/*
** The following code executes when the parse fails
*/
#ifndef YYNOERRORRECOVERY
static void yy_parse_failed(
  yyParser *yypParser           /* The parser */
){
  LemonARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sFail!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser fails */
  LemonARG_STORE; /* Suppress warning about unused %extra_argument variable */
}
#endif /* YYNOERRORRECOVERY */

/*
** The following code executes when a syntax error first occurs.
*/
static void yy_syntax_error(
  yyParser *yypParser,           /* The parser */
  int yymajor,                   /* The major type of the error token */
  YYMINORTYPE yyminor            /* The minor type of the error token */
){
  LemonARG_FETCH;
#define TOKEN (yyminor.yy0)
#line 61 "lparser.y"

    throw AYA::ParseError("syntax error");
#line 1481 "lparser.c"
  LemonARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/*
** The following is executed when the parser accepts
*/
static void yy_accept(
  yyParser *yypParser           /* The parser */
){
  LemonARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sAccept!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser accepts */
  LemonARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/* The main parser program.
** The first argument is a pointer to a structure obtained from
** "LemonAlloc" which describes the current state of the parser.
** The second argument is the major token number.  The third is
** the minor token.  The fourth optional argument is whatever the
** user wants (and specified in the grammar) and is available for
** use by the action routines.
**
** Inputs:
** <ul>
** <li> A pointer to the parser (an opaque structure.)
** <li> The major token number.
** <li> The minor token number.
** <li> An option argument of a grammar-specified type.
** </ul>
**
** Outputs:
** None.
*/
void Lemon(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  LemonTOKENTYPE yyminor       /* The value for the token */
  LemonARG_PDECL               /* Optional %extra_argument parameter */
){
  YYMINORTYPE yyminorunion;
  int yyact;            /* The parser action. */
  int yyendofinput;     /* True if we are at the end of input */
#ifdef YYERRORSYMBOL
  int yyerrorhit = 0;   /* True if yymajor has invoked an error */
#endif
  yyParser *yypParser;  /* The parser */

  /* (re)initialize the parser, if necessary */
  yypParser = (yyParser*)yyp;
  if( yypParser->yyidx<0 ){
#if YYSTACKDEPTH<=0
    if( yypParser->yystksz <=0 ){
      /*memset(&yyminorunion, 0, sizeof(yyminorunion));*/
      yyminorunion = yyzerominor;
      yyStackOverflow(yypParser, &yyminorunion);
      return;
    }
#endif
    yypParser->yyidx = 0;
    yypParser->yyerrcnt = -1;
    yypParser->yystack[0].stateno = 0;
    yypParser->yystack[0].major = 0;
  }
  yyminorunion.yy0 = yyminor;
  yyendofinput = (yymajor==0);
  LemonARG_STORE;

#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sInput %s\n",yyTracePrompt,yyTokenName[yymajor]);
  }
#endif

  do{
    yyact = yy_find_shift_action(yypParser,(YYCODETYPE)yymajor);
    if( yyact<YYNSTATE ){
      assert( !yyendofinput );  /* Impossible to shift the $ token */
      yy_shift(yypParser,yyact,yymajor,&yyminorunion);
      yypParser->yyerrcnt--;
      yymajor = YYNOCODE;
    }else if( yyact < YYNSTATE + YYNRULE ){
      yy_reduce(yypParser,yyact-YYNSTATE);
    }else{
      assert( yyact == YY_ERROR_ACTION );
#ifdef YYERRORSYMBOL
      int yymx;
#endif
#ifndef NDEBUG
      if( yyTraceFILE ){
        fprintf(yyTraceFILE,"%sSyntax Error!\n",yyTracePrompt);
      }
#endif
#ifdef YYERRORSYMBOL
      /* A syntax error has occurred.
      ** The response to an error depends upon whether or not the
      ** grammar defines an error token "ERROR".  
      **
      ** This is what we do if the grammar does define ERROR:
      **
      **  * Call the %syntax_error function.
      **
      **  * Begin popping the stack until we enter a state where
      **    it is legal to shift the error symbol, then shift
      **    the error symbol.
      **
      **  * Set the error count to three.
      **
      **  * Begin accepting and shifting new tokens.  No new error
      **    processing will occur until three tokens have been
      **    shifted successfully.
      **
      */
      if( yypParser->yyerrcnt<0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yymx = yypParser->yystack[yypParser->yyidx].major;
      if( yymx==YYERRORSYMBOL || yyerrorhit ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE,"%sDiscard input token %s\n",
             yyTracePrompt,yyTokenName[yymajor]);
        }
#endif
        yy_destructor(yypParser, (YYCODETYPE)yymajor,&yyminorunion);
        yymajor = YYNOCODE;
      }else{
         while(
          yypParser->yyidx >= 0 &&
          yymx != YYERRORSYMBOL &&
          (yyact = yy_find_reduce_action(
                        yypParser->yystack[yypParser->yyidx].stateno,
                        YYERRORSYMBOL)) >= YYNSTATE
        ){
          yy_pop_parser_stack(yypParser);
        }
        if( yypParser->yyidx < 0 || yymajor==0 ){
          yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
          yy_parse_failed(yypParser);
          yymajor = YYNOCODE;
        }else if( yymx!=YYERRORSYMBOL ){
          YYMINORTYPE u2;
          u2.YYERRSYMDT = 0;
          yy_shift(yypParser,yyact,YYERRORSYMBOL,&u2);
        }
      }
      yypParser->yyerrcnt = 3;
      yyerrorhit = 1;
#elif defined(YYNOERRORRECOVERY)
      /* If the YYNOERRORRECOVERY macro is defined, then do not attempt to
      ** do any kind of error recovery.  Instead, simply invoke the syntax
      ** error routine and continue going as if nothing had happened.
      **
      ** Applications can set this macro (for example inside %include) if
      ** they intend to abandon the parse upon the first syntax error seen.
      */
      yy_syntax_error(yypParser,yymajor,yyminorunion);
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      yymajor = YYNOCODE;
      
#else  /* YYERRORSYMBOL is not defined */
      /* This is what we do if the grammar does not define ERROR:
      **
      **  * Report an error message, and throw away the input token.
      **
      **  * If the input token is $, then fail the parse.
      **
      ** As before, subsequent error messages are suppressed until
      ** three input tokens have been successfully shifted.
      */
      if( yypParser->yyerrcnt<=0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yypParser->yyerrcnt = 3;
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      if( yyendofinput ){
        yy_parse_failed(yypParser);
      }
      yymajor = YYNOCODE;
#endif
    }
  }while( yymajor!=YYNOCODE && yypParser->yyidx>=0 );
  return;
}
