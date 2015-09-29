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
#define YYNOCODE 75
#define YYACTIONTYPE unsigned short int
#define LemonTOKENTYPE AYA::Node*
typedef union {
  int yyinit;
  LemonTOKENTYPE yy0;
  NodeDictList* yy65;
  BlockNode* yy84;
  NodeList<IdentNode>* yy105;
  NodeList<>* yy143;
  std::vector<std::pair<Node*, Node*> >* yy144;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define LemonARG_SDECL  AYA::Node** currentNode ;
#define LemonARG_PDECL , AYA::Node** currentNode 
#define LemonARG_FETCH  AYA::Node** currentNode  = yypParser->currentNode 
#define LemonARG_STORE yypParser->currentNode  = currentNode 
#define YYNSTATE 183
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
#define YY_ACTTAB_COUNT (825)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    27,   80,  174,    9,   28,  127,  133,  131,  166,  173,
 /*    10 */    95,   99,  118,    8,    3,   15,   96,  159,   23,    6,
 /*    20 */   175,  113,   45,   20,   11,   10,  132,   19,  151,  150,
 /*    30 */   109,   44,   42,   49,   14,  171,   13,  167,   12,   25,
 /*    40 */   165,  164,  163,  162,  161,  117,   39,   27,   80,  174,
 /*    50 */    45,   28,  180,  169,  130,  166,  173,   95,   98,  104,
 /*    60 */     8,  116,  183,   96,  159,   23,    6,    1,  113,  128,
 /*    70 */    20,  181,  138,   59,   19,  151,  150,  109,   44,  184,
 /*    80 */    49,   61,  171,   13,  179,   12,   61,  165,  164,  163,
 /*    90 */   162,  161,  177,   39,   47,   48,   46,   35,   36,   43,
 /*   100 */    40,   38,   37,   34,   33,   32,   31,   30,   29,   29,
 /*   110 */   158,   53,   52,   24,  147,   53,   52,  105,  147,   64,
 /*   120 */    48,   46,   35,   36,   43,   40,   38,   37,   34,   33,
 /*   130 */    32,   31,   30,  106,   29,  155,   48,   46,   35,   36,
 /*   140 */    43,   40,   38,   37,   34,   33,   32,   31,   30,  112,
 /*   150 */    29,   22,  264,  264,  264,  264,   34,   33,   32,   31,
 /*   160 */    30,  172,   29,   48,   46,   35,   36,   43,   40,   38,
 /*   170 */    37,   34,   33,   32,   31,   30,   21,   29,   46,   35,
 /*   180 */    36,   43,   40,   38,   37,   34,   33,   32,   31,   30,
 /*   190 */    41,   29,   48,   46,   35,   36,   43,   40,   38,   37,
 /*   200 */    34,   33,   32,   31,   30,  154,   29,   35,   36,   43,
 /*   210 */    40,   38,   37,   34,   33,   32,   31,   30,  160,   29,
 /*   220 */    48,   46,   35,   36,   43,   40,   38,   37,   34,   33,
 /*   230 */    32,   31,   30,  153,   29,   43,   40,   38,   37,   34,
 /*   240 */    33,   32,   31,   30,   54,   29,   26,   63,   48,   46,
 /*   250 */    35,   36,   43,   40,   38,   37,   34,   33,   32,   31,
 /*   260 */    30,   17,   29,   32,   31,   30,  157,   29,   62,   16,
 /*   270 */     7,  181,   48,   46,   35,   36,   43,   40,   38,   37,
 /*   280 */    34,   33,   32,   31,   30,  139,   29,  136,  135,   53,
 /*   290 */    52,   61,  147,  156,    5,   56,   48,   46,   35,   36,
 /*   300 */    43,   40,   38,   37,   34,   33,   32,   31,   30,   18,
 /*   310 */    29,   55,   48,   46,   35,   36,   43,   40,   38,   37,
 /*   320 */    34,   33,   32,   31,   30,  110,   29,   53,   52,    4,
 /*   330 */   147,   48,   46,   35,   36,   43,   40,   38,   37,   34,
 /*   340 */    33,   32,   31,   30,   27,   29,  100,  140,   28,  137,
 /*   350 */   266,  148,  144,   57,  142,  265,  129,  101,  178,   84,
 /*   360 */   125,  159,   72,  174,    2,  266,  166,  173,   95,  166,
 /*   370 */   173,   95,  149,   97,  146,   44,  176,   65,  145,  171,
 /*   380 */    13,  143,   12,  141,  165,  164,  163,  162,  161,  266,
 /*   390 */    39,   27,  266,  266,  266,   28,  182,   84,  125,  103,
 /*   400 */   101,  178,   84,  125,  166,  173,   95,  266,  159,  166,
 /*   410 */   173,   95,  266,  266,  266,  266,  266,  266,  266,   27,
 /*   420 */   266,  266,   44,   28,   65,  266,  171,   13,  170,   12,
 /*   430 */   266,  165,  164,  163,  162,  161,  159,   39,  134,   84,
 /*   440 */   125,  266,  266,  266,  266,  266,  166,  173,   95,  266,
 /*   450 */    44,  266,   65,  266,  171,   13,  266,   12,  168,  165,
 /*   460 */   164,  163,  162,  161,  266,   39,  266,   48,   46,   35,
 /*   470 */    36,   43,   40,   38,   37,   34,   33,   32,   31,   30,
 /*   480 */    27,   29,  266,  266,   28,  266,   85,  174,  126,  101,
 /*   490 */   178,   84,  125,  166,  173,   95,  266,  159,  166,  173,
 /*   500 */    95,  266,  266,   53,   52,  266,  147,  266,  266,  107,
 /*   510 */   266,   44,  266,   65,  266,  171,   13,  266,   12,  266,
 /*   520 */   165,  164,  163,  162,  161,  108,   39,  115,  101,  178,
 /*   530 */    84,  125,  114,  101,  178,   84,  125,  166,  173,   95,
 /*   540 */   266,  266,  166,  173,   95,  266,  266,  266,  111,  101,
 /*   550 */   178,   84,  125,  266,   83,  174,  266,  266,  166,  173,
 /*   560 */    95,  166,  173,   95,  266,  266,  266,  266,  266,  266,
 /*   570 */   266,   60,  101,  178,   84,  125,  152,  101,  178,   84,
 /*   580 */   125,  166,  173,   95,  266,  266,  166,  173,   95,   58,
 /*   590 */   101,  178,   84,  125,  102,  101,  178,   84,  125,  166,
 /*   600 */   173,   95,   86,  174,  166,  173,   95,   79,  174,  166,
 /*   610 */   173,   95,   75,  174,  166,  173,   95,   87,  174,  166,
 /*   620 */   173,   95,   74,  174,  166,  173,   95,  266,  266,  166,
 /*   630 */   173,   95,  266,  266,   82,  174,  266,   88,  174,  266,
 /*   640 */   266,  166,  173,   95,  166,  173,   95,  266,  266,   73,
 /*   650 */   174,  266,   92,  174,  266,  266,  166,  173,   95,  166,
 /*   660 */   173,   95,   91,  174,  266,   90,  174,  266,  266,  166,
 /*   670 */   173,   95,  166,  173,   95,   89,  174,  266,   94,  174,
 /*   680 */   266,  266,  166,  173,   95,  166,  173,   95,   93,  174,
 /*   690 */   266,  266,  124,  174,  266,  166,  173,   95,  266,  166,
 /*   700 */   173,   95,  266,  266,  123,  174,  266,  122,  174,  266,
 /*   710 */   266,  166,  173,   95,  166,  173,   95,  266,  266,  121,
 /*   720 */   174,  266,  120,  174,  266,  266,  166,  173,   95,  166,
 /*   730 */   173,   95,  119,  174,  266,   81,  174,  266,  266,  166,
 /*   740 */   173,   95,  166,  173,   95,   71,  174,  266,   78,  174,
 /*   750 */   266,  266,  166,  173,   95,  166,  173,   95,   70,  174,
 /*   760 */   266,  266,   77,  174,  266,  166,  173,   95,  266,  166,
 /*   770 */   173,   95,  266,  266,   69,  174,  266,   68,  174,  266,
 /*   780 */   266,  166,  173,   95,  166,  173,   95,  266,  266,   76,
 /*   790 */   174,  266,   67,  174,  266,  266,  166,  173,   95,  166,
 /*   800 */   173,   95,   51,  174,  266,   50,  174,  266,  266,  166,
 /*   810 */   173,   95,  166,  173,   95,   66,  174,  266,  266,  266,
 /*   820 */   266,  266,  166,  173,   95,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    10,   62,   63,   42,   14,   44,   16,   18,   69,   70,
 /*    10 */    71,   72,   19,   23,   35,   36,   26,   27,   28,   29,
 /*    20 */    42,   31,   44,   33,   21,   22,   17,   37,   38,   39,
 /*    30 */    40,   41,   44,   43,   41,   45,   46,   49,   48,   46,
 /*    40 */    50,   51,   52,   53,   54,   27,   56,   10,   62,   63,
 /*    50 */    44,   14,   27,   47,   19,   69,   70,   71,   72,   19,
 /*    60 */    23,   43,    0,   26,   27,   28,   29,   42,   31,   20,
 /*    70 */    33,   66,   27,   68,   37,   38,   39,   40,   41,    0,
 /*    80 */    43,   41,   45,   46,   27,   48,   41,   50,   51,   52,
 /*    90 */    53,   54,   24,   56,   25,    1,    2,    3,    4,    5,
 /*   100 */     6,    7,    8,    9,   10,   11,   12,   13,   15,   15,
 /*   110 */    27,   21,   22,   25,   24,   21,   22,   27,   24,   27,
 /*   120 */     1,    2,    3,    4,    5,    6,    7,    8,    9,   10,
 /*   130 */    11,   12,   13,   43,   15,   24,    1,    2,    3,    4,
 /*   140 */     5,    6,    7,    8,    9,   10,   11,   12,   13,   27,
 /*   150 */    15,   30,    5,    6,    7,    8,    9,   10,   11,   12,
 /*   160 */    13,   42,   15,    1,    2,    3,    4,    5,    6,    7,
 /*   170 */     8,    9,   10,   11,   12,   13,   32,   15,    2,    3,
 /*   180 */     4,    5,    6,    7,    8,    9,   10,   11,   12,   13,
 /*   190 */    55,   15,    1,    2,    3,    4,    5,    6,    7,    8,
 /*   200 */     9,   10,   11,   12,   13,   24,   15,    3,    4,    5,
 /*   210 */     6,    7,    8,    9,   10,   11,   12,   13,   56,   15,
 /*   220 */     1,    2,    3,    4,    5,    6,    7,    8,    9,   10,
 /*   230 */    11,   12,   13,   24,   15,    5,    6,    7,    8,    9,
 /*   240 */    10,   11,   12,   13,   27,   15,   55,   27,    1,    2,
 /*   250 */     3,    4,    5,    6,    7,    8,    9,   10,   11,   12,
 /*   260 */    13,   25,   15,   11,   12,   13,   47,   15,   27,   25,
 /*   270 */    23,   66,    1,    2,    3,    4,    5,    6,    7,    8,
 /*   280 */     9,   10,   11,   12,   13,   27,   15,   24,   24,   21,
 /*   290 */    22,   41,   24,   66,   23,   66,    1,    2,    3,    4,
 /*   300 */     5,    6,    7,    8,    9,   10,   11,   12,   13,   41,
 /*   310 */    15,   66,    1,    2,    3,    4,    5,    6,    7,    8,
 /*   320 */     9,   10,   11,   12,   13,   64,   15,   21,   22,   34,
 /*   330 */    24,    1,    2,    3,    4,    5,    6,    7,    8,    9,
 /*   340 */    10,   11,   12,   13,   10,   15,   67,   66,   14,   64,
 /*   350 */    74,   65,   65,   42,   65,   58,   59,   60,   61,   62,
 /*   360 */    63,   27,   62,   63,   34,   74,   69,   70,   71,   69,
 /*   370 */    70,   71,   65,   73,   65,   41,   42,   43,   65,   45,
 /*   380 */    46,   65,   48,   65,   50,   51,   52,   53,   54,   74,
 /*   390 */    56,   10,   74,   74,   74,   14,   61,   62,   63,   59,
 /*   400 */    60,   61,   62,   63,   69,   70,   71,   74,   27,   69,
 /*   410 */    70,   71,   74,   74,   74,   74,   74,   74,   74,   10,
 /*   420 */    74,   74,   41,   14,   43,   74,   45,   46,   47,   48,
 /*   430 */    74,   50,   51,   52,   53,   54,   27,   56,   61,   62,
 /*   440 */    63,   74,   74,   74,   74,   74,   69,   70,   71,   74,
 /*   450 */    41,   74,   43,   74,   45,   46,   74,   48,   49,   50,
 /*   460 */    51,   52,   53,   54,   74,   56,   74,    1,    2,    3,
 /*   470 */     4,    5,    6,    7,    8,    9,   10,   11,   12,   13,
 /*   480 */    10,   15,   74,   74,   14,   74,   62,   63,   59,   60,
 /*   490 */    61,   62,   63,   69,   70,   71,   74,   27,   69,   70,
 /*   500 */    71,   74,   74,   21,   22,   74,   24,   74,   74,   27,
 /*   510 */    74,   41,   74,   43,   74,   45,   46,   74,   48,   74,
 /*   520 */    50,   51,   52,   53,   54,   43,   56,   59,   60,   61,
 /*   530 */    62,   63,   59,   60,   61,   62,   63,   69,   70,   71,
 /*   540 */    74,   74,   69,   70,   71,   74,   74,   74,   59,   60,
 /*   550 */    61,   62,   63,   74,   62,   63,   74,   74,   69,   70,
 /*   560 */    71,   69,   70,   71,   74,   74,   74,   74,   74,   74,
 /*   570 */    74,   59,   60,   61,   62,   63,   59,   60,   61,   62,
 /*   580 */    63,   69,   70,   71,   74,   74,   69,   70,   71,   59,
 /*   590 */    60,   61,   62,   63,   59,   60,   61,   62,   63,   69,
 /*   600 */    70,   71,   62,   63,   69,   70,   71,   62,   63,   69,
 /*   610 */    70,   71,   62,   63,   69,   70,   71,   62,   63,   69,
 /*   620 */    70,   71,   62,   63,   69,   70,   71,   74,   74,   69,
 /*   630 */    70,   71,   74,   74,   62,   63,   74,   62,   63,   74,
 /*   640 */    74,   69,   70,   71,   69,   70,   71,   74,   74,   62,
 /*   650 */    63,   74,   62,   63,   74,   74,   69,   70,   71,   69,
 /*   660 */    70,   71,   62,   63,   74,   62,   63,   74,   74,   69,
 /*   670 */    70,   71,   69,   70,   71,   62,   63,   74,   62,   63,
 /*   680 */    74,   74,   69,   70,   71,   69,   70,   71,   62,   63,
 /*   690 */    74,   74,   62,   63,   74,   69,   70,   71,   74,   69,
 /*   700 */    70,   71,   74,   74,   62,   63,   74,   62,   63,   74,
 /*   710 */    74,   69,   70,   71,   69,   70,   71,   74,   74,   62,
 /*   720 */    63,   74,   62,   63,   74,   74,   69,   70,   71,   69,
 /*   730 */    70,   71,   62,   63,   74,   62,   63,   74,   74,   69,
 /*   740 */    70,   71,   69,   70,   71,   62,   63,   74,   62,   63,
 /*   750 */    74,   74,   69,   70,   71,   69,   70,   71,   62,   63,
 /*   760 */    74,   74,   62,   63,   74,   69,   70,   71,   74,   69,
 /*   770 */    70,   71,   74,   74,   62,   63,   74,   62,   63,   74,
 /*   780 */    74,   69,   70,   71,   69,   70,   71,   74,   74,   62,
 /*   790 */    63,   74,   62,   63,   74,   74,   69,   70,   71,   69,
 /*   800 */    70,   71,   62,   63,   74,   62,   63,   74,   74,   69,
 /*   810 */    70,   71,   69,   70,   71,   62,   63,   74,   74,   74,
 /*   820 */    74,   74,   69,   70,   71,
};
#define YY_SHIFT_USE_DFLT (-40)
#define YY_SHIFT_COUNT (133)
#define YY_SHIFT_MIN   (-39)
#define YY_SHIFT_MAX   (482)
static const short yy_shift_ofst[] = {
 /*     0 */   -10,   37,   37,   37,   37,   37,   37,   37,   37,   37,
 /*    10 */    37,   37,  409,  381,  334,  470,  470,  470,  470,  470,
 /*    20 */   470,  470,  470,  470,  470,  470,  470,  470,  470,  470,
 /*    30 */   470,  470,  470,  470,  470,  470,  470,  470,  470,  470,
 /*    40 */   470,  470,  470,  470,  470,  470,  470,  470,  470,   45,
 /*    50 */    94,   94,  482,   90,  268,  306,  306,  306,  -21,   40,
 /*    60 */   -21,   25,  250,  250,  250,  250,  330,  311,  295,  271,
 /*    70 */   247,  219,  191,  162,  135,  119,  466,  466,  466,  466,
 /*    80 */   466,  466,  466,  466,  466,  176,  204,  147,  147,  230,
 /*    90 */   230,  147,  147,  252,  252,   -7,   18,  -12,    6,  -22,
 /*   100 */   -39,    3,  264,  263,  258,  244,  241,  236,  220,  217,
 /*   110 */   209,  181,  144,  122,  121,  111,   92,   88,   83,   93,
 /*   120 */    93,   93,   93,   93,   93,   69,   68,   57,   79,   49,
 /*   130 */    62,   35,  -11,    9,
};
#define YY_REDUCE_USE_DFLT (-62)
#define YY_REDUCE_COUNT (65)
#define YY_REDUCE_MIN   (-61)
#define YY_REDUCE_MAX   (753)
static const short yy_reduce_ofst[] = {
 /*     0 */   297,  535,  530,  517,  512,  489,  473,  468,  429,  340,
 /*    10 */   377,  335,  300,  -14,  -61,  753,  743,  740,  730,  727,
 /*    20 */   715,  712,  700,  696,  686,  683,  673,  670,  660,  657,
 /*    30 */   645,  642,  630,  626,  616,  613,  603,  600,  590,  587,
 /*    40 */   575,  572,  560,  555,  550,  545,  540,  492,  424,    5,
 /*    50 */   318,  316,  313,  309,  307,  289,  287,  286,  285,  281,
 /*    60 */   261,  279,  245,  229,  227,  205,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   189,  189,  189,  189,  189,  189,  189,  189,  189,  189,
 /*    10 */   189,  189,  264,  264,  264,  264,  264,  264,  264,  264,
 /*    20 */   264,  264,  264,  264,  264,  264,  264,  264,  264,  264,
 /*    30 */   264,  264,  264,  264,  264,  264,  264,  264,  264,  264,
 /*    40 */   264,  264,  264,  264,  264,  264,  264,  264,  264,  264,
 /*    50 */   264,  264,  264,  264,  264,  264,  264,  264,  199,  264,
 /*    60 */   199,  264,  264,  264,  264,  264,  264,  264,  264,  264,
 /*    70 */   264,  264,  264,  264,  264,  264,  202,  196,  194,  263,
 /*    80 */   262,  240,  241,  192,  190,  243,  244,  245,  246,  250,
 /*    90 */   249,  248,  247,  252,  251,  233,  264,  264,  264,  264,
 /*   100 */   264,  185,  264,  264,  264,  264,  264,  264,  264,  264,
 /*   110 */   264,  264,  264,  264,  264,  264,  264,  193,  264,  258,
 /*   120 */   257,  256,  255,  254,  253,  225,  264,  264,  264,  264,
 /*   130 */   264,  264,  264,  264,  188,  221,  222,  201,  218,  219,
 /*   140 */   216,  212,  210,  213,  211,  209,  208,  207,  206,  205,
 /*   150 */   204,  203,  200,  198,  197,  195,  217,  261,  260,  259,
 /*   160 */   242,  239,  238,  237,  236,  235,  234,  232,  231,  230,
 /*   170 */   229,  228,  227,  226,  225,  224,  223,  191,  186,  215,
 /*   180 */   214,  220,  187,
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
  "END",           "ASSIG",         "LOCAL",         "IDENT",       
  "WHILE",         "REPEAT",        "UNTIL",         "FOR",         
  "IN",            "IF",            "THEN",          "ELSE",        
  "ELSEIF",        "RETURN",        "NEXT",          "BREAK",       
  "CLASS",         "PL",            "PR",            "DEF",         
  "COMMA",         "STRING",        "SBL",           "SBR",         
  "CBL",           "CBR",           "NIL",           "FALSE",       
  "TRUE",          "INT",           "REAL",          "COLON",       
  "PIPE",          "error",         "chunk",         "block",       
  "stat_list",     "stat",          "exp",           "var",         
  "else",          "class_body",    "func_body",     "ident_list",  
  "func_ident",    "function",      "functioncall",  "prefixexp",   
  "exp_list",      "dict_list",   
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
 /*  10 */ "stat ::= LOCAL IDENT",
 /*  11 */ "stat ::= LOCAL IDENT ASSIG exp",
 /*  12 */ "stat ::= WHILE exp DO block END",
 /*  13 */ "stat ::= REPEAT block UNTIL exp",
 /*  14 */ "stat ::= FOR IDENT IN exp DO block END",
 /*  15 */ "stat ::= IF exp THEN block else END",
 /*  16 */ "else ::=",
 /*  17 */ "else ::= ELSE block",
 /*  18 */ "else ::= ELSEIF exp THEN block else",
 /*  19 */ "stat ::= RETURN exp",
 /*  20 */ "stat ::= NEXT",
 /*  21 */ "stat ::= BREAK",
 /*  22 */ "stat ::= CLASS IDENT class_body",
 /*  23 */ "stat ::= CLASS IDENT PL exp PR class_body",
 /*  24 */ "class_body ::= END",
 /*  25 */ "class_body ::= NL class_body",
 /*  26 */ "class_body ::= SCOLON class_body",
 /*  27 */ "class_body ::= NL DEF IDENT func_body class_body",
 /*  28 */ "class_body ::= SCOLON DEF IDENT func_body class_body",
 /*  29 */ "class_body ::= NL IDENT ASSIG exp class_body",
 /*  30 */ "class_body ::= SCOLON IDENT ASSIG exp class_body",
 /*  31 */ "ident_list ::= IDENT",
 /*  32 */ "ident_list ::= ident_list COMMA IDENT",
 /*  33 */ "stat ::= DEF func_ident func_body",
 /*  34 */ "stat ::= LOCAL DEF IDENT func_body",
 /*  35 */ "func_ident ::= IDENT",
 /*  36 */ "func_ident ::= func_ident DOT IDENT",
 /*  37 */ "function ::= DEF func_body",
 /*  38 */ "func_body ::= PL PR block END",
 /*  39 */ "func_body ::= PL ident_list PR block END",
 /*  40 */ "functioncall ::= prefixexp PL PR",
 /*  41 */ "functioncall ::= prefixexp PL exp_list PR",
 /*  42 */ "prefixexp ::= var",
 /*  43 */ "prefixexp ::= functioncall",
 /*  44 */ "prefixexp ::= PL exp PR",
 /*  45 */ "prefixexp ::= STRING",
 /*  46 */ "prefixexp ::= SBL SBR",
 /*  47 */ "prefixexp ::= SBL exp_list SBR",
 /*  48 */ "prefixexp ::= CBL CBR",
 /*  49 */ "prefixexp ::= CBL dict_list CBR",
 /*  50 */ "exp ::= prefixexp",
 /*  51 */ "exp ::= function",
 /*  52 */ "exp ::= NIL",
 /*  53 */ "exp ::= FALSE",
 /*  54 */ "exp ::= TRUE",
 /*  55 */ "exp ::= INT",
 /*  56 */ "exp ::= REAL",
 /*  57 */ "dict_list ::= exp COLON exp",
 /*  58 */ "dict_list ::= dict_list COMMA exp COLON exp",
 /*  59 */ "exp ::= PIPE exp PIPE",
 /*  60 */ "exp ::= exp OR exp",
 /*  61 */ "exp ::= exp AND exp",
 /*  62 */ "exp ::= exp L exp",
 /*  63 */ "exp ::= exp G exp",
 /*  64 */ "exp ::= exp LEQ exp",
 /*  65 */ "exp ::= exp GEQ exp",
 /*  66 */ "exp ::= exp NEQ exp",
 /*  67 */ "exp ::= exp EQ exp",
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
  { 61, 2 },
  { 61, 4 },
  { 61, 5 },
  { 61, 4 },
  { 61, 7 },
  { 61, 6 },
  { 64, 0 },
  { 64, 2 },
  { 64, 5 },
  { 61, 2 },
  { 61, 1 },
  { 61, 1 },
  { 61, 3 },
  { 61, 6 },
  { 65, 1 },
  { 65, 2 },
  { 65, 2 },
  { 65, 5 },
  { 65, 5 },
  { 65, 5 },
  { 65, 5 },
  { 67, 1 },
  { 67, 3 },
  { 61, 3 },
  { 61, 4 },
  { 68, 1 },
  { 68, 3 },
  { 69, 2 },
  { 66, 4 },
  { 66, 5 },
  { 70, 3 },
  { 70, 4 },
  { 71, 1 },
  { 71, 1 },
  { 71, 3 },
  { 71, 1 },
  { 71, 2 },
  { 71, 3 },
  { 71, 2 },
  { 71, 3 },
  { 62, 1 },
  { 62, 1 },
  { 62, 1 },
  { 62, 1 },
  { 62, 1 },
  { 62, 1 },
  { 62, 1 },
  { 73, 3 },
  { 73, 5 },
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
  { 63, 4 },
  { 72, 1 },
  { 72, 3 },
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
{ *currentNode = yygotominor.yy0 = yymsp[-1].minor.yy84; }
#line 1059 "lparser.c"
        break;
      case 2: /* block ::= stat_list */
#line 71 "lparser.y"
{ yygotominor.yy84 = new BlockNode(yymsp[0].minor.yy143);  }
#line 1064 "lparser.c"
        break;
      case 3: /* stat_list ::= stat */
#line 73 "lparser.y"
{ yygotominor.yy143 = new NodeList<>(); if(yymsp[0].minor.yy0){ yygotominor.yy143->push_back(yymsp[0].minor.yy0); }  }
#line 1069 "lparser.c"
        break;
      case 4: /* stat_list ::= stat_list NL stat */
      case 5: /* stat_list ::= stat_list SCOLON stat */ yytestcase(yyruleno==5);
#line 74 "lparser.y"
{ yygotominor.yy143 = yymsp[-2].minor.yy143;  if(yymsp[0].minor.yy0){ yygotominor.yy143->push_back(yymsp[0].minor.yy0); }  }
#line 1075 "lparser.c"
        break;
      case 6: /* stat ::= */
      case 16: /* else ::= */ yytestcase(yyruleno==16);
#line 78 "lparser.y"
{ yygotominor.yy0 = NULL; }
#line 1081 "lparser.c"
        break;
      case 7: /* stat ::= exp */
#line 79 "lparser.y"
{ yygotominor.yy0 = new StatNode(yymsp[0].minor.yy0); }
#line 1086 "lparser.c"
        break;
      case 8: /* stat ::= DO block END */
#line 80 "lparser.y"
{ yygotominor.yy0 = yymsp[-1].minor.yy84; yymsp[-1].minor.yy84->createScope(); }
#line 1091 "lparser.c"
        break;
      case 9: /* stat ::= var ASSIG exp */
#line 83 "lparser.y"
{ yygotominor.yy0 = new AssignNode(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1096 "lparser.c"
        break;
      case 10: /* stat ::= LOCAL IDENT */
#line 85 "lparser.y"
{ yygotominor.yy0 = new DeclNode(yymsp[0].minor.yy0, NULL); }
#line 1101 "lparser.c"
        break;
      case 11: /* stat ::= LOCAL IDENT ASSIG exp */
#line 86 "lparser.y"
{ yygotominor.yy0 = new DeclNode(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1106 "lparser.c"
        break;
      case 12: /* stat ::= WHILE exp DO block END */
#line 95 "lparser.y"
{ yygotominor.yy0 = new WhileNode(yymsp[-3].minor.yy0, yymsp[-1].minor.yy84); }
#line 1111 "lparser.c"
        break;
      case 13: /* stat ::= REPEAT block UNTIL exp */
#line 97 "lparser.y"
{ yygotominor.yy0 = new RepeatNode(yymsp[0].minor.yy0, yymsp[-2].minor.yy84); }
#line 1116 "lparser.c"
        break;
      case 14: /* stat ::= FOR IDENT IN exp DO block END */
#line 99 "lparser.y"
{ yygotominor.yy0 = new ForNode(yymsp[-5].minor.yy0, yymsp[-3].minor.yy0, yymsp[-1].minor.yy84); }
#line 1121 "lparser.c"
        break;
      case 15: /* stat ::= IF exp THEN block else END */
#line 101 "lparser.y"
{ yygotominor.yy0 = new IfNode(yymsp[-4].minor.yy0, yymsp[-2].minor.yy84, yymsp[-1].minor.yy0); }
#line 1126 "lparser.c"
        break;
      case 17: /* else ::= ELSE block */
#line 103 "lparser.y"
{ yygotominor.yy0 = yymsp[0].minor.yy84; }
#line 1131 "lparser.c"
        break;
      case 18: /* else ::= ELSEIF exp THEN block else */
#line 104 "lparser.y"
{ yygotominor.yy0 = new IfNode(yymsp[-3].minor.yy0, yymsp[-1].minor.yy84, yymsp[0].minor.yy0); }
#line 1136 "lparser.c"
        break;
      case 19: /* stat ::= RETURN exp */
#line 107 "lparser.y"
{ yygotominor.yy0 = new ReturnNode(yymsp[0].minor.yy0); }
#line 1141 "lparser.c"
        break;
      case 22: /* stat ::= CLASS IDENT class_body */
#line 113 "lparser.y"
{ yygotominor.yy0 = new ClassNode(yymsp[-1].minor.yy0, NULL, yymsp[0].minor.yy144); }
#line 1146 "lparser.c"
        break;
      case 23: /* stat ::= CLASS IDENT PL exp PR class_body */
#line 114 "lparser.y"
{ yygotominor.yy0 = new ClassNode(yymsp[-4].minor.yy0, yymsp[-2].minor.yy0, yymsp[0].minor.yy144); }
#line 1151 "lparser.c"
        break;
      case 24: /* class_body ::= END */
#line 115 "lparser.y"
{ yygotominor.yy144 = new std::vector<std::pair<Node*, Node*> >(); }
#line 1156 "lparser.c"
        break;
      case 25: /* class_body ::= NL class_body */
      case 26: /* class_body ::= SCOLON class_body */ yytestcase(yyruleno==26);
#line 116 "lparser.y"
{ yygotominor.yy144 = yymsp[0].minor.yy144; }
#line 1162 "lparser.c"
        break;
      case 27: /* class_body ::= NL DEF IDENT func_body class_body */
      case 28: /* class_body ::= SCOLON DEF IDENT func_body class_body */ yytestcase(yyruleno==28);
#line 118 "lparser.y"
{ yygotominor.yy144 = yymsp[0].minor.yy144; yymsp[0].minor.yy144->push_back(std::make_pair(yymsp[-2].minor.yy0, yymsp[-1].minor.yy0)); }
#line 1168 "lparser.c"
        break;
      case 29: /* class_body ::= NL IDENT ASSIG exp class_body */
      case 30: /* class_body ::= SCOLON IDENT ASSIG exp class_body */ yytestcase(yyruleno==30);
#line 120 "lparser.y"
{ yygotominor.yy144 = yymsp[0].minor.yy144; yymsp[0].minor.yy144->push_back(std::make_pair(yymsp[-3].minor.yy0, yymsp[-1].minor.yy0)); }
#line 1174 "lparser.c"
        break;
      case 31: /* ident_list ::= IDENT */
#line 126 "lparser.y"
{
    yygotominor.yy105 = new NodeList<IdentNode>();

    assert(dynamic_cast<IdentNode*>(yymsp[0].minor.yy0));
    yygotominor.yy105->push_back(static_cast<IdentNode*>(yymsp[0].minor.yy0));

}
#line 1185 "lparser.c"
        break;
      case 32: /* ident_list ::= ident_list COMMA IDENT */
#line 134 "lparser.y"
{
    yygotominor.yy105 = yymsp[-2].minor.yy105;

    assert(dynamic_cast<IdentNode*>(yymsp[0].minor.yy0));
    yygotominor.yy105->push_back(static_cast<IdentNode*>(yymsp[0].minor.yy0));
}
#line 1195 "lparser.c"
        break;
      case 33: /* stat ::= DEF func_ident func_body */
#line 141 "lparser.y"
{ yygotominor.yy0 = new AssignNode(yymsp[-1].minor.yy0, yymsp[0].minor.yy0); }
#line 1200 "lparser.c"
        break;
      case 34: /* stat ::= LOCAL DEF IDENT func_body */
#line 142 "lparser.y"
{ yygotominor.yy0 = new DeclNode(yymsp[-1].minor.yy0, yymsp[0].minor.yy0); }
#line 1205 "lparser.c"
        break;
      case 35: /* func_ident ::= IDENT */
      case 76: /* var ::= IDENT */ yytestcase(yyruleno==76);
#line 143 "lparser.y"
{ yygotominor.yy0 = new VarNode(yymsp[0].minor.yy0); }
#line 1211 "lparser.c"
        break;
      case 36: /* func_ident ::= func_ident DOT IDENT */
      case 77: /* var ::= prefixexp DOT IDENT */ yytestcase(yyruleno==77);
#line 144 "lparser.y"
{ yygotominor.yy0 = new MemberAccessNode(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1217 "lparser.c"
        break;
      case 37: /* function ::= DEF func_body */
      case 42: /* prefixexp ::= var */ yytestcase(yyruleno==42);
      case 43: /* prefixexp ::= functioncall */ yytestcase(yyruleno==43);
      case 45: /* prefixexp ::= STRING */ yytestcase(yyruleno==45);
      case 50: /* exp ::= prefixexp */ yytestcase(yyruleno==50);
      case 51: /* exp ::= function */ yytestcase(yyruleno==51);
      case 55: /* exp ::= INT */ yytestcase(yyruleno==55);
      case 56: /* exp ::= REAL */ yytestcase(yyruleno==56);
#line 147 "lparser.y"
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
#line 1229 "lparser.c"
        break;
      case 38: /* func_body ::= PL PR block END */
#line 148 "lparser.y"
{ yygotominor.yy0 = new FuncNode(NULL, yymsp[-1].minor.yy84); }
#line 1234 "lparser.c"
        break;
      case 39: /* func_body ::= PL ident_list PR block END */
#line 149 "lparser.y"
{ yygotominor.yy0 = new FuncNode(yymsp[-3].minor.yy105, yymsp[-1].minor.yy84); }
#line 1239 "lparser.c"
        break;
      case 40: /* functioncall ::= prefixexp PL PR */
#line 151 "lparser.y"
{ yygotominor.yy0 = new CallNode(yymsp[-2].minor.yy0, NULL); }
#line 1244 "lparser.c"
        break;
      case 41: /* functioncall ::= prefixexp PL exp_list PR */
#line 152 "lparser.y"
{ yygotominor.yy0 = new CallNode(yymsp[-3].minor.yy0, yymsp[-1].minor.yy143); }
#line 1249 "lparser.c"
        break;
      case 44: /* prefixexp ::= PL exp PR */
#line 156 "lparser.y"
{ yygotominor.yy0 = yymsp[-1].minor.yy0; }
#line 1254 "lparser.c"
        break;
      case 46: /* prefixexp ::= SBL SBR */
#line 161 "lparser.y"
{ yygotominor.yy0 = new ListConstrNode(NULL); }
#line 1259 "lparser.c"
        break;
      case 47: /* prefixexp ::= SBL exp_list SBR */
#line 162 "lparser.y"
{ yygotominor.yy0 = new ListConstrNode(yymsp[-1].minor.yy143); }
#line 1264 "lparser.c"
        break;
      case 48: /* prefixexp ::= CBL CBR */
#line 163 "lparser.y"
{ yygotominor.yy0 = new DictConstrNode(NULL); }
#line 1269 "lparser.c"
        break;
      case 49: /* prefixexp ::= CBL dict_list CBR */
#line 164 "lparser.y"
{ yygotominor.yy0 = new DictConstrNode(yymsp[-1].minor.yy65); }
#line 1274 "lparser.c"
        break;
      case 52: /* exp ::= NIL */
#line 170 "lparser.y"
{ yygotominor.yy0 = new NilLitNode(); }
#line 1279 "lparser.c"
        break;
      case 53: /* exp ::= FALSE */
#line 171 "lparser.y"
{ yygotominor.yy0 = new BoolLitNode(false); }
#line 1284 "lparser.c"
        break;
      case 54: /* exp ::= TRUE */
#line 172 "lparser.y"
{ yygotominor.yy0 = new BoolLitNode(true); }
#line 1289 "lparser.c"
        break;
      case 57: /* dict_list ::= exp COLON exp */
#line 179 "lparser.y"
{ yygotominor.yy65 = new NodeDictList(); yygotominor.yy65->push_back(std::make_pair(yymsp[-2].minor.yy0, yymsp[0].minor.yy0)); }
#line 1294 "lparser.c"
        break;
      case 58: /* dict_list ::= dict_list COMMA exp COLON exp */
#line 180 "lparser.y"
{ yygotominor.yy65 = yymsp[-4].minor.yy65; yygotominor.yy65->push_back(std::make_pair(yymsp[-2].minor.yy0, yymsp[0].minor.yy0)); }
#line 1299 "lparser.c"
        break;
      case 59: /* exp ::= PIPE exp PIPE */
#line 184 "lparser.y"
{ yygotominor.yy0 = new UnOpNode<'|'>(yymsp[-1].minor.yy0); }
#line 1304 "lparser.c"
        break;
      case 60: /* exp ::= exp OR exp */
#line 186 "lparser.y"
{ yygotominor.yy0 = new OrNode(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1309 "lparser.c"
        break;
      case 61: /* exp ::= exp AND exp */
#line 187 "lparser.y"
{ yygotominor.yy0 = new AndNode(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1314 "lparser.c"
        break;
      case 62: /* exp ::= exp L exp */
#line 189 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'<'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1319 "lparser.c"
        break;
      case 63: /* exp ::= exp G exp */
#line 190 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'>'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1324 "lparser.c"
        break;
      case 64: /* exp ::= exp LEQ exp */
#line 191 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'<'+'='>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1329 "lparser.c"
        break;
      case 65: /* exp ::= exp GEQ exp */
#line 192 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'>'+'='>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1334 "lparser.c"
        break;
      case 66: /* exp ::= exp NEQ exp */
#line 193 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'!'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1339 "lparser.c"
        break;
      case 67: /* exp ::= exp EQ exp */
#line 194 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'='>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1344 "lparser.c"
        break;
      case 68: /* exp ::= exp PLUS exp */
#line 196 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'+'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1349 "lparser.c"
        break;
      case 69: /* exp ::= exp MINUS exp */
#line 197 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'-'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1354 "lparser.c"
        break;
      case 70: /* exp ::= exp MUL exp */
#line 199 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'*'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1359 "lparser.c"
        break;
      case 71: /* exp ::= exp DIV exp */
#line 200 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'/'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1364 "lparser.c"
        break;
      case 72: /* exp ::= exp MOD exp */
#line 201 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'%'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1369 "lparser.c"
        break;
      case 73: /* exp ::= exp EXP exp */
#line 203 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'^'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1374 "lparser.c"
        break;
      case 74: /* exp ::= NOT exp */
#line 205 "lparser.y"
{ yygotominor.yy0 = new UnOpNode<'!'>(yymsp[0].minor.yy0); }
#line 1379 "lparser.c"
        break;
      case 75: /* exp ::= MINUS exp */
#line 206 "lparser.y"
{ yygotominor.yy0 = new UnOpNode<'-'>(yymsp[0].minor.yy0); }
#line 1384 "lparser.c"
        break;
      case 78: /* var ::= prefixexp SBL exp SBR */
#line 213 "lparser.y"
{ yygotominor.yy0 = new IndexAccessNode(yymsp[-3].minor.yy0, yymsp[-1].minor.yy0); }
#line 1389 "lparser.c"
        break;
      case 79: /* exp_list ::= exp */
#line 216 "lparser.y"
{ yygotominor.yy143 = new NodeList<>(); yygotominor.yy143->push_back(yymsp[0].minor.yy0); }
#line 1394 "lparser.c"
        break;
      case 80: /* exp_list ::= exp_list COMMA exp */
#line 217 "lparser.y"
{ yygotominor.yy143 = yymsp[-2].minor.yy143; yygotominor.yy143->push_back(yymsp[0].minor.yy0); }
#line 1399 "lparser.c"
        break;
      default:
      /* (0) chunk ::= TERMINATION UNINITIALIZED WARNING DOT */ yytestcase(yyruleno==0);
      /* (20) stat ::= NEXT */ yytestcase(yyruleno==20);
      /* (21) stat ::= BREAK */ yytestcase(yyruleno==21);
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
#line 1467 "lparser.c"
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
