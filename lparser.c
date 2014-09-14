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
#line 39 "lparser.c"
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
#define YYNSTATE 138
#define YYNRULE 65
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
#define YY_ACTTAB_COUNT (583)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    21,   11,   10,   59,   22,   74,  105,    5,  126,  128,
 /*    10 */    96,  129,   21,    8,   87,   97,   22,   89,   76,   18,
 /*    20 */     6,  104,   47,   99,   16,   38,    9,  118,   15,  112,
 /*    30 */   111,   86,   43,   37,  103,  125,  124,  123,  122,  121,
 /*    40 */   120,   35,   21,  138,   49,   37,   22,  125,  124,  123,
 /*    50 */   122,  121,  120,   35,  135,    8,  102,   97,   46,   89,
 /*    60 */    76,   18,    6,  100,   47,   38,   16,  139,  130,  132,
 /*    70 */    15,  112,  111,    1,   43,   37,   45,  125,  124,  123,
 /*    80 */   122,  121,  120,   35,   41,   39,   30,   31,   36,   34,
 /*    90 */    33,   32,   29,   28,   27,   26,   25,   24,  134,   23,
 /*   100 */    40,   41,   39,   30,   31,   36,   34,   33,   32,   29,
 /*   110 */    28,   27,   26,   25,   24,   12,   23,   23,  203,  203,
 /*   120 */   203,  203,   29,   28,   27,   26,   25,   24,  127,   23,
 /*   130 */    41,   39,   30,   31,   36,   34,   33,   32,   29,   28,
 /*   140 */    27,   26,   25,   24,   88,   23,   26,   25,   24,   20,
 /*   150 */    23,   19,  119,    7,   41,   39,   30,   31,   36,   34,
 /*   160 */    33,   32,   29,   28,   27,   26,   25,   24,   48,   23,
 /*   170 */   116,   41,   39,   30,   31,   36,   34,   33,   32,   29,
 /*   180 */    28,   27,   26,   25,   24,  115,   23,   17,  114,    4,
 /*   190 */    30,   31,   36,   34,   33,   32,   29,   28,   27,   26,
 /*   200 */    25,   24,  108,   23,    3,   14,    2,  107,   41,   39,
 /*   210 */    30,   31,   36,   34,   33,   32,   29,   28,   27,   26,
 /*   220 */    25,   24,  135,   23,   39,   30,   31,   36,   34,   33,
 /*   230 */    32,   29,   28,   27,   26,   25,   24,   21,   23,   45,
 /*   240 */   136,   22,   36,   34,   33,   32,   29,   28,   27,   26,
 /*   250 */    25,   24,  118,   23,  204,  101,   79,  133,   62,   13,
 /*   260 */   117,   75,   78,  126,  128,   96,  129,   99,  110,   49,
 /*   270 */    37,  131,  125,  124,  123,  122,  121,  120,   35,   81,
 /*   280 */    79,  133,   62,   98,   79,  133,   62,  126,  128,   96,
 /*   290 */   129,  126,  128,   96,  129,   82,  109,   85,   79,  133,
 /*   300 */    62,   84,   79,  133,   62,  126,  128,   96,  129,  126,
 /*   310 */   128,   96,  129,   83,   79,  133,   62,  205,  205,  205,
 /*   320 */   205,  126,  128,   96,  129,   44,   79,  133,   62,  113,
 /*   330 */    79,  133,   62,  126,  128,   96,  129,  126,  128,   96,
 /*   340 */   129,   42,   79,  133,   62,   80,   79,  133,   62,  126,
 /*   350 */   128,   96,  129,  126,  128,   96,  129,  203,   28,   27,
 /*   360 */    26,   25,   24,   59,   23,   77,  137,   62,  126,  128,
 /*   370 */    96,  129,  126,  128,   96,  129,  205,  205,  205,  106,
 /*   380 */    62,  205,  205,  205,   63,  126,  128,   96,  129,  126,
 /*   390 */   128,   96,  129,   61,  205,  205,  205,   64,  126,  128,
 /*   400 */    96,  129,  126,  128,   96,  129,  205,   60,  205,  205,
 /*   410 */   205,   54,  126,  128,   96,  129,  126,  128,   96,  129,
 /*   420 */    65,  205,  205,  205,   53,  126,  128,   96,  129,  126,
 /*   430 */   128,   96,  129,   70,  205,  205,  205,  205,  126,  128,
 /*   440 */    96,  129,  205,   69,  205,  205,  205,   68,  126,  128,
 /*   450 */    96,  129,  126,  128,   96,  129,   67,  205,  205,  205,
 /*   460 */    66,  126,  128,   96,  129,  126,  128,   96,  129,  205,
 /*   470 */    71,  205,  205,  205,   73,  126,  128,   96,  129,  126,
 /*   480 */   128,   96,  129,   72,  205,  205,  205,   95,  126,  128,
 /*   490 */    96,  129,  126,  128,   96,  129,  205,   94,  205,  205,
 /*   500 */   205,  205,  126,  128,   96,  129,   93,  205,  205,  205,
 /*   510 */    92,  126,  128,   96,  129,  126,  128,   96,  129,   91,
 /*   520 */   205,  205,  205,   90,  126,  128,   96,  129,  126,  128,
 /*   530 */    96,  129,  205,   58,  205,  205,  205,   57,  126,  128,
 /*   540 */    96,  129,  126,  128,   96,  129,   52,  205,  205,  205,
 /*   550 */    56,  126,  128,   96,  129,  126,  128,   96,  129,  205,
 /*   560 */   205,   51,  205,  205,  205,   55,  126,  128,   96,  129,
 /*   570 */   126,  128,   96,  129,   50,  205,  205,  205,  205,  126,
 /*   580 */   128,   96,  129,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    11,   22,   23,   58,   15,   60,   17,   24,   63,   64,
 /*    10 */    65,   66,   11,   24,   26,   26,   15,   28,   29,   30,
 /*    20 */    31,   18,   33,   42,   35,   42,   45,   26,   39,   40,
 /*    30 */    41,   43,   43,   44,   19,   46,   47,   48,   49,   50,
 /*    40 */    51,   52,   11,    0,   43,   44,   15,   46,   47,   48,
 /*    50 */    49,   50,   51,   52,   26,   24,   20,   26,   26,   28,
 /*    60 */    29,   30,   31,   21,   33,   42,   35,    0,   45,   25,
 /*    70 */    39,   40,   41,   45,   43,   44,   44,   46,   47,   48,
 /*    80 */    49,   50,   51,   52,    1,    2,    3,    4,    5,    6,
 /*    90 */     7,    8,    9,   10,   11,   12,   13,   14,   26,   16,
 /*   100 */    27,    1,    2,    3,    4,    5,    6,    7,    8,    9,
 /*   110 */    10,   11,   12,   13,   14,   44,   16,   16,    5,    6,
 /*   120 */     7,    8,    9,   10,   11,   12,   13,   14,   45,   16,
 /*   130 */     1,    2,    3,    4,    5,    6,    7,    8,    9,   10,
 /*   140 */    11,   12,   13,   14,   26,   16,   12,   13,   14,   27,
 /*   150 */    16,   27,   52,   24,    1,    2,    3,    4,    5,    6,
 /*   160 */     7,    8,    9,   10,   11,   12,   13,   14,   26,   16,
 /*   170 */    25,    1,    2,    3,    4,    5,    6,    7,    8,    9,
 /*   180 */    10,   11,   12,   13,   14,   25,   16,   32,   25,   36,
 /*   190 */     3,    4,    5,    6,    7,    8,    9,   10,   11,   12,
 /*   200 */    13,   14,   25,   16,   37,   38,   36,   25,    1,    2,
 /*   210 */     3,    4,    5,    6,    7,    8,    9,   10,   11,   12,
 /*   220 */    13,   14,   26,   16,    2,    3,    4,    5,    6,    7,
 /*   230 */     8,    9,   10,   11,   12,   13,   14,   11,   16,   44,
 /*   240 */    62,   15,    5,    6,    7,    8,    9,   10,   11,   12,
 /*   250 */    13,   14,   26,   16,   54,   55,   56,   57,   58,   34,
 /*   260 */    62,   59,   59,   63,   64,   65,   66,   42,   62,   43,
 /*   270 */    44,   45,   46,   47,   48,   49,   50,   51,   52,   55,
 /*   280 */    56,   57,   58,   55,   56,   57,   58,   63,   64,   65,
 /*   290 */    66,   63,   64,   65,   66,   61,   61,   55,   56,   57,
 /*   300 */    58,   55,   56,   57,   58,   63,   64,   65,   66,   63,
 /*   310 */    64,   65,   66,   55,   56,   57,   58,   67,   67,   67,
 /*   320 */    67,   63,   64,   65,   66,   55,   56,   57,   58,   55,
 /*   330 */    56,   57,   58,   63,   64,   65,   66,   63,   64,   65,
 /*   340 */    66,   55,   56,   57,   58,   55,   56,   57,   58,   63,
 /*   350 */    64,   65,   66,   63,   64,   65,   66,    9,   10,   11,
 /*   360 */    12,   13,   14,   58,   16,   60,   57,   58,   63,   64,
 /*   370 */    65,   66,   63,   64,   65,   66,   67,   67,   67,   57,
 /*   380 */    58,   67,   67,   67,   58,   63,   64,   65,   66,   63,
 /*   390 */    64,   65,   66,   58,   67,   67,   67,   58,   63,   64,
 /*   400 */    65,   66,   63,   64,   65,   66,   67,   58,   67,   67,
 /*   410 */    67,   58,   63,   64,   65,   66,   63,   64,   65,   66,
 /*   420 */    58,   67,   67,   67,   58,   63,   64,   65,   66,   63,
 /*   430 */    64,   65,   66,   58,   67,   67,   67,   67,   63,   64,
 /*   440 */    65,   66,   67,   58,   67,   67,   67,   58,   63,   64,
 /*   450 */    65,   66,   63,   64,   65,   66,   58,   67,   67,   67,
 /*   460 */    58,   63,   64,   65,   66,   63,   64,   65,   66,   67,
 /*   470 */    58,   67,   67,   67,   58,   63,   64,   65,   66,   63,
 /*   480 */    64,   65,   66,   58,   67,   67,   67,   58,   63,   64,
 /*   490 */    65,   66,   63,   64,   65,   66,   67,   58,   67,   67,
 /*   500 */    67,   67,   63,   64,   65,   66,   58,   67,   67,   67,
 /*   510 */    58,   63,   64,   65,   66,   63,   64,   65,   66,   58,
 /*   520 */    67,   67,   67,   58,   63,   64,   65,   66,   63,   64,
 /*   530 */    65,   66,   67,   58,   67,   67,   67,   58,   63,   64,
 /*   540 */    65,   66,   63,   64,   65,   66,   58,   67,   67,   67,
 /*   550 */    58,   63,   64,   65,   66,   63,   64,   65,   66,   67,
 /*   560 */    67,   58,   67,   67,   67,   58,   63,   64,   65,   66,
 /*   570 */    63,   64,   65,   66,   58,   67,   67,   67,   67,   63,
 /*   580 */    64,   65,   66,
};
#define YY_SHIFT_USE_DFLT (-22)
#define YY_SHIFT_COUNT (105)
#define YY_SHIFT_MIN   (-21)
#define YY_SHIFT_MAX   (348)
static const short yy_shift_ofst[] = {
 /*     0 */   -11,   31,   31,   31,   31,   31,   31,   31,   31,   31,
 /*    10 */    31,   31,  226,    1,    1,    1,    1,    1,    1,    1,
 /*    20 */     1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
 /*    30 */     1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
 /*    40 */     1,    1,  167,   32,  167,   28,  195,  196,  195,  195,
 /*    50 */   170,  153,  129,  100,   83,  207,  207,  207,  207,  207,
 /*    60 */   207,  207,  207,  222,  187,  113,  237,  237,  113,  113,
 /*    70 */   113,  348,  134,  134,  -17,  225,  -12,   23,  -19,  -21,
 /*    80 */   182,  177,  163,  160,  155,  145,  142,  124,  122,  118,
 /*    90 */   101,  101,  101,  101,  101,  101,   71,   73,   44,   72,
 /*   100 */    67,   42,   43,   36,   15,    3,
};
#define YY_REDUCE_USE_DFLT (-56)
#define YY_REDUCE_COUNT (49)
#define YY_REDUCE_MIN   (-55)
#define YY_REDUCE_MAX   (516)
static const short yy_reduce_ofst[] = {
 /*     0 */   200,  290,  286,  274,  270,  258,  246,  242,  228,  224,
 /*    10 */   322,  309,  305,  -55,  516,  507,  503,  492,  488,  479,
 /*    20 */   475,  465,  461,  452,  448,  439,  429,  425,  416,  412,
 /*    30 */   402,  398,  389,  385,  375,  366,  362,  353,  349,  339,
 /*    40 */   335,  326,  235,  178,  234,  203,  206,  202,  198,  178,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   144,  144,  144,  144,  144,  144,  144,  144,  144,  144,
 /*    10 */   144,  144,  203,  203,  203,  203,  203,  203,  203,  203,
 /*    20 */   203,  203,  203,  203,  203,  203,  203,  203,  203,  203,
 /*    30 */   203,  203,  203,  203,  203,  203,  203,  203,  203,  203,
 /*    40 */   203,  203,  156,  203,  156,  203,  203,  203,  203,  203,
 /*    50 */   203,  203,  203,  203,  203,  159,  153,  151,  148,  201,
 /*    60 */   202,  147,  145,  183,  184,  185,  190,  189,  188,  187,
 /*    70 */   186,  191,  193,  192,  203,  203,  203,  203,  203,  140,
 /*    80 */   203,  203,  203,  203,  203,  203,  203,  150,  149,  203,
 /*    90 */   199,  198,  197,  196,  195,  194,  174,  200,  203,  203,
 /*   100 */   203,  203,  203,  203,  203,  203,  143,  167,  168,  158,
 /*   110 */   164,  161,  160,  157,  155,  154,  152,  165,  200,  182,
 /*   120 */   181,  180,  179,  178,  177,  176,  175,  173,  172,  171,
 /*   130 */   170,  169,  146,  141,  163,  162,  166,  142,
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
  "DO",            "END",           "IDENT",         "ASSIG",       
  "GLOBAL",        "LOCAL",         "WHILE",         "REPEAT",      
  "UNTIL",         "FOR",           "IN",            "IF",          
  "THEN",          "ELSE",          "ELSEIF",        "RETURN",      
  "NEXT",          "BREAK",         "COMMA",         "DEF",         
  "PL",            "PR",            "NIL",           "FALSE",       
  "TRUE",          "INT",           "REAL",          "STRING",      
  "PIPE",          "error",         "chunk",         "block",       
  "stat_list",     "stat",          "exp",           "ident_list",  
  "exp_list",      "else",          "func_body",     "function",    
  "functioncall",  "prefixexp",     "var",         
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
 /*   9 */ "stat ::= IDENT ASSIG exp",
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
 /*  63 */ "exp_list ::= exp",
 /*  64 */ "exp_list ::= exp_list COMMA exp",
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
  { 61, 0 },
  { 61, 2 },
  { 61, 5 },
  { 57, 2 },
  { 57, 1 },
  { 57, 1 },
  { 59, 1 },
  { 59, 3 },
  { 57, 3 },
  { 57, 4 },
  { 63, 2 },
  { 62, 4 },
  { 62, 5 },
  { 64, 3 },
  { 64, 4 },
  { 65, 1 },
  { 65, 1 },
  { 65, 3 },
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
  { 66, 1 },
  { 60, 1 },
  { 60, 3 },
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
#line 62 "lparser.y"
{ *currentNode = yygotominor.yy0 = yymsp[-1].minor.yy76; }
#line 959 "lparser.c"
        break;
      case 2: /* block ::= stat_list */
#line 66 "lparser.y"
{ yygotominor.yy76 = new BlockNode(yymsp[0].minor.yy77);  }
#line 964 "lparser.c"
        break;
      case 3: /* stat_list ::= stat */
#line 68 "lparser.y"
{ yygotominor.yy77 = new NodeList<>(); if(yymsp[0].minor.yy0){ yygotominor.yy77->push_back(yymsp[0].minor.yy0); }  }
#line 969 "lparser.c"
        break;
      case 4: /* stat_list ::= stat_list NL stat */
      case 5: /* stat_list ::= stat_list SCOLON stat */ yytestcase(yyruleno==5);
#line 69 "lparser.y"
{ yygotominor.yy77 = yymsp[-2].minor.yy77;  if(yymsp[0].minor.yy0){ yygotominor.yy77->push_back(yymsp[0].minor.yy0); }  }
#line 975 "lparser.c"
        break;
      case 6: /* stat ::= */
      case 11: /* stat ::= GLOBAL IDENT */ yytestcase(yyruleno==11);
      case 18: /* else ::= */ yytestcase(yyruleno==18);
#line 74 "lparser.y"
{ yygotominor.yy0 = NULL; }
#line 982 "lparser.c"
        break;
      case 7: /* stat ::= exp */
#line 75 "lparser.y"
{ yygotominor.yy0 = new StatNode(yymsp[0].minor.yy0); }
#line 987 "lparser.c"
        break;
      case 8: /* stat ::= DO block END */
#line 76 "lparser.y"
{ yygotominor.yy0 = yymsp[-1].minor.yy76; yymsp[-1].minor.yy76->createScope(); }
#line 992 "lparser.c"
        break;
      case 9: /* stat ::= IDENT ASSIG exp */
      case 10: /* stat ::= GLOBAL IDENT ASSIG exp */ yytestcase(yyruleno==10);
#line 79 "lparser.y"
{ yygotominor.yy0 = new AssignNode(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 998 "lparser.c"
        break;
      case 12: /* stat ::= LOCAL IDENT */
#line 83 "lparser.y"
{ yygotominor.yy0 = new DeclNode(yymsp[0].minor.yy0, NULL); }
#line 1003 "lparser.c"
        break;
      case 13: /* stat ::= LOCAL IDENT ASSIG exp */
#line 84 "lparser.y"
{ yygotominor.yy0 = new DeclNode(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1008 "lparser.c"
        break;
      case 14: /* stat ::= WHILE exp DO block END */
#line 93 "lparser.y"
{ yygotominor.yy0 = new WhileNode(yymsp[-3].minor.yy0, yymsp[-1].minor.yy76); }
#line 1013 "lparser.c"
        break;
      case 15: /* stat ::= REPEAT block UNTIL exp */
#line 95 "lparser.y"
{ yygotominor.yy0 = new RepeatNode(yymsp[0].minor.yy0, yymsp[-2].minor.yy76); }
#line 1018 "lparser.c"
        break;
      case 17: /* stat ::= IF exp THEN block else END */
#line 99 "lparser.y"
{ yygotominor.yy0 = new IfNode(yymsp[-4].minor.yy0, yymsp[-2].minor.yy76, yymsp[-1].minor.yy0); }
#line 1023 "lparser.c"
        break;
      case 19: /* else ::= ELSE block */
#line 101 "lparser.y"
{ yygotominor.yy0 = yymsp[0].minor.yy76; }
#line 1028 "lparser.c"
        break;
      case 20: /* else ::= ELSEIF exp THEN block else */
#line 102 "lparser.y"
{ yygotominor.yy0 = new IfNode(yymsp[-3].minor.yy0, yymsp[-1].minor.yy76, yymsp[0].minor.yy0); }
#line 1033 "lparser.c"
        break;
      case 21: /* stat ::= RETURN exp */
#line 105 "lparser.y"
{ yygotominor.yy0 = new ReturnNode(yymsp[0].minor.yy0); }
#line 1038 "lparser.c"
        break;
      case 24: /* ident_list ::= IDENT */
#line 113 "lparser.y"
{
    yygotominor.yy63 = new NodeList<IdentNode>();

    assert(dynamic_cast<IdentNode*>(yymsp[0].minor.yy0));
    yygotominor.yy63->push_back(static_cast<IdentNode*>(yymsp[0].minor.yy0));

}
#line 1049 "lparser.c"
        break;
      case 25: /* ident_list ::= ident_list COMMA IDENT */
#line 121 "lparser.y"
{
    yygotominor.yy63 = yymsp[-2].minor.yy63;

    assert(dynamic_cast<IdentNode*>(yymsp[0].minor.yy0));
    yygotominor.yy63->push_back(static_cast<IdentNode*>(yymsp[0].minor.yy0));
}
#line 1059 "lparser.c"
        break;
      case 26: /* stat ::= DEF IDENT func_body */
#line 129 "lparser.y"
{ yygotominor.yy0 = new AssignNode(yymsp[-1].minor.yy0, yymsp[0].minor.yy0); }
#line 1064 "lparser.c"
        break;
      case 28: /* function ::= DEF func_body */
      case 33: /* prefixexp ::= var */ yytestcase(yyruleno==33);
      case 34: /* prefixexp ::= functioncall */ yytestcase(yyruleno==34);
      case 36: /* exp ::= prefixexp */ yytestcase(yyruleno==36);
      case 37: /* exp ::= function */ yytestcase(yyruleno==37);
      case 41: /* exp ::= INT */ yytestcase(yyruleno==41);
      case 42: /* exp ::= REAL */ yytestcase(yyruleno==42);
      case 43: /* exp ::= STRING */ yytestcase(yyruleno==43);
#line 133 "lparser.y"
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
#line 1076 "lparser.c"
        break;
      case 29: /* func_body ::= PL PR block END */
#line 134 "lparser.y"
{ yygotominor.yy0 = new FuncNode(NULL, yymsp[-1].minor.yy76); }
#line 1081 "lparser.c"
        break;
      case 30: /* func_body ::= PL ident_list PR block END */
#line 135 "lparser.y"
{ yygotominor.yy0 = new FuncNode(yymsp[-3].minor.yy63, yymsp[-1].minor.yy76); }
#line 1086 "lparser.c"
        break;
      case 31: /* functioncall ::= prefixexp PL PR */
#line 137 "lparser.y"
{ yygotominor.yy0 = new CallNode(yymsp[-2].minor.yy0, NULL); }
#line 1091 "lparser.c"
        break;
      case 32: /* functioncall ::= prefixexp PL exp_list PR */
#line 138 "lparser.y"
{ yygotominor.yy0 = new CallNode(yymsp[-3].minor.yy0, yymsp[-1].minor.yy77); }
#line 1096 "lparser.c"
        break;
      case 35: /* prefixexp ::= PL exp PR */
#line 142 "lparser.y"
{ yygotominor.yy0 = yymsp[-1].minor.yy0; }
#line 1101 "lparser.c"
        break;
      case 38: /* exp ::= NIL */
#line 148 "lparser.y"
{ yygotominor.yy0 = new NilLitNode(); }
#line 1106 "lparser.c"
        break;
      case 39: /* exp ::= FALSE */
#line 149 "lparser.y"
{ yygotominor.yy0 = new BoolLitNode(false); }
#line 1111 "lparser.c"
        break;
      case 40: /* exp ::= TRUE */
#line 150 "lparser.y"
{ yygotominor.yy0 = new BoolLitNode(true); }
#line 1116 "lparser.c"
        break;
      case 44: /* exp ::= PIPE exp PIPE */
#line 156 "lparser.y"
{ yygotominor.yy0 = new UnOpNode<'|'>(yymsp[-1].minor.yy0); }
#line 1121 "lparser.c"
        break;
      case 45: /* exp ::= exp OR exp */
#line 158 "lparser.y"
{ yygotominor.yy0 = new OrNode(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1126 "lparser.c"
        break;
      case 46: /* exp ::= exp AND exp */
#line 159 "lparser.y"
{ yygotominor.yy0 = new AndNode(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1131 "lparser.c"
        break;
      case 47: /* exp ::= exp L exp */
#line 161 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'<'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1136 "lparser.c"
        break;
      case 48: /* exp ::= exp G exp */
#line 162 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'>'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1141 "lparser.c"
        break;
      case 49: /* exp ::= exp LEQ exp */
#line 163 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'<'+'='>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1146 "lparser.c"
        break;
      case 50: /* exp ::= exp GEQ exp */
#line 164 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'>'+'='>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1151 "lparser.c"
        break;
      case 51: /* exp ::= exp NEQ exp */
#line 165 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'!'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1156 "lparser.c"
        break;
      case 52: /* exp ::= exp EQ exp */
#line 166 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'='>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1161 "lparser.c"
        break;
      case 54: /* exp ::= exp PLUS exp */
#line 170 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'+'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1166 "lparser.c"
        break;
      case 55: /* exp ::= exp MINUS exp */
#line 171 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'-'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1171 "lparser.c"
        break;
      case 56: /* exp ::= exp MUL exp */
#line 173 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'*'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1176 "lparser.c"
        break;
      case 57: /* exp ::= exp DIV exp */
#line 174 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'/'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1181 "lparser.c"
        break;
      case 58: /* exp ::= exp MOD exp */
#line 175 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'%'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1186 "lparser.c"
        break;
      case 59: /* exp ::= exp EXP exp */
#line 177 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'^'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1191 "lparser.c"
        break;
      case 60: /* exp ::= NOT exp */
#line 179 "lparser.y"
{ yygotominor.yy0 = new UnOpNode<'!'>(yymsp[0].minor.yy0); }
#line 1196 "lparser.c"
        break;
      case 61: /* exp ::= MINUS exp */
#line 180 "lparser.y"
{ yygotominor.yy0 = new UnOpNode<'-'>(yymsp[0].minor.yy0); }
#line 1201 "lparser.c"
        break;
      case 62: /* var ::= IDENT */
#line 191 "lparser.y"
{ yygotominor.yy0 = new VarNode(yymsp[0].minor.yy0); }
#line 1206 "lparser.c"
        break;
      case 63: /* exp_list ::= exp */
#line 194 "lparser.y"
{ yygotominor.yy77 = new NodeList<>(); yygotominor.yy77->push_back(yymsp[0].minor.yy0); }
#line 1211 "lparser.c"
        break;
      case 64: /* exp_list ::= exp_list COMMA exp */
#line 195 "lparser.y"
{ yygotominor.yy77 = yymsp[-2].minor.yy77; yygotominor.yy77->push_back(yymsp[0].minor.yy0); }
#line 1216 "lparser.c"
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
#line 55 "lparser.y"

    throw AYA::ParseError("syntax error");
#line 1287 "lparser.c"
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
