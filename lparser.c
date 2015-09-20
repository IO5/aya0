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
    #include "parser/for_node.h"
    #include "parser/class_node.h"

    #ifdef DEBUG
        #include <iostream>
    #endif // DEBUG

    using namespace AYA;
#line 44 "lparser.c"
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
#define YYACTIONTYPE unsigned char
#define LemonTOKENTYPE AYA::Node*
typedef union {
  int yyinit;
  LemonTOKENTYPE yy0;
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
#define YYNSTATE 164
#define YYNRULE 76
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
#define YY_ACTTAB_COUNT (715)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    24,  119,  104,  129,   25,  118,  120,  240,   31,   30,
 /*    10 */    29,   28,   27,    8,   26,  117,  103,  141,   84,   20,
 /*    20 */     6,   15,   97,   92,   17,   13,   11,   10,   16,  133,
 /*    30 */   132,   93,   40,  164,   45,   23,  154,  150,  149,  148,
 /*    40 */   147,  146,   12,   24,  111,  115,   38,   25,  161,   29,
 /*    50 */    28,   27,    9,   26,  114,  156,    8,   41,   41,  103,
 /*    60 */   141,   84,   20,    6,    1,   97,  144,   17,  129,  101,
 /*    70 */   165,   16,  133,  132,   93,   40,  162,   45,   48,  154,
 /*    80 */   150,  149,  148,  147,  146,   12,  100,  111,   92,   38,
 /*    90 */   125,   44,   42,   33,   34,   39,   37,   36,   35,   32,
 /*   100 */    31,   30,   29,   28,   27,   52,   26,  160,   44,   42,
 /*   110 */    33,   34,   39,   37,   36,   35,   32,   31,   30,   29,
 /*   120 */    28,   27,  158,   26,  240,  240,  240,  240,   32,   31,
 /*   130 */    30,   29,   28,   27,  152,   26,   44,   42,   33,   34,
 /*   140 */    39,   37,   36,   35,   32,   31,   30,   29,   28,   27,
 /*   150 */    43,   26,   33,   34,   39,   37,   36,   35,   32,   31,
 /*   160 */    30,   29,   28,   27,  142,   26,   44,   42,   33,   34,
 /*   170 */    39,   37,   36,   35,   32,   31,   30,   29,   28,   27,
 /*   180 */   140,   26,    3,   14,   91,  143,   26,  102,   22,  139,
 /*   190 */    19,   44,   42,   33,   34,   39,   37,   36,   35,   32,
 /*   200 */    31,   30,   29,   28,   27,   21,   26,   52,   54,   50,
 /*   210 */   137,   96,   18,  136,    7,   46,   44,   42,   33,   34,
 /*   220 */    39,   37,   36,   35,   32,   31,   30,   29,   28,   27,
 /*   230 */   135,   26,   53,  123,  126,  122,  162,   52,  138,    5,
 /*   240 */    49,   44,   42,   33,   34,   39,   37,   36,   35,   32,
 /*   250 */    31,   30,   29,   28,   27,  242,   26,   87,   44,   42,
 /*   260 */    33,   34,   39,   37,   36,   35,   32,   31,   30,   29,
 /*   270 */    28,   27,   94,   26,  242,  130,    4,   39,   37,   36,
 /*   280 */    35,   32,   31,   30,   29,   28,   27,  128,   26,  127,
 /*   290 */   124,  242,  131,    2,  242,   44,   42,   33,   34,   39,
 /*   300 */    37,   36,   35,   32,   31,   30,   29,   28,   27,   24,
 /*   310 */    26,  242,  242,   25,   72,  155,  242,  242,  242,  242,
 /*   320 */    24,  151,  153,   83,   25,  242,  141,  241,  116,   88,
 /*   330 */   159,   71,  112,  242,  242,  242,  242,  141,  151,  153,
 /*   340 */    83,   40,  157,   55,  242,  154,  150,  149,  148,  147,
 /*   350 */   146,   12,   40,  111,   55,   38,  154,  150,  149,  148,
 /*   360 */   147,  146,   12,  145,  111,  242,   38,   42,   33,   34,
 /*   370 */    39,   37,   36,   35,   32,   31,   30,   29,   28,   27,
 /*   380 */    24,   26,  242,  242,   25,  242,  242,  242,   90,   88,
 /*   390 */   159,   71,  112,  242,   69,  155,  242,  141,  151,  153,
 /*   400 */    83,  151,  153,   83,   86,  242,  242,  242,  242,  242,
 /*   410 */   242,  242,   40,  242,   55,  242,  154,  150,  149,  148,
 /*   420 */   147,  146,   12,  242,  111,  242,   38,  113,   88,  159,
 /*   430 */    71,  112,   99,   88,  159,   71,  112,  151,  153,   83,
 /*   440 */   242,  242,  151,  153,   83,   98,   88,  159,   71,  112,
 /*   450 */    95,   88,  159,   71,  112,  151,  153,   83,   69,  155,
 /*   460 */   151,  153,   83,   70,  155,  151,  153,   83,   85,  242,
 /*   470 */   151,  153,   83,   51,   88,  159,   71,  112,  134,   88,
 /*   480 */   159,   71,  112,  151,  153,   83,  242,  242,  151,  153,
 /*   490 */    83,   47,   88,  159,   71,  112,   89,   88,  159,   71,
 /*   500 */   112,  151,  153,   83,  242,  242,  151,  153,   83,  163,
 /*   510 */    71,  112,  121,   71,  112,  242,  242,  151,  153,   83,
 /*   520 */   151,  153,   83,   73,  155,  242,   68,  155,  242,  242,
 /*   530 */   151,  153,   83,  151,  153,   83,   63,  155,  242,   74,
 /*   540 */   155,  242,  242,  151,  153,   83,  151,  153,   83,   62,
 /*   550 */   155,  242,   79,  155,  242,  242,  151,  153,   83,  151,
 /*   560 */   153,   83,   78,  155,  242,   77,  155,  242,  242,  151,
 /*   570 */   153,   83,  151,  153,   83,   76,  155,  242,   75,  155,
 /*   580 */   242,  242,  151,  153,   83,  151,  153,   83,   80,  155,
 /*   590 */   242,   82,  155,  242,  242,  151,  153,   83,  151,  153,
 /*   600 */    83,   81,  155,  242,  110,  155,  242,  242,  151,  153,
 /*   610 */    83,  151,  153,   83,  109,  155,  242,  108,  155,  242,
 /*   620 */   242,  151,  153,   83,  151,  153,   83,  107,  155,  242,
 /*   630 */   106,  155,  242,  242,  151,  153,   83,  151,  153,   83,
 /*   640 */   105,  155,  242,   61,  155,  242,  242,  151,  153,   83,
 /*   650 */   151,  153,   83,   67,  155,  242,   66,  155,  242,  242,
 /*   660 */   151,  153,   83,  151,  153,   83,   60,  155,  242,   65,
 /*   670 */   155,  242,  242,  151,  153,   83,  151,  153,   83,   59,
 /*   680 */   155,  242,   58,  155,  242,  242,  151,  153,   83,  151,
 /*   690 */   153,   83,   64,  155,  242,   57,  155,  242,  242,  151,
 /*   700 */   153,   83,  151,  153,   83,   56,  155,  242,  242,  242,
 /*   710 */   242,  242,  151,  153,   83,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    11,   18,   20,   25,   15,   19,   17,    9,   10,   11,
 /*    10 */    12,   13,   14,   24,   16,   20,   27,   28,   29,   30,
 /*    20 */    31,   43,   33,   45,   35,   43,   22,   23,   39,   40,
 /*    30 */    41,   42,   43,    0,   45,   53,   47,   48,   49,   50,
 /*    40 */    51,   52,   53,   11,   55,   21,   57,   15,   28,   12,
 /*    50 */    13,   14,   44,   16,   46,   44,   24,   46,   46,   27,
 /*    60 */    28,   29,   30,   31,   44,   33,   54,   35,   25,   28,
 /*    70 */     0,   39,   40,   41,   42,   43,   67,   45,   69,   47,
 /*    80 */    48,   49,   50,   51,   52,   53,   45,   55,   45,   57,
 /*    90 */    28,    1,    2,    3,    4,    5,    6,    7,    8,    9,
 /*   100 */    10,   11,   12,   13,   14,   43,   16,   28,    1,    2,
 /*   110 */     3,    4,    5,    6,    7,    8,    9,   10,   11,   12,
 /*   120 */    13,   14,   25,   16,    5,    6,    7,    8,    9,   10,
 /*   130 */    11,   12,   13,   14,   44,   16,    1,    2,    3,    4,
 /*   140 */     5,    6,    7,    8,    9,   10,   11,   12,   13,   14,
 /*   150 */    26,   16,    3,    4,    5,    6,    7,    8,    9,   10,
 /*   160 */    11,   12,   13,   14,   57,   16,    1,    2,    3,    4,
 /*   170 */     5,    6,    7,    8,    9,   10,   11,   12,   13,   14,
 /*   180 */    28,   16,   37,   38,   20,   56,   16,   28,   26,   54,
 /*   190 */    32,    1,    2,    3,    4,    5,    6,    7,    8,    9,
 /*   200 */    10,   11,   12,   13,   14,   26,   16,   43,   28,   44,
 /*   210 */    25,   28,   34,   25,   24,   28,    1,    2,    3,    4,
 /*   220 */     5,    6,    7,    8,    9,   10,   11,   12,   13,   14,
 /*   230 */    25,   16,   28,   25,   28,   25,   67,   43,   67,   24,
 /*   240 */    67,    1,    2,    3,    4,    5,    6,    7,    8,    9,
 /*   250 */    10,   11,   12,   13,   14,   74,   16,   68,    1,    2,
 /*   260 */     3,    4,    5,    6,    7,    8,    9,   10,   11,   12,
 /*   270 */    13,   14,   65,   16,   74,   66,   36,    5,    6,    7,
 /*   280 */     8,    9,   10,   11,   12,   13,   14,   66,   16,   67,
 /*   290 */    65,   74,   66,   36,   74,    1,    2,    3,    4,    5,
 /*   300 */     6,    7,    8,    9,   10,   11,   12,   13,   14,   11,
 /*   310 */    16,   74,   74,   15,   63,   64,   74,   74,   74,   74,
 /*   320 */    11,   70,   71,   72,   15,   74,   28,   59,   60,   61,
 /*   330 */    62,   63,   64,   74,   74,   74,   74,   28,   70,   71,
 /*   340 */    72,   43,   44,   45,   74,   47,   48,   49,   50,   51,
 /*   350 */    52,   53,   43,   55,   45,   57,   47,   48,   49,   50,
 /*   360 */    51,   52,   53,   54,   55,   74,   57,    2,    3,    4,
 /*   370 */     5,    6,    7,    8,    9,   10,   11,   12,   13,   14,
 /*   380 */    11,   16,   74,   74,   15,   74,   74,   74,   60,   61,
 /*   390 */    62,   63,   64,   74,   63,   64,   74,   28,   70,   71,
 /*   400 */    72,   70,   71,   72,   73,   74,   74,   74,   74,   74,
 /*   410 */    74,   74,   43,   74,   45,   74,   47,   48,   49,   50,
 /*   420 */    51,   52,   53,   74,   55,   74,   57,   60,   61,   62,
 /*   430 */    63,   64,   60,   61,   62,   63,   64,   70,   71,   72,
 /*   440 */    74,   74,   70,   71,   72,   60,   61,   62,   63,   64,
 /*   450 */    60,   61,   62,   63,   64,   70,   71,   72,   63,   64,
 /*   460 */    70,   71,   72,   63,   64,   70,   71,   72,   73,   74,
 /*   470 */    70,   71,   72,   60,   61,   62,   63,   64,   60,   61,
 /*   480 */    62,   63,   64,   70,   71,   72,   74,   74,   70,   71,
 /*   490 */    72,   60,   61,   62,   63,   64,   60,   61,   62,   63,
 /*   500 */    64,   70,   71,   72,   74,   74,   70,   71,   72,   62,
 /*   510 */    63,   64,   62,   63,   64,   74,   74,   70,   71,   72,
 /*   520 */    70,   71,   72,   63,   64,   74,   63,   64,   74,   74,
 /*   530 */    70,   71,   72,   70,   71,   72,   63,   64,   74,   63,
 /*   540 */    64,   74,   74,   70,   71,   72,   70,   71,   72,   63,
 /*   550 */    64,   74,   63,   64,   74,   74,   70,   71,   72,   70,
 /*   560 */    71,   72,   63,   64,   74,   63,   64,   74,   74,   70,
 /*   570 */    71,   72,   70,   71,   72,   63,   64,   74,   63,   64,
 /*   580 */    74,   74,   70,   71,   72,   70,   71,   72,   63,   64,
 /*   590 */    74,   63,   64,   74,   74,   70,   71,   72,   70,   71,
 /*   600 */    72,   63,   64,   74,   63,   64,   74,   74,   70,   71,
 /*   610 */    72,   70,   71,   72,   63,   64,   74,   63,   64,   74,
 /*   620 */    74,   70,   71,   72,   70,   71,   72,   63,   64,   74,
 /*   630 */    63,   64,   74,   74,   70,   71,   72,   70,   71,   72,
 /*   640 */    63,   64,   74,   63,   64,   74,   74,   70,   71,   72,
 /*   650 */    70,   71,   72,   63,   64,   74,   63,   64,   74,   74,
 /*   660 */    70,   71,   72,   70,   71,   72,   63,   64,   74,   63,
 /*   670 */    64,   74,   74,   70,   71,   72,   70,   71,   72,   63,
 /*   680 */    64,   74,   63,   64,   74,   74,   70,   71,   72,   70,
 /*   690 */    71,   72,   63,   64,   74,   63,   64,   74,   74,   70,
 /*   700 */    71,   72,   70,   71,   72,   63,   64,   74,   74,   74,
 /*   710 */    74,   74,   70,   71,   72,
};
#define YY_SHIFT_USE_DFLT (-23)
#define YY_SHIFT_COUNT (120)
#define YY_SHIFT_MIN   (-22)
#define YY_SHIFT_MAX   (369)
static const short yy_shift_ofst[] = {
 /*     0 */   -11,   32,   32,   32,   32,   32,   32,   32,   32,   32,
 /*    10 */    32,   32,  309,  298,  369,  369,  369,  369,  369,  369,
 /*    20 */   369,  369,  369,  369,  369,  369,  369,  369,  369,  369,
 /*    30 */   369,  369,  369,  369,  369,  369,  369,  369,  369,  369,
 /*    40 */   369,  369,  369,  369,  369,   62,  -22,  145,  164,   43,
 /*    50 */    43,  145,   20,  194,  194,  194,  257,  165,  240,  215,
 /*    60 */   190,  135,  107,   90,  294,  294,  294,  294,  294,  294,
 /*    70 */   294,  294,  365,  149,  119,  272,  272,  119,  119,  119,
 /*    80 */    -2,   37,   37,  -18,   41,   12,   11,    8,    4,  210,
 /*    90 */   208,  206,  204,  187,  205,  188,  178,  183,  158,  185,
 /*   100 */   180,  179,  162,  159,  152,  170,  170,  170,  170,  170,
 /*   110 */   170,  129,  124,   97,   79,   70,   24,   33,   -5,  -14,
 /*   120 */   -17,
};
#define YY_REDUCE_USE_DFLT (-1)
#define YY_REDUCE_COUNT (55)
#define YY_REDUCE_MIN   (0)
#define YY_REDUCE_MAX   (642)
static const short yy_reduce_ofst[] = {
 /*     0 */   268,  436,  431,  418,  413,  390,  385,  372,  367,  328,
 /*    10 */   450,  447,  395,  331,  642,  632,  629,  619,  616,  606,
 /*    20 */   603,  593,  590,  580,  577,  567,  564,  554,  551,  541,
 /*    30 */   538,  528,  525,  515,  512,  502,  499,  489,  486,  476,
 /*    40 */   473,  463,  460,  400,  251,    9,  226,  225,  222,  221,
 /*    50 */   209,  207,  189,  173,  171,  169,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   170,  170,  170,  170,  170,  170,  170,  170,  170,  170,
 /*    10 */   170,  170,  240,  240,  240,  240,  240,  240,  240,  240,
 /*    20 */   240,  240,  240,  240,  240,  240,  240,  240,  240,  240,
 /*    30 */   240,  240,  240,  240,  240,  240,  240,  240,  240,  240,
 /*    40 */   240,  240,  240,  240,  240,  240,  240,  182,  240,  240,
 /*    50 */   240,  182,  240,  240,  240,  240,  240,  240,  240,  240,
 /*    60 */   240,  240,  240,  240,  185,  179,  177,  174,  239,  238,
 /*    70 */   173,  171,  218,  219,  220,  225,  224,  223,  222,  221,
 /*    80 */   226,  228,  227,  207,  240,  240,  240,  240,  166,  240,
 /*    90 */   240,  240,  240,  240,  240,  240,  240,  240,  240,  240,
 /*   100 */   240,  176,  175,  240,  240,  234,  233,  232,  231,  230,
 /*   110 */   229,  240,  203,  240,  240,  240,  240,  240,  240,  240,
 /*   120 */   240,  169,  199,  200,  184,  196,  197,  194,  191,  190,
 /*   130 */   189,  188,  187,  186,  183,  181,  180,  178,  195,  237,
 /*   140 */   236,  235,  217,  216,  215,  214,  213,  212,  211,  210,
 /*   150 */   209,  208,  206,  205,  204,  203,  202,  201,  172,  167,
 /*   160 */   193,  192,  198,  168,
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
  "CBR",           "PIPE",          "error",         "chunk",       
  "block",         "stat_list",     "stat",          "exp",         
  "var",           "else",          "class_body",    "func_body",   
  "ident_list",    "func_ident",    "function",      "functioncall",
  "prefixexp",     "exp_list",    
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
 /*  26 */ "class_body ::= END",
 /*  27 */ "class_body ::= DEF IDENT func_body class_body",
 /*  28 */ "ident_list ::= IDENT",
 /*  29 */ "ident_list ::= ident_list COMMA IDENT",
 /*  30 */ "stat ::= DEF func_ident func_body",
 /*  31 */ "stat ::= LOCAL DEF IDENT func_body",
 /*  32 */ "func_ident ::= IDENT",
 /*  33 */ "func_ident ::= func_ident DOT IDENT",
 /*  34 */ "function ::= DEF func_body",
 /*  35 */ "func_body ::= PL PR block END",
 /*  36 */ "func_body ::= PL ident_list PR block END",
 /*  37 */ "functioncall ::= prefixexp PL PR",
 /*  38 */ "functioncall ::= prefixexp PL exp_list PR",
 /*  39 */ "prefixexp ::= var",
 /*  40 */ "prefixexp ::= STRING",
 /*  41 */ "prefixexp ::= functioncall",
 /*  42 */ "prefixexp ::= PL exp PR",
 /*  43 */ "exp ::= prefixexp",
 /*  44 */ "exp ::= function",
 /*  45 */ "exp ::= NIL",
 /*  46 */ "exp ::= FALSE",
 /*  47 */ "exp ::= TRUE",
 /*  48 */ "exp ::= INT",
 /*  49 */ "exp ::= REAL",
 /*  50 */ "exp ::= SBL SBR",
 /*  51 */ "exp ::= SBL exp_list SBR",
 /*  52 */ "exp ::= CBL CBR",
 /*  53 */ "exp ::= PIPE exp PIPE",
 /*  54 */ "exp ::= exp OR exp",
 /*  55 */ "exp ::= exp AND exp",
 /*  56 */ "exp ::= exp L exp",
 /*  57 */ "exp ::= exp G exp",
 /*  58 */ "exp ::= exp LEQ exp",
 /*  59 */ "exp ::= exp GEQ exp",
 /*  60 */ "exp ::= exp NEQ exp",
 /*  61 */ "exp ::= exp EQ exp",
 /*  62 */ "exp ::= exp RANGEOP exp",
 /*  63 */ "exp ::= exp PLUS exp",
 /*  64 */ "exp ::= exp MINUS exp",
 /*  65 */ "exp ::= exp MUL exp",
 /*  66 */ "exp ::= exp DIV exp",
 /*  67 */ "exp ::= exp MOD exp",
 /*  68 */ "exp ::= exp EXP exp",
 /*  69 */ "exp ::= NOT exp",
 /*  70 */ "exp ::= MINUS exp",
 /*  71 */ "var ::= IDENT",
 /*  72 */ "var ::= prefixexp DOT IDENT",
 /*  73 */ "var ::= prefixexp SBL exp SBR",
 /*  74 */ "exp_list ::= exp",
 /*  75 */ "exp_list ::= exp_list COMMA exp",
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
  { 66, 1 },
  { 66, 4 },
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
  { 72, 1 },
  { 72, 3 },
  { 63, 1 },
  { 63, 1 },
  { 63, 1 },
  { 63, 1 },
  { 63, 1 },
  { 63, 1 },
  { 63, 1 },
  { 63, 2 },
  { 63, 3 },
  { 63, 2 },
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
{ *currentNode = yygotominor.yy0 = yymsp[-1].minor.yy84; }
#line 1021 "lparser.c"
        break;
      case 2: /* block ::= stat_list */
#line 71 "lparser.y"
{ yygotominor.yy84 = new BlockNode(yymsp[0].minor.yy143);  }
#line 1026 "lparser.c"
        break;
      case 3: /* stat_list ::= stat */
#line 73 "lparser.y"
{ yygotominor.yy143 = new NodeList<>(); if(yymsp[0].minor.yy0){ yygotominor.yy143->push_back(yymsp[0].minor.yy0); }  }
#line 1031 "lparser.c"
        break;
      case 4: /* stat_list ::= stat_list NL stat */
      case 5: /* stat_list ::= stat_list SCOLON stat */ yytestcase(yyruleno==5);
#line 74 "lparser.y"
{ yygotominor.yy143 = yymsp[-2].minor.yy143;  if(yymsp[0].minor.yy0){ yygotominor.yy143->push_back(yymsp[0].minor.yy0); }  }
#line 1037 "lparser.c"
        break;
      case 6: /* stat ::= */
      case 18: /* else ::= */ yytestcase(yyruleno==18);
#line 78 "lparser.y"
{ yygotominor.yy0 = NULL; }
#line 1043 "lparser.c"
        break;
      case 7: /* stat ::= exp */
#line 79 "lparser.y"
{ yygotominor.yy0 = new StatNode(yymsp[0].minor.yy0); }
#line 1048 "lparser.c"
        break;
      case 8: /* stat ::= DO block END */
#line 80 "lparser.y"
{ yygotominor.yy0 = yymsp[-1].minor.yy84; yymsp[-1].minor.yy84->createScope(); }
#line 1053 "lparser.c"
        break;
      case 9: /* stat ::= var ASSIG exp */
#line 83 "lparser.y"
{ yygotominor.yy0 = new AssignNode(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1058 "lparser.c"
        break;
      case 10: /* stat ::= GLOBAL IDENT ASSIG exp */
#line 84 "lparser.y"
{ yygotominor.yy0 = new AssignNode(new VarNode(yymsp[-2].minor.yy0), yymsp[0].minor.yy0); }
#line 1063 "lparser.c"
        break;
      case 11: /* stat ::= GLOBAL IDENT */
#line 85 "lparser.y"
{ yygotominor.yy0 = new AssignNode(new VarNode(yymsp[0].minor.yy0), new NilLitNode()); }
#line 1068 "lparser.c"
        break;
      case 12: /* stat ::= LOCAL IDENT */
#line 87 "lparser.y"
{ yygotominor.yy0 = new DeclNode(yymsp[0].minor.yy0, NULL); }
#line 1073 "lparser.c"
        break;
      case 13: /* stat ::= LOCAL IDENT ASSIG exp */
#line 88 "lparser.y"
{ yygotominor.yy0 = new DeclNode(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1078 "lparser.c"
        break;
      case 14: /* stat ::= WHILE exp DO block END */
#line 97 "lparser.y"
{ yygotominor.yy0 = new WhileNode(yymsp[-3].minor.yy0, yymsp[-1].minor.yy84); }
#line 1083 "lparser.c"
        break;
      case 15: /* stat ::= REPEAT block UNTIL exp */
#line 99 "lparser.y"
{ yygotominor.yy0 = new RepeatNode(yymsp[0].minor.yy0, yymsp[-2].minor.yy84); }
#line 1088 "lparser.c"
        break;
      case 16: /* stat ::= FOR IDENT IN exp DO block END */
#line 101 "lparser.y"
{ yygotominor.yy0 = new ForNode(yymsp[-5].minor.yy0, yymsp[-3].minor.yy0, yymsp[-1].minor.yy84); }
#line 1093 "lparser.c"
        break;
      case 17: /* stat ::= IF exp THEN block else END */
#line 103 "lparser.y"
{ yygotominor.yy0 = new IfNode(yymsp[-4].minor.yy0, yymsp[-2].minor.yy84, yymsp[-1].minor.yy0); }
#line 1098 "lparser.c"
        break;
      case 19: /* else ::= ELSE block */
#line 105 "lparser.y"
{ yygotominor.yy0 = yymsp[0].minor.yy84; }
#line 1103 "lparser.c"
        break;
      case 20: /* else ::= ELSEIF exp THEN block else */
#line 106 "lparser.y"
{ yygotominor.yy0 = new IfNode(yymsp[-3].minor.yy0, yymsp[-1].minor.yy84, yymsp[0].minor.yy0); }
#line 1108 "lparser.c"
        break;
      case 21: /* stat ::= RETURN exp */
#line 109 "lparser.y"
{ yygotominor.yy0 = new ReturnNode(yymsp[0].minor.yy0); }
#line 1113 "lparser.c"
        break;
      case 24: /* stat ::= CLASS IDENT class_body */
#line 115 "lparser.y"
{ yygotominor.yy0 = new ClassNode(yymsp[-1].minor.yy0, NULL, yymsp[0].minor.yy144); }
#line 1118 "lparser.c"
        break;
      case 25: /* stat ::= CLASS IDENT PL exp PR class_body */
#line 116 "lparser.y"
{ yygotominor.yy0 = new ClassNode(yymsp[-4].minor.yy0, yymsp[-2].minor.yy0, yymsp[0].minor.yy144); }
#line 1123 "lparser.c"
        break;
      case 26: /* class_body ::= END */
#line 117 "lparser.y"
{ yygotominor.yy144 = new std::vector<std::pair<Node*, Node*> >(); }
#line 1128 "lparser.c"
        break;
      case 27: /* class_body ::= DEF IDENT func_body class_body */
#line 118 "lparser.y"
{ yygotominor.yy144 = yymsp[0].minor.yy144; yymsp[0].minor.yy144->push_back(std::make_pair(yymsp[-2].minor.yy0, yymsp[-1].minor.yy0)); }
#line 1133 "lparser.c"
        break;
      case 28: /* ident_list ::= IDENT */
#line 124 "lparser.y"
{
    yygotominor.yy105 = new NodeList<IdentNode>();

    assert(dynamic_cast<IdentNode*>(yymsp[0].minor.yy0));
    yygotominor.yy105->push_back(static_cast<IdentNode*>(yymsp[0].minor.yy0));

}
#line 1144 "lparser.c"
        break;
      case 29: /* ident_list ::= ident_list COMMA IDENT */
#line 132 "lparser.y"
{
    yygotominor.yy105 = yymsp[-2].minor.yy105;

    assert(dynamic_cast<IdentNode*>(yymsp[0].minor.yy0));
    yygotominor.yy105->push_back(static_cast<IdentNode*>(yymsp[0].minor.yy0));
}
#line 1154 "lparser.c"
        break;
      case 30: /* stat ::= DEF func_ident func_body */
#line 139 "lparser.y"
{ yygotominor.yy0 = new AssignNode(yymsp[-1].minor.yy0, yymsp[0].minor.yy0); }
#line 1159 "lparser.c"
        break;
      case 31: /* stat ::= LOCAL DEF IDENT func_body */
#line 140 "lparser.y"
{ yygotominor.yy0 = new DeclNode(yymsp[-1].minor.yy0, yymsp[0].minor.yy0); }
#line 1164 "lparser.c"
        break;
      case 32: /* func_ident ::= IDENT */
      case 71: /* var ::= IDENT */ yytestcase(yyruleno==71);
#line 141 "lparser.y"
{ yygotominor.yy0 = new VarNode(yymsp[0].minor.yy0); }
#line 1170 "lparser.c"
        break;
      case 33: /* func_ident ::= func_ident DOT IDENT */
      case 72: /* var ::= prefixexp DOT IDENT */ yytestcase(yyruleno==72);
#line 142 "lparser.y"
{ yygotominor.yy0 = new MemberAccessNode(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1176 "lparser.c"
        break;
      case 34: /* function ::= DEF func_body */
      case 39: /* prefixexp ::= var */ yytestcase(yyruleno==39);
      case 40: /* prefixexp ::= STRING */ yytestcase(yyruleno==40);
      case 41: /* prefixexp ::= functioncall */ yytestcase(yyruleno==41);
      case 43: /* exp ::= prefixexp */ yytestcase(yyruleno==43);
      case 44: /* exp ::= function */ yytestcase(yyruleno==44);
      case 48: /* exp ::= INT */ yytestcase(yyruleno==48);
      case 49: /* exp ::= REAL */ yytestcase(yyruleno==49);
#line 145 "lparser.y"
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
#line 1188 "lparser.c"
        break;
      case 35: /* func_body ::= PL PR block END */
#line 146 "lparser.y"
{ yygotominor.yy0 = new FuncNode(NULL, yymsp[-1].minor.yy84); }
#line 1193 "lparser.c"
        break;
      case 36: /* func_body ::= PL ident_list PR block END */
#line 147 "lparser.y"
{ yygotominor.yy0 = new FuncNode(yymsp[-3].minor.yy105, yymsp[-1].minor.yy84); }
#line 1198 "lparser.c"
        break;
      case 37: /* functioncall ::= prefixexp PL PR */
#line 149 "lparser.y"
{ yygotominor.yy0 = new CallNode(yymsp[-2].minor.yy0, NULL); }
#line 1203 "lparser.c"
        break;
      case 38: /* functioncall ::= prefixexp PL exp_list PR */
#line 150 "lparser.y"
{ yygotominor.yy0 = new CallNode(yymsp[-3].minor.yy0, yymsp[-1].minor.yy143); }
#line 1208 "lparser.c"
        break;
      case 42: /* prefixexp ::= PL exp PR */
#line 155 "lparser.y"
{ yygotominor.yy0 = yymsp[-1].minor.yy0; }
#line 1213 "lparser.c"
        break;
      case 45: /* exp ::= NIL */
#line 161 "lparser.y"
{ yygotominor.yy0 = new NilLitNode(); }
#line 1218 "lparser.c"
        break;
      case 46: /* exp ::= FALSE */
#line 162 "lparser.y"
{ yygotominor.yy0 = new BoolLitNode(false); }
#line 1223 "lparser.c"
        break;
      case 47: /* exp ::= TRUE */
#line 163 "lparser.y"
{ yygotominor.yy0 = new BoolLitNode(true); }
#line 1228 "lparser.c"
        break;
      case 50: /* exp ::= SBL SBR */
#line 170 "lparser.y"
{ yygotominor.yy0 = new ListConstrNode(NULL); }
#line 1233 "lparser.c"
        break;
      case 51: /* exp ::= SBL exp_list SBR */
#line 171 "lparser.y"
{ yygotominor.yy0 = new ListConstrNode(yymsp[-1].minor.yy143); }
#line 1238 "lparser.c"
        break;
      case 52: /* exp ::= CBL CBR */
#line 172 "lparser.y"
{ yygotominor.yy0; }
#line 1243 "lparser.c"
        break;
      case 53: /* exp ::= PIPE exp PIPE */
#line 175 "lparser.y"
{ yygotominor.yy0 = new UnOpNode<'|'>(yymsp[-1].minor.yy0); }
#line 1248 "lparser.c"
        break;
      case 54: /* exp ::= exp OR exp */
#line 177 "lparser.y"
{ yygotominor.yy0 = new OrNode(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1253 "lparser.c"
        break;
      case 55: /* exp ::= exp AND exp */
#line 178 "lparser.y"
{ yygotominor.yy0 = new AndNode(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1258 "lparser.c"
        break;
      case 56: /* exp ::= exp L exp */
#line 180 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'<'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1263 "lparser.c"
        break;
      case 57: /* exp ::= exp G exp */
#line 181 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'>'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1268 "lparser.c"
        break;
      case 58: /* exp ::= exp LEQ exp */
#line 182 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'<'+'='>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1273 "lparser.c"
        break;
      case 59: /* exp ::= exp GEQ exp */
#line 183 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'>'+'='>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1278 "lparser.c"
        break;
      case 60: /* exp ::= exp NEQ exp */
#line 184 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'!'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1283 "lparser.c"
        break;
      case 61: /* exp ::= exp EQ exp */
#line 185 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'='>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1288 "lparser.c"
        break;
      case 63: /* exp ::= exp PLUS exp */
#line 189 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'+'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1293 "lparser.c"
        break;
      case 64: /* exp ::= exp MINUS exp */
#line 190 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'-'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1298 "lparser.c"
        break;
      case 65: /* exp ::= exp MUL exp */
#line 192 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'*'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1303 "lparser.c"
        break;
      case 66: /* exp ::= exp DIV exp */
#line 193 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'/'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1308 "lparser.c"
        break;
      case 67: /* exp ::= exp MOD exp */
#line 194 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'%'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1313 "lparser.c"
        break;
      case 68: /* exp ::= exp EXP exp */
#line 196 "lparser.y"
{ yygotominor.yy0 = new BinOpNode<'^'>(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1318 "lparser.c"
        break;
      case 69: /* exp ::= NOT exp */
#line 198 "lparser.y"
{ yygotominor.yy0 = new UnOpNode<'!'>(yymsp[0].minor.yy0); }
#line 1323 "lparser.c"
        break;
      case 70: /* exp ::= MINUS exp */
#line 199 "lparser.y"
{ yygotominor.yy0 = new UnOpNode<'-'>(yymsp[0].minor.yy0); }
#line 1328 "lparser.c"
        break;
      case 73: /* var ::= prefixexp SBL exp SBR */
#line 206 "lparser.y"
{ yygotominor.yy0 = new IndexAccessNode(yymsp[-3].minor.yy0, yymsp[-1].minor.yy0); }
#line 1333 "lparser.c"
        break;
      case 74: /* exp_list ::= exp */
#line 209 "lparser.y"
{ yygotominor.yy143 = new NodeList<>(); yygotominor.yy143->push_back(yymsp[0].minor.yy0); }
#line 1338 "lparser.c"
        break;
      case 75: /* exp_list ::= exp_list COMMA exp */
#line 210 "lparser.y"
{ yygotominor.yy143 = yymsp[-2].minor.yy143; yygotominor.yy143->push_back(yymsp[0].minor.yy0); }
#line 1343 "lparser.c"
        break;
      default:
      /* (0) chunk ::= TERMINATION UNINITIALIZED WARNING DOT */ yytestcase(yyruleno==0);
      /* (22) stat ::= NEXT */ yytestcase(yyruleno==22);
      /* (23) stat ::= BREAK */ yytestcase(yyruleno==23);
      /* (62) exp ::= exp RANGEOP exp */ yytestcase(yyruleno==62);
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
#line 1412 "lparser.c"
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
