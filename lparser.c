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


    #ifdef DEBUG
        #include <iostream>
    #endif // DEBUG

    using namespace AYA;
#line 29 "lparser.c"
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
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define LemonARG_SDECL
#define LemonARG_PDECL
#define LemonARG_FETCH
#define LemonARG_STORE
#define YYNSTATE 143
#define YYNRULE 70
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
#define YY_ACTTAB_COUNT (498)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    20,  142,   63,   79,   21,   15,  106,  121,   11,   10,
 /*    10 */     1,  105,    8,  137,   76,   43,   50,   19,    6,   92,
 /*    20 */    49,  143,   17,   13,  104,    5,   12,  116,  115,   40,
 /*    30 */    84,   37,   52,  136,  135,  134,  133,  132,  131,   35,
 /*    40 */    20,   91,  123,   92,   21,   14,  213,   27,   26,   25,
 /*    50 */    24,   23,    8,   22,   38,   43,   50,   19,    6,  123,
 /*    60 */    49,    9,   17,   46,  141,  102,   12,  116,  115,   40,
 /*    70 */    84,   37,   92,  136,  135,  134,  133,  132,  131,   35,
 /*    80 */    39,   36,   29,   30,   34,   33,   32,   31,   28,   27,
 /*    90 */    26,   25,   24,   23,  205,   22,  139,   39,   36,   29,
 /*   100 */    30,   34,   33,   32,   31,   28,   27,   26,   25,   24,
 /*   110 */    23,  144,   22,   25,   24,   23,   38,   22,   54,   44,
 /*   120 */    22,  205,  138,  125,   39,   36,   29,   30,   34,   33,
 /*   130 */    32,   31,   28,   27,   26,   25,   24,   23,   51,   22,
 /*   140 */   120,  119,   18,  118,  112,  111,  130,   83,   39,   36,
 /*   150 */    29,   30,   34,   33,   32,   31,   28,   27,   26,   25,
 /*   160 */    24,   23,  109,   22,  108,  127,   45,  141,   44,  128,
 /*   170 */     7,   41,   39,   36,   29,   30,   34,   33,   32,   31,
 /*   180 */    28,   27,   26,   25,   24,   23,  123,   22,  124,   39,
 /*   190 */    36,   29,   30,   34,   33,   32,   31,   28,   27,   26,
 /*   200 */    25,   24,   23,   78,   22,    4,   87,   36,   29,   30,
 /*   210 */    34,   33,   32,   31,   28,   27,   26,   25,   24,   23,
 /*   220 */    47,   22,    2,   29,   30,   34,   33,   32,   31,   28,
 /*   230 */    27,   26,   25,   24,   23,   20,   22,   16,  113,   21,
 /*   240 */   213,  213,  213,  213,   28,   27,   26,   25,   24,   23,
 /*   250 */     3,   22,   34,   33,   32,   31,   28,   27,   26,   25,
 /*   260 */    24,   23,  114,   22,   53,  128,   37,   85,  136,  135,
 /*   270 */   134,  133,  132,  131,   35,  126,  214,  103,   80,  140,
 /*   280 */    63,   79,   75,  215,   42,  121,   82,   80,  140,   63,
 /*   290 */    79,  137,   76,  215,  121,  101,   80,  140,   63,   79,
 /*   300 */   137,   76,  215,  121,   90,   80,  140,   63,   79,  137,
 /*   310 */    76,  215,  121,   89,   80,  140,   63,   79,  137,   76,
 /*   320 */    64,  121,   88,   80,  140,   63,   79,  137,   76,  215,
 /*   330 */   121,  137,  129,  122,  215,   62,  137,   76,  215,  215,
 /*   340 */   215,   48,   80,  140,   63,   79,  137,  129,  215,  121,
 /*   350 */   117,   80,  140,   63,   79,  137,   76,  215,  121,  110,
 /*   360 */    80,  140,   63,   79,  137,   76,  215,  121,   81,   80,
 /*   370 */   140,   63,   79,  137,   76,   61,  121,  100,   59,  107,
 /*   380 */    63,   79,  137,   76,  215,  121,  137,  129,  215,  137,
 /*   390 */   129,  137,   76,  215,  215,   61,  215,   93,  215,  215,
 /*   400 */    61,  215,   77,   61,  215,   86,  137,  129,   65,  215,
 /*   410 */    58,  137,  129,   71,  137,  129,  215,   70,  215,  137,
 /*   420 */   129,  137,  129,   69,  137,  129,   68,  215,  137,  129,
 /*   430 */    67,  215,   66,  215,  137,  129,   72,  137,  129,   74,
 /*   440 */   215,  137,  129,  137,  129,   73,  215,  137,  129,   99,
 /*   450 */   137,  129,  215,  215,   98,  215,  137,  129,  215,   97,
 /*   460 */   137,  129,   96,  215,   95,  137,  129,   94,  215,   57,
 /*   470 */   137,  129,   60,  137,  129,  137,  129,  215,  137,  129,
 /*   480 */   137,  129,   56,  137,  129,   55,  215,  215,  215,  215,
 /*   490 */   215,  215,  215,  137,  129,  215,  137,  129,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    11,   57,   58,   59,   15,   25,   17,   63,   21,   22,
 /*    10 */    43,   18,   23,   69,   70,   26,   27,   28,   29,   52,
 /*    20 */    31,    0,   33,   32,   19,   23,   37,   38,   39,   40,
 /*    30 */    41,   42,   52,   44,   45,   46,   47,   48,   49,   50,
 /*    40 */    11,   40,   41,   52,   15,   25,    9,   10,   11,   12,
 /*    50 */    13,   14,   23,   16,   52,   26,   27,   28,   29,   41,
 /*    60 */    31,   43,   33,   66,   67,   20,   37,   38,   39,   40,
 /*    70 */    41,   42,   52,   44,   45,   46,   47,   48,   49,   50,
 /*    80 */     1,    2,    3,    4,    5,    6,    7,    8,    9,   10,
 /*    90 */    11,   12,   13,   14,   25,   16,   24,    1,    2,    3,
 /*   100 */     4,    5,    6,    7,    8,    9,   10,   11,   12,   13,
 /*   110 */    14,    0,   16,   12,   13,   14,   52,   16,   41,   42,
 /*   120 */    16,   52,   43,   41,    1,    2,    3,    4,    5,    6,
 /*   130 */     7,    8,    9,   10,   11,   12,   13,   14,   41,   16,
 /*   140 */    24,   24,   30,   24,   41,   43,   50,   42,    1,    2,
 /*   150 */     3,    4,    5,    6,    7,    8,    9,   10,   11,   12,
 /*   160 */    13,   14,   24,   16,   24,   70,   68,   67,   42,   41,
 /*   170 */    23,   61,    1,    2,    3,    4,    5,    6,    7,    8,
 /*   180 */     9,   10,   11,   12,   13,   14,   41,   16,   67,    1,
 /*   190 */     2,    3,    4,    5,    6,    7,    8,    9,   10,   11,
 /*   200 */    12,   13,   14,   61,   16,   34,   65,    2,    3,    4,
 /*   210 */     5,    6,    7,    8,    9,   10,   11,   12,   13,   14,
 /*   220 */    64,   16,   34,    3,    4,    5,    6,    7,    8,    9,
 /*   230 */    10,   11,   12,   13,   14,   11,   16,   35,   71,   15,
 /*   240 */     5,    6,    7,    8,    9,   10,   11,   12,   13,   14,
 /*   250 */    36,   16,    5,    6,    7,    8,    9,   10,   11,   12,
 /*   260 */    13,   14,   67,   16,   40,   41,   42,   51,   44,   45,
 /*   270 */    46,   47,   48,   49,   50,   62,   54,   55,   56,   57,
 /*   280 */    58,   59,   61,   72,   61,   63,   55,   56,   57,   58,
 /*   290 */    59,   69,   70,   72,   63,   55,   56,   57,   58,   59,
 /*   300 */    69,   70,   72,   63,   55,   56,   57,   58,   59,   69,
 /*   310 */    70,   72,   63,   55,   56,   57,   58,   59,   69,   70,
 /*   320 */    58,   63,   55,   56,   57,   58,   59,   69,   70,   72,
 /*   330 */    63,   69,   70,   62,   72,   58,   69,   70,   72,   72,
 /*   340 */    72,   55,   56,   57,   58,   59,   69,   70,   72,   63,
 /*   350 */    55,   56,   57,   58,   59,   69,   70,   72,   63,   55,
 /*   360 */    56,   57,   58,   59,   69,   70,   72,   63,   55,   56,
 /*   370 */    57,   58,   59,   69,   70,   58,   63,   60,   58,   57,
 /*   380 */    58,   59,   69,   70,   72,   63,   69,   70,   72,   69,
 /*   390 */    70,   69,   70,   72,   72,   58,   72,   60,   72,   72,
 /*   400 */    58,   72,   60,   58,   72,   60,   69,   70,   58,   72,
 /*   410 */    58,   69,   70,   58,   69,   70,   72,   58,   72,   69,
 /*   420 */    70,   69,   70,   58,   69,   70,   58,   72,   69,   70,
 /*   430 */    58,   72,   58,   72,   69,   70,   58,   69,   70,   58,
 /*   440 */    72,   69,   70,   69,   70,   58,   72,   69,   70,   58,
 /*   450 */    69,   70,   72,   72,   58,   72,   69,   70,   72,   58,
 /*   460 */    69,   70,   58,   72,   58,   69,   70,   58,   72,   58,
 /*   470 */    69,   70,   58,   69,   70,   69,   70,   72,   69,   70,
 /*   480 */    69,   70,   58,   69,   70,   58,   72,   72,   72,   72,
 /*   490 */    72,   72,   72,   69,   70,   72,   69,   70,
};
#define YY_SHIFT_USE_DFLT (-34)
#define YY_SHIFT_COUNT (106)
#define YY_SHIFT_MIN   (-33)
#define YY_SHIFT_MAX   (247)
static const short yy_shift_ofst[] = {
 /*     0 */   -11,   29,   29,   29,   29,   29,   29,   29,   29,   29,
 /*    10 */    29,   29,  224,  224,  224,  224,  224,  224,  224,  224,
 /*    20 */   224,  224,  224,  224,  224,  224,  224,  224,  224,  224,
 /*    30 */   224,  224,  224,  224,  224,  224,  224,  224,  224,  224,
 /*    40 */    77,   20,   20,    1,   18,  216,  126,  214,  202,  145,
 /*    50 */   145,  126,  128,  126,  -34,  188,  171,  147,   96,   79,
 /*    60 */   123,  123,  123,  123,  205,  220,  247,  247,  235,  235,
 /*    70 */   235,  235,   37,  101,  101,  -33,   69,    2,   -9,  -20,
 /*    80 */   -13,  140,  138,  102,  105,  103,   64,  119,  117,  112,
 /*    90 */   116,   97,   82,   64,  104,  104,  104,  104,  104,  104,
 /*   100 */    64,   72,  111,   45,   21,    5,   -7,
};
#define YY_REDUCE_USE_DFLT (-57)
#define YY_REDUCE_COUNT (54)
#define YY_REDUCE_MIN   (-56)
#define YY_REDUCE_MAX   (427)
static const short yy_reduce_ofst[] = {
 /*     0 */   222,  313,  304,  295,  286,  267,  258,  249,  240,  231,
 /*    10 */   322,  -56,  345,  342,  337,  317,  427,  424,  414,  411,
 /*    20 */   409,  406,  404,  401,  396,  391,  387,  381,  378,  374,
 /*    30 */   372,  368,  365,  359,  355,  352,  350,  320,  277,  262,
 /*    40 */    -3,  271,  213,  223,  221,  167,  195,  141,  156,  142,
 /*    50 */   110,  121,   95,  100,   98,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   149,  149,  149,  149,  149,  149,  149,  149,  149,  149,
 /*    10 */   149,  149,  213,  213,  213,  213,  213,  213,  213,  213,
 /*    20 */   213,  213,  213,  213,  213,  213,  213,  213,  213,  213,
 /*    30 */   213,  213,  213,  213,  213,  213,  213,  213,  213,  213,
 /*    40 */   213,  155,  155,  213,  213,  171,  213,  164,  162,  213,
 /*    50 */   213,  213,  213,  213,  202,  213,  213,  213,  213,  213,
 /*    60 */   159,  208,  209,  150,  184,  185,  191,  190,  189,  188,
 /*    70 */   187,  186,  192,  194,  193,  213,  201,  213,  213,  213,
 /*    80 */   145,  213,  213,  213,  207,  213,  166,  213,  213,  213,
 /*    90 */   213,  213,  213,  156,  200,  199,  198,  197,  196,  195,
 /*   100 */   152,  213,  213,  213,  213,  213,  213,  148,  174,  173,
 /*   110 */   163,  212,  204,  203,  169,  168,  167,  165,  161,  160,
 /*   120 */   158,  157,  154,  210,  170,  211,  153,  206,  207,  201,
 /*   130 */   183,  182,  181,  180,  179,  178,  177,  176,  175,  151,
 /*   140 */   146,  172,  147,
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
  "EOS",           "NL",            "SCOLON",        "DO",          
  "END",           "ASSIG",         "LOCAL",         "GLOBAL",      
  "WHILE",         "REPEAT",        "UNTIL",         "FOR",         
  "IN",            "IF",            "THEN",          "ELSEIF",      
  "ELSE",          "RETURN",        "NEXT",          "BREAK",       
  "DEF",           "IDENT",         "PL",            "PR",          
  "NIL",           "FALSE",         "TRUE",          "INT",         
  "REAL",          "STRING",        "PIPE",          "DOT",         
  "COMMA",         "error",         "chunk",         "block",       
  "stat_list",     "stat",          "exp",           "var_list",    
  "exp_list",      "ident_list",    "var_init",      "functioncall",
  "elseif",        "else",          "func_ident",    "func_body",   
  "member_list",   "function",      "var",           "member",      
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "chunk ::= TERMINATION UNINITIALIZED WARNING",
 /*   1 */ "chunk ::= block EOS",
 /*   2 */ "block ::= stat_list",
 /*   3 */ "stat_list ::= stat",
 /*   4 */ "stat_list ::= stat_list NL stat",
 /*   5 */ "stat_list ::= stat_list SCOLON stat",
 /*   6 */ "stat ::=",
 /*   7 */ "stat ::= exp",
 /*   8 */ "stat ::= DO block END",
 /*   9 */ "stat ::= var_list ASSIG exp_list",
 /*  10 */ "stat ::= LOCAL ident_list var_init",
 /*  11 */ "stat ::= GLOBAL ident_list var_init",
 /*  12 */ "var_init ::=",
 /*  13 */ "var_init ::= ASSIG exp_list",
 /*  14 */ "stat ::= functioncall",
 /*  15 */ "stat ::= WHILE exp DO block END",
 /*  16 */ "stat ::= REPEAT block UNTIL exp",
 /*  17 */ "stat ::= FOR ident_list IN exp_list DO block END",
 /*  18 */ "stat ::= IF exp THEN block elseif else END",
 /*  19 */ "elseif ::=",
 /*  20 */ "elseif ::= ELSEIF exp THEN block",
 /*  21 */ "else ::=",
 /*  22 */ "else ::= ELSE block",
 /*  23 */ "stat ::= RETURN exp_list",
 /*  24 */ "stat ::= NEXT",
 /*  25 */ "stat ::= BREAK",
 /*  26 */ "stat ::= DEF func_ident func_body",
 /*  27 */ "stat ::= LOCAL DEF IDENT func_body",
 /*  28 */ "func_ident ::= IDENT member_list",
 /*  29 */ "function ::= DEF func_body",
 /*  30 */ "func_body ::= PL PR block END",
 /*  31 */ "func_body ::= PL ident_list PR block END",
 /*  32 */ "exp ::= PL exp PR",
 /*  33 */ "exp ::= function",
 /*  34 */ "exp ::= NIL",
 /*  35 */ "exp ::= FALSE",
 /*  36 */ "exp ::= TRUE",
 /*  37 */ "exp ::= INT",
 /*  38 */ "exp ::= REAL",
 /*  39 */ "exp ::= STRING",
 /*  40 */ "exp ::= PIPE exp PIPE",
 /*  41 */ "exp ::= exp OR exp",
 /*  42 */ "exp ::= exp AND exp",
 /*  43 */ "exp ::= exp L exp",
 /*  44 */ "exp ::= exp G exp",
 /*  45 */ "exp ::= exp LEQ exp",
 /*  46 */ "exp ::= exp GEQ exp",
 /*  47 */ "exp ::= exp NEQ exp",
 /*  48 */ "exp ::= exp EQ exp",
 /*  49 */ "exp ::= exp RANGEOP exp",
 /*  50 */ "exp ::= exp PLUS exp",
 /*  51 */ "exp ::= exp MINUS exp",
 /*  52 */ "exp ::= exp MUL exp",
 /*  53 */ "exp ::= exp DIV exp",
 /*  54 */ "exp ::= exp MOD exp",
 /*  55 */ "exp ::= exp EXP exp",
 /*  56 */ "exp ::= NOT exp",
 /*  57 */ "exp ::= MINUS exp",
 /*  58 */ "exp ::= var",
 /*  59 */ "member_list ::=",
 /*  60 */ "member_list ::= member_list member",
 /*  61 */ "member ::= DOT IDENT",
 /*  62 */ "var_list ::= var",
 /*  63 */ "var_list ::= var_list COMMA var",
 /*  64 */ "var ::= IDENT",
 /*  65 */ "exp_list ::= exp",
 /*  66 */ "exp_list ::= exp_list COMMA exp",
 /*  67 */ "ident_list ::= IDENT",
 /*  68 */ "ident_list ::= ident_list COMMA IDENT",
 /*  69 */ "functioncall ::= IDENT PL PR",
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
  { 54, 3 },
  { 54, 2 },
  { 55, 1 },
  { 56, 1 },
  { 56, 3 },
  { 56, 3 },
  { 57, 0 },
  { 57, 1 },
  { 57, 3 },
  { 57, 3 },
  { 57, 3 },
  { 57, 3 },
  { 62, 0 },
  { 62, 2 },
  { 57, 1 },
  { 57, 5 },
  { 57, 4 },
  { 57, 7 },
  { 57, 7 },
  { 64, 0 },
  { 64, 4 },
  { 65, 0 },
  { 65, 2 },
  { 57, 2 },
  { 57, 1 },
  { 57, 1 },
  { 57, 3 },
  { 57, 4 },
  { 66, 2 },
  { 69, 2 },
  { 67, 4 },
  { 67, 5 },
  { 58, 3 },
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
  { 58, 1 },
  { 68, 0 },
  { 68, 2 },
  { 71, 2 },
  { 59, 1 },
  { 59, 3 },
  { 70, 1 },
  { 60, 1 },
  { 60, 3 },
  { 61, 1 },
  { 61, 3 },
  { 63, 3 },
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
      case 6: /* stat ::= */
#line 62 "lparser.y"
{ yygotominor.yy0=NULL; }
#line 941 "lparser.c"
        break;
      case 7: /* stat ::= exp */
#line 63 "lparser.y"
{ yygotominor.yy0=yymsp[0].minor.yy0; }
#line 946 "lparser.c"
        break;
      case 8: /* stat ::= DO block END */
#line 64 "lparser.y"
{ yygotominor.yy0; }
#line 951 "lparser.c"
        break;
      case 32: /* exp ::= PL exp PR */
#line 105 "lparser.y"
{ yygotominor.yy0 = yymsp[-1].minor.yy0; }
#line 956 "lparser.c"
        break;
      case 33: /* exp ::= function */
      case 37: /* exp ::= INT */ yytestcase(yyruleno==37);
      case 38: /* exp ::= REAL */ yytestcase(yyruleno==38);
      case 39: /* exp ::= STRING */ yytestcase(yyruleno==39);
#line 106 "lparser.y"
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
#line 964 "lparser.c"
        break;
      case 34: /* exp ::= NIL */
#line 109 "lparser.y"
{ yygotominor.yy0 = new NilLitNode(); }
#line 969 "lparser.c"
        break;
      case 35: /* exp ::= FALSE */
#line 110 "lparser.y"
{ yygotominor.yy0 = new BoolLitNode(false); }
#line 974 "lparser.c"
        break;
      case 36: /* exp ::= TRUE */
#line 111 "lparser.y"
{ yygotominor.yy0 = new BoolLitNode(true); }
#line 979 "lparser.c"
        break;
      case 40: /* exp ::= PIPE exp PIPE */
#line 118 "lparser.y"
{ yygotominor.yy0 = new UnOpNode<'|'>(yymsp[-1].minor.yy0); }
#line 984 "lparser.c"
        break;
      case 41: /* exp ::= exp OR exp */
#line 120 "lparser.y"
{ yygotominor.yy0 = new OrNode(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 989 "lparser.c"
        break;
      case 42: /* exp ::= exp AND exp */
#line 121 "lparser.y"
{ yygotominor.yy0 = new AndNode(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 994 "lparser.c"
        break;
      case 43: /* exp ::= exp L exp */
#line 123 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'<'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 999 "lparser.c"
        break;
      case 44: /* exp ::= exp G exp */
#line 124 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'>'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1004 "lparser.c"
        break;
      case 45: /* exp ::= exp LEQ exp */
#line 125 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'<'+'='>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1009 "lparser.c"
        break;
      case 46: /* exp ::= exp GEQ exp */
#line 126 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'>'+'='>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1014 "lparser.c"
        break;
      case 47: /* exp ::= exp NEQ exp */
#line 127 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'!'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1019 "lparser.c"
        break;
      case 48: /* exp ::= exp EQ exp */
#line 128 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'='>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1024 "lparser.c"
        break;
      case 50: /* exp ::= exp PLUS exp */
#line 132 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'+'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1029 "lparser.c"
        break;
      case 51: /* exp ::= exp MINUS exp */
#line 133 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'-'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1034 "lparser.c"
        break;
      case 52: /* exp ::= exp MUL exp */
#line 135 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'*'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1039 "lparser.c"
        break;
      case 53: /* exp ::= exp DIV exp */
#line 136 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'/'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1044 "lparser.c"
        break;
      case 54: /* exp ::= exp MOD exp */
#line 137 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'%'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1049 "lparser.c"
        break;
      case 55: /* exp ::= exp EXP exp */
#line 139 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'^'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1054 "lparser.c"
        break;
      case 56: /* exp ::= NOT exp */
#line 141 "lparser.y"
{ yygotominor.yy0 = new UnOpNode<'!'>(yymsp[0].minor.yy0); }
#line 1059 "lparser.c"
        break;
      case 57: /* exp ::= MINUS exp */
#line 142 "lparser.y"
{ yygotominor.yy0 = new UnOpNode<'-'>(yymsp[0].minor.yy0); }
#line 1064 "lparser.c"
        break;
      default:
      /* (0) chunk ::= TERMINATION UNINITIALIZED WARNING */ yytestcase(yyruleno==0);
      /* (1) chunk ::= block EOS */ yytestcase(yyruleno==1);
      /* (2) block ::= stat_list */ yytestcase(yyruleno==2);
      /* (3) stat_list ::= stat */ yytestcase(yyruleno==3);
      /* (4) stat_list ::= stat_list NL stat */ yytestcase(yyruleno==4);
      /* (5) stat_list ::= stat_list SCOLON stat */ yytestcase(yyruleno==5);
      /* (9) stat ::= var_list ASSIG exp_list */ yytestcase(yyruleno==9);
      /* (10) stat ::= LOCAL ident_list var_init */ yytestcase(yyruleno==10);
      /* (11) stat ::= GLOBAL ident_list var_init */ yytestcase(yyruleno==11);
      /* (12) var_init ::= */ yytestcase(yyruleno==12);
      /* (13) var_init ::= ASSIG exp_list */ yytestcase(yyruleno==13);
      /* (14) stat ::= functioncall */ yytestcase(yyruleno==14);
      /* (15) stat ::= WHILE exp DO block END */ yytestcase(yyruleno==15);
      /* (16) stat ::= REPEAT block UNTIL exp */ yytestcase(yyruleno==16);
      /* (17) stat ::= FOR ident_list IN exp_list DO block END */ yytestcase(yyruleno==17);
      /* (18) stat ::= IF exp THEN block elseif else END */ yytestcase(yyruleno==18);
      /* (19) elseif ::= */ yytestcase(yyruleno==19);
      /* (20) elseif ::= ELSEIF exp THEN block */ yytestcase(yyruleno==20);
      /* (21) else ::= */ yytestcase(yyruleno==21);
      /* (22) else ::= ELSE block */ yytestcase(yyruleno==22);
      /* (23) stat ::= RETURN exp_list */ yytestcase(yyruleno==23);
      /* (24) stat ::= NEXT */ yytestcase(yyruleno==24);
      /* (25) stat ::= BREAK */ yytestcase(yyruleno==25);
      /* (26) stat ::= DEF func_ident func_body */ yytestcase(yyruleno==26);
      /* (27) stat ::= LOCAL DEF IDENT func_body */ yytestcase(yyruleno==27);
      /* (28) func_ident ::= IDENT member_list */ yytestcase(yyruleno==28);
      /* (29) function ::= DEF func_body */ yytestcase(yyruleno==29);
      /* (30) func_body ::= PL PR block END */ yytestcase(yyruleno==30);
      /* (31) func_body ::= PL ident_list PR block END */ yytestcase(yyruleno==31);
      /* (49) exp ::= exp RANGEOP exp */ yytestcase(yyruleno==49);
      /* (58) exp ::= var */ yytestcase(yyruleno==58);
      /* (59) member_list ::= */ yytestcase(yyruleno==59);
      /* (60) member_list ::= member_list member */ yytestcase(yyruleno==60);
      /* (61) member ::= DOT IDENT */ yytestcase(yyruleno==61);
      /* (62) var_list ::= var */ yytestcase(yyruleno==62);
      /* (63) var_list ::= var_list COMMA var */ yytestcase(yyruleno==63);
      /* (64) var ::= IDENT */ yytestcase(yyruleno==64);
      /* (65) exp_list ::= exp */ yytestcase(yyruleno==65);
      /* (66) exp_list ::= exp_list COMMA exp */ yytestcase(yyruleno==66);
      /* (67) ident_list ::= IDENT */ yytestcase(yyruleno==67);
      /* (68) ident_list ::= ident_list COMMA IDENT */ yytestcase(yyruleno==68);
      /* (69) functioncall ::= IDENT PL PR */ yytestcase(yyruleno==69);
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
#line 45 "lparser.y"

    throw AYA::ParseError("syntax error");
#line 1171 "lparser.c"
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
