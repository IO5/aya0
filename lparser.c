/* Driver template for the LEMON parser generator.
** The author disclaims copyright to this source code.
*/
/* First off, code is included that follows the "include" declaration
** in the input grammar file. */
#include <stdio.h>
#line 21 "lparser.y"

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
#define YYNOCODE 76
#define YYACTIONTYPE unsigned short int
#define LemonTOKENTYPE AYA::Node*
typedef union {
  int yyinit;
  LemonTOKENTYPE yy0;
  NodeList<>* yy5;
  NodeList<IdentNode>* yy7;
  NodeDictList* yy8;
  BlockNode* yy10;
  std::vector<std::pair<Node*, Node*> >* yy146;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define LemonARG_SDECL  AYA::Node** currentNode ;
#define LemonARG_PDECL , AYA::Node** currentNode 
#define LemonARG_FETCH  AYA::Node** currentNode  = yypParser->currentNode 
#define LemonARG_STORE yypParser->currentNode  = currentNode 
#define YYNSTATE 186
#define YYNRULE 82
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
#define YY_ACTTAB_COUNT (837)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    28,   80,  177,    9,   29,  131,  137,  135,  169,  176,
 /*    10 */    97,  101,  122,    8,  136,  134,  121,  162,   98,   23,
 /*    20 */     6,  178,  115,   46,   20,  186,   11,   10,   19,  154,
 /*    30 */   153,  111,   45,   43,   50,   14,  174,   13,  170,   12,
 /*    40 */    26,  168,  167,  166,  165,  164,  119,   40,   28,   80,
 /*    50 */   177,  132,   29,   96,   95,  183,  169,  176,   97,  100,
 /*    60 */   106,    8,  187,  118,  121,  162,   98,   23,    6,  182,
 /*    70 */   115,    1,   20,  184,   18,   55,   19,  154,  153,  111,
 /*    80 */    45,  142,   50,   60,  174,   13,   48,   12,  180,  168,
 /*    90 */   167,  166,  165,  164,   30,   40,   60,   49,   47,   36,
 /*   100 */    37,   44,   41,   39,   38,   35,   34,   33,   32,   31,
 /*   110 */   161,   30,   33,   32,   31,  120,   30,   96,   95,   49,
 /*   120 */    47,   36,   37,   44,   41,   39,   38,   35,   34,   33,
 /*   130 */    32,   31,   25,   30,   24,   49,   47,   36,   37,   44,
 /*   140 */    41,   39,   38,   35,   34,   33,   32,   31,   63,   30,
 /*   150 */    36,   37,   44,   41,   39,   38,   35,   34,   33,   32,
 /*   160 */    31,  175,   30,   49,   47,   36,   37,   44,   41,   39,
 /*   170 */    38,   35,   34,   33,   32,   31,  158,   30,   47,   36,
 /*   180 */    37,   44,   41,   39,   38,   35,   34,   33,   32,   31,
 /*   190 */    42,   30,   49,   47,   36,   37,   44,   41,   39,   38,
 /*   200 */    35,   34,   33,   32,   31,   22,   30,  268,  268,  268,
 /*   210 */   268,   35,   34,   33,   32,   31,  114,   30,   21,  163,
 /*   220 */   157,   49,   47,   36,   37,   44,   41,   39,   38,   35,
 /*   230 */    34,   33,   32,   31,  156,   30,   44,   41,   39,   38,
 /*   240 */    35,   34,   33,   32,   31,   46,   30,   27,  172,   49,
 /*   250 */    47,   36,   37,   44,   41,   39,   38,   35,   34,   33,
 /*   260 */    32,   31,   53,   30,    3,   15,  150,   62,  160,  107,
 /*   270 */    61,    7,   17,   49,   47,   36,   37,   44,   41,   39,
 /*   280 */    38,   35,   34,   33,   32,   31,  110,   30,   96,   95,
 /*   290 */    16,  143,  140,  139,  184,    5,   60,   49,   47,   36,
 /*   300 */    37,   44,   41,   39,   38,   35,   34,   33,   32,   31,
 /*   310 */   151,   30,  159,   49,   47,   36,   37,   44,   41,   39,
 /*   320 */    38,   35,   34,   33,   32,   31,   57,   30,   56,  149,
 /*   330 */   102,    4,  108,   49,   47,   36,   37,   44,   41,   39,
 /*   340 */    38,   35,   34,   33,   32,   31,   28,   30,  112,  109,
 /*   350 */    29,  146,  148,  141,  144,   58,  152,  269,  133,  103,
 /*   360 */   181,   84,  129,  162,   71,  177,  147,    2,  169,  176,
 /*   370 */    97,  169,  176,   97,  145,   99,  270,  270,   45,  179,
 /*   380 */    64,  270,  174,   13,  270,   12,  270,  168,  167,  166,
 /*   390 */   165,  164,  270,   40,   28,  270,  270,  270,   29,  185,
 /*   400 */    84,  129,  270,  270,  270,  270,  270,  169,  176,   97,
 /*   410 */   270,  162,  270,   49,   47,   36,   37,   44,   41,   39,
 /*   420 */    38,   35,   34,   33,   32,   31,   45,   30,   64,  270,
 /*   430 */   174,   13,  173,   12,  270,  168,  167,  166,  165,  164,
 /*   440 */   270,   40,   28,  270,  270,  270,   29,  270,  270,  270,
 /*   450 */   105,  103,  181,   84,  129,  270,  138,   84,  129,  162,
 /*   460 */   169,  176,   97,  270,  169,  176,   97,  270,  270,  270,
 /*   470 */   270,  270,  270,  270,   45,  270,   64,  270,  174,   13,
 /*   480 */   270,   12,  171,  168,  167,  166,  165,  164,  270,   40,
 /*   490 */    28,  270,  270,  270,   29,  270,   85,  177,  130,  103,
 /*   500 */   181,   84,  129,  169,  176,   97,  270,  162,  169,  176,
 /*   510 */    97,  270,  270,  270,  270,  270,  270,  270,  270,  270,
 /*   520 */   270,  270,   45,  270,   64,  270,  174,   13,  270,   12,
 /*   530 */   270,  168,  167,  166,  165,  164,  270,   40,  270,  117,
 /*   540 */   103,  181,   84,  129,  116,  103,  181,   84,  129,  169,
 /*   550 */   176,   97,  270,  270,  169,  176,   97,  270,  270,  113,
 /*   560 */   103,  181,   84,  129,  270,   83,  177,  270,  270,  169,
 /*   570 */   176,   97,  169,  176,   97,  270,  270,  270,  270,  270,
 /*   580 */   270,  270,  270,   59,  103,  181,   84,  129,  155,  103,
 /*   590 */   181,   84,  129,  169,  176,   97,  270,  270,  169,  176,
 /*   600 */    97,   54,  103,  181,   84,  129,  104,  103,  181,   84,
 /*   610 */   129,  169,  176,   97,   86,  177,  169,  176,   97,   79,
 /*   620 */   177,  169,  176,   97,   74,  177,  169,  176,   97,   87,
 /*   630 */   177,  169,  176,   97,   73,  177,  169,  176,   97,  270,
 /*   640 */   270,  169,  176,   97,  270,  270,  270,   82,  177,  270,
 /*   650 */    88,  177,  270,  270,  169,  176,   97,  169,  176,   97,
 /*   660 */   270,  270,   72,  177,  270,   92,  177,  270,  270,  169,
 /*   670 */   176,   97,  169,  176,   97,   91,  177,  270,   90,  177,
 /*   680 */   270,  270,  169,  176,   97,  169,  176,   97,   89,  177,
 /*   690 */   270,   94,  177,  270,  270,  169,  176,   97,  169,  176,
 /*   700 */    97,   93,  177,  270,  270,  128,  177,  270,  169,  176,
 /*   710 */    97,  270,  169,  176,   97,  127,  177,  270,  126,  177,
 /*   720 */   270,  270,  169,  176,   97,  169,  176,   97,  270,  125,
 /*   730 */   177,  270,  270,  124,  177,  270,  169,  176,   97,  270,
 /*   740 */   169,  176,   97,  123,  177,  270,   81,  177,  270,  270,
 /*   750 */   169,  176,   97,  169,  176,   97,   70,  177,  270,   78,
 /*   760 */   177,  270,  270,  169,  176,   97,  169,  176,   97,   77,
 /*   770 */   177,  270,   69,  177,  270,  270,  169,  176,   97,  169,
 /*   780 */   176,   97,   76,  177,  270,  270,   68,  177,  270,  169,
 /*   790 */   176,   97,  270,  169,  176,   97,  270,   67,  177,  270,
 /*   800 */    75,  177,  270,  270,  169,  176,   97,  169,  176,   97,
 /*   810 */    66,  177,  270,  270,   52,  177,  270,  169,  176,   97,
 /*   820 */   270,  169,  176,   97,   51,  177,  270,   65,  177,  270,
 /*   830 */   270,  169,  176,   97,  169,  176,   97,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    10,   63,   64,   43,   14,   45,   16,   18,   70,   71,
 /*    10 */    72,   73,   19,   23,   17,   19,   26,   27,   28,   29,
 /*    20 */    30,   43,   32,   45,   34,    0,   21,   22,   38,   39,
 /*    30 */    40,   41,   42,   45,   44,   42,   46,   47,   50,   49,
 /*    40 */    47,   51,   52,   53,   54,   55,   27,   57,   10,   63,
 /*    50 */    64,   20,   14,   21,   22,   27,   70,   71,   72,   73,
 /*    60 */    19,   23,    0,   44,   26,   27,   28,   29,   30,   27,
 /*    70 */    32,   43,   34,   67,   42,   69,   38,   39,   40,   41,
 /*    80 */    42,   27,   44,   42,   46,   47,   25,   49,   24,   51,
 /*    90 */    52,   53,   54,   55,   15,   57,   42,    1,    2,    3,
 /*   100 */     4,    5,    6,    7,    8,    9,   10,   11,   12,   13,
 /*   110 */    27,   15,   11,   12,   13,   27,   15,   21,   22,    1,
 /*   120 */     2,    3,    4,    5,    6,    7,    8,    9,   10,   11,
 /*   130 */    12,   13,   25,   15,   25,    1,    2,    3,    4,    5,
 /*   140 */     6,    7,    8,    9,   10,   11,   12,   13,   27,   15,
 /*   150 */     3,    4,    5,    6,    7,    8,    9,   10,   11,   12,
 /*   160 */    13,   43,   15,    1,    2,    3,    4,    5,    6,    7,
 /*   170 */     8,    9,   10,   11,   12,   13,   24,   15,    2,    3,
 /*   180 */     4,    5,    6,    7,    8,    9,   10,   11,   12,   13,
 /*   190 */    56,   15,    1,    2,    3,    4,    5,    6,    7,    8,
 /*   200 */     9,   10,   11,   12,   13,   31,   15,    5,    6,    7,
 /*   210 */     8,    9,   10,   11,   12,   13,   27,   15,   33,   57,
 /*   220 */    24,    1,    2,    3,    4,    5,    6,    7,    8,    9,
 /*   230 */    10,   11,   12,   13,   24,   15,    5,    6,    7,    8,
 /*   240 */     9,   10,   11,   12,   13,   45,   15,   56,   48,    1,
 /*   250 */     2,    3,    4,    5,    6,    7,    8,    9,   10,   11,
 /*   260 */    12,   13,   27,   15,   36,   37,   24,   27,   48,   27,
 /*   270 */    27,   23,   25,    1,    2,    3,    4,    5,    6,    7,
 /*   280 */     8,    9,   10,   11,   12,   13,   44,   15,   21,   22,
 /*   290 */    25,   27,   24,   24,   67,   23,   42,    1,    2,    3,
 /*   300 */     4,    5,    6,    7,    8,    9,   10,   11,   12,   13,
 /*   310 */    66,   15,   67,    1,    2,    3,    4,    5,    6,    7,
 /*   320 */     8,    9,   10,   11,   12,   13,   67,   15,   67,   24,
 /*   330 */    68,   35,   27,    1,    2,    3,    4,    5,    6,    7,
 /*   340 */     8,    9,   10,   11,   12,   13,   10,   15,   65,   44,
 /*   350 */    14,   66,   66,   65,   67,   43,   66,   59,   60,   61,
 /*   360 */    62,   63,   64,   27,   63,   64,   66,   35,   70,   71,
 /*   370 */    72,   70,   71,   72,   66,   74,   75,   75,   42,   43,
 /*   380 */    44,   75,   46,   47,   75,   49,   75,   51,   52,   53,
 /*   390 */    54,   55,   75,   57,   10,   75,   75,   75,   14,   62,
 /*   400 */    63,   64,   75,   75,   75,   75,   75,   70,   71,   72,
 /*   410 */    75,   27,   75,    1,    2,    3,    4,    5,    6,    7,
 /*   420 */     8,    9,   10,   11,   12,   13,   42,   15,   44,   75,
 /*   430 */    46,   47,   48,   49,   75,   51,   52,   53,   54,   55,
 /*   440 */    75,   57,   10,   75,   75,   75,   14,   75,   75,   75,
 /*   450 */    60,   61,   62,   63,   64,   75,   62,   63,   64,   27,
 /*   460 */    70,   71,   72,   75,   70,   71,   72,   75,   75,   75,
 /*   470 */    75,   75,   75,   75,   42,   75,   44,   75,   46,   47,
 /*   480 */    75,   49,   50,   51,   52,   53,   54,   55,   75,   57,
 /*   490 */    10,   75,   75,   75,   14,   75,   63,   64,   60,   61,
 /*   500 */    62,   63,   64,   70,   71,   72,   75,   27,   70,   71,
 /*   510 */    72,   75,   75,   75,   75,   75,   75,   75,   75,   75,
 /*   520 */    75,   75,   42,   75,   44,   75,   46,   47,   75,   49,
 /*   530 */    75,   51,   52,   53,   54,   55,   75,   57,   75,   60,
 /*   540 */    61,   62,   63,   64,   60,   61,   62,   63,   64,   70,
 /*   550 */    71,   72,   75,   75,   70,   71,   72,   75,   75,   60,
 /*   560 */    61,   62,   63,   64,   75,   63,   64,   75,   75,   70,
 /*   570 */    71,   72,   70,   71,   72,   75,   75,   75,   75,   75,
 /*   580 */    75,   75,   75,   60,   61,   62,   63,   64,   60,   61,
 /*   590 */    62,   63,   64,   70,   71,   72,   75,   75,   70,   71,
 /*   600 */    72,   60,   61,   62,   63,   64,   60,   61,   62,   63,
 /*   610 */    64,   70,   71,   72,   63,   64,   70,   71,   72,   63,
 /*   620 */    64,   70,   71,   72,   63,   64,   70,   71,   72,   63,
 /*   630 */    64,   70,   71,   72,   63,   64,   70,   71,   72,   75,
 /*   640 */    75,   70,   71,   72,   75,   75,   75,   63,   64,   75,
 /*   650 */    63,   64,   75,   75,   70,   71,   72,   70,   71,   72,
 /*   660 */    75,   75,   63,   64,   75,   63,   64,   75,   75,   70,
 /*   670 */    71,   72,   70,   71,   72,   63,   64,   75,   63,   64,
 /*   680 */    75,   75,   70,   71,   72,   70,   71,   72,   63,   64,
 /*   690 */    75,   63,   64,   75,   75,   70,   71,   72,   70,   71,
 /*   700 */    72,   63,   64,   75,   75,   63,   64,   75,   70,   71,
 /*   710 */    72,   75,   70,   71,   72,   63,   64,   75,   63,   64,
 /*   720 */    75,   75,   70,   71,   72,   70,   71,   72,   75,   63,
 /*   730 */    64,   75,   75,   63,   64,   75,   70,   71,   72,   75,
 /*   740 */    70,   71,   72,   63,   64,   75,   63,   64,   75,   75,
 /*   750 */    70,   71,   72,   70,   71,   72,   63,   64,   75,   63,
 /*   760 */    64,   75,   75,   70,   71,   72,   70,   71,   72,   63,
 /*   770 */    64,   75,   63,   64,   75,   75,   70,   71,   72,   70,
 /*   780 */    71,   72,   63,   64,   75,   75,   63,   64,   75,   70,
 /*   790 */    71,   72,   75,   70,   71,   72,   75,   63,   64,   75,
 /*   800 */    63,   64,   75,   75,   70,   71,   72,   70,   71,   72,
 /*   810 */    63,   64,   75,   75,   63,   64,   75,   70,   71,   72,
 /*   820 */    75,   70,   71,   72,   63,   64,   75,   63,   64,   75,
 /*   830 */    75,   70,   71,   72,   70,   71,   72,
};
#define YY_SHIFT_USE_DFLT (-41)
#define YY_SHIFT_COUNT (137)
#define YY_SHIFT_MIN   (-40)
#define YY_SHIFT_MAX   (480)
static const short yy_shift_ofst[] = {
 /*     0 */   -10,   38,   38,   38,   38,   38,   38,   38,   38,   38,
 /*    10 */    38,   38,  432,  384,  336,  480,  480,  480,  480,  480,
 /*    20 */   480,  480,  480,  480,  480,  480,  480,  480,  480,  480,
 /*    30 */   480,  480,  480,  480,  480,  480,  480,  480,  480,  480,
 /*    40 */   480,  480,  480,  480,  480,  480,  480,  480,  480,  480,
 /*    50 */    54,   96,   96,   32,  228,   41,  267,  267,  267,  228,
 /*    60 */    28,  254,  254,  254,  254,  332,  312,  296,  272,  248,
 /*    70 */   220,  191,  162,  134,  118,  412,  412,  412,  412,  412,
 /*    80 */   412,  412,  412,  412,  412,  176,  147,  202,  202,  231,
 /*    90 */   231,  202,  202,  101,  101,  305,  242,   -7,   19,  -12,
 /*   100 */   200,  -22,  -40,    5,  269,  268,  264,  265,  247,  243,
 /*   110 */   240,  235,  210,  196,  185,  189,  174,  152,  121,  109,
 /*   120 */   107,   88,   83,   79,   79,   79,   79,   79,   79,   61,
 /*   130 */    64,   42,   62,   31,   25,   -4,  -11,   -3,
};
#define YY_REDUCE_USE_DFLT (-63)
#define YY_REDUCE_COUNT (64)
#define YY_REDUCE_MIN   (-62)
#define YY_REDUCE_MAX   (764)
static const short yy_reduce_ofst[] = {
 /*     0 */   298,  546,  541,  528,  523,  499,  484,  479,  438,  390,
 /*    10 */   394,  337,  301,  -14,  -62,  764,  761,  751,  747,  737,
 /*    20 */   734,  723,  719,  709,  706,  696,  693,  683,  680,  670,
 /*    30 */   666,  655,  652,  642,  638,  628,  625,  615,  612,  602,
 /*    40 */   599,  587,  584,  571,  566,  561,  556,  551,  502,  433,
 /*    50 */     6,  308,  300,  290,  288,  287,  286,  285,  244,  283,
 /*    60 */   262,  261,  259,  245,  227,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   192,  192,  192,  192,  192,  192,  192,  192,  192,  192,
 /*    10 */   192,  192,  268,  268,  268,  268,  268,  268,  268,  268,
 /*    20 */   268,  268,  268,  268,  268,  268,  268,  268,  268,  268,
 /*    30 */   268,  268,  268,  268,  268,  268,  268,  268,  268,  268,
 /*    40 */   268,  268,  268,  268,  268,  268,  268,  268,  268,  268,
 /*    50 */   268,  268,  268,  268,  204,  268,  268,  268,  268,  204,
 /*    60 */   268,  268,  268,  268,  268,  268,  268,  268,  268,  268,
 /*    70 */   268,  268,  268,  268,  268,  207,  201,  199,  196,  267,
 /*    80 */   266,  244,  245,  195,  193,  247,  248,  249,  250,  254,
 /*    90 */   253,  252,  251,  256,  255,  268,  268,  237,  268,  268,
 /*   100 */   268,  268,  268,  188,  268,  268,  268,  268,  268,  268,
 /*   110 */   268,  268,  268,  268,  268,  268,  268,  268,  268,  198,
 /*   120 */   197,  268,  268,  262,  261,  260,  259,  258,  257,  229,
 /*   130 */   268,  268,  268,  268,  268,  268,  268,  268,  191,  225,
 /*   140 */   226,  206,  222,  223,  220,  216,  214,  217,  215,  213,
 /*   150 */   212,  211,  210,  209,  208,  205,  203,  202,  200,  221,
 /*   160 */   265,  264,  263,  246,  243,  242,  241,  240,  239,  238,
 /*   170 */   236,  235,  234,  233,  232,  231,  230,  229,  228,  227,
 /*   180 */   194,  189,  219,  218,  224,  190,
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
  "GEQ",           "PLUS",          "MINUS",         "MUL",         
  "DIV",           "MOD",           "NOT",           "EXP",         
  "TERMINATION",   "UNINITIALIZED",  "WARNING",       "DOT",         
  "EOS",           "NL",            "SCOLON",        "DO",          
  "END",           "ASSIG",         "GLOBAL",        "IDENT",       
  "LOCAL",         "WHILE",         "REPEAT",        "UNTIL",       
  "FOR",           "IN",            "IF",            "THEN",        
  "ELSE",          "ELSEIF",        "RETURN",        "NEXT",        
  "BREAK",         "CLASS",         "PL",            "PR",          
  "DEF",           "COMMA",         "STRING",        "SBL",         
  "SBR",           "CBL",           "CBR",           "NIL",         
  "FALSE",         "TRUE",          "INT",           "REAL",        
  "COLON",         "PIPE",          "error",         "chunk",       
  "block",         "stat_list",     "stat",          "exp",         
  "var",           "else",          "class_body",    "func_body",   
  "ident_list",    "func_ident",    "function",      "functioncall",
  "prefixexp",     "exp_list",      "dict_list",   
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
 /*  69 */ "exp ::= exp PLUS exp",
 /*  70 */ "exp ::= exp MINUS exp",
 /*  71 */ "exp ::= exp MUL exp",
 /*  72 */ "exp ::= exp DIV exp",
 /*  73 */ "exp ::= exp MOD exp",
 /*  74 */ "exp ::= exp EXP exp",
 /*  75 */ "exp ::= NOT exp",
 /*  76 */ "exp ::= MINUS exp",
 /*  77 */ "var ::= IDENT",
 /*  78 */ "var ::= prefixexp DOT IDENT",
 /*  79 */ "var ::= prefixexp SBL exp SBR",
 /*  80 */ "exp_list ::= exp",
 /*  81 */ "exp_list ::= exp_list COMMA exp",
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
  { 59, 4 },
  { 59, 2 },
  { 60, 1 },
  { 61, 1 },
  { 61, 3 },
  { 61, 3 },
  { 62, 0 },
  { 62, 1 },
  { 62, 3 },
  { 62, 3 },
  { 62, 4 },
  { 62, 2 },
  { 62, 2 },
  { 62, 4 },
  { 62, 5 },
  { 62, 4 },
  { 62, 7 },
  { 62, 6 },
  { 65, 0 },
  { 65, 2 },
  { 65, 5 },
  { 62, 2 },
  { 62, 1 },
  { 62, 1 },
  { 62, 3 },
  { 62, 6 },
  { 66, 2 },
  { 66, 2 },
  { 66, 5 },
  { 66, 5 },
  { 66, 5 },
  { 66, 5 },
  { 68, 1 },
  { 68, 3 },
  { 62, 3 },
  { 62, 4 },
  { 69, 1 },
  { 69, 3 },
  { 70, 2 },
  { 67, 4 },
  { 67, 5 },
  { 71, 3 },
  { 71, 4 },
  { 72, 1 },
  { 72, 1 },
  { 72, 3 },
  { 72, 1 },
  { 72, 2 },
  { 72, 3 },
  { 72, 2 },
  { 72, 3 },
  { 63, 1 },
  { 63, 1 },
  { 63, 1 },
  { 63, 1 },
  { 63, 1 },
  { 63, 1 },
  { 63, 1 },
  { 74, 3 },
  { 74, 5 },
  { 63, 3 },
  { 63, 3 },
  { 63, 3 },
  { 63, 3 },
  { 63, 3 },
  { 63, 3 },
  { 63, 3 },
  { 63, 3 },
  { 63, 3 },
  { 63, 3 },
  { 63, 3 },
  { 63, 3 },
  { 63, 3 },
  { 63, 3 },
  { 63, 3 },
  { 63, 2 },
  { 63, 2 },
  { 64, 1 },
  { 64, 3 },
  { 64, 4 },
  { 73, 1 },
  { 73, 3 },
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
#line 67 "lparser.y"
{ *currentNode = yygotominor.yy0 = yymsp[-1].minor.yy10; }
#line 1063 "lparser.c"
        break;
      case 2: /* block ::= stat_list */
#line 71 "lparser.y"
{ yygotominor.yy10 = new BlockNode(yymsp[0].minor.yy5);  }
#line 1068 "lparser.c"
        break;
      case 3: /* stat_list ::= stat */
#line 73 "lparser.y"
{ yygotominor.yy5 = new NodeList<>(); if(yymsp[0].minor.yy0){ yygotominor.yy5->push_back(yymsp[0].minor.yy0); }  }
#line 1073 "lparser.c"
        break;
      case 4: /* stat_list ::= stat_list NL stat */
      case 5: /* stat_list ::= stat_list SCOLON stat */ yytestcase(yyruleno==5);
#line 74 "lparser.y"
{ yygotominor.yy5 = yymsp[-2].minor.yy5;  if(yymsp[0].minor.yy0){ yygotominor.yy5->push_back(yymsp[0].minor.yy0); }  }
#line 1079 "lparser.c"
        break;
      case 6: /* stat ::= */
      case 18: /* else ::= */ yytestcase(yyruleno==18);
#line 78 "lparser.y"
{ yygotominor.yy0 = NULL; }
#line 1085 "lparser.c"
        break;
      case 7: /* stat ::= exp */
#line 79 "lparser.y"
{ yygotominor.yy0 = new StatNode(yymsp[0].minor.yy0); }
#line 1090 "lparser.c"
        break;
      case 8: /* stat ::= DO block END */
#line 80 "lparser.y"
{ yygotominor.yy0 = yymsp[-1].minor.yy10; yymsp[-1].minor.yy10->createScope(); }
#line 1095 "lparser.c"
        break;
      case 9: /* stat ::= var ASSIG exp */
#line 83 "lparser.y"
{ yygotominor.yy0 = new AssignNode(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1100 "lparser.c"
        break;
      case 10: /* stat ::= GLOBAL IDENT ASSIG exp */
#line 84 "lparser.y"
{ yygotominor.yy0 = new AssignNode(new VarNode(yymsp[-2].minor.yy0), yymsp[0].minor.yy0); }
#line 1105 "lparser.c"
        break;
      case 11: /* stat ::= GLOBAL IDENT */
#line 85 "lparser.y"
{ yygotominor.yy0 = new AssignNode(new VarNode(yymsp[0].minor.yy0), new NilLitNode()); }
#line 1110 "lparser.c"
        break;
      case 12: /* stat ::= LOCAL IDENT */
#line 87 "lparser.y"
{ yygotominor.yy0 = new DeclNode(yymsp[0].minor.yy0, NULL); }
#line 1115 "lparser.c"
        break;
      case 13: /* stat ::= LOCAL IDENT ASSIG exp */
#line 88 "lparser.y"
{ yygotominor.yy0 = new DeclNode(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1120 "lparser.c"
        break;
      case 14: /* stat ::= WHILE exp DO block END */
#line 97 "lparser.y"
{ yygotominor.yy0 = new WhileNode(yymsp[-3].minor.yy0, yymsp[-1].minor.yy10); }
#line 1125 "lparser.c"
        break;
      case 15: /* stat ::= REPEAT block UNTIL exp */
#line 99 "lparser.y"
{ yygotominor.yy0 = new RepeatNode(yymsp[0].minor.yy0, yymsp[-2].minor.yy10); }
#line 1130 "lparser.c"
        break;
      case 16: /* stat ::= FOR IDENT IN exp DO block END */
#line 101 "lparser.y"
{ yygotominor.yy0 = new ForNode(yymsp[-5].minor.yy0, yymsp[-3].minor.yy0, yymsp[-1].minor.yy10); }
#line 1135 "lparser.c"
        break;
      case 17: /* stat ::= IF exp THEN block else END */
#line 103 "lparser.y"
{ yygotominor.yy0 = new IfNode(yymsp[-4].minor.yy0, yymsp[-2].minor.yy10, yymsp[-1].minor.yy0); }
#line 1140 "lparser.c"
        break;
      case 19: /* else ::= ELSE block */
#line 105 "lparser.y"
{ yygotominor.yy0 = yymsp[0].minor.yy10; }
#line 1145 "lparser.c"
        break;
      case 20: /* else ::= ELSEIF exp THEN block else */
#line 106 "lparser.y"
{ yygotominor.yy0 = new IfNode(yymsp[-3].minor.yy0, yymsp[-1].minor.yy10, yymsp[0].minor.yy0); }
#line 1150 "lparser.c"
        break;
      case 21: /* stat ::= RETURN exp */
#line 109 "lparser.y"
{ yygotominor.yy0 = new ReturnNode(yymsp[0].minor.yy0); }
#line 1155 "lparser.c"
        break;
      case 24: /* stat ::= CLASS IDENT class_body */
#line 115 "lparser.y"
{ yygotominor.yy0 = new ClassNode(yymsp[-1].minor.yy0, NULL, yymsp[0].minor.yy146); }
#line 1160 "lparser.c"
        break;
      case 25: /* stat ::= CLASS IDENT PL exp PR class_body */
#line 116 "lparser.y"
{ yygotominor.yy0 = new ClassNode(yymsp[-4].minor.yy0, yymsp[-2].minor.yy0, yymsp[0].minor.yy146); }
#line 1165 "lparser.c"
        break;
      case 26: /* class_body ::= NL END */
      case 27: /* class_body ::= SCOLON END */ yytestcase(yyruleno==27);
#line 117 "lparser.y"
{ yygotominor.yy146 = new std::vector<std::pair<Node*, Node*> >(); }
#line 1171 "lparser.c"
        break;
      case 28: /* class_body ::= NL DEF IDENT func_body class_body */
      case 29: /* class_body ::= SCOLON DEF IDENT func_body class_body */ yytestcase(yyruleno==29);
#line 119 "lparser.y"
{ yygotominor.yy146 = yymsp[0].minor.yy146; yymsp[0].minor.yy146->push_back(std::make_pair(yymsp[-2].minor.yy0, yymsp[-1].minor.yy0)); }
#line 1177 "lparser.c"
        break;
      case 30: /* class_body ::= NL IDENT ASSIG exp class_body */
      case 31: /* class_body ::= SCOLON IDENT ASSIG exp class_body */ yytestcase(yyruleno==31);
#line 121 "lparser.y"
{ yygotominor.yy146 = yymsp[0].minor.yy146; yymsp[0].minor.yy146->push_back(std::make_pair(yymsp[-3].minor.yy0, yymsp[-1].minor.yy0)); }
#line 1183 "lparser.c"
        break;
      case 32: /* ident_list ::= IDENT */
#line 127 "lparser.y"
{
    yygotominor.yy7 = new NodeList<IdentNode>();

    assert(dynamic_cast<IdentNode*>(yymsp[0].minor.yy0));
    yygotominor.yy7->push_back(static_cast<IdentNode*>(yymsp[0].minor.yy0));

}
#line 1194 "lparser.c"
        break;
      case 33: /* ident_list ::= ident_list COMMA IDENT */
#line 135 "lparser.y"
{
    yygotominor.yy7 = yymsp[-2].minor.yy7;

    assert(dynamic_cast<IdentNode*>(yymsp[0].minor.yy0));
    yygotominor.yy7->push_back(static_cast<IdentNode*>(yymsp[0].minor.yy0));
}
#line 1204 "lparser.c"
        break;
      case 34: /* stat ::= DEF func_ident func_body */
#line 142 "lparser.y"
{ yygotominor.yy0 = new AssignNode(yymsp[-1].minor.yy0, yymsp[0].minor.yy0); }
#line 1209 "lparser.c"
        break;
      case 35: /* stat ::= LOCAL DEF IDENT func_body */
#line 143 "lparser.y"
{ yygotominor.yy0 = new DeclNode(yymsp[-1].minor.yy0, yymsp[0].minor.yy0); }
#line 1214 "lparser.c"
        break;
      case 36: /* func_ident ::= IDENT */
      case 77: /* var ::= IDENT */ yytestcase(yyruleno==77);
#line 144 "lparser.y"
{ yygotominor.yy0 = new VarNode(yymsp[0].minor.yy0); }
#line 1220 "lparser.c"
        break;
      case 37: /* func_ident ::= func_ident DOT IDENT */
      case 78: /* var ::= prefixexp DOT IDENT */ yytestcase(yyruleno==78);
#line 145 "lparser.y"
{ yygotominor.yy0 = new MemberAccessNode(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1226 "lparser.c"
        break;
      case 38: /* function ::= DEF func_body */
      case 43: /* prefixexp ::= var */ yytestcase(yyruleno==43);
      case 44: /* prefixexp ::= functioncall */ yytestcase(yyruleno==44);
      case 46: /* prefixexp ::= STRING */ yytestcase(yyruleno==46);
      case 51: /* exp ::= prefixexp */ yytestcase(yyruleno==51);
      case 52: /* exp ::= function */ yytestcase(yyruleno==52);
      case 56: /* exp ::= INT */ yytestcase(yyruleno==56);
      case 57: /* exp ::= REAL */ yytestcase(yyruleno==57);
#line 148 "lparser.y"
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
#line 1238 "lparser.c"
        break;
      case 39: /* func_body ::= PL PR block END */
#line 149 "lparser.y"
{ yygotominor.yy0 = new FuncNode(NULL, yymsp[-1].minor.yy10); }
#line 1243 "lparser.c"
        break;
      case 40: /* func_body ::= PL ident_list PR block END */
#line 150 "lparser.y"
{ yygotominor.yy0 = new FuncNode(yymsp[-3].minor.yy7, yymsp[-1].minor.yy10); }
#line 1248 "lparser.c"
        break;
      case 41: /* functioncall ::= prefixexp PL PR */
#line 152 "lparser.y"
{ yygotominor.yy0 = new CallNode(yymsp[-2].minor.yy0, NULL); }
#line 1253 "lparser.c"
        break;
      case 42: /* functioncall ::= prefixexp PL exp_list PR */
#line 153 "lparser.y"
{ yygotominor.yy0 = new CallNode(yymsp[-3].minor.yy0, yymsp[-1].minor.yy5); }
#line 1258 "lparser.c"
        break;
      case 45: /* prefixexp ::= PL exp PR */
#line 157 "lparser.y"
{ yygotominor.yy0 = yymsp[-1].minor.yy0; }
#line 1263 "lparser.c"
        break;
      case 47: /* prefixexp ::= SBL SBR */
#line 162 "lparser.y"
{ yygotominor.yy0 = new ListConstrNode(NULL); }
#line 1268 "lparser.c"
        break;
      case 48: /* prefixexp ::= SBL exp_list SBR */
#line 163 "lparser.y"
{ yygotominor.yy0 = new ListConstrNode(yymsp[-1].minor.yy5); }
#line 1273 "lparser.c"
        break;
      case 49: /* prefixexp ::= CBL CBR */
#line 164 "lparser.y"
{ yygotominor.yy0 = new DictConstrNode(NULL); }
#line 1278 "lparser.c"
        break;
      case 50: /* prefixexp ::= CBL dict_list CBR */
#line 165 "lparser.y"
{ yygotominor.yy0 = new DictConstrNode(yymsp[-1].minor.yy8); }
#line 1283 "lparser.c"
        break;
      case 53: /* exp ::= NIL */
#line 171 "lparser.y"
{ yygotominor.yy0 = new NilLitNode(); }
#line 1288 "lparser.c"
        break;
      case 54: /* exp ::= FALSE */
#line 172 "lparser.y"
{ yygotominor.yy0 = new BoolLitNode(false); }
#line 1293 "lparser.c"
        break;
      case 55: /* exp ::= TRUE */
#line 173 "lparser.y"
{ yygotominor.yy0 = new BoolLitNode(true); }
#line 1298 "lparser.c"
        break;
      case 58: /* dict_list ::= exp COLON exp */
#line 180 "lparser.y"
{ yygotominor.yy8 = new NodeDictList(); yygotominor.yy8->push_back(std::make_pair(yymsp[-2].minor.yy0, yymsp[0].minor.yy0)); }
#line 1303 "lparser.c"
        break;
      case 59: /* dict_list ::= dict_list COMMA exp COLON exp */
#line 181 "lparser.y"
{ yygotominor.yy8 = yymsp[-4].minor.yy8; yygotominor.yy8->push_back(std::make_pair(yymsp[-2].minor.yy0, yymsp[0].minor.yy0)); }
#line 1308 "lparser.c"
        break;
      case 60: /* exp ::= PIPE exp PIPE */
#line 185 "lparser.y"
{ yygotominor.yy0 = new UnOpNode<'|'>(yymsp[-1].minor.yy0); }
#line 1313 "lparser.c"
        break;
      case 61: /* exp ::= exp OR exp */
#line 187 "lparser.y"
{ yygotominor.yy0 = new OrNode(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1318 "lparser.c"
        break;
      case 62: /* exp ::= exp AND exp */
#line 188 "lparser.y"
{ yygotominor.yy0 = new AndNode(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1323 "lparser.c"
        break;
      case 63: /* exp ::= exp L exp */
#line 190 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'<'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1328 "lparser.c"
        break;
      case 64: /* exp ::= exp G exp */
#line 191 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'>'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1333 "lparser.c"
        break;
      case 65: /* exp ::= exp LEQ exp */
#line 192 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'<'+'='>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1338 "lparser.c"
        break;
      case 66: /* exp ::= exp GEQ exp */
#line 193 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'>'+'='>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1343 "lparser.c"
        break;
      case 67: /* exp ::= exp NEQ exp */
#line 194 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'!'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1348 "lparser.c"
        break;
      case 68: /* exp ::= exp EQ exp */
#line 195 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'='>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1353 "lparser.c"
        break;
      case 69: /* exp ::= exp PLUS exp */
#line 197 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'+'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1358 "lparser.c"
        break;
      case 70: /* exp ::= exp MINUS exp */
#line 198 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'-'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1363 "lparser.c"
        break;
      case 71: /* exp ::= exp MUL exp */
#line 200 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'*'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1368 "lparser.c"
        break;
      case 72: /* exp ::= exp DIV exp */
#line 201 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'/'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1373 "lparser.c"
        break;
      case 73: /* exp ::= exp MOD exp */
#line 202 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'%'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1378 "lparser.c"
        break;
      case 74: /* exp ::= exp EXP exp */
#line 204 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'^'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1383 "lparser.c"
        break;
      case 75: /* exp ::= NOT exp */
#line 206 "lparser.y"
{ yygotominor.yy0 = new UnOpNode<'!'>(yymsp[0].minor.yy0); }
#line 1388 "lparser.c"
        break;
      case 76: /* exp ::= MINUS exp */
#line 207 "lparser.y"
{ yygotominor.yy0 = new UnOpNode<'-'>(yymsp[0].minor.yy0); }
#line 1393 "lparser.c"
        break;
      case 79: /* var ::= prefixexp SBL exp SBR */
#line 214 "lparser.y"
{ yygotominor.yy0 = new IndexAccessNode(yymsp[-3].minor.yy0, yymsp[-1].minor.yy0); }
#line 1398 "lparser.c"
        break;
      case 80: /* exp_list ::= exp */
#line 217 "lparser.y"
{ yygotominor.yy5 = new NodeList<>(); yygotominor.yy5->push_back(yymsp[0].minor.yy0); }
#line 1403 "lparser.c"
        break;
      case 81: /* exp_list ::= exp_list COMMA exp */
#line 218 "lparser.y"
{ yygotominor.yy5 = yymsp[-2].minor.yy5; yygotominor.yy5->push_back(yymsp[0].minor.yy0); }
#line 1408 "lparser.c"
        break;
      default:
      /* (0) chunk ::= TERMINATION UNINITIALIZED WARNING DOT */ yytestcase(yyruleno==0);
      /* (22) stat ::= NEXT */ yytestcase(yyruleno==22);
      /* (23) stat ::= BREAK */ yytestcase(yyruleno==23);
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
#line 60 "lparser.y"

    throw AYA::ParseError("syntax error");
#line 1476 "lparser.c"
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
