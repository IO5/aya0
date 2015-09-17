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
    #include "parser/stat_node.h"
    #include "parser/block_node.h"
    #include "parser/loop_node.h"
    #include "parser/if_node.h"
    #include "parser/return_node.h"
    #include "parser/func_node.h"
    #include "parser/call_node.h"
    #include "parser/decl_node.h"
    #include "parser/list_constr_node.h"

    #ifdef DEBUG
        #include <iostream>
    #endif // DEBUG

    using namespace AYA;
#line 41 "lparser.c"
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
#define YYNOCODE 73
#define YYACTIONTYPE unsigned char
#define LemonTOKENTYPE AYA::Node*
typedef union {
  int yyinit;
  LemonTOKENTYPE yy0;
  NodeList<IdentNode>* yy13;
  BlockNode* yy52;
  NodeList<>* yy59;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define LemonARG_SDECL  AYA::Node** currentNode ;
#define LemonARG_PDECL , AYA::Node** currentNode 
#define LemonARG_FETCH  AYA::Node** currentNode  = yypParser->currentNode 
#define LemonARG_STORE yypParser->currentNode  = currentNode 
#define YYNSTATE 149
#define YYNRULE 71
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
#define YY_ACTTAB_COUNT (667)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    22,   11,   10,   94,   23,  115,  110,  220,   29,   28,
 /*    10 */    27,   26,   25,    8,   24,  109,   93,  126,   77,   19,
 /*    20 */     6,   47,   48,  104,   17,  108,    9,   13,   16,  119,
 /*    30 */   118,  107,   43,   38,  149,  139,  135,  134,  133,  132,
 /*    40 */   131,   12,   22,  101,   39,   36,   23,  141,   27,   26,
 /*    50 */    25,    5,   24,   91,   39,    8,  146,  150,   93,  126,
 /*    60 */    77,   19,    6,  145,   48,  129,   17,  105,   90,   39,
 /*    70 */    16,  119,  118,    1,   43,   38,   14,  139,  135,  134,
 /*    80 */   133,  132,  131,   12,  104,  101,  143,   36,   41,   42,
 /*    90 */    40,   31,   32,   37,   35,   34,   33,   30,   29,   28,
 /*   100 */    27,   26,   25,  128,   24,   24,   42,   40,   31,   32,
 /*   110 */    37,   35,   34,   33,   30,   29,   28,   27,   26,   25,
 /*   120 */   123,   24,  125,  220,  220,  220,  220,   30,   29,   28,
 /*   130 */    27,   26,   25,  137,   24,   42,   40,   31,   32,   37,
 /*   140 */    35,   34,   33,   30,   29,   28,   27,   26,   25,   21,
 /*   150 */    24,    3,   15,   85,   92,   20,   49,   18,    7,   45,
 /*   160 */   147,  127,  122,   42,   40,   31,   32,   37,   35,   34,
 /*   170 */    33,   30,   29,   28,   27,   26,   25,   47,   24,  121,
 /*   180 */    42,   40,   31,   32,   37,   35,   34,   33,   30,   29,
 /*   190 */    28,   27,   26,   25,  116,   24,  113,  112,    4,   31,
 /*   200 */    32,   37,   35,   34,   33,   30,   29,   28,   27,   26,
 /*   210 */    25,  147,   24,   47,  124,    2,   76,   42,   40,   31,
 /*   220 */    32,   37,   35,   34,   33,   30,   29,   28,   27,   26,
 /*   230 */    25,   22,   24,  146,   81,   23,   37,   35,   34,   33,
 /*   240 */    30,   29,   28,   27,   26,   25,   86,   24,  126,  221,
 /*   250 */   106,   82,  144,   63,  102,  117,  114,  222,  222,  222,
 /*   260 */   136,  138,   80,   50,   38,  142,  139,  135,  134,  133,
 /*   270 */   132,  131,   12,  222,  101,   22,   36,  222,  222,   23,
 /*   280 */   148,   63,  102,   84,   82,  144,   63,  102,  136,  138,
 /*   290 */    80,  222,  126,  136,  138,   80,  222,  222,  222,  222,
 /*   300 */   222,  222,  222,  222,  222,  222,  222,   50,   38,  222,
 /*   310 */   139,  135,  134,  133,  132,  131,   12,  130,  101,  222,
 /*   320 */    36,   40,   31,   32,   37,   35,   34,   33,   30,   29,
 /*   330 */    28,   27,   26,   25,   22,   24,  222,  222,   23,  222,
 /*   340 */   222,  222,  222,  103,   82,  144,   63,  102,  222,   61,
 /*   350 */   140,  126,   75,  136,  138,   80,  136,  138,   80,  222,
 /*   360 */   222,  222,  222,  222,  222,  222,   50,   38,  222,  139,
 /*   370 */   135,  134,  133,  132,  131,   12,  222,  101,  222,   36,
 /*   380 */    89,   82,  144,   63,  102,   88,   82,  144,   63,  102,
 /*   390 */   136,  138,   80,  222,  222,  136,  138,   80,   87,   82,
 /*   400 */   144,   63,  102,   46,   82,  144,   63,  102,  136,  138,
 /*   410 */    80,  222,  222,  136,  138,   80,   61,  140,  222,   79,
 /*   420 */   222,  222,  222,  136,  138,   80,  120,   82,  144,   63,
 /*   430 */   102,   44,   82,  144,   63,  102,  136,  138,   80,  222,
 /*   440 */   222,  136,  138,   80,   83,   82,  144,   63,  102,  222,
 /*   450 */    61,  140,  222,   78,  136,  138,   80,  136,  138,   80,
 /*   460 */   111,   63,  102,  222,   64,  140,  222,  222,  136,  138,
 /*   470 */    80,  136,  138,   80,  222,  222,   62,  140,  222,   65,
 /*   480 */   140,  222,  222,  136,  138,   80,  136,  138,   80,   60,
 /*   490 */   140,  222,   55,  140,  222,  222,  136,  138,   80,  136,
 /*   500 */   138,   80,  222,  222,   66,  140,  222,   54,  140,  222,
 /*   510 */   222,  136,  138,   80,  136,  138,   80,   71,  140,  222,
 /*   520 */    70,  140,  222,  222,  136,  138,   80,  136,  138,   80,
 /*   530 */   222,   69,  140,  222,   68,  140,  222,  222,  136,  138,
 /*   540 */    80,  136,  138,   80,  222,  222,   67,  140,  222,   72,
 /*   550 */   140,  222,  222,  136,  138,   80,  136,  138,   80,   74,
 /*   560 */   140,  222,   73,  140,  222,  222,  136,  138,   80,  136,
 /*   570 */   138,   80,  222,  222,  100,  140,  222,   99,  140,  222,
 /*   580 */   222,  136,  138,   80,  136,  138,   80,   98,  140,  222,
 /*   590 */    97,  140,  222,  222,  136,  138,   80,  136,  138,   80,
 /*   600 */   222,   96,  140,  222,   95,  140,  222,  222,  136,  138,
 /*   610 */    80,  136,  138,   80,  222,  222,   59,  140,  222,   58,
 /*   620 */   140,  222,  222,  136,  138,   80,  136,  138,   80,   53,
 /*   630 */   140,  222,   57,  140,  222,  222,  136,  138,   80,  136,
 /*   640 */   138,   80,  222,  222,   52,  140,  222,   56,  140,  222,
 /*   650 */   222,  136,  138,   80,  136,  138,   80,   51,  140,  222,
 /*   660 */   222,  222,  222,  222,  136,  138,   80,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    11,   22,   23,   20,   15,   28,   17,    9,   10,   11,
 /*    10 */    12,   13,   14,   24,   16,   18,   27,   28,   29,   30,
 /*    20 */    31,   44,   33,   42,   35,   19,   45,   44,   39,   40,
 /*    30 */    41,   20,   43,   44,    0,   46,   47,   48,   49,   50,
 /*    40 */    51,   52,   11,   54,   42,   56,   15,   45,   12,   13,
 /*    50 */    14,   24,   16,   28,   42,   24,   28,    0,   27,   28,
 /*    60 */    29,   30,   31,   28,   33,   53,   35,   21,   43,   42,
 /*    70 */    39,   40,   41,   45,   43,   44,   34,   46,   47,   48,
 /*    80 */    49,   50,   51,   52,   42,   54,   25,   56,   26,    1,
 /*    90 */     2,    3,    4,    5,    6,    7,    8,    9,   10,   11,
 /*   100 */    12,   13,   14,   55,   16,   16,    1,    2,    3,    4,
 /*   110 */     5,    6,    7,    8,    9,   10,   11,   12,   13,   14,
 /*   120 */    25,   16,   28,    5,    6,    7,    8,    9,   10,   11,
 /*   130 */    12,   13,   14,   45,   16,    1,    2,    3,    4,    5,
 /*   140 */     6,    7,    8,    9,   10,   11,   12,   13,   14,   26,
 /*   150 */    16,   37,   38,   20,   28,   26,   28,   32,   24,   67,
 /*   160 */    68,   56,   25,    1,    2,    3,    4,    5,    6,    7,
 /*   170 */     8,    9,   10,   11,   12,   13,   14,   44,   16,   25,
 /*   180 */     1,    2,    3,    4,    5,    6,    7,    8,    9,   10,
 /*   190 */    11,   12,   13,   14,   28,   16,   25,   25,   36,    3,
 /*   200 */     4,    5,    6,    7,    8,    9,   10,   11,   12,   13,
 /*   210 */    14,   68,   16,   44,   68,   36,   64,    1,    2,    3,
 /*   220 */     4,    5,    6,    7,    8,    9,   10,   11,   12,   13,
 /*   230 */    14,   11,   16,   28,   64,   15,    5,    6,    7,    8,
 /*   240 */     9,   10,   11,   12,   13,   14,   66,   16,   28,   58,
 /*   250 */    59,   60,   61,   62,   63,   68,   66,   72,   72,   72,
 /*   260 */    69,   70,   71,   43,   44,   45,   46,   47,   48,   49,
 /*   270 */    50,   51,   52,   72,   54,   11,   56,   72,   72,   15,
 /*   280 */    61,   62,   63,   59,   60,   61,   62,   63,   69,   70,
 /*   290 */    71,   72,   28,   69,   70,   71,   72,   72,   72,   72,
 /*   300 */    72,   72,   72,   72,   72,   72,   72,   43,   44,   72,
 /*   310 */    46,   47,   48,   49,   50,   51,   52,   53,   54,   72,
 /*   320 */    56,    2,    3,    4,    5,    6,    7,    8,    9,   10,
 /*   330 */    11,   12,   13,   14,   11,   16,   72,   72,   15,   72,
 /*   340 */    72,   72,   72,   59,   60,   61,   62,   63,   72,   62,
 /*   350 */    63,   28,   65,   69,   70,   71,   69,   70,   71,   72,
 /*   360 */    72,   72,   72,   72,   72,   72,   43,   44,   72,   46,
 /*   370 */    47,   48,   49,   50,   51,   52,   72,   54,   72,   56,
 /*   380 */    59,   60,   61,   62,   63,   59,   60,   61,   62,   63,
 /*   390 */    69,   70,   71,   72,   72,   69,   70,   71,   59,   60,
 /*   400 */    61,   62,   63,   59,   60,   61,   62,   63,   69,   70,
 /*   410 */    71,   72,   72,   69,   70,   71,   62,   63,   72,   65,
 /*   420 */    72,   72,   72,   69,   70,   71,   59,   60,   61,   62,
 /*   430 */    63,   59,   60,   61,   62,   63,   69,   70,   71,   72,
 /*   440 */    72,   69,   70,   71,   59,   60,   61,   62,   63,   72,
 /*   450 */    62,   63,   72,   65,   69,   70,   71,   69,   70,   71,
 /*   460 */    61,   62,   63,   72,   62,   63,   72,   72,   69,   70,
 /*   470 */    71,   69,   70,   71,   72,   72,   62,   63,   72,   62,
 /*   480 */    63,   72,   72,   69,   70,   71,   69,   70,   71,   62,
 /*   490 */    63,   72,   62,   63,   72,   72,   69,   70,   71,   69,
 /*   500 */    70,   71,   72,   72,   62,   63,   72,   62,   63,   72,
 /*   510 */    72,   69,   70,   71,   69,   70,   71,   62,   63,   72,
 /*   520 */    62,   63,   72,   72,   69,   70,   71,   69,   70,   71,
 /*   530 */    72,   62,   63,   72,   62,   63,   72,   72,   69,   70,
 /*   540 */    71,   69,   70,   71,   72,   72,   62,   63,   72,   62,
 /*   550 */    63,   72,   72,   69,   70,   71,   69,   70,   71,   62,
 /*   560 */    63,   72,   62,   63,   72,   72,   69,   70,   71,   69,
 /*   570 */    70,   71,   72,   72,   62,   63,   72,   62,   63,   72,
 /*   580 */    72,   69,   70,   71,   69,   70,   71,   62,   63,   72,
 /*   590 */    62,   63,   72,   72,   69,   70,   71,   69,   70,   71,
 /*   600 */    72,   62,   63,   72,   62,   63,   72,   72,   69,   70,
 /*   610 */    71,   69,   70,   71,   72,   72,   62,   63,   72,   62,
 /*   620 */    63,   72,   72,   69,   70,   71,   69,   70,   71,   62,
 /*   630 */    63,   72,   62,   63,   72,   72,   69,   70,   71,   69,
 /*   640 */    70,   71,   72,   72,   62,   63,   72,   62,   63,   72,
 /*   650 */    72,   69,   70,   71,   69,   70,   71,   62,   63,   72,
 /*   660 */    72,   72,   72,   72,   69,   70,   71,
};
#define YY_SHIFT_USE_DFLT (-24)
#define YY_SHIFT_COUNT (110)
#define YY_SHIFT_MIN   (-23)
#define YY_SHIFT_MAX   (323)
static const short yy_shift_ofst[] = {
 /*     0 */   -11,   31,   31,   31,   31,   31,   31,   31,   31,   31,
 /*    10 */    31,   31,  264,  220,  323,  323,  323,  323,  323,  323,
 /*    20 */   323,  323,  323,  323,  323,  323,  323,  323,  323,  323,
 /*    30 */   323,  323,  323,  323,  323,  323,  323,  323,  323,  323,
 /*    40 */   323,  323,  323,  -23,  114,  133,  114,   28,  205,  169,
 /*    50 */   169,  179,  162,  134,  105,   88,  216,  216,  216,  216,
 /*    60 */   216,  216,  216,  216,  319,  196,  118,  231,  231,  118,
 /*    70 */   118,  118,   -2,   36,   36,   27,   42,   25,   12,    2,
 /*    80 */   -17,  -19,  -21,  172,  171,  166,  154,  137,  125,   95,
 /*    90 */   128,  129,  123,  126,   94,   89,   89,   89,   89,   89,
 /*   100 */    89,   48,   62,   61,   35,   57,   46,   34,   11,    6,
 /*   110 */    -3,
};
#define YY_REDUCE_USE_DFLT (-1)
#define YY_REDUCE_COUNT (50)
#define YY_REDUCE_MIN   (0)
#define YY_REDUCE_MAX   (595)
static const short yy_reduce_ofst[] = {
 /*     0 */   191,  385,  372,  367,  344,  339,  326,  321,  284,  224,
 /*    10 */   399,  219,  388,  354,  287,  595,  585,  582,  570,  567,
 /*    20 */   557,  554,  542,  539,  528,  525,  515,  512,  500,  497,
 /*    30 */   487,  484,  472,  469,  458,  455,  445,  442,  430,  427,
 /*    40 */   417,  414,  402,   92,  190,  187,  180,  170,  152,  146,
 /*    50 */   143,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   155,  155,  155,  155,  155,  155,  155,  155,  155,  155,
 /*    10 */   155,  155,  220,  220,  220,  220,  220,  220,  220,  220,
 /*    20 */   220,  220,  220,  220,  220,  220,  220,  220,  220,  220,
 /*    30 */   220,  220,  220,  220,  220,  220,  220,  220,  220,  220,
 /*    40 */   220,  220,  220,  220,  167,  220,  167,  220,  220,  220,
 /*    50 */   220,  220,  220,  220,  220,  220,  170,  164,  162,  159,
 /*    60 */   219,  218,  158,  156,  199,  200,  201,  206,  205,  204,
 /*    70 */   203,  202,  207,  209,  208,  220,  220,  220,  220,  220,
 /*    80 */   188,  220,  151,  220,  220,  220,  220,  220,  220,  220,
 /*    90 */   220,  161,  160,  220,  220,  215,  214,  213,  212,  211,
 /*   100 */   210,  220,  184,  220,  220,  220,  220,  220,  220,  220,
 /*   110 */   220,  154,  180,  181,  169,  177,  178,  175,  172,  171,
 /*   120 */   168,  166,  165,  163,  176,  217,  216,  198,  197,  196,
 /*   130 */   195,  194,  193,  192,  191,  190,  189,  187,  186,  185,
 /*   140 */   184,  183,  182,  157,  152,  174,  173,  179,  153,
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
  "NEXT",          "BREAK",         "COMMA",         "DEF",         
  "PL",            "PR",            "STRING",        "NIL",         
  "FALSE",         "TRUE",          "INT",           "REAL",        
  "SBL",           "SBR",           "CBL",           "CBR",         
  "PIPE",          "error",         "chunk",         "block",       
  "stat_list",     "stat",          "exp",           "var",         
  "ident_list",    "exp_list",      "else",          "func_ident",  
  "func_body",     "function",      "functioncall",  "prefixexp",   
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
 /*  16 */ "stat ::= FOR ident_list IN exp_list DO block END",
 /*  17 */ "stat ::= IF exp THEN block else END",
 /*  18 */ "else ::=",
 /*  19 */ "else ::= ELSE block",
 /*  20 */ "else ::= ELSEIF exp THEN block else",
 /*  21 */ "stat ::= RETURN exp",
 /*  22 */ "stat ::= NEXT",
 /*  23 */ "stat ::= BREAK",
 /*  24 */ "ident_list ::= IDENT",
 /*  25 */ "ident_list ::= ident_list COMMA IDENT",
 /*  26 */ "stat ::= DEF func_ident func_body",
 /*  27 */ "stat ::= LOCAL DEF IDENT func_body",
 /*  28 */ "func_ident ::= IDENT",
 /*  29 */ "func_ident ::= func_ident DOT IDENT",
 /*  30 */ "function ::= DEF func_body",
 /*  31 */ "func_body ::= PL PR block END",
 /*  32 */ "func_body ::= PL ident_list PR block END",
 /*  33 */ "functioncall ::= prefixexp PL PR",
 /*  34 */ "functioncall ::= prefixexp PL exp_list PR",
 /*  35 */ "prefixexp ::= var",
 /*  36 */ "prefixexp ::= STRING",
 /*  37 */ "prefixexp ::= functioncall",
 /*  38 */ "prefixexp ::= PL exp PR",
 /*  39 */ "exp ::= prefixexp",
 /*  40 */ "exp ::= function",
 /*  41 */ "exp ::= NIL",
 /*  42 */ "exp ::= FALSE",
 /*  43 */ "exp ::= TRUE",
 /*  44 */ "exp ::= INT",
 /*  45 */ "exp ::= REAL",
 /*  46 */ "exp ::= SBL SBR",
 /*  47 */ "exp ::= SBL exp_list SBR",
 /*  48 */ "exp ::= CBL CBR",
 /*  49 */ "exp ::= PIPE exp PIPE",
 /*  50 */ "exp ::= exp OR exp",
 /*  51 */ "exp ::= exp AND exp",
 /*  52 */ "exp ::= exp L exp",
 /*  53 */ "exp ::= exp G exp",
 /*  54 */ "exp ::= exp LEQ exp",
 /*  55 */ "exp ::= exp GEQ exp",
 /*  56 */ "exp ::= exp NEQ exp",
 /*  57 */ "exp ::= exp EQ exp",
 /*  58 */ "exp ::= exp RANGEOP exp",
 /*  59 */ "exp ::= exp PLUS exp",
 /*  60 */ "exp ::= exp MINUS exp",
 /*  61 */ "exp ::= exp MUL exp",
 /*  62 */ "exp ::= exp DIV exp",
 /*  63 */ "exp ::= exp MOD exp",
 /*  64 */ "exp ::= exp EXP exp",
 /*  65 */ "exp ::= NOT exp",
 /*  66 */ "exp ::= MINUS exp",
 /*  67 */ "var ::= IDENT",
 /*  68 */ "var ::= prefixexp DOT IDENT",
 /*  69 */ "exp_list ::= exp",
 /*  70 */ "exp_list ::= exp_list COMMA exp",
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
  { 58, 4 },
  { 58, 2 },
  { 59, 1 },
  { 60, 1 },
  { 60, 3 },
  { 60, 3 },
  { 61, 0 },
  { 61, 1 },
  { 61, 3 },
  { 61, 3 },
  { 61, 4 },
  { 61, 2 },
  { 61, 2 },
  { 61, 4 },
  { 61, 5 },
  { 61, 4 },
  { 61, 7 },
  { 61, 6 },
  { 66, 0 },
  { 66, 2 },
  { 66, 5 },
  { 61, 2 },
  { 61, 1 },
  { 61, 1 },
  { 64, 1 },
  { 64, 3 },
  { 61, 3 },
  { 61, 4 },
  { 67, 1 },
  { 67, 3 },
  { 69, 2 },
  { 68, 4 },
  { 68, 5 },
  { 70, 3 },
  { 70, 4 },
  { 71, 1 },
  { 71, 1 },
  { 71, 1 },
  { 71, 3 },
  { 62, 1 },
  { 62, 1 },
  { 62, 1 },
  { 62, 1 },
  { 62, 1 },
  { 62, 1 },
  { 62, 1 },
  { 62, 2 },
  { 62, 3 },
  { 62, 2 },
  { 62, 3 },
  { 62, 3 },
  { 62, 3 },
  { 62, 3 },
  { 62, 3 },
  { 62, 3 },
  { 62, 3 },
  { 62, 3 },
  { 62, 3 },
  { 62, 3 },
  { 62, 3 },
  { 62, 3 },
  { 62, 3 },
  { 62, 3 },
  { 62, 3 },
  { 62, 3 },
  { 62, 2 },
  { 62, 2 },
  { 63, 1 },
  { 63, 3 },
  { 65, 1 },
  { 65, 3 },
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
#line 64 "lparser.y"
{ *currentNode = yygotominor.yy0 = yymsp[-1].minor.yy52; }
#line 993 "lparser.c"
        break;
      case 2: /* block ::= stat_list */
#line 68 "lparser.y"
{ yygotominor.yy52 = new BlockNode(yymsp[0].minor.yy59);  }
#line 998 "lparser.c"
        break;
      case 3: /* stat_list ::= stat */
#line 70 "lparser.y"
{ yygotominor.yy59 = new NodeList<>(); if(yymsp[0].minor.yy0){ yygotominor.yy59->push_back(yymsp[0].minor.yy0); }  }
#line 1003 "lparser.c"
        break;
      case 4: /* stat_list ::= stat_list NL stat */
      case 5: /* stat_list ::= stat_list SCOLON stat */ yytestcase(yyruleno==5);
#line 71 "lparser.y"
{ yygotominor.yy59 = yymsp[-2].minor.yy59;  if(yymsp[0].minor.yy0){ yygotominor.yy59->push_back(yymsp[0].minor.yy0); }  }
#line 1009 "lparser.c"
        break;
      case 6: /* stat ::= */
      case 11: /* stat ::= GLOBAL IDENT */ yytestcase(yyruleno==11);
      case 18: /* else ::= */ yytestcase(yyruleno==18);
#line 75 "lparser.y"
{ yygotominor.yy0 = NULL; }
#line 1016 "lparser.c"
        break;
      case 7: /* stat ::= exp */
#line 76 "lparser.y"
{ yygotominor.yy0 = new StatNode(yymsp[0].minor.yy0); }
#line 1021 "lparser.c"
        break;
      case 8: /* stat ::= DO block END */
#line 77 "lparser.y"
{ yygotominor.yy0 = yymsp[-1].minor.yy52; yymsp[-1].minor.yy52->createScope(); }
#line 1026 "lparser.c"
        break;
      case 9: /* stat ::= var ASSIG exp */
#line 80 "lparser.y"
{ yygotominor.yy0 = new AssignNode(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1031 "lparser.c"
        break;
      case 10: /* stat ::= GLOBAL IDENT ASSIG exp */
#line 81 "lparser.y"
{ yygotominor.yy0 = new AssignNode(new VarNode(yymsp[-2].minor.yy0), yymsp[0].minor.yy0); }
#line 1036 "lparser.c"
        break;
      case 12: /* stat ::= LOCAL IDENT */
#line 84 "lparser.y"
{ yygotominor.yy0 = new DeclNode(yymsp[0].minor.yy0, NULL); }
#line 1041 "lparser.c"
        break;
      case 13: /* stat ::= LOCAL IDENT ASSIG exp */
#line 85 "lparser.y"
{ yygotominor.yy0 = new DeclNode(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1046 "lparser.c"
        break;
      case 14: /* stat ::= WHILE exp DO block END */
#line 94 "lparser.y"
{ yygotominor.yy0 = new WhileNode(yymsp[-3].minor.yy0, yymsp[-1].minor.yy52); }
#line 1051 "lparser.c"
        break;
      case 15: /* stat ::= REPEAT block UNTIL exp */
#line 96 "lparser.y"
{ yygotominor.yy0 = new RepeatNode(yymsp[0].minor.yy0, yymsp[-2].minor.yy52); }
#line 1056 "lparser.c"
        break;
      case 17: /* stat ::= IF exp THEN block else END */
#line 100 "lparser.y"
{ yygotominor.yy0 = new IfNode(yymsp[-4].minor.yy0, yymsp[-2].minor.yy52, yymsp[-1].minor.yy0); }
#line 1061 "lparser.c"
        break;
      case 19: /* else ::= ELSE block */
#line 102 "lparser.y"
{ yygotominor.yy0 = yymsp[0].minor.yy52; }
#line 1066 "lparser.c"
        break;
      case 20: /* else ::= ELSEIF exp THEN block else */
#line 103 "lparser.y"
{ yygotominor.yy0 = new IfNode(yymsp[-3].minor.yy0, yymsp[-1].minor.yy52, yymsp[0].minor.yy0); }
#line 1071 "lparser.c"
        break;
      case 21: /* stat ::= RETURN exp */
#line 106 "lparser.y"
{ yygotominor.yy0 = new ReturnNode(yymsp[0].minor.yy0); }
#line 1076 "lparser.c"
        break;
      case 24: /* ident_list ::= IDENT */
#line 114 "lparser.y"
{
    yygotominor.yy13 = new NodeList<IdentNode>();

    assert(dynamic_cast<IdentNode*>(yymsp[0].minor.yy0));
    yygotominor.yy13->push_back(static_cast<IdentNode*>(yymsp[0].minor.yy0));

}
#line 1087 "lparser.c"
        break;
      case 25: /* ident_list ::= ident_list COMMA IDENT */
#line 122 "lparser.y"
{
    yygotominor.yy13 = yymsp[-2].minor.yy13;

    assert(dynamic_cast<IdentNode*>(yymsp[0].minor.yy0));
    yygotominor.yy13->push_back(static_cast<IdentNode*>(yymsp[0].minor.yy0));
}
#line 1097 "lparser.c"
        break;
      case 26: /* stat ::= DEF func_ident func_body */
#line 129 "lparser.y"
{ yygotominor.yy0 = new AssignNode(yymsp[-1].minor.yy0, yymsp[0].minor.yy0); }
#line 1102 "lparser.c"
        break;
      case 27: /* stat ::= LOCAL DEF IDENT func_body */
#line 130 "lparser.y"
{ yygotominor.yy0 = new DeclNode(yymsp[-1].minor.yy0, yymsp[0].minor.yy0); }
#line 1107 "lparser.c"
        break;
      case 28: /* func_ident ::= IDENT */
      case 67: /* var ::= IDENT */ yytestcase(yyruleno==67);
#line 131 "lparser.y"
{ yygotominor.yy0 = new VarNode(yymsp[0].minor.yy0); }
#line 1113 "lparser.c"
        break;
      case 29: /* func_ident ::= func_ident DOT IDENT */
      case 68: /* var ::= prefixexp DOT IDENT */ yytestcase(yyruleno==68);
#line 132 "lparser.y"
{ yygotominor.yy0 = new MemberAccessNode(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1119 "lparser.c"
        break;
      case 30: /* function ::= DEF func_body */
      case 35: /* prefixexp ::= var */ yytestcase(yyruleno==35);
      case 36: /* prefixexp ::= STRING */ yytestcase(yyruleno==36);
      case 37: /* prefixexp ::= functioncall */ yytestcase(yyruleno==37);
      case 39: /* exp ::= prefixexp */ yytestcase(yyruleno==39);
      case 40: /* exp ::= function */ yytestcase(yyruleno==40);
      case 44: /* exp ::= INT */ yytestcase(yyruleno==44);
      case 45: /* exp ::= REAL */ yytestcase(yyruleno==45);
#line 135 "lparser.y"
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
#line 1131 "lparser.c"
        break;
      case 31: /* func_body ::= PL PR block END */
#line 136 "lparser.y"
{ yygotominor.yy0 = new FuncNode(NULL, yymsp[-1].minor.yy52); }
#line 1136 "lparser.c"
        break;
      case 32: /* func_body ::= PL ident_list PR block END */
#line 137 "lparser.y"
{ yygotominor.yy0 = new FuncNode(yymsp[-3].minor.yy13, yymsp[-1].minor.yy52); }
#line 1141 "lparser.c"
        break;
      case 33: /* functioncall ::= prefixexp PL PR */
#line 139 "lparser.y"
{ yygotominor.yy0 = new CallNode(yymsp[-2].minor.yy0, NULL); }
#line 1146 "lparser.c"
        break;
      case 34: /* functioncall ::= prefixexp PL exp_list PR */
#line 140 "lparser.y"
{ yygotominor.yy0 = new CallNode(yymsp[-3].minor.yy0, yymsp[-1].minor.yy59); }
#line 1151 "lparser.c"
        break;
      case 38: /* prefixexp ::= PL exp PR */
#line 145 "lparser.y"
{ yygotominor.yy0 = yymsp[-1].minor.yy0; }
#line 1156 "lparser.c"
        break;
      case 41: /* exp ::= NIL */
#line 151 "lparser.y"
{ yygotominor.yy0 = new NilLitNode(); }
#line 1161 "lparser.c"
        break;
      case 42: /* exp ::= FALSE */
#line 152 "lparser.y"
{ yygotominor.yy0 = new BoolLitNode(false); }
#line 1166 "lparser.c"
        break;
      case 43: /* exp ::= TRUE */
#line 153 "lparser.y"
{ yygotominor.yy0 = new BoolLitNode(true); }
#line 1171 "lparser.c"
        break;
      case 46: /* exp ::= SBL SBR */
#line 160 "lparser.y"
{ yygotominor.yy0 = new ListConstrNode(NULL); }
#line 1176 "lparser.c"
        break;
      case 47: /* exp ::= SBL exp_list SBR */
#line 161 "lparser.y"
{ yygotominor.yy0 = new ListConstrNode(yymsp[-1].minor.yy59); }
#line 1181 "lparser.c"
        break;
      case 48: /* exp ::= CBL CBR */
#line 162 "lparser.y"
{ yygotominor.yy0; }
#line 1186 "lparser.c"
        break;
      case 49: /* exp ::= PIPE exp PIPE */
#line 165 "lparser.y"
{ yygotominor.yy0 = new UnOpNode<'|'>(yymsp[-1].minor.yy0); }
#line 1191 "lparser.c"
        break;
      case 50: /* exp ::= exp OR exp */
#line 167 "lparser.y"
{ yygotominor.yy0 = new OrNode(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1196 "lparser.c"
        break;
      case 51: /* exp ::= exp AND exp */
#line 168 "lparser.y"
{ yygotominor.yy0 = new AndNode(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1201 "lparser.c"
        break;
      case 52: /* exp ::= exp L exp */
#line 170 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'<'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1206 "lparser.c"
        break;
      case 53: /* exp ::= exp G exp */
#line 171 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'>'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1211 "lparser.c"
        break;
      case 54: /* exp ::= exp LEQ exp */
#line 172 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'<'+'='>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1216 "lparser.c"
        break;
      case 55: /* exp ::= exp GEQ exp */
#line 173 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'>'+'='>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1221 "lparser.c"
        break;
      case 56: /* exp ::= exp NEQ exp */
#line 174 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'!'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1226 "lparser.c"
        break;
      case 57: /* exp ::= exp EQ exp */
#line 175 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'='>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1231 "lparser.c"
        break;
      case 59: /* exp ::= exp PLUS exp */
#line 179 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'+'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1236 "lparser.c"
        break;
      case 60: /* exp ::= exp MINUS exp */
#line 180 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'-'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1241 "lparser.c"
        break;
      case 61: /* exp ::= exp MUL exp */
#line 182 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'*'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1246 "lparser.c"
        break;
      case 62: /* exp ::= exp DIV exp */
#line 183 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'/'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1251 "lparser.c"
        break;
      case 63: /* exp ::= exp MOD exp */
#line 184 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'%'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1256 "lparser.c"
        break;
      case 64: /* exp ::= exp EXP exp */
#line 186 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'^'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1261 "lparser.c"
        break;
      case 65: /* exp ::= NOT exp */
#line 188 "lparser.y"
{ yygotominor.yy0 = new UnOpNode<'!'>(yymsp[0].minor.yy0); }
#line 1266 "lparser.c"
        break;
      case 66: /* exp ::= MINUS exp */
#line 189 "lparser.y"
{ yygotominor.yy0 = new UnOpNode<'-'>(yymsp[0].minor.yy0); }
#line 1271 "lparser.c"
        break;
      case 69: /* exp_list ::= exp */
#line 198 "lparser.y"
{ yygotominor.yy59 = new NodeList<>(); yygotominor.yy59->push_back(yymsp[0].minor.yy0); }
#line 1276 "lparser.c"
        break;
      case 70: /* exp_list ::= exp_list COMMA exp */
#line 199 "lparser.y"
{ yygotominor.yy59 = yymsp[-2].minor.yy59; yygotominor.yy59->push_back(yymsp[0].minor.yy0); }
#line 1281 "lparser.c"
        break;
      default:
      /* (0) chunk ::= TERMINATION UNINITIALIZED WARNING DOT */ yytestcase(yyruleno==0);
      /* (16) stat ::= FOR ident_list IN exp_list DO block END */ yytestcase(yyruleno==16);
      /* (22) stat ::= NEXT */ yytestcase(yyruleno==22);
      /* (23) stat ::= BREAK */ yytestcase(yyruleno==23);
      /* (58) exp ::= exp RANGEOP exp */ yytestcase(yyruleno==58);
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
#line 57 "lparser.y"

    throw AYA::ParseError("syntax error");
#line 1351 "lparser.c"
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
