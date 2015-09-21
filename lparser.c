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
#define YYNSTATE 180
#define YYNRULE 81
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
#define YY_ACTTAB_COUNT (805)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    26,    9,  118,  127,   27,   42,  133,  261,   33,   32,
 /*    10 */    31,   30,   29,    8,   28,  158,  117,  156,   96,   21,
 /*    20 */     6,  172,  111,   45,   18,   14,  132,  177,   17,  148,
 /*    30 */   147,  107,   44,  131,   49,   24,  170,  166,  165,  164,
 /*    40 */   163,  162,   13,    1,   12,  138,   26,   39,   77,  171,
 /*    50 */    27,   95,   94,   11,   10,  167,  169,   93,   99,    8,
 /*    60 */    57,   45,  117,  156,   96,   21,    6,  130,  111,  160,
 /*    70 */    18,  104,   16,  180,   17,  148,  147,  107,   44,  178,
 /*    80 */    49,   52,  170,  166,  165,  164,  163,  162,   13,  128,
 /*    90 */    12,  144,  115,   39,   57,   48,   46,   35,   36,   43,
 /*   100 */    40,   38,   37,   34,   33,   32,   31,   30,   29,  114,
 /*   110 */    28,  106,   48,   46,   35,   36,   43,   40,   38,   37,
 /*   120 */    34,   33,   32,   31,   30,   29,  181,   28,  261,  261,
 /*   130 */   261,  261,   34,   33,   32,   31,   30,   29,  168,   28,
 /*   140 */    48,   46,   35,   36,   43,   40,   38,   37,   34,   33,
 /*   150 */    32,   31,   30,   29,  174,   28,   35,   36,   43,   40,
 /*   160 */    38,   37,   34,   33,   32,   31,   30,   29,   41,   28,
 /*   170 */    48,   46,   35,   36,   43,   40,   38,   37,   34,   33,
 /*   180 */    32,   31,   30,   29,  176,   28,   47,   43,   40,   38,
 /*   190 */    37,   34,   33,   32,   31,   30,   29,  157,   28,   48,
 /*   200 */    46,   35,   36,   43,   40,   38,   37,   34,   33,   32,
 /*   210 */    31,   30,   29,   28,   28,   77,  171,   31,   30,   29,
 /*   220 */   155,   28,  167,  169,   93,   98,   25,  143,   48,   46,
 /*   230 */    35,   36,   43,   40,   38,   37,   34,   33,   32,   31,
 /*   240 */    30,   29,  116,   28,    3,   15,   23,  105,   95,   94,
 /*   250 */    22,    7,  154,   48,   46,   35,   36,   43,   40,   38,
 /*   260 */    37,   34,   33,   32,   31,   30,   29,   60,   28,  152,
 /*   270 */    20,  110,  151,  150,   19,  136,    5,   50,   48,   46,
 /*   280 */    35,   36,   43,   40,   38,   37,   34,   33,   32,   31,
 /*   290 */    30,   29,   59,   28,   58,   48,   46,   35,   36,   43,
 /*   300 */    40,   38,   37,   34,   33,   32,   31,   30,   29,  139,
 /*   310 */    28,  135,  145,    4,  178,   48,   46,   35,   36,   43,
 /*   320 */    40,   38,   37,   34,   33,   32,   31,   30,   29,  153,
 /*   330 */    28,   57,  100,   68,  171,   54,   53,  108,   55,  141,
 /*   340 */   167,  169,   93,  142,   97,  137,  140,  146,  263,  263,
 /*   350 */     2,  263,   48,   46,   35,   36,   43,   40,   38,   37,
 /*   360 */    34,   33,   32,   31,   30,   29,   26,   28,  263,  263,
 /*   370 */    27,  263,  263,  263,  263,  263,  262,  129,  101,  175,
 /*   380 */    81,  125,  263,  156,  179,   81,  125,  167,  169,   93,
 /*   390 */   263,  263,  167,  169,   93,  263,  263,  263,   44,  173,
 /*   400 */    61,  263,  170,  166,  165,  164,  163,  162,   13,  263,
 /*   410 */    12,   26,  263,   39,  263,   27,  263,  263,  263,  263,
 /*   420 */   103,  101,  175,   81,  125,   26,   82,  171,  156,   27,
 /*   430 */   167,  169,   93,  167,  169,   93,  263,  263,  263,  263,
 /*   440 */   263,  263,  156,   44,  263,   61,  263,  170,  166,  165,
 /*   450 */   164,  163,  162,   13,  161,   12,  263,   44,   39,   61,
 /*   460 */   263,  170,  166,  165,  164,  163,  162,   13,  263,   12,
 /*   470 */   159,  263,   39,   46,   35,   36,   43,   40,   38,   37,
 /*   480 */    34,   33,   32,   31,   30,   29,   26,   28,  263,  263,
 /*   490 */    27,  263,   80,  171,  126,  101,  175,   81,  125,  167,
 /*   500 */   169,   93,  263,  156,  167,  169,   93,  134,   81,  125,
 /*   510 */   263,  263,  263,  263,  263,  167,  169,   93,   44,  263,
 /*   520 */    61,  263,  170,  166,  165,  164,  163,  162,   13,  263,
 /*   530 */    12,  263,  263,   39,  113,  101,  175,   81,  125,  112,
 /*   540 */   101,  175,   81,  125,  167,  169,   93,  263,  263,  167,
 /*   550 */   169,   93,  109,  101,  175,   81,  125,   56,  101,  175,
 /*   560 */    81,  125,  167,  169,   93,   83,  171,  167,  169,   93,
 /*   570 */    76,  171,  167,  169,   93,  263,  263,  167,  169,   93,
 /*   580 */   149,  101,  175,   81,  125,   51,  101,  175,   81,  125,
 /*   590 */   167,  169,   93,  263,  263,  167,  169,   93,  102,  101,
 /*   600 */   175,   81,  125,  263,   71,  171,  263,  263,  167,  169,
 /*   610 */    93,  167,  169,   93,   84,  171,  263,   70,  171,  263,
 /*   620 */   263,  167,  169,   93,  167,  169,   93,   79,  171,  263,
 /*   630 */    85,  171,  263,  263,  167,  169,   93,  167,  169,   93,
 /*   640 */   263,  263,   69,  171,  263,   89,  171,  263,  263,  167,
 /*   650 */   169,   93,  167,  169,   93,   88,  171,  263,  263,  263,
 /*   660 */    87,  171,  167,  169,   93,   86,  171,  167,  169,   93,
 /*   670 */    90,  171,  167,  169,   93,   92,  171,  167,  169,   93,
 /*   680 */    91,  171,  167,  169,   93,  263,  263,  167,  169,   93,
 /*   690 */   124,  171,  263,  123,  171,  263,  263,  167,  169,   93,
 /*   700 */   167,  169,   93,  122,  171,  263,  263,  121,  171,  263,
 /*   710 */   167,  169,   93,  263,  167,  169,   93,  120,  171,  263,
 /*   720 */   119,  171,  263,  263,  167,  169,   93,  167,  169,   93,
 /*   730 */    78,  171,  263,   67,  171,  263,  263,  167,  169,   93,
 /*   740 */   167,  169,   93,   75,  171,  263,   74,  171,  263,  263,
 /*   750 */   167,  169,   93,  167,  169,   93,   66,  171,  263,   73,
 /*   760 */   171,  263,  263,  167,  169,   93,  167,  169,   93,   65,
 /*   770 */   171,  263,   64,  171,  263,  263,  167,  169,   93,  167,
 /*   780 */   169,   93,   72,  171,  263,   63,  171,  263,  263,  167,
 /*   790 */   169,   93,  167,  169,   93,   62,  171,  263,  263,  263,
 /*   800 */   263,  263,  167,  169,   93,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    11,   44,   20,   46,   15,   46,   17,    9,   10,   11,
 /*    10 */    12,   13,   14,   24,   16,   56,   27,   28,   29,   30,
 /*    20 */    31,   44,   33,   46,   35,   43,   18,   28,   39,   40,
 /*    30 */    41,   42,   43,   19,   45,   53,   47,   48,   49,   50,
 /*    40 */    51,   52,   53,   44,   55,   28,   11,   58,   64,   65,
 /*    50 */    15,   22,   23,   22,   23,   71,   72,   73,   74,   24,
 /*    60 */    43,   46,   27,   28,   29,   30,   31,   20,   33,   54,
 /*    70 */    35,   20,   43,    0,   39,   40,   41,   42,   43,   68,
 /*    80 */    45,   70,   47,   48,   49,   50,   51,   52,   53,   21,
 /*    90 */    55,   25,   28,   58,   43,    1,    2,    3,    4,    5,
 /*   100 */     6,    7,    8,    9,   10,   11,   12,   13,   14,   45,
 /*   110 */    16,   45,    1,    2,    3,    4,    5,    6,    7,    8,
 /*   120 */     9,   10,   11,   12,   13,   14,    0,   16,    5,    6,
 /*   130 */     7,    8,    9,   10,   11,   12,   13,   14,   44,   16,
 /*   140 */     1,    2,    3,    4,    5,    6,    7,    8,    9,   10,
 /*   150 */    11,   12,   13,   14,   25,   16,    3,    4,    5,    6,
 /*   160 */     7,    8,    9,   10,   11,   12,   13,   14,   57,   16,
 /*   170 */     1,    2,    3,    4,    5,    6,    7,    8,    9,   10,
 /*   180 */    11,   12,   13,   14,   28,   16,   26,    5,    6,    7,
 /*   190 */     8,    9,   10,   11,   12,   13,   14,   58,   16,    1,
 /*   200 */     2,    3,    4,    5,    6,    7,    8,    9,   10,   11,
 /*   210 */    12,   13,   14,   16,   16,   64,   65,   12,   13,   14,
 /*   220 */    28,   16,   71,   72,   73,   74,   57,   25,    1,    2,
 /*   230 */     3,    4,    5,    6,    7,    8,    9,   10,   11,   12,
 /*   240 */    13,   14,   28,   16,   37,   38,   26,   45,   22,   23,
 /*   250 */    26,   24,   54,    1,    2,    3,    4,    5,    6,    7,
 /*   260 */     8,    9,   10,   11,   12,   13,   14,   28,   16,   25,
 /*   270 */    32,   28,   25,   25,   34,   25,   24,   28,    1,    2,
 /*   280 */     3,    4,    5,    6,    7,    8,    9,   10,   11,   12,
 /*   290 */    13,   14,   28,   16,   28,    1,    2,    3,    4,    5,
 /*   300 */     6,    7,    8,    9,   10,   11,   12,   13,   14,   28,
 /*   310 */    16,   25,   67,   36,   68,    1,    2,    3,    4,    5,
 /*   320 */     6,    7,    8,    9,   10,   11,   12,   13,   14,   68,
 /*   330 */    16,   43,   69,   64,   65,   68,   68,   66,   44,   67,
 /*   340 */    71,   72,   73,   67,   75,   66,   68,   67,   76,   76,
 /*   350 */    36,   76,    1,    2,    3,    4,    5,    6,    7,    8,
 /*   360 */     9,   10,   11,   12,   13,   14,   11,   16,   76,   76,
 /*   370 */    15,   76,   76,   76,   76,   76,   60,   61,   62,   63,
 /*   380 */    64,   65,   76,   28,   63,   64,   65,   71,   72,   73,
 /*   390 */    76,   76,   71,   72,   73,   76,   76,   76,   43,   44,
 /*   400 */    45,   76,   47,   48,   49,   50,   51,   52,   53,   76,
 /*   410 */    55,   11,   76,   58,   76,   15,   76,   76,   76,   76,
 /*   420 */    61,   62,   63,   64,   65,   11,   64,   65,   28,   15,
 /*   430 */    71,   72,   73,   71,   72,   73,   76,   76,   76,   76,
 /*   440 */    76,   76,   28,   43,   76,   45,   76,   47,   48,   49,
 /*   450 */    50,   51,   52,   53,   54,   55,   76,   43,   58,   45,
 /*   460 */    76,   47,   48,   49,   50,   51,   52,   53,   76,   55,
 /*   470 */    56,   76,   58,    2,    3,    4,    5,    6,    7,    8,
 /*   480 */     9,   10,   11,   12,   13,   14,   11,   16,   76,   76,
 /*   490 */    15,   76,   64,   65,   61,   62,   63,   64,   65,   71,
 /*   500 */    72,   73,   76,   28,   71,   72,   73,   63,   64,   65,
 /*   510 */    76,   76,   76,   76,   76,   71,   72,   73,   43,   76,
 /*   520 */    45,   76,   47,   48,   49,   50,   51,   52,   53,   76,
 /*   530 */    55,   76,   76,   58,   61,   62,   63,   64,   65,   61,
 /*   540 */    62,   63,   64,   65,   71,   72,   73,   76,   76,   71,
 /*   550 */    72,   73,   61,   62,   63,   64,   65,   61,   62,   63,
 /*   560 */    64,   65,   71,   72,   73,   64,   65,   71,   72,   73,
 /*   570 */    64,   65,   71,   72,   73,   76,   76,   71,   72,   73,
 /*   580 */    61,   62,   63,   64,   65,   61,   62,   63,   64,   65,
 /*   590 */    71,   72,   73,   76,   76,   71,   72,   73,   61,   62,
 /*   600 */    63,   64,   65,   76,   64,   65,   76,   76,   71,   72,
 /*   610 */    73,   71,   72,   73,   64,   65,   76,   64,   65,   76,
 /*   620 */    76,   71,   72,   73,   71,   72,   73,   64,   65,   76,
 /*   630 */    64,   65,   76,   76,   71,   72,   73,   71,   72,   73,
 /*   640 */    76,   76,   64,   65,   76,   64,   65,   76,   76,   71,
 /*   650 */    72,   73,   71,   72,   73,   64,   65,   76,   76,   76,
 /*   660 */    64,   65,   71,   72,   73,   64,   65,   71,   72,   73,
 /*   670 */    64,   65,   71,   72,   73,   64,   65,   71,   72,   73,
 /*   680 */    64,   65,   71,   72,   73,   76,   76,   71,   72,   73,
 /*   690 */    64,   65,   76,   64,   65,   76,   76,   71,   72,   73,
 /*   700 */    71,   72,   73,   64,   65,   76,   76,   64,   65,   76,
 /*   710 */    71,   72,   73,   76,   71,   72,   73,   64,   65,   76,
 /*   720 */    64,   65,   76,   76,   71,   72,   73,   71,   72,   73,
 /*   730 */    64,   65,   76,   64,   65,   76,   76,   71,   72,   73,
 /*   740 */    71,   72,   73,   64,   65,   76,   64,   65,   76,   76,
 /*   750 */    71,   72,   73,   71,   72,   73,   64,   65,   76,   64,
 /*   760 */    65,   76,   76,   71,   72,   73,   71,   72,   73,   64,
 /*   770 */    65,   76,   64,   65,   76,   76,   71,   72,   73,   71,
 /*   780 */    72,   73,   64,   65,   76,   64,   65,   76,   76,   71,
 /*   790 */    72,   73,   71,   72,   73,   64,   65,   76,   76,   76,
 /*   800 */    76,   76,   71,   72,   73,
};
#define YY_SHIFT_USE_DFLT (-44)
#define YY_SHIFT_COUNT (133)
#define YY_SHIFT_MIN   (-43)
#define YY_SHIFT_MAX   (475)
static const short yy_shift_ofst[] = {
 /*     0 */   -11,   35,   35,   35,   35,   35,   35,   35,   35,   35,
 /*    10 */    35,   35,  414,  400,  355,  475,  475,  475,  475,  475,
 /*    20 */   475,  475,  475,  475,  475,  475,  475,  475,  475,  475,
 /*    30 */   475,  475,  475,  475,  475,  475,  475,  475,  475,  475,
 /*    40 */   475,  475,  475,  475,  475,  475,  475,  475,  475,   17,
 /*    50 */    29,  207,   51,  226,  226,  226,  207,   -1,  288,  288,
 /*    60 */   288,  288,  314,  294,  277,  252,  227,  198,  169,  139,
 /*    70 */   111,   94,  351,  351,  351,  351,  351,  351,  351,  351,
 /*    80 */   351,  351,  471,  153,  123,  123,  182,  182,  123,  123,
 /*    90 */    -2,  205,  205,  -18,  202,   66,   64,  -41,   15,  -23,
 /*   100 */   -43,   31,  286,  250,  281,  266,  264,  249,  248,  247,
 /*   110 */   240,  243,  238,  244,  239,  224,  220,  214,  192,  197,
 /*   120 */   197,  197,  197,  197,  197,  160,  129,  156,  126,   68,
 /*   130 */    73,   47,   14,    8,
};
#define YY_REDUCE_USE_DFLT (-17)
#define YY_REDUCE_COUNT (61)
#define YY_REDUCE_MIN   (-16)
#define YY_REDUCE_MAX   (731)
static const short yy_reduce_ofst[] = {
 /*     0 */   316,  537,  524,  519,  496,  491,  478,  473,  433,  359,
 /*    10 */   444,  321,  269,  151,  -16,  731,  721,  718,  708,  705,
 /*    20 */   695,  692,  682,  679,  669,  666,  656,  653,  643,  639,
 /*    30 */   629,  626,  616,  611,  606,  601,  596,  591,  581,  578,
 /*    40 */   566,  563,  553,  550,  540,  506,  501,  428,  362,   11,
 /*    50 */   280,  279,  278,  276,  272,  245,  271,  263,  268,  267,
 /*    60 */   261,  246,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   186,  186,  186,  186,  186,  186,  186,  186,  186,  186,
 /*    10 */   186,  186,  261,  261,  261,  261,  261,  261,  261,  261,
 /*    20 */   261,  261,  261,  261,  261,  261,  261,  261,  261,  261,
 /*    30 */   261,  261,  261,  261,  261,  261,  261,  261,  261,  261,
 /*    40 */   261,  261,  261,  261,  261,  261,  261,  261,  261,  261,
 /*    50 */   261,  198,  261,  261,  261,  261,  198,  261,  261,  261,
 /*    60 */   261,  261,  261,  261,  261,  261,  261,  261,  261,  261,
 /*    70 */   261,  261,  201,  195,  193,  190,  260,  259,  236,  237,
 /*    80 */   189,  187,  239,  240,  241,  242,  246,  245,  244,  243,
 /*    90 */   247,  249,  248,  225,  261,  261,  261,  261,  261,  261,
 /*   100 */   261,  182,  261,  261,  261,  261,  261,  261,  261,  261,
 /*   110 */   261,  261,  261,  261,  261,  192,  191,  261,  261,  255,
 /*   120 */   254,  253,  252,  251,  250,  221,  261,  261,  261,  261,
 /*   130 */   261,  261,  261,  261,  185,  217,  218,  200,  214,  215,
 /*   140 */   212,  208,  209,  207,  206,  205,  204,  203,  202,  199,
 /*   150 */   197,  196,  194,  213,  258,  257,  256,  238,  235,  234,
 /*   160 */   233,  232,  231,  230,  229,  228,  227,  226,  224,  223,
 /*   170 */   222,  221,  220,  219,  188,  183,  211,  210,  216,  184,
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
  "NIL",           "FALSE",         "TRUE",          "INT",         
  "REAL",          "SBL",           "SBR",           "CBL",         
  "CBR",           "COLON",         "PIPE",          "error",       
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
 /*  30 */ "ident_list ::= IDENT",
 /*  31 */ "ident_list ::= ident_list COMMA IDENT",
 /*  32 */ "stat ::= DEF func_ident func_body",
 /*  33 */ "stat ::= LOCAL DEF IDENT func_body",
 /*  34 */ "func_ident ::= IDENT",
 /*  35 */ "func_ident ::= func_ident DOT IDENT",
 /*  36 */ "function ::= DEF func_body",
 /*  37 */ "func_body ::= PL PR block END",
 /*  38 */ "func_body ::= PL ident_list PR block END",
 /*  39 */ "functioncall ::= prefixexp PL PR",
 /*  40 */ "functioncall ::= prefixexp PL exp_list PR",
 /*  41 */ "prefixexp ::= var",
 /*  42 */ "prefixexp ::= STRING",
 /*  43 */ "prefixexp ::= functioncall",
 /*  44 */ "prefixexp ::= PL exp PR",
 /*  45 */ "exp ::= prefixexp",
 /*  46 */ "exp ::= function",
 /*  47 */ "exp ::= NIL",
 /*  48 */ "exp ::= FALSE",
 /*  49 */ "exp ::= TRUE",
 /*  50 */ "exp ::= INT",
 /*  51 */ "exp ::= REAL",
 /*  52 */ "exp ::= SBL SBR",
 /*  53 */ "exp ::= SBL exp_list SBR",
 /*  54 */ "exp ::= CBL CBR",
 /*  55 */ "exp ::= CBL dict_list CBR",
 /*  56 */ "dict_list ::= exp COLON exp",
 /*  57 */ "dict_list ::= dict_list COMMA exp COLON exp",
 /*  58 */ "exp ::= PIPE exp PIPE",
 /*  59 */ "exp ::= exp OR exp",
 /*  60 */ "exp ::= exp AND exp",
 /*  61 */ "exp ::= exp L exp",
 /*  62 */ "exp ::= exp G exp",
 /*  63 */ "exp ::= exp LEQ exp",
 /*  64 */ "exp ::= exp GEQ exp",
 /*  65 */ "exp ::= exp NEQ exp",
 /*  66 */ "exp ::= exp EQ exp",
 /*  67 */ "exp ::= exp RANGEOP exp",
 /*  68 */ "exp ::= exp PLUS exp",
 /*  69 */ "exp ::= exp MINUS exp",
 /*  70 */ "exp ::= exp MUL exp",
 /*  71 */ "exp ::= exp DIV exp",
 /*  72 */ "exp ::= exp MOD exp",
 /*  73 */ "exp ::= exp EXP exp",
 /*  74 */ "exp ::= NOT exp",
 /*  75 */ "exp ::= MINUS exp",
 /*  76 */ "var ::= IDENT",
 /*  77 */ "var ::= prefixexp DOT IDENT",
 /*  78 */ "var ::= prefixexp SBL exp SBR",
 /*  79 */ "exp_list ::= exp",
 /*  80 */ "exp_list ::= exp_list COMMA exp",
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
  { 73, 1 },
  { 73, 3 },
  { 64, 1 },
  { 64, 1 },
  { 64, 1 },
  { 64, 1 },
  { 64, 1 },
  { 64, 1 },
  { 64, 1 },
  { 64, 2 },
  { 64, 3 },
  { 64, 2 },
  { 64, 3 },
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
#line 1054 "lparser.c"
        break;
      case 2: /* block ::= stat_list */
#line 72 "lparser.y"
{ yygotominor.yy132 = new BlockNode(yymsp[0].minor.yy115);  }
#line 1059 "lparser.c"
        break;
      case 3: /* stat_list ::= stat */
#line 74 "lparser.y"
{ yygotominor.yy115 = new NodeList<>(); if(yymsp[0].minor.yy0){ yygotominor.yy115->push_back(yymsp[0].minor.yy0); }  }
#line 1064 "lparser.c"
        break;
      case 4: /* stat_list ::= stat_list NL stat */
      case 5: /* stat_list ::= stat_list SCOLON stat */ yytestcase(yyruleno==5);
#line 75 "lparser.y"
{ yygotominor.yy115 = yymsp[-2].minor.yy115;  if(yymsp[0].minor.yy0){ yygotominor.yy115->push_back(yymsp[0].minor.yy0); }  }
#line 1070 "lparser.c"
        break;
      case 6: /* stat ::= */
      case 18: /* else ::= */ yytestcase(yyruleno==18);
#line 79 "lparser.y"
{ yygotominor.yy0 = NULL; }
#line 1076 "lparser.c"
        break;
      case 7: /* stat ::= exp */
#line 80 "lparser.y"
{ yygotominor.yy0 = new StatNode(yymsp[0].minor.yy0); }
#line 1081 "lparser.c"
        break;
      case 8: /* stat ::= DO block END */
#line 81 "lparser.y"
{ yygotominor.yy0 = yymsp[-1].minor.yy132; yymsp[-1].minor.yy132->createScope(); }
#line 1086 "lparser.c"
        break;
      case 9: /* stat ::= var ASSIG exp */
#line 84 "lparser.y"
{ yygotominor.yy0 = new AssignNode(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1091 "lparser.c"
        break;
      case 10: /* stat ::= GLOBAL IDENT ASSIG exp */
#line 85 "lparser.y"
{ yygotominor.yy0 = new AssignNode(new VarNode(yymsp[-2].minor.yy0), yymsp[0].minor.yy0); }
#line 1096 "lparser.c"
        break;
      case 11: /* stat ::= GLOBAL IDENT */
#line 86 "lparser.y"
{ yygotominor.yy0 = new AssignNode(new VarNode(yymsp[0].minor.yy0), new NilLitNode()); }
#line 1101 "lparser.c"
        break;
      case 12: /* stat ::= LOCAL IDENT */
#line 88 "lparser.y"
{ yygotominor.yy0 = new DeclNode(yymsp[0].minor.yy0, NULL); }
#line 1106 "lparser.c"
        break;
      case 13: /* stat ::= LOCAL IDENT ASSIG exp */
#line 89 "lparser.y"
{ yygotominor.yy0 = new DeclNode(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1111 "lparser.c"
        break;
      case 14: /* stat ::= WHILE exp DO block END */
#line 98 "lparser.y"
{ yygotominor.yy0 = new WhileNode(yymsp[-3].minor.yy0, yymsp[-1].minor.yy132); }
#line 1116 "lparser.c"
        break;
      case 15: /* stat ::= REPEAT block UNTIL exp */
#line 100 "lparser.y"
{ yygotominor.yy0 = new RepeatNode(yymsp[0].minor.yy0, yymsp[-2].minor.yy132); }
#line 1121 "lparser.c"
        break;
      case 16: /* stat ::= FOR IDENT IN exp DO block END */
#line 102 "lparser.y"
{ yygotominor.yy0 = new ForNode(yymsp[-5].minor.yy0, yymsp[-3].minor.yy0, yymsp[-1].minor.yy132); }
#line 1126 "lparser.c"
        break;
      case 17: /* stat ::= IF exp THEN block else END */
#line 104 "lparser.y"
{ yygotominor.yy0 = new IfNode(yymsp[-4].minor.yy0, yymsp[-2].minor.yy132, yymsp[-1].minor.yy0); }
#line 1131 "lparser.c"
        break;
      case 19: /* else ::= ELSE block */
#line 106 "lparser.y"
{ yygotominor.yy0 = yymsp[0].minor.yy132; }
#line 1136 "lparser.c"
        break;
      case 20: /* else ::= ELSEIF exp THEN block else */
#line 107 "lparser.y"
{ yygotominor.yy0 = new IfNode(yymsp[-3].minor.yy0, yymsp[-1].minor.yy132, yymsp[0].minor.yy0); }
#line 1141 "lparser.c"
        break;
      case 21: /* stat ::= RETURN exp */
#line 110 "lparser.y"
{ yygotominor.yy0 = new ReturnNode(yymsp[0].minor.yy0); }
#line 1146 "lparser.c"
        break;
      case 24: /* stat ::= CLASS IDENT class_body */
#line 116 "lparser.y"
{ yygotominor.yy0 = new ClassNode(yymsp[-1].minor.yy0, NULL, yymsp[0].minor.yy88); }
#line 1151 "lparser.c"
        break;
      case 25: /* stat ::= CLASS IDENT PL exp PR class_body */
#line 117 "lparser.y"
{ yygotominor.yy0 = new ClassNode(yymsp[-4].minor.yy0, yymsp[-2].minor.yy0, yymsp[0].minor.yy88); }
#line 1156 "lparser.c"
        break;
      case 26: /* class_body ::= NL END */
      case 27: /* class_body ::= SCOLON END */ yytestcase(yyruleno==27);
#line 118 "lparser.y"
{ yygotominor.yy88 = new std::vector<std::pair<Node*, Node*> >(); }
#line 1162 "lparser.c"
        break;
      case 28: /* class_body ::= NL DEF IDENT func_body class_body */
      case 29: /* class_body ::= SCOLON DEF IDENT func_body class_body */ yytestcase(yyruleno==29);
#line 120 "lparser.y"
{ yygotominor.yy88 = yymsp[0].minor.yy88; yymsp[0].minor.yy88->push_back(std::make_pair(yymsp[-2].minor.yy0, yymsp[-1].minor.yy0)); }
#line 1168 "lparser.c"
        break;
      case 30: /* ident_list ::= IDENT */
#line 127 "lparser.y"
{
    yygotominor.yy69 = new NodeList<IdentNode>();

    assert(dynamic_cast<IdentNode*>(yymsp[0].minor.yy0));
    yygotominor.yy69->push_back(static_cast<IdentNode*>(yymsp[0].minor.yy0));

}
#line 1179 "lparser.c"
        break;
      case 31: /* ident_list ::= ident_list COMMA IDENT */
#line 135 "lparser.y"
{
    yygotominor.yy69 = yymsp[-2].minor.yy69;

    assert(dynamic_cast<IdentNode*>(yymsp[0].minor.yy0));
    yygotominor.yy69->push_back(static_cast<IdentNode*>(yymsp[0].minor.yy0));
}
#line 1189 "lparser.c"
        break;
      case 32: /* stat ::= DEF func_ident func_body */
#line 142 "lparser.y"
{ yygotominor.yy0 = new AssignNode(yymsp[-1].minor.yy0, yymsp[0].minor.yy0); }
#line 1194 "lparser.c"
        break;
      case 33: /* stat ::= LOCAL DEF IDENT func_body */
#line 143 "lparser.y"
{ yygotominor.yy0 = new DeclNode(yymsp[-1].minor.yy0, yymsp[0].minor.yy0); }
#line 1199 "lparser.c"
        break;
      case 34: /* func_ident ::= IDENT */
      case 76: /* var ::= IDENT */ yytestcase(yyruleno==76);
#line 144 "lparser.y"
{ yygotominor.yy0 = new VarNode(yymsp[0].minor.yy0); }
#line 1205 "lparser.c"
        break;
      case 35: /* func_ident ::= func_ident DOT IDENT */
      case 77: /* var ::= prefixexp DOT IDENT */ yytestcase(yyruleno==77);
#line 145 "lparser.y"
{ yygotominor.yy0 = new MemberAccessNode(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1211 "lparser.c"
        break;
      case 36: /* function ::= DEF func_body */
      case 41: /* prefixexp ::= var */ yytestcase(yyruleno==41);
      case 42: /* prefixexp ::= STRING */ yytestcase(yyruleno==42);
      case 43: /* prefixexp ::= functioncall */ yytestcase(yyruleno==43);
      case 45: /* exp ::= prefixexp */ yytestcase(yyruleno==45);
      case 46: /* exp ::= function */ yytestcase(yyruleno==46);
      case 50: /* exp ::= INT */ yytestcase(yyruleno==50);
      case 51: /* exp ::= REAL */ yytestcase(yyruleno==51);
#line 148 "lparser.y"
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
#line 1223 "lparser.c"
        break;
      case 37: /* func_body ::= PL PR block END */
#line 149 "lparser.y"
{ yygotominor.yy0 = new FuncNode(NULL, yymsp[-1].minor.yy132); }
#line 1228 "lparser.c"
        break;
      case 38: /* func_body ::= PL ident_list PR block END */
#line 150 "lparser.y"
{ yygotominor.yy0 = new FuncNode(yymsp[-3].minor.yy69, yymsp[-1].minor.yy132); }
#line 1233 "lparser.c"
        break;
      case 39: /* functioncall ::= prefixexp PL PR */
#line 152 "lparser.y"
{ yygotominor.yy0 = new CallNode(yymsp[-2].minor.yy0, NULL); }
#line 1238 "lparser.c"
        break;
      case 40: /* functioncall ::= prefixexp PL exp_list PR */
#line 153 "lparser.y"
{ yygotominor.yy0 = new CallNode(yymsp[-3].minor.yy0, yymsp[-1].minor.yy115); }
#line 1243 "lparser.c"
        break;
      case 44: /* prefixexp ::= PL exp PR */
#line 158 "lparser.y"
{ yygotominor.yy0 = yymsp[-1].minor.yy0; }
#line 1248 "lparser.c"
        break;
      case 47: /* exp ::= NIL */
#line 164 "lparser.y"
{ yygotominor.yy0 = new NilLitNode(); }
#line 1253 "lparser.c"
        break;
      case 48: /* exp ::= FALSE */
#line 165 "lparser.y"
{ yygotominor.yy0 = new BoolLitNode(false); }
#line 1258 "lparser.c"
        break;
      case 49: /* exp ::= TRUE */
#line 166 "lparser.y"
{ yygotominor.yy0 = new BoolLitNode(true); }
#line 1263 "lparser.c"
        break;
      case 52: /* exp ::= SBL SBR */
#line 173 "lparser.y"
{ yygotominor.yy0 = new ListConstrNode(NULL); }
#line 1268 "lparser.c"
        break;
      case 53: /* exp ::= SBL exp_list SBR */
#line 174 "lparser.y"
{ yygotominor.yy0 = new ListConstrNode(yymsp[-1].minor.yy115); }
#line 1273 "lparser.c"
        break;
      case 54: /* exp ::= CBL CBR */
#line 176 "lparser.y"
{ yygotominor.yy0 = new DictConstrNode(NULL); }
#line 1278 "lparser.c"
        break;
      case 55: /* exp ::= CBL dict_list CBR */
#line 177 "lparser.y"
{ yygotominor.yy0 = new DictConstrNode(yymsp[-1].minor.yy129); }
#line 1283 "lparser.c"
        break;
      case 56: /* dict_list ::= exp COLON exp */
#line 180 "lparser.y"
{ yygotominor.yy129 = new NodeDictList(); yygotominor.yy129->push_back(std::make_pair(yymsp[-2].minor.yy0, yymsp[0].minor.yy0)); }
#line 1288 "lparser.c"
        break;
      case 57: /* dict_list ::= dict_list COMMA exp COLON exp */
#line 181 "lparser.y"
{ yygotominor.yy129 = yymsp[-4].minor.yy129; yygotominor.yy129->push_back(std::make_pair(yymsp[-2].minor.yy0, yymsp[0].minor.yy0)); }
#line 1293 "lparser.c"
        break;
      case 58: /* exp ::= PIPE exp PIPE */
#line 185 "lparser.y"
{ yygotominor.yy0 = new UnOpNode<'|'>(yymsp[-1].minor.yy0); }
#line 1298 "lparser.c"
        break;
      case 59: /* exp ::= exp OR exp */
#line 187 "lparser.y"
{ yygotominor.yy0 = new OrNode(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1303 "lparser.c"
        break;
      case 60: /* exp ::= exp AND exp */
#line 188 "lparser.y"
{ yygotominor.yy0 = new AndNode(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1308 "lparser.c"
        break;
      case 61: /* exp ::= exp L exp */
#line 190 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'<'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1313 "lparser.c"
        break;
      case 62: /* exp ::= exp G exp */
#line 191 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'>'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1318 "lparser.c"
        break;
      case 63: /* exp ::= exp LEQ exp */
#line 192 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'<'+'='>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1323 "lparser.c"
        break;
      case 64: /* exp ::= exp GEQ exp */
#line 193 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'>'+'='>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1328 "lparser.c"
        break;
      case 65: /* exp ::= exp NEQ exp */
#line 194 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'!'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1333 "lparser.c"
        break;
      case 66: /* exp ::= exp EQ exp */
#line 195 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'='>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1338 "lparser.c"
        break;
      case 68: /* exp ::= exp PLUS exp */
#line 199 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'+'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1343 "lparser.c"
        break;
      case 69: /* exp ::= exp MINUS exp */
#line 200 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'-'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1348 "lparser.c"
        break;
      case 70: /* exp ::= exp MUL exp */
#line 202 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'*'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1353 "lparser.c"
        break;
      case 71: /* exp ::= exp DIV exp */
#line 203 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'/'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1358 "lparser.c"
        break;
      case 72: /* exp ::= exp MOD exp */
#line 204 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'%'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1363 "lparser.c"
        break;
      case 73: /* exp ::= exp EXP exp */
#line 206 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'^'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1368 "lparser.c"
        break;
      case 74: /* exp ::= NOT exp */
#line 208 "lparser.y"
{ yygotominor.yy0 = new UnOpNode<'!'>(yymsp[0].minor.yy0); }
#line 1373 "lparser.c"
        break;
      case 75: /* exp ::= MINUS exp */
#line 209 "lparser.y"
{ yygotominor.yy0 = new UnOpNode<'-'>(yymsp[0].minor.yy0); }
#line 1378 "lparser.c"
        break;
      case 78: /* var ::= prefixexp SBL exp SBR */
#line 216 "lparser.y"
{ yygotominor.yy0 = new IndexAccessNode(yymsp[-3].minor.yy0, yymsp[-1].minor.yy0); }
#line 1383 "lparser.c"
        break;
      case 79: /* exp_list ::= exp */
#line 219 "lparser.y"
{ yygotominor.yy115 = new NodeList<>(); yygotominor.yy115->push_back(yymsp[0].minor.yy0); }
#line 1388 "lparser.c"
        break;
      case 80: /* exp_list ::= exp_list COMMA exp */
#line 220 "lparser.y"
{ yygotominor.yy115 = yymsp[-2].minor.yy115; yygotominor.yy115->push_back(yymsp[0].minor.yy0); }
#line 1393 "lparser.c"
        break;
      default:
      /* (0) chunk ::= TERMINATION UNINITIALIZED WARNING DOT */ yytestcase(yyruleno==0);
      /* (22) stat ::= NEXT */ yytestcase(yyruleno==22);
      /* (23) stat ::= BREAK */ yytestcase(yyruleno==23);
      /* (67) exp ::= exp RANGEOP exp */ yytestcase(yyruleno==67);
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
#line 1462 "lparser.c"
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
