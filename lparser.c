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
#line 40 "lparser.c"
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
#define YYNOCODE 68
#define YYACTIONTYPE unsigned char
#define LemonTOKENTYPE AYA::Node*
typedef union {
  int yyinit;
  LemonTOKENTYPE yy0;
  NodeList<IdentNode>* yy63;
  BlockNode* yy76;
  NodeList<>* yy77;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define LemonARG_SDECL  AYA::Node** currentNode ;
#define LemonARG_PDECL , AYA::Node** currentNode 
#define LemonARG_FETCH  AYA::Node** currentNode  = yypParser->currentNode 
#define LemonARG_STORE yypParser->currentNode  = currentNode 
#define YYNSTATE 140
#define YYNRULE 66
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
#define YY_ACTTAB_COUNT (597)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    21,   11,   10,   91,   22,   46,  106,  206,   28,   27,
 /*    10 */    26,   25,   24,    8,   23,  105,   90,  120,   76,   18,
 /*    20 */     6,   45,   47,  100,   16,    5,    9,   12,   15,  113,
 /*    30 */   112,  104,   43,   37,  103,  127,  126,  125,  124,  123,
 /*    40 */   122,   35,   21,   38,   59,  131,   22,   74,   88,   13,
 /*    50 */   128,  130,   78,   38,  140,    8,  132,  100,   90,  120,
 /*    60 */    76,   18,    6,   87,   47,  101,   16,    3,   14,  141,
 /*    70 */    15,  113,  112,  136,   43,   37,  134,  127,  126,  125,
 /*    80 */   124,  123,  122,   35,   41,   39,   30,   31,   36,   34,
 /*    90 */    33,   32,   29,   28,   27,   26,   25,   24,   23,   23,
 /*   100 */   137,   41,   39,   30,   31,   36,   34,   33,   32,   29,
 /*   110 */    28,   27,   26,   25,   24,   40,   23,    1,  206,  206,
 /*   120 */   206,  206,   29,   28,   27,   26,   25,   24,  129,   23,
 /*   130 */    41,   39,   30,   31,   36,   34,   33,   32,   29,   28,
 /*   140 */    27,   26,   25,   24,  119,   23,   26,   25,   24,   89,
 /*   150 */    23,   20,  121,    7,   41,   39,   30,   31,   36,   34,
 /*   160 */    33,   32,   29,   28,   27,   26,   25,   24,   19,   23,
 /*   170 */   117,   41,   39,   30,   31,   36,   34,   33,   32,   29,
 /*   180 */    28,   27,   26,   25,   24,   48,   23,   17,  116,    4,
 /*   190 */    30,   31,   36,   34,   33,   32,   29,   28,   27,   26,
 /*   200 */    25,   24,  115,   23,  109,  108,    2,  138,   41,   39,
 /*   210 */    30,   31,   36,   34,   33,   32,   29,   28,   27,   26,
 /*   220 */    25,   24,   45,   23,   39,   30,   31,   36,   34,   33,
 /*   230 */    32,   29,   28,   27,   26,   25,   24,   21,   23,  118,
 /*   240 */   137,   22,   59,  131,  111,   77,   75,   21,  128,  130,
 /*   250 */    78,   22,   79,   83,  120,  207,  102,   80,  135,   62,
 /*   260 */    98,  110,  208,  208,  120,  128,  130,   78,  208,   49,
 /*   270 */    37,  133,  127,  126,  125,  124,  123,  122,   35,   49,
 /*   280 */    37,  208,  127,  126,  125,  124,  123,  122,   35,   36,
 /*   290 */    34,   33,   32,   29,   28,   27,   26,   25,   24,  208,
 /*   300 */    23,  208,  208,   82,   80,  135,   62,   98,  208,  208,
 /*   310 */   208,  208,  128,  130,   78,   99,   80,  135,   62,   98,
 /*   320 */   208,  208,  208,  208,  128,  130,   78,   86,   80,  135,
 /*   330 */    62,   98,  208,  208,  208,  208,  128,  130,   78,  208,
 /*   340 */    85,   80,  135,   62,   98,  208,  208,  208,  208,  128,
 /*   350 */   130,   78,   84,   80,  135,   62,   98,  208,  139,   62,
 /*   360 */    98,  128,  130,   78,  208,  128,  130,   78,   44,   80,
 /*   370 */   135,   62,   98,  208,  208,  208,  208,  128,  130,   78,
 /*   380 */   114,   80,  135,   62,   98,  208,  208,  208,  208,  128,
 /*   390 */   130,   78,   42,   80,  135,   62,   98,  208,  208,  208,
 /*   400 */   208,  128,  130,   78,  208,   81,   80,  135,   62,   98,
 /*   410 */   107,   62,   98,  208,  128,  130,   78,  128,  130,   78,
 /*   420 */    63,  131,  208,  208,   61,  131,  128,  130,   78,  208,
 /*   430 */   128,  130,   78,  208,  208,  208,   64,  131,  208,   60,
 /*   440 */   131,  208,  128,  130,   78,  128,  130,   78,   54,  131,
 /*   450 */   208,   65,  131,  208,  128,  130,   78,  128,  130,   78,
 /*   460 */    53,  131,  208,  208,   70,  131,  128,  130,   78,  208,
 /*   470 */   128,  130,   78,   69,  131,  208,   68,  131,  208,  128,
 /*   480 */   130,   78,  128,  130,   78,   67,  131,  208,  208,   66,
 /*   490 */   131,  128,  130,   78,  208,  128,  130,   78,   71,  131,
 /*   500 */   208,   73,  131,  208,  128,  130,   78,  128,  130,   78,
 /*   510 */    72,  131,  208,   97,  131,  208,  128,  130,   78,  128,
 /*   520 */   130,   78,  208,   96,  131,  208,   95,  131,  208,  128,
 /*   530 */   130,   78,  128,  130,   78,   94,  131,  208,   93,  131,
 /*   540 */   208,  128,  130,   78,  128,  130,   78,  208,   92,  131,
 /*   550 */   208,   58,  131,  208,  128,  130,   78,  128,  130,   78,
 /*   560 */    57,  131,  208,   52,  131,  208,  128,  130,   78,  128,
 /*   570 */   130,   78,   56,  131,  208,   51,  131,  208,  128,  130,
 /*   580 */    78,  128,  130,   78,  208,   55,  131,  208,   50,  131,
 /*   590 */   208,  128,  130,   78,  128,  130,   78,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    11,   22,   23,   20,   15,   28,   17,    9,   10,   11,
 /*    10 */    12,   13,   14,   24,   16,   18,   27,   28,   29,   30,
 /*    20 */    31,   44,   33,   42,   35,   24,   45,   44,   39,   40,
 /*    30 */    41,   19,   43,   44,   20,   46,   47,   48,   49,   50,
 /*    40 */    51,   52,   11,   42,   58,   59,   15,   61,   28,   34,
 /*    50 */    64,   65,   66,   42,    0,   24,   45,   42,   27,   28,
 /*    60 */    29,   30,   31,   43,   33,   21,   35,   37,   38,    0,
 /*    70 */    39,   40,   41,   28,   43,   44,   25,   46,   47,   48,
 /*    80 */    49,   50,   51,   52,    1,    2,    3,    4,    5,    6,
 /*    90 */     7,    8,    9,   10,   11,   12,   13,   14,   16,   16,
 /*   100 */    28,    1,    2,    3,    4,    5,    6,    7,    8,    9,
 /*   110 */    10,   11,   12,   13,   14,   26,   16,   45,    5,    6,
 /*   120 */     7,    8,    9,   10,   11,   12,   13,   14,   45,   16,
 /*   130 */     1,    2,    3,    4,    5,    6,    7,    8,    9,   10,
 /*   140 */    11,   12,   13,   14,   28,   16,   12,   13,   14,   28,
 /*   150 */    16,   26,   52,   24,    1,    2,    3,    4,    5,    6,
 /*   160 */     7,    8,    9,   10,   11,   12,   13,   14,   26,   16,
 /*   170 */    25,    1,    2,    3,    4,    5,    6,    7,    8,    9,
 /*   180 */    10,   11,   12,   13,   14,   28,   16,   32,   25,   36,
 /*   190 */     3,    4,    5,    6,    7,    8,    9,   10,   11,   12,
 /*   200 */    13,   14,   25,   16,   25,   25,   36,   63,    1,    2,
 /*   210 */     3,    4,    5,    6,    7,    8,    9,   10,   11,   12,
 /*   220 */    13,   14,   44,   16,    2,    3,    4,    5,    6,    7,
 /*   230 */     8,    9,   10,   11,   12,   13,   14,   11,   16,   63,
 /*   240 */    28,   15,   58,   59,   63,   61,   60,   11,   64,   65,
 /*   250 */    66,   15,   60,   62,   28,   54,   55,   56,   57,   58,
 /*   260 */    59,   62,   67,   67,   28,   64,   65,   66,   67,   43,
 /*   270 */    44,   45,   46,   47,   48,   49,   50,   51,   52,   43,
 /*   280 */    44,   67,   46,   47,   48,   49,   50,   51,   52,    5,
 /*   290 */     6,    7,    8,    9,   10,   11,   12,   13,   14,   67,
 /*   300 */    16,   67,   67,   55,   56,   57,   58,   59,   67,   67,
 /*   310 */    67,   67,   64,   65,   66,   55,   56,   57,   58,   59,
 /*   320 */    67,   67,   67,   67,   64,   65,   66,   55,   56,   57,
 /*   330 */    58,   59,   67,   67,   67,   67,   64,   65,   66,   67,
 /*   340 */    55,   56,   57,   58,   59,   67,   67,   67,   67,   64,
 /*   350 */    65,   66,   55,   56,   57,   58,   59,   67,   57,   58,
 /*   360 */    59,   64,   65,   66,   67,   64,   65,   66,   55,   56,
 /*   370 */    57,   58,   59,   67,   67,   67,   67,   64,   65,   66,
 /*   380 */    55,   56,   57,   58,   59,   67,   67,   67,   67,   64,
 /*   390 */    65,   66,   55,   56,   57,   58,   59,   67,   67,   67,
 /*   400 */    67,   64,   65,   66,   67,   55,   56,   57,   58,   59,
 /*   410 */    57,   58,   59,   67,   64,   65,   66,   64,   65,   66,
 /*   420 */    58,   59,   67,   67,   58,   59,   64,   65,   66,   67,
 /*   430 */    64,   65,   66,   67,   67,   67,   58,   59,   67,   58,
 /*   440 */    59,   67,   64,   65,   66,   64,   65,   66,   58,   59,
 /*   450 */    67,   58,   59,   67,   64,   65,   66,   64,   65,   66,
 /*   460 */    58,   59,   67,   67,   58,   59,   64,   65,   66,   67,
 /*   470 */    64,   65,   66,   58,   59,   67,   58,   59,   67,   64,
 /*   480 */    65,   66,   64,   65,   66,   58,   59,   67,   67,   58,
 /*   490 */    59,   64,   65,   66,   67,   64,   65,   66,   58,   59,
 /*   500 */    67,   58,   59,   67,   64,   65,   66,   64,   65,   66,
 /*   510 */    58,   59,   67,   58,   59,   67,   64,   65,   66,   64,
 /*   520 */    65,   66,   67,   58,   59,   67,   58,   59,   67,   64,
 /*   530 */    65,   66,   64,   65,   66,   58,   59,   67,   58,   59,
 /*   540 */    67,   64,   65,   66,   64,   65,   66,   67,   58,   59,
 /*   550 */    67,   58,   59,   67,   64,   65,   66,   64,   65,   66,
 /*   560 */    58,   59,   67,   58,   59,   67,   64,   65,   66,   64,
 /*   570 */    65,   66,   58,   59,   67,   58,   59,   67,   64,   65,
 /*   580 */    66,   64,   65,   66,   67,   58,   59,   67,   58,   59,
 /*   590 */    67,   64,   65,   66,   64,   65,   66,
};
#define YY_SHIFT_USE_DFLT (-24)
#define YY_SHIFT_COUNT (106)
#define YY_SHIFT_MIN   (-23)
#define YY_SHIFT_MAX   (284)
static const short yy_shift_ofst[] = {
 /*     0 */   -11,   31,   31,   31,   31,   31,   31,   31,   31,   31,
 /*    10 */    31,   31,  226,  236,  236,  236,  236,  236,  236,  236,
 /*    20 */   236,  236,  236,  236,  236,  236,  236,  236,  236,  236,
 /*    30 */   236,  236,  236,  236,  236,  236,  236,  236,  236,  236,
 /*    40 */   236,  236,   30,  -23,   30,   72,  178,  212,  178,  178,
 /*    50 */   170,  153,  129,  100,   83,  207,  207,  207,  207,  207,
 /*    60 */   207,  207,  207,  222,  187,  113,  284,  284,  113,  113,
 /*    70 */   113,   -2,  134,  134,    1,   15,   20,   11,  -17,  -19,
 /*    80 */   -21,  180,  179,  177,  163,  155,  145,  157,  142,  125,
 /*    90 */   121,  116,   82,   82,   82,   82,   82,   82,   89,   51,
 /*   100 */    45,   69,   44,   54,   14,   12,   -3,
};
#define YY_REDUCE_USE_DFLT (-15)
#define YY_REDUCE_COUNT (49)
#define YY_REDUCE_MIN   (-14)
#define YY_REDUCE_MAX   (530)
static const short yy_reduce_ofst[] = {
 /*     0 */   201,  350,  337,  325,  313,  297,  285,  272,  260,  248,
 /*    10 */   353,  301,  184,  -14,  530,  527,  517,  514,  505,  502,
 /*    20 */   493,  490,  480,  477,  468,  465,  455,  452,  443,  440,
 /*    30 */   431,  427,  418,  415,  406,  402,  393,  390,  381,  378,
 /*    40 */   366,  362,  199,  144,  191,  192,  181,  186,  176,  144,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   146,  146,  146,  146,  146,  146,  146,  146,  146,  146,
 /*    10 */   146,  146,  206,  206,  206,  206,  206,  206,  206,  206,
 /*    20 */   206,  206,  206,  206,  206,  206,  206,  206,  206,  206,
 /*    30 */   206,  206,  206,  206,  206,  206,  206,  206,  206,  206,
 /*    40 */   206,  206,  158,  206,  158,  206,  206,  206,  206,  206,
 /*    50 */   206,  206,  206,  206,  206,  161,  155,  153,  150,  204,
 /*    60 */   205,  149,  147,  185,  186,  187,  192,  191,  190,  189,
 /*    70 */   188,  193,  195,  194,  206,  206,  206,  206,  176,  206,
 /*    80 */   142,  206,  206,  206,  206,  206,  206,  206,  152,  151,
 /*    90 */   206,  206,  201,  200,  199,  198,  197,  196,  173,  206,
 /*   100 */   206,  206,  206,  206,  206,  206,  206,  145,  169,  170,
 /*   110 */   160,  166,  163,  162,  159,  157,  156,  154,  167,  203,
 /*   120 */   202,  184,  183,  182,  181,  180,  179,  178,  177,  175,
 /*   130 */   174,  173,  172,  171,  148,  143,  165,  164,  168,  144,
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
  "PL",            "PR",            "NIL",           "FALSE",       
  "TRUE",          "INT",           "REAL",          "STRING",      
  "PIPE",          "error",         "chunk",         "block",       
  "stat_list",     "stat",          "exp",           "var",         
  "ident_list",    "exp_list",      "else",          "func_body",   
  "function",      "functioncall",  "prefixexp",   
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
 /*  26 */ "stat ::= DEF IDENT func_body",
 /*  27 */ "stat ::= LOCAL DEF IDENT func_body",
 /*  28 */ "function ::= DEF func_body",
 /*  29 */ "func_body ::= PL PR block END",
 /*  30 */ "func_body ::= PL ident_list PR block END",
 /*  31 */ "functioncall ::= prefixexp PL PR",
 /*  32 */ "functioncall ::= prefixexp PL exp_list PR",
 /*  33 */ "prefixexp ::= var",
 /*  34 */ "prefixexp ::= functioncall",
 /*  35 */ "prefixexp ::= PL exp PR",
 /*  36 */ "exp ::= prefixexp",
 /*  37 */ "exp ::= function",
 /*  38 */ "exp ::= NIL",
 /*  39 */ "exp ::= FALSE",
 /*  40 */ "exp ::= TRUE",
 /*  41 */ "exp ::= INT",
 /*  42 */ "exp ::= REAL",
 /*  43 */ "exp ::= STRING",
 /*  44 */ "exp ::= PIPE exp PIPE",
 /*  45 */ "exp ::= exp OR exp",
 /*  46 */ "exp ::= exp AND exp",
 /*  47 */ "exp ::= exp L exp",
 /*  48 */ "exp ::= exp G exp",
 /*  49 */ "exp ::= exp LEQ exp",
 /*  50 */ "exp ::= exp GEQ exp",
 /*  51 */ "exp ::= exp NEQ exp",
 /*  52 */ "exp ::= exp EQ exp",
 /*  53 */ "exp ::= exp RANGEOP exp",
 /*  54 */ "exp ::= exp PLUS exp",
 /*  55 */ "exp ::= exp MINUS exp",
 /*  56 */ "exp ::= exp MUL exp",
 /*  57 */ "exp ::= exp DIV exp",
 /*  58 */ "exp ::= exp MOD exp",
 /*  59 */ "exp ::= exp EXP exp",
 /*  60 */ "exp ::= NOT exp",
 /*  61 */ "exp ::= MINUS exp",
 /*  62 */ "var ::= IDENT",
 /*  63 */ "var ::= prefixexp DOT IDENT",
 /*  64 */ "exp_list ::= exp",
 /*  65 */ "exp_list ::= exp_list COMMA exp",
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
  { 54, 4 },
  { 54, 2 },
  { 55, 1 },
  { 56, 1 },
  { 56, 3 },
  { 56, 3 },
  { 57, 0 },
  { 57, 1 },
  { 57, 3 },
  { 57, 3 },
  { 57, 4 },
  { 57, 2 },
  { 57, 2 },
  { 57, 4 },
  { 57, 5 },
  { 57, 4 },
  { 57, 7 },
  { 57, 6 },
  { 62, 0 },
  { 62, 2 },
  { 62, 5 },
  { 57, 2 },
  { 57, 1 },
  { 57, 1 },
  { 60, 1 },
  { 60, 3 },
  { 57, 3 },
  { 57, 4 },
  { 64, 2 },
  { 63, 4 },
  { 63, 5 },
  { 65, 3 },
  { 65, 4 },
  { 66, 1 },
  { 66, 1 },
  { 66, 3 },
  { 58, 1 },
  { 58, 1 },
  { 58, 1 },
  { 58, 1 },
  { 58, 1 },
  { 58, 1 },
  { 58, 1 },
  { 58, 1 },
  { 58, 3 },
  { 58, 3 },
  { 58, 3 },
  { 58, 3 },
  { 58, 3 },
  { 58, 3 },
  { 58, 3 },
  { 58, 3 },
  { 58, 3 },
  { 58, 3 },
  { 58, 3 },
  { 58, 3 },
  { 58, 3 },
  { 58, 3 },
  { 58, 3 },
  { 58, 3 },
  { 58, 2 },
  { 58, 2 },
  { 59, 1 },
  { 59, 3 },
  { 61, 1 },
  { 61, 3 },
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
#line 63 "lparser.y"
{ *currentNode = yygotominor.yy0 = yymsp[-1].minor.yy76; }
#line 964 "lparser.c"
        break;
      case 2: /* block ::= stat_list */
#line 67 "lparser.y"
{ yygotominor.yy76 = new BlockNode(yymsp[0].minor.yy77);  }
#line 969 "lparser.c"
        break;
      case 3: /* stat_list ::= stat */
#line 69 "lparser.y"
{ yygotominor.yy77 = new NodeList<>(); if(yymsp[0].minor.yy0){ yygotominor.yy77->push_back(yymsp[0].minor.yy0); }  }
#line 974 "lparser.c"
        break;
      case 4: /* stat_list ::= stat_list NL stat */
      case 5: /* stat_list ::= stat_list SCOLON stat */ yytestcase(yyruleno==5);
#line 70 "lparser.y"
{ yygotominor.yy77 = yymsp[-2].minor.yy77;  if(yymsp[0].minor.yy0){ yygotominor.yy77->push_back(yymsp[0].minor.yy0); }  }
#line 980 "lparser.c"
        break;
      case 6: /* stat ::= */
      case 11: /* stat ::= GLOBAL IDENT */ yytestcase(yyruleno==11);
      case 18: /* else ::= */ yytestcase(yyruleno==18);
#line 75 "lparser.y"
{ yygotominor.yy0 = NULL; }
#line 987 "lparser.c"
        break;
      case 7: /* stat ::= exp */
#line 76 "lparser.y"
{ yygotominor.yy0 = new StatNode(yymsp[0].minor.yy0); }
#line 992 "lparser.c"
        break;
      case 8: /* stat ::= DO block END */
#line 77 "lparser.y"
{ yygotominor.yy0 = yymsp[-1].minor.yy76; yymsp[-1].minor.yy76->createScope(); }
#line 997 "lparser.c"
        break;
      case 9: /* stat ::= var ASSIG exp */
#line 80 "lparser.y"
{ yygotominor.yy0 = new AssignNode(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1002 "lparser.c"
        break;
      case 10: /* stat ::= GLOBAL IDENT ASSIG exp */
#line 81 "lparser.y"
{ yygotominor.yy0 = new AssignNode(new VarNode(yymsp[-2].minor.yy0), yymsp[0].minor.yy0); }
#line 1007 "lparser.c"
        break;
      case 12: /* stat ::= LOCAL IDENT */
#line 84 "lparser.y"
{ yygotominor.yy0 = new DeclNode(yymsp[0].minor.yy0, NULL); }
#line 1012 "lparser.c"
        break;
      case 13: /* stat ::= LOCAL IDENT ASSIG exp */
#line 85 "lparser.y"
{ yygotominor.yy0 = new DeclNode(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1017 "lparser.c"
        break;
      case 14: /* stat ::= WHILE exp DO block END */
#line 94 "lparser.y"
{ yygotominor.yy0 = new WhileNode(yymsp[-3].minor.yy0, yymsp[-1].minor.yy76); }
#line 1022 "lparser.c"
        break;
      case 15: /* stat ::= REPEAT block UNTIL exp */
#line 96 "lparser.y"
{ yygotominor.yy0 = new RepeatNode(yymsp[0].minor.yy0, yymsp[-2].minor.yy76); }
#line 1027 "lparser.c"
        break;
      case 17: /* stat ::= IF exp THEN block else END */
#line 100 "lparser.y"
{ yygotominor.yy0 = new IfNode(yymsp[-4].minor.yy0, yymsp[-2].minor.yy76, yymsp[-1].minor.yy0); }
#line 1032 "lparser.c"
        break;
      case 19: /* else ::= ELSE block */
#line 102 "lparser.y"
{ yygotominor.yy0 = yymsp[0].minor.yy76; }
#line 1037 "lparser.c"
        break;
      case 20: /* else ::= ELSEIF exp THEN block else */
#line 103 "lparser.y"
{ yygotominor.yy0 = new IfNode(yymsp[-3].minor.yy0, yymsp[-1].minor.yy76, yymsp[0].minor.yy0); }
#line 1042 "lparser.c"
        break;
      case 21: /* stat ::= RETURN exp */
#line 106 "lparser.y"
{ yygotominor.yy0 = new ReturnNode(yymsp[0].minor.yy0); }
#line 1047 "lparser.c"
        break;
      case 24: /* ident_list ::= IDENT */
#line 114 "lparser.y"
{
    yygotominor.yy63 = new NodeList<IdentNode>();

    assert(dynamic_cast<IdentNode*>(yymsp[0].minor.yy0));
    yygotominor.yy63->push_back(static_cast<IdentNode*>(yymsp[0].minor.yy0));

}
#line 1058 "lparser.c"
        break;
      case 25: /* ident_list ::= ident_list COMMA IDENT */
#line 122 "lparser.y"
{
    yygotominor.yy63 = yymsp[-2].minor.yy63;

    assert(dynamic_cast<IdentNode*>(yymsp[0].minor.yy0));
    yygotominor.yy63->push_back(static_cast<IdentNode*>(yymsp[0].minor.yy0));
}
#line 1068 "lparser.c"
        break;
      case 26: /* stat ::= DEF IDENT func_body */
#line 130 "lparser.y"
{ yygotominor.yy0 = new AssignNode(new VarNode(yymsp[-1].minor.yy0), yymsp[0].minor.yy0); }
#line 1073 "lparser.c"
        break;
      case 28: /* function ::= DEF func_body */
      case 33: /* prefixexp ::= var */ yytestcase(yyruleno==33);
      case 34: /* prefixexp ::= functioncall */ yytestcase(yyruleno==34);
      case 36: /* exp ::= prefixexp */ yytestcase(yyruleno==36);
      case 37: /* exp ::= function */ yytestcase(yyruleno==37);
      case 41: /* exp ::= INT */ yytestcase(yyruleno==41);
      case 42: /* exp ::= REAL */ yytestcase(yyruleno==42);
      case 43: /* exp ::= STRING */ yytestcase(yyruleno==43);
#line 134 "lparser.y"
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
#line 1085 "lparser.c"
        break;
      case 29: /* func_body ::= PL PR block END */
#line 135 "lparser.y"
{ yygotominor.yy0 = new FuncNode(NULL, yymsp[-1].minor.yy76); }
#line 1090 "lparser.c"
        break;
      case 30: /* func_body ::= PL ident_list PR block END */
#line 136 "lparser.y"
{ yygotominor.yy0 = new FuncNode(yymsp[-3].minor.yy63, yymsp[-1].minor.yy76); }
#line 1095 "lparser.c"
        break;
      case 31: /* functioncall ::= prefixexp PL PR */
#line 138 "lparser.y"
{ yygotominor.yy0 = new CallNode(yymsp[-2].minor.yy0, NULL); }
#line 1100 "lparser.c"
        break;
      case 32: /* functioncall ::= prefixexp PL exp_list PR */
#line 139 "lparser.y"
{ yygotominor.yy0 = new CallNode(yymsp[-3].minor.yy0, yymsp[-1].minor.yy77); }
#line 1105 "lparser.c"
        break;
      case 35: /* prefixexp ::= PL exp PR */
#line 143 "lparser.y"
{ yygotominor.yy0 = yymsp[-1].minor.yy0; }
#line 1110 "lparser.c"
        break;
      case 38: /* exp ::= NIL */
#line 149 "lparser.y"
{ yygotominor.yy0 = new NilLitNode(); }
#line 1115 "lparser.c"
        break;
      case 39: /* exp ::= FALSE */
#line 150 "lparser.y"
{ yygotominor.yy0 = new BoolLitNode(false); }
#line 1120 "lparser.c"
        break;
      case 40: /* exp ::= TRUE */
#line 151 "lparser.y"
{ yygotominor.yy0 = new BoolLitNode(true); }
#line 1125 "lparser.c"
        break;
      case 44: /* exp ::= PIPE exp PIPE */
#line 157 "lparser.y"
{ yygotominor.yy0 = new UnOpNode<'|'>(yymsp[-1].minor.yy0); }
#line 1130 "lparser.c"
        break;
      case 45: /* exp ::= exp OR exp */
#line 159 "lparser.y"
{ yygotominor.yy0 = new OrNode(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1135 "lparser.c"
        break;
      case 46: /* exp ::= exp AND exp */
#line 160 "lparser.y"
{ yygotominor.yy0 = new AndNode(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1140 "lparser.c"
        break;
      case 47: /* exp ::= exp L exp */
#line 162 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'<'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1145 "lparser.c"
        break;
      case 48: /* exp ::= exp G exp */
#line 163 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'>'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1150 "lparser.c"
        break;
      case 49: /* exp ::= exp LEQ exp */
#line 164 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'<'+'='>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1155 "lparser.c"
        break;
      case 50: /* exp ::= exp GEQ exp */
#line 165 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'>'+'='>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1160 "lparser.c"
        break;
      case 51: /* exp ::= exp NEQ exp */
#line 166 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'!'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1165 "lparser.c"
        break;
      case 52: /* exp ::= exp EQ exp */
#line 167 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'='>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1170 "lparser.c"
        break;
      case 54: /* exp ::= exp PLUS exp */
#line 171 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'+'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1175 "lparser.c"
        break;
      case 55: /* exp ::= exp MINUS exp */
#line 172 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'-'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1180 "lparser.c"
        break;
      case 56: /* exp ::= exp MUL exp */
#line 174 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'*'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1185 "lparser.c"
        break;
      case 57: /* exp ::= exp DIV exp */
#line 175 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'/'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1190 "lparser.c"
        break;
      case 58: /* exp ::= exp MOD exp */
#line 176 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'%'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1195 "lparser.c"
        break;
      case 59: /* exp ::= exp EXP exp */
#line 178 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'^'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1200 "lparser.c"
        break;
      case 60: /* exp ::= NOT exp */
#line 180 "lparser.y"
{ yygotominor.yy0 = new UnOpNode<'!'>(yymsp[0].minor.yy0); }
#line 1205 "lparser.c"
        break;
      case 61: /* exp ::= MINUS exp */
#line 181 "lparser.y"
{ yygotominor.yy0 = new UnOpNode<'-'>(yymsp[0].minor.yy0); }
#line 1210 "lparser.c"
        break;
      case 62: /* var ::= IDENT */
#line 192 "lparser.y"
{ yygotominor.yy0 = new VarNode(yymsp[0].minor.yy0); }
#line 1215 "lparser.c"
        break;
      case 63: /* var ::= prefixexp DOT IDENT */
#line 193 "lparser.y"
{ yygotominor.yy0 = new MemberAccessNode(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1220 "lparser.c"
        break;
      case 64: /* exp_list ::= exp */
#line 196 "lparser.y"
{ yygotominor.yy77 = new NodeList<>(); yygotominor.yy77->push_back(yymsp[0].minor.yy0); }
#line 1225 "lparser.c"
        break;
      case 65: /* exp_list ::= exp_list COMMA exp */
#line 197 "lparser.y"
{ yygotominor.yy77 = yymsp[-2].minor.yy77; yygotominor.yy77->push_back(yymsp[0].minor.yy0); }
#line 1230 "lparser.c"
        break;
      default:
      /* (0) chunk ::= TERMINATION UNINITIALIZED WARNING DOT */ yytestcase(yyruleno==0);
      /* (16) stat ::= FOR ident_list IN exp_list DO block END */ yytestcase(yyruleno==16);
      /* (22) stat ::= NEXT */ yytestcase(yyruleno==22);
      /* (23) stat ::= BREAK */ yytestcase(yyruleno==23);
      /* (27) stat ::= LOCAL DEF IDENT func_body */ yytestcase(yyruleno==27);
      /* (53) exp ::= exp RANGEOP exp */ yytestcase(yyruleno==53);
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
#line 56 "lparser.y"

    throw AYA::ParseError("syntax error");
#line 1301 "lparser.c"
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
