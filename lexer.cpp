#include "lexer"
#include <quex/code_base/analyzer/C-adaptions.h>
QUEX_NAMESPACE_MAIN_OPEN
/* Global */QUEX_NAME(Mode)  QUEX_NAME(MAIN);
/* Global */QUEX_NAME(Mode)  QUEX_NAME(STRING);
#ifndef __QUEX_INDICATOR_DUMPED_TOKEN_ID_DEFINED
    static QUEX_TYPE_TOKEN_ID    QUEX_NAME_TOKEN(DumpedTokenIdObject);
#endif
#define self  (*(QUEX_TYPE_DERIVED_ANALYZER*)me)
#define __self_result_token_id    QUEX_NAME_TOKEN(DumpedTokenIdObject)

void
QUEX_NAME(MAIN_on_entry)(QUEX_TYPE_ANALYZER* me, const QUEX_NAME(Mode)* FromMode) {
    (void)me;
    (void)FromMode;
#   ifdef QUEX_OPTION_RUNTIME_MODE_TRANSITION_CHECK
    QUEX_NAME(MAIN).has_entry_from(FromMode);
#   endif

}

void
QUEX_NAME(MAIN_on_exit)(QUEX_TYPE_ANALYZER* me, const QUEX_NAME(Mode)* ToMode)  {
    (void)me;
    (void)ToMode;
#   ifdef QUEX_OPTION_RUNTIME_MODE_TRANSITION_CHECK
    QUEX_NAME(MAIN).has_exit_to(ToMode);
#   endif

}

#if defined(QUEX_OPTION_INDENTATION_TRIGGER) 
void
QUEX_NAME(MAIN_on_indentation)(QUEX_TYPE_ANALYZER*    me, 
                                        QUEX_TYPE_INDENTATION  Indentation, 
                                        QUEX_TYPE_CHARACTER*   Begin) {
    (void)me;
    (void)Indentation;
    (void)Begin;
    return;
}
#endif

#ifdef QUEX_OPTION_RUNTIME_MODE_TRANSITION_CHECK
bool
QUEX_NAME(MAIN_has_base)(const QUEX_NAME(Mode)* Mode) {
    (void)Mode;
    return false;
}
bool
QUEX_NAME(MAIN_has_entry_from)(const QUEX_NAME(Mode)* Mode) {
    (void)Mode;
    return true; /* default */
}
bool
QUEX_NAME(MAIN_has_exit_to)(const QUEX_NAME(Mode)* Mode) {
    (void)Mode;
    return false;
}
#endif    

void
QUEX_NAME(STRING_on_entry)(QUEX_TYPE_ANALYZER* me, const QUEX_NAME(Mode)* FromMode) {
    (void)me;
    (void)FromMode;
#   ifdef QUEX_OPTION_RUNTIME_MODE_TRANSITION_CHECK
    QUEX_NAME(STRING).has_entry_from(FromMode);
#   endif

}

void
QUEX_NAME(STRING_on_exit)(QUEX_TYPE_ANALYZER* me, const QUEX_NAME(Mode)* ToMode)  {
    (void)me;
    (void)ToMode;
#   ifdef QUEX_OPTION_RUNTIME_MODE_TRANSITION_CHECK
    QUEX_NAME(STRING).has_exit_to(ToMode);
#   endif

}

#if defined(QUEX_OPTION_INDENTATION_TRIGGER) 
void
QUEX_NAME(STRING_on_indentation)(QUEX_TYPE_ANALYZER*    me, 
                                        QUEX_TYPE_INDENTATION  Indentation, 
                                        QUEX_TYPE_CHARACTER*   Begin) {
    (void)me;
    (void)Indentation;
    (void)Begin;
    return;
}
#endif

#ifdef QUEX_OPTION_RUNTIME_MODE_TRANSITION_CHECK
bool
QUEX_NAME(STRING_has_base)(const QUEX_NAME(Mode)* Mode) {
    (void)Mode;
    return false;
}
bool
QUEX_NAME(STRING_has_entry_from)(const QUEX_NAME(Mode)* Mode) {
    (void)Mode;
    return true; /* default */
}
bool
QUEX_NAME(STRING_has_exit_to)(const QUEX_NAME(Mode)* Mode) {
    (void)Mode;
    return false;
}
#endif    
#undef self
#undef __self_result_token_id
QUEX_NAMESPACE_MAIN_CLOSE

/* #include "lexer"*/
QUEX_NAMESPACE_MAIN_OPEN
QUEX_TYPE_CHARACTER  QUEX_LEXEME_NULL_IN_ITS_NAMESPACE = (QUEX_TYPE_CHARACTER)0;
#ifdef      __QUEX_COUNT_VOID
#   undef   __QUEX_COUNT_VOID
#endif
#ifdef      __QUEX_OPTION_COUNTER
#    define __QUEX_COUNT_VOID(ME, BEGIN, END) \
            do {                              \
                QUEX_NAME(MAIN_counter)((ME), (BEGIN), (END));     \
                __quex_debug_counter();       \
            } while(0)
#else
#    define __QUEX_COUNT_VOID(ME, BEGIN, END) /* empty */
#endif
#ifdef __QUEX_OPTION_COUNTER
static void
QUEX_NAME(MAIN_counter)(QUEX_TYPE_ANALYZER* me, QUEX_TYPE_CHARACTER* LexemeBegin, QUEX_TYPE_CHARACTER* LexemeEnd)
{
#   define self (*me)
    QUEX_TYPE_CHARACTER* iterator    = LexemeBegin;
#   if defined(QUEX_OPTION_COLUMN_NUMBER_COUNTING)
    const QUEX_TYPE_CHARACTER* reference_p = LexemeBegin;
#   endif
__QUEX_IF_COUNT_COLUMNS(reference_p = iterator);
    __QUEX_IF_COUNT_SHIFT_VALUES();

    __quex_assert(LexemeBegin <= LexemeEnd);
    for(iterator=LexemeBegin; iterator < LexemeEnd; ) {
        if( (*(iterator)) >= 0xB ) {
                            ++(((iterator)));
            continue;
        } else if( (*(iterator)) == 0xA ) {
            __QUEX_IF_COUNT_LINES_ADD((size_t)1);
        __QUEX_IF_COUNT_COLUMNS_SET((size_t)1);
        __QUEX_IF_COUNT_COLUMNS(reference_p = (iterator) + 1);
                ++(((iterator)));
            continue;
        } else if( (*(iterator)) == 0x9 ) {
                    __QUEX_IF_COUNT_COLUMNS_ADD((size_t)(((iterator) - reference_p)));
        __QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_end &= ~ ((size_t)0x3));
        __QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_end += 4);
        __QUEX_IF_COUNT_COLUMNS(reference_p = (iterator) + 1);
                ++(((iterator)));
            continue;
        } else {
                            ++(((iterator)));
            continue;
        }

    }
    __quex_assert(iterator == LexemeEnd); /* Otherwise, lexeme violates codec character boundaries. */
__QUEX_IF_COUNT_COLUMNS_ADD((size_t)((iterator - reference_p)));
   return;
#  undef self
}
#endif /* __QUEX_OPTION_COUNTER */
#include <quex/code_base/analyzer/member/basic>
#include <quex/code_base/buffer/Buffer>
#ifdef QUEX_OPTION_TOKEN_POLICY_QUEUE
#   include <quex/code_base/token/TokenQueue>
#endif

#ifdef    CONTINUE
#   undef CONTINUE
#endif
#define   CONTINUE goto __REENTRY_PREPARATION; 

#ifdef    RETURN
#   undef RETURN
#endif

#define RETURN    __QUEX_PURE_RETURN;
#include <quex/code_base/temporary_macros_on>

__QUEX_TYPE_ANALYZER_RETURN_VALUE  
QUEX_NAME(MAIN_analyzer_function)(QUEX_TYPE_ANALYZER* me) 
{
    /* NOTE: Different modes correspond to different analyzer functions. The 
     *       analyzer functions are all located inside the main class as static
     *       functions. That means, they are something like 'globals'. They 
     *       receive a pointer to the lexical analyzer, since static members do
     *       not have access to the 'this' pointer.                          */
#   if defined(QUEX_OPTION_TOKEN_POLICY_SINGLE)
    register QUEX_TYPE_TOKEN_ID __self_result_token_id 
           = (QUEX_TYPE_TOKEN_ID)__QUEX_SETTING_TOKEN_ID_UNINITIALIZED;
#   endif
#   ifdef     self
#       undef self
#   endif
#   define self (*((QUEX_TYPE_ANALYZER*)me))
    const QUEX_TYPE_CHARACTER      Skipper1479_Closer[2]          = { 0x2A, 0x2F,  };
    const QUEX_TYPE_CHARACTER      Skipper1479_Opener[2]          = { 0x2F, 0x2A,  };
    const QUEX_TYPE_CHARACTER*     Skipper1479_CloserEnd          = Skipper1479_Closer + (ptrdiff_t)2;
    const QUEX_TYPE_CHARACTER      Skipper1476[1]                 = { 0xA,  };
    void*                          position                       = (void*)0x0;
    const QUEX_TYPE_CHARACTER*     Skipper1479_OpenerEnd          = Skipper1479_Opener + (ptrdiff_t)2;
    const QUEX_TYPE_CHARACTER      Skipper1482[1]                 = { 0xA,  };
    const size_t                   Skipper1482L                   = 1;
    const QUEX_TYPE_CHARACTER*     Skipper1479_Opener_it          = 0x0;
    size_t                         counter                        = 0;
    QUEX_TYPE_CHARACTER_POSITION   reference_p                    = (QUEX_TYPE_CHARACTER_POSITION)0x0;
    QUEX_TYPE_GOTO_LABEL           target_state_index             = QUEX_GOTO_LABEL_VOID;
    QUEX_TYPE_ACCEPTANCE_ID        last_acceptance               /* un-initilized */;
    QUEX_TYPE_GOTO_LABEL           target_state_else_index        = QUEX_GOTO_LABEL_VOID;
    const size_t                   PositionRegisterN              = (size_t)0;
    QUEX_TYPE_CHARACTER*           text_end                       = (QUEX_TYPE_CHARACTER*)0x0;
    QUEX_TYPE_CHARACTER            input                          = (QUEX_TYPE_CHARACTER)(0x00);
    const QUEX_TYPE_CHARACTER*     Skipper1479_Closer_it          = 0x0;
    const size_t                   Skipper1476L                   = 1;
#   ifdef QUEX_OPTION_COLUMN_NUMBER_COUNTING
#   endif /* QUEX_OPTION_COLUMN_NUMBER_COUNTING */
#   ifndef QUEX_OPTION_COMPUTED_GOTOS
#   endif /* QUEX_OPTION_COMPUTED_GOTOS */
#   define MAIN      (QUEX_NAME(MAIN))
#   define STRING    (QUEX_NAME(STRING))

    /* Post context positions do not have to be reset or initialized. If a state
     * is reached which is associated with 'end of post context' it is clear what
     * post context is meant. This results from the ways the state machine is 
     * constructed. Post context position's live cycle:
     *
     * (1)   unitialized (don't care)
     * (1.b) on buffer reload it may, or may not be adapted (don't care)
     * (2)   when a post context begin state is passed, then it is **SET** (now: take care)
     * (2.b) on buffer reload it **is adapted**.
     * (3)   when a terminal state of the post context is reached (which can only be reached
     *       for that particular post context), then the post context position is used
     *       to reset the input position.                                              */
#   if    defined(QUEX_OPTION_AUTOMATIC_ANALYSIS_CONTINUATION_ON_MODE_CHANGE) \
       || defined(QUEX_OPTION_ASSERTS)
    me->DEBUG_analyzer_function_at_entry = me->current_analyzer_function;
#   endif
__REENTRY:
    me->buffer._lexeme_start_p = me->buffer._input_p;
    QUEX_LEXEME_TERMINATING_ZERO_UNDO(&me->buffer);
_2117: /* INIT_STATE_TRANSITION_BLOCK */
    input = *(me->buffer._input_p);
    __quex_debug("Init State\n");
    __quex_debug_state(1984);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1984, 1475);
        case 0x9: goto _2022;
        case 0xA: goto _2014;
        case 0xD: 
        case 0x20: goto _1994;
        case 0x21: goto _2003;
        case 0x22: goto _2018;
        case 0x23: goto _2024;
        case 0x25: goto _1997;
        case 0x27: goto _2002;
        case 0x28: goto _2005;
        case 0x29: goto _2010;
        case 0x2A: goto _1992;
        case 0x2B: goto _2009;
        case 0x2C: goto _1988;
        case 0x2D: goto _1990;
        case 0x2E: goto _2017;
        case 0x2F: goto _2026;
        case 0x30: goto _2118;
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: goto _2119;
        case 0x3B: goto _2015;
        case 0x3C: goto _1987;
        case 0x3D: goto _1985;
        case 0x3E: goto _2008;
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: goto _2006;
        case 0x5B: goto _2016;
        case 0x5D: goto _2020;
        case 0x5E: goto _2028;
        case 0x5F: goto _2006;
        case 0x61: goto _1999;
        case 0x62: goto _2012;
        case 0x63: goto _1995;
        case 0x64: goto _2000;
        case 0x65: goto _1989;
        case 0x66: goto _1996;
        case 0x67: goto _2019;
        case 0x68: goto _2006;
        case 0x69: goto _1991;
        case 0x6A: 
        case 0x6B: goto _2006;
        case 0x6C: goto _1986;
        case 0x6D: goto _2006;
        case 0x6E: goto _2021;
        case 0x6F: goto _2007;
        case 0x70: 
        case 0x71: goto _2006;
        case 0x72: goto _2027;
        case 0x73: goto _2006;
        case 0x74: goto _1993;
        case 0x75: goto _2013;
        case 0x76: goto _2006;
        case 0x77: goto _2011;
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;
        case 0x7B: goto _2023;
        case 0x7C: goto _2025;
        case 0x7D: goto _2004;

    }
    __quex_debug_drop_out(1984);

goto _2121; /* TERMINAL_FAILURE */

_1984:


    ++(me->buffer._input_p);
    goto _2117;


    __quex_assert_no_passage();
_2006: /* (2006 from 2006) (2006 from 2000) (2006 from 1999) (2006 from 2013) (2006 from 2012) (2006 from 2011) (2006 from 2007) (2006 from 1989) (2006 from 1986) (2006 from 1984) (2006 from 1996) (2006 from 1995) (2006 from 1993) (2006 from 1991) (2006 from 2037) (2006 from 2036) (2006 from 2035) (2006 from 2034) (2006 from 2033) (2006 from 2032) (2006 from 2031) (2006 from 2046) (2006 from 2045) (2006 from 2044) (2006 from 2043) (2006 from 2042) (2006 from 2041) (2006 from 2040) (2006 from 2021) (2006 from 2019) (2006 from 2030) (2006 from 2029) (2006 from 2027) (2006 from 2115) (2006 from 2114) (2006 from 2113) (2006 from 2112) (2006 from 2070) (2006 from 2069) (2006 from 2068) (2006 from 2067) (2006 from 2066) (2006 from 2065) (2006 from 2064) (2006 from 2063) (2006 from 2072) (2006 from 2053) (2006 from 2052) (2006 from 2051) (2006 from 2050) (2006 from 2049) (2006 from 2048) (2006 from 2047) (2006 from 2062) (2006 from 2061) (2006 from 2060) (2006 from 2059) (2006 from 2102) (2006 from 2101) (2006 from 2100) (2006 from 2099) (2006 from 2098) (2006 from 2097) (2006 from 2096) (2006 from 2095) (2006 from 2109) (2006 from 2108) (2006 from 2107) (2006 from 2106) (2006 from 2105) (2006 from 2104) (2006 from 2103) (2006 from 2086) (2006 from 2085) (2006 from 2084) (2006 from 2083) (2006 from 2082) (2006 from 2081) (2006 from 2080) (2006 from 2079) (2006 from 2094) (2006 from 2093) (2006 from 2092) (2006 from 2091) (2006 from 2090) (2006 from 2089) (2006 from 2088) (2006 from 2087) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2006);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2006, 2122);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2122:
    __quex_debug_drop_out(2006);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2056: /* (2056 from 2055) (2056 from 2074) (2056 from 2001) (2056 from 2076) (2056 from 1998) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2056);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2056, 2123);
        case 0x2B: 
        case 0x2D: goto _2058;
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: goto _2057;

    }
_2123:
    __quex_debug_drop_out(2056);
switch( last_acceptance ) {
    case 1449: me->buffer._input_p -= 1;  goto TERMINAL_1449;
    case 1446: me->buffer._input_p -= 1;  goto TERMINAL_1446;
    case 1447: me->buffer._input_p -= 1;  goto TERMINAL_1447;

}

    __quex_assert_no_passage();
_2078: /* (2078 from 2078) (2078 from 2077) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2078);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2078, 2124);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: goto _2078;

    }
_2124:
    __quex_debug_drop_out(2078);
goto TERMINAL_1448;

    __quex_assert_no_passage();
_2075: /* (2075 from 2076) (2075 from 1998) (2075 from 2001) (2075 from 2074) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2075);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2075, 2125);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: goto _2126;

    }
_2125:
    __quex_debug_drop_out(2075);
switch( last_acceptance ) {
    case 1449: me->buffer._input_p -= 1;  goto TERMINAL_1449;
    case 1446: me->buffer._input_p -= 1;  goto TERMINAL_1446;
    case 1447: me->buffer._input_p -= 1;  goto TERMINAL_1447;

}

    __quex_assert_no_passage();
_2126: /* (2055 from 2055) (2055 from 2017) (2055 from 2075) */
    { last_acceptance = 1449; __quex_debug("last_acceptance = 1449\n"); }

_2055:

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2055);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2055, 2127);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: goto _2126;
        case 0x45: 
        case 0x65: goto _2056;

    }
_2127:
    __quex_debug_drop_out(2055);
goto TERMINAL_1449;

    __quex_assert_no_passage();
_2057: /* (2057 from 2057) (2057 from 2058) (2057 from 2056) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2057);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2057, 2128);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: goto _2057;

    }
_2128:
    __quex_debug_drop_out(2057);
goto TERMINAL_1449;

    __quex_assert_no_passage();
_2129: /* (2074 from 2074) (2074 from 2001) (2074 from 2076) */
    { last_acceptance = 1449; __quex_debug("last_acceptance = 1449\n"); }

_2074:

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2074);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2074, 2130);
        case 0x2E: goto _2075;
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: goto _2129;
        case 0x45: 
        case 0x65: goto _2056;

    }
_2130:
    __quex_debug_drop_out(2074);
goto TERMINAL_1449;

    __quex_assert_no_passage();
_2058: /* (2058 from 2056) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2058);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2058, 2131);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: goto _2057;

    }
_2131:
    __quex_debug_drop_out(2058);
switch( last_acceptance ) {
    case 1449: me->buffer._input_p -= 2;  goto TERMINAL_1449;
    case 1446: me->buffer._input_p -= 2;  goto TERMINAL_1446;
    case 1447: me->buffer._input_p -= 2;  goto TERMINAL_1447;

}

    __quex_assert_no_passage();
_2132: /* (2076 from 2076) (2076 from 2001) */
    { last_acceptance = 1446; __quex_debug("last_acceptance = 1446\n"); }

_2076:

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2076);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2076, 2133);
        case 0x2E: goto _2075;
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: goto _2132;
        case 0x38: 
        case 0x39: goto _2129;
        case 0x45: 
        case 0x65: goto _2056;

    }
_2133:
    __quex_debug_drop_out(2076);
goto TERMINAL_1446;

    __quex_assert_no_passage();
_2077: /* (2077 from 2001) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2077);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2077, 2134);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: goto _2078;

    }
_2134:
    __quex_debug_drop_out(2077);
me->buffer._input_p -= 1; 
goto TERMINAL_1446;

    __quex_assert_no_passage();
_2048: /* (2048 from 2040) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2048);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2048, 2135);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2135:
    __quex_debug_drop_out(2048);
goto TERMINAL_1416;

    __quex_assert_no_passage();
_2049: /* (2049 from 2019) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2049);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2049, 2136);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: goto _2006;
        case 0x6F: goto _2050;
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2136:
    __quex_debug_drop_out(2049);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2050: /* (2050 from 2049) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2050);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2050, 2137);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: goto _2006;
        case 0x62: goto _2051;
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2137:
    __quex_debug_drop_out(2050);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2051: /* (2051 from 2050) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2051);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2051, 2138);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: goto _2006;
        case 0x61: goto _2052;
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2138:
    __quex_debug_drop_out(2051);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2052: /* (2052 from 2051) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2052);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2052, 2139);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: goto _2006;
        case 0x6C: goto _2053;
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2139:
    __quex_debug_drop_out(2052);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2053: /* (2053 from 2052) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2053);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2053, 2140);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2140:
    __quex_debug_drop_out(2053);
goto TERMINAL_1415;

    __quex_assert_no_passage();
_2054: /* (2054 from 2017) */

    ++(me->buffer._input_p);
    __quex_debug_state(2054);
    __quex_debug_drop_out(2054);
goto TERMINAL_1429;

    __quex_assert_no_passage();
_2059: /* (2059 from 2013) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2059);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2059, 2142);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: goto _2006;
        case 0x74: goto _2060;
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2142:
    __quex_debug_drop_out(2059);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2060: /* (2060 from 2059) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2060);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2060, 2143);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: goto _2006;
        case 0x69: goto _2061;
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2143:
    __quex_debug_drop_out(2060);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2061: /* (2061 from 2060) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2061);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2061, 2144);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: goto _2006;
        case 0x6C: goto _2062;
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2144:
    __quex_debug_drop_out(2061);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2062: /* (2062 from 2061) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2062);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2062, 2145);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2145:
    __quex_debug_drop_out(2062);
goto TERMINAL_1410;

    __quex_assert_no_passage();
_2063: /* (2063 from 2012) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2063);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2063, 2146);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: goto _2006;
        case 0x65: goto _2064;
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2146:
    __quex_debug_drop_out(2063);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2064: /* (2064 from 2063) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2064);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2064, 2147);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: goto _2006;
        case 0x61: goto _2065;
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2147:
    __quex_debug_drop_out(2064);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2065: /* (2065 from 2064) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2065);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2065, 2148);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: goto _2006;
        case 0x6B: goto _2066;
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2148:
    __quex_debug_drop_out(2065);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2066: /* (2066 from 2065) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2066);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2066, 2149);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2149:
    __quex_debug_drop_out(2066);
goto TERMINAL_1412;

    __quex_assert_no_passage();
_2067: /* (2067 from 2011) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2067);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2067, 2150);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: goto _2006;
        case 0x69: goto _2068;
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2150:
    __quex_debug_drop_out(2067);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2068: /* (2068 from 2067) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2068);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2068, 2151);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: goto _2006;
        case 0x6C: goto _2069;
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2151:
    __quex_debug_drop_out(2068);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2069: /* (2069 from 2068) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2069);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2069, 2152);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: goto _2006;
        case 0x65: goto _2070;
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2152:
    __quex_debug_drop_out(2069);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2070: /* (2070 from 2069) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2070);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2070, 2153);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2153:
    __quex_debug_drop_out(2070);
goto TERMINAL_1406;

    __quex_assert_no_passage();
_2071: /* (2071 from 2008) */

    ++(me->buffer._input_p);
    __quex_debug_state(2071);
    __quex_debug_drop_out(2071);
goto TERMINAL_1425;

    __quex_assert_no_passage();
_2072: /* (2072 from 2007) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2072);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2072, 2155);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2155:
    __quex_debug_drop_out(2072);
goto TERMINAL_1419;

    __quex_assert_no_passage();
_2073: /* (2073 from 2003) */

    ++(me->buffer._input_p);
    __quex_debug_state(2073);
    __quex_debug_drop_out(2073);
goto TERMINAL_1426;

    __quex_assert_no_passage();
_2079: /* (2079 from 2000) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2079);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2079, 2157);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2157:
    __quex_debug_drop_out(2079);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_2080: /* (2080 from 2000) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2080);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2080, 2158);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: goto _2006;
        case 0x66: goto _2081;
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2158:
    __quex_debug_drop_out(2080);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2081: /* (2081 from 2080) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2081);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2081, 2159);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2159:
    __quex_debug_drop_out(2081);
goto TERMINAL_1398;

    __quex_assert_no_passage();
_2082: /* (2082 from 1999) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2082);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2082, 2160);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: goto _2006;
        case 0x64: goto _2083;
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2160:
    __quex_debug_drop_out(2082);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2083: /* (2083 from 2082) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2083);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2083, 2161);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2161:
    __quex_debug_drop_out(2083);
goto TERMINAL_1420;

    __quex_assert_no_passage();
_2084: /* (2084 from 1996) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2084);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2084, 2162);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: goto _2006;
        case 0x72: goto _2089;
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2162:
    __quex_debug_drop_out(2084);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2085: /* (2085 from 1996) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2085);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2085, 2163);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: goto _2006;
        case 0x6C: goto _2086;
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2163:
    __quex_debug_drop_out(2085);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2086: /* (2086 from 2085) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2086);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2086, 2164);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: goto _2006;
        case 0x73: goto _2087;
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2164:
    __quex_debug_drop_out(2086);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2087: /* (2087 from 2086) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2087);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2087, 2165);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: goto _2006;
        case 0x65: goto _2088;
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2165:
    __quex_debug_drop_out(2087);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2088: /* (2088 from 2087) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2088);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2088, 2166);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2166:
    __quex_debug_drop_out(2088);
goto TERMINAL_1418;

    __quex_assert_no_passage();
_2089: /* (2089 from 2084) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2089);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2089, 2167);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2167:
    __quex_debug_drop_out(2089);
goto TERMINAL_1407;

    __quex_assert_no_passage();
_2090: /* (2090 from 1995) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2090);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2090, 2168);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: goto _2006;
        case 0x61: goto _2091;
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2168:
    __quex_debug_drop_out(2090);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2091: /* (2091 from 2090) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2091);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2091, 2169);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: goto _2006;
        case 0x73: goto _2092;
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2169:
    __quex_debug_drop_out(2091);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2092: /* (2092 from 2091) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2092);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2092, 2170);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: goto _2006;
        case 0x73: goto _2093;
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2170:
    __quex_debug_drop_out(2092);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2093: /* (2093 from 2092) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2093);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2093, 2171);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2171:
    __quex_debug_drop_out(2093);
goto TERMINAL_1399;

    __quex_assert_no_passage();
_2094: /* (2094 from 1993) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2094);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2094, 2172);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: goto _2006;
        case 0x65: goto _2098;
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2172:
    __quex_debug_drop_out(2094);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2095: /* (2095 from 1993) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2095);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2095, 2173);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: goto _2006;
        case 0x75: goto _2096;
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2173:
    __quex_debug_drop_out(2095);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2096: /* (2096 from 2095) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2096);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2096, 2174);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: goto _2006;
        case 0x65: goto _2097;
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2174:
    __quex_debug_drop_out(2096);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2097: /* (2097 from 2096) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2097);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2097, 2175);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2175:
    __quex_debug_drop_out(2097);
goto TERMINAL_1417;

    __quex_assert_no_passage();
_2098: /* (2098 from 2094) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2098);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2098, 2176);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: goto _2006;
        case 0x6E: goto _2099;
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2176:
    __quex_debug_drop_out(2098);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2099: /* (2099 from 2098) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2099);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2099, 2177);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2177:
    __quex_debug_drop_out(2099);
goto TERMINAL_1403;

    __quex_assert_no_passage();
_2100: /* (2100 from 1991) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2100);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2100, 2178);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2178:
    __quex_debug_drop_out(2100);
goto TERMINAL_1402;

    __quex_assert_no_passage();
_2101: /* (2101 from 1991) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2101);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2101, 2179);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: goto _2006;
        case 0x66: goto _2102;
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2179:
    __quex_debug_drop_out(2101);
goto TERMINAL_1408;

    __quex_assert_no_passage();
_2102: /* (2102 from 2101) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2102);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2102, 2180);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2180:
    __quex_debug_drop_out(2102);
goto TERMINAL_1451;

    __quex_assert_no_passage();
_2103: /* (2103 from 1989) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2103);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2103, 2181);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: goto _2006;
        case 0x69: goto _2106;
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: goto _2006;
        case 0x73: goto _2107;
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2181:
    __quex_debug_drop_out(2103);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2104: /* (2104 from 1989) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2104);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2104, 2182);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: goto _2006;
        case 0x64: goto _2105;
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2182:
    __quex_debug_drop_out(2104);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2105: /* (2105 from 2104) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2105);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2105, 2183);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2183:
    __quex_debug_drop_out(2105);
goto TERMINAL_1401;

    __quex_assert_no_passage();
_2106: /* (2106 from 2103) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2106);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2106, 2184);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: goto _2006;
        case 0x66: goto _2109;
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2184:
    __quex_debug_drop_out(2106);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2107: /* (2107 from 2103) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2107);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2107, 2185);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: goto _2006;
        case 0x65: goto _2108;
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2185:
    __quex_debug_drop_out(2107);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2108: /* (2108 from 2107) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2108);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2108, 2186);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2186:
    __quex_debug_drop_out(2108);
goto TERMINAL_1404;

    __quex_assert_no_passage();
_2109: /* (2109 from 2106) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2109);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2109, 2187);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2187:
    __quex_debug_drop_out(2109);
goto TERMINAL_1405;

    __quex_assert_no_passage();
_2110: /* (2110 from 1987) */

    ++(me->buffer._input_p);
    __quex_debug_state(2110);
    __quex_debug_drop_out(2110);
goto TERMINAL_1427;

    __quex_assert_no_passage();
_2111: /* (2111 from 1987) */

    ++(me->buffer._input_p);
    __quex_debug_state(2111);
    __quex_debug_drop_out(2111);
goto TERMINAL_1424;

    __quex_assert_no_passage();
_2112: /* (2112 from 1986) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2112);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2112, 2190);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: goto _2006;
        case 0x63: goto _2113;
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2190:
    __quex_debug_drop_out(2112);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2113: /* (2113 from 2112) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2113);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2113, 2191);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: goto _2006;
        case 0x61: goto _2114;
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2191:
    __quex_debug_drop_out(2113);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2114: /* (2114 from 2113) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2114);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2114, 2192);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: goto _2006;
        case 0x6C: goto _2115;
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2192:
    __quex_debug_drop_out(2114);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2115: /* (2115 from 2114) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2115);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2115, 2193);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2193:
    __quex_debug_drop_out(2115);
goto TERMINAL_1414;

    __quex_assert_no_passage();
_2116: /* (2116 from 1985) */

    ++(me->buffer._input_p);
    __quex_debug_state(2116);
    __quex_debug_drop_out(2116);
goto TERMINAL_1428;

    __quex_assert_no_passage();
_2119: /* (1998 from 1998) (1998 from 1984) */
    { last_acceptance = 1447; __quex_debug("last_acceptance = 1447\n"); }

_1998:

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1998);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1998, 2195);
        case 0x2E: goto _2075;
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: goto _2119;
        case 0x45: 
        case 0x65: goto _2056;

    }
_2195:
    __quex_debug_drop_out(1998);
goto TERMINAL_1447;

    __quex_assert_no_passage();
_2029: /* (2029 from 2027) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2029);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2029, 2196);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: goto _2006;
        case 0x70: goto _2030;
        case 0x71: 
        case 0x72: 
        case 0x73: goto _2006;
        case 0x74: goto _2031;
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2196:
    __quex_debug_drop_out(2029);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2030: /* (2030 from 2029) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2030);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2030, 2197);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: goto _2006;
        case 0x65: goto _2035;
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2197:
    __quex_debug_drop_out(2030);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2031: /* (2031 from 2029) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2031);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2031, 2198);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: goto _2006;
        case 0x75: goto _2032;
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2198:
    __quex_debug_drop_out(2031);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2032: /* (2032 from 2031) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2032);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2032, 2199);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: goto _2006;
        case 0x72: goto _2033;
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2199:
    __quex_debug_drop_out(2032);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2033: /* (2033 from 2032) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2033);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2033, 2200);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: goto _2006;
        case 0x6E: goto _2034;
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2200:
    __quex_debug_drop_out(2033);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2034: /* (2034 from 2033) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2034);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2034, 2201);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2201:
    __quex_debug_drop_out(2034);
goto TERMINAL_1411;

    __quex_assert_no_passage();
_2035: /* (2035 from 2030) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2035);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2035, 2202);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: goto _2006;
        case 0x61: goto _2036;
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2202:
    __quex_debug_drop_out(2035);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2036: /* (2036 from 2035) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2036);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2036, 2203);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: goto _2006;
        case 0x74: goto _2037;
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2203:
    __quex_debug_drop_out(2036);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2037: /* (2037 from 2036) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2037);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2037, 2204);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2204:
    __quex_debug_drop_out(2037);
goto TERMINAL_1409;

    __quex_assert_no_passage();
_2038: /* (2038 from 2026) */

    ++(me->buffer._input_p);
    __quex_debug_state(2038);
    __quex_debug_drop_out(2038);
goto TERMINAL_1392;

    __quex_assert_no_passage();
_2039: /* (2039 from 2026) */

    ++(me->buffer._input_p);
    __quex_debug_state(2039);
    __quex_debug_drop_out(2039);
goto TERMINAL_1393;

    __quex_assert_no_passage();
_2040: /* (2040 from 2021) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2040);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2040, 2207);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: goto _2006;
        case 0x6C: goto _2048;
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2207:
    __quex_debug_drop_out(2040);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2041: /* (2041 from 2021) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2041);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2041, 2208);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: goto _2006;
        case 0x6E: goto _2047;
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2208:
    __quex_debug_drop_out(2041);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2042: /* (2042 from 2021) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2042);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2042, 2209);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: goto _2006;
        case 0x74: goto _2046;
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2209:
    __quex_debug_drop_out(2042);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2043: /* (2043 from 2021) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2043);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2043, 2210);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: goto _2006;
        case 0x78: goto _2044;
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2210:
    __quex_debug_drop_out(2043);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2044: /* (2044 from 2043) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2044);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2044, 2211);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: goto _2006;
        case 0x74: goto _2045;
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2211:
    __quex_debug_drop_out(2044);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2045: /* (2045 from 2044) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2045);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2045, 2212);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2212:
    __quex_debug_drop_out(2045);
goto TERMINAL_1413;

    __quex_assert_no_passage();
_2046: /* (2046 from 2042) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2046);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2046, 2213);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2213:
    __quex_debug_drop_out(2046);
goto TERMINAL_1421;

    __quex_assert_no_passage();
_2047: /* (2047 from 2041) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2047);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2047, 2214);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2214:
    __quex_debug_drop_out(2047);
goto TERMINAL_1450;

    __quex_assert_no_passage();
_1985: /* (1985 from 1984) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1985);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1985, 2215);
        case 0x3D: goto _2116;

    }
_2215:
    __quex_debug_drop_out(1985);
goto TERMINAL_1437;

    __quex_assert_no_passage();
_1986: /* (1986 from 1984) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1986);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1986, 2216);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: goto _2006;
        case 0x6F: goto _2112;
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2216:
    __quex_debug_drop_out(1986);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_1987: /* (1987 from 1984) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1987);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1987, 2217);
        case 0x3D: goto _2111;
        case 0x3E: goto _2110;

    }
_2217:
    __quex_debug_drop_out(1987);
goto TERMINAL_1422;

    __quex_assert_no_passage();
_1988: /* (1988 from 1984) */

    ++(me->buffer._input_p);
    __quex_debug_state(1988);
    __quex_debug_drop_out(1988);
goto TERMINAL_1438;

    __quex_assert_no_passage();
_1989: /* (1989 from 1984) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1989);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1989, 2219);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: goto _2006;
        case 0x6C: goto _2103;
        case 0x6D: goto _2006;
        case 0x6E: goto _2104;
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2219:
    __quex_debug_drop_out(1989);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_1990: /* (1990 from 1984) */

    ++(me->buffer._input_p);
    __quex_debug_state(1990);
    __quex_debug_drop_out(1990);
goto TERMINAL_1431;

    __quex_assert_no_passage();
_1991: /* (1991 from 1984) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1991);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1991, 2221);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: goto _2006;
        case 0x66: goto _2100;
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: goto _2006;
        case 0x6E: goto _2101;
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2221:
    __quex_debug_drop_out(1991);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_1992: /* (1992 from 1984) */

    ++(me->buffer._input_p);
    __quex_debug_state(1992);
    __quex_debug_drop_out(1992);
goto TERMINAL_1432;

    __quex_assert_no_passage();
_1993: /* (1993 from 1984) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1993);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1993, 2223);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: goto _2006;
        case 0x68: goto _2094;
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: goto _2006;
        case 0x72: goto _2095;
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2223:
    __quex_debug_drop_out(1993);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_1994: /* (1994 from 1984) */

    ++(me->buffer._input_p);
    __quex_debug_state(1994);
    __quex_debug_drop_out(1994);
goto TERMINAL_1389;

    __quex_assert_no_passage();
_1995: /* (1995 from 1984) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1995);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1995, 2225);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: goto _2006;
        case 0x6C: goto _2090;
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2225:
    __quex_debug_drop_out(1995);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_1996: /* (1996 from 1984) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1996);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1996, 2226);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: goto _2006;
        case 0x61: goto _2085;
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: goto _2006;
        case 0x6F: goto _2084;
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2226:
    __quex_debug_drop_out(1996);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_1997: /* (1997 from 1984) */

    ++(me->buffer._input_p);
    __quex_debug_state(1997);
    __quex_debug_drop_out(1997);
goto TERMINAL_1434;

    __quex_assert_no_passage();
_1999: /* (1999 from 1984) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1999);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1999, 2228);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: goto _2006;
        case 0x6E: goto _2082;
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2228:
    __quex_debug_drop_out(1999);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2000: /* (2000 from 1984) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2000);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2000, 2229);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: goto _2006;
        case 0x65: goto _2080;
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: goto _2006;
        case 0x6F: goto _2079;
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2229:
    __quex_debug_drop_out(2000);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2118: /* (2001 from 1984) */
    { last_acceptance = 1446; __quex_debug("last_acceptance = 1446\n"); }

_2001:

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2001);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2001, 2230);
        case 0x2E: goto _2075;
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: goto _2132;
        case 0x38: 
        case 0x39: goto _2129;
        case 0x45: goto _2056;
        case 0x58: goto _2077;
        case 0x65: goto _2056;
        case 0x78: goto _2077;

    }
_2230:
    __quex_debug_drop_out(2001);
goto TERMINAL_1446;

    __quex_assert_no_passage();
_2002: /* (2002 from 1984) */

    ++(me->buffer._input_p);
    __quex_debug_state(2002);
    __quex_debug_drop_out(2002);
goto TERMINAL_1397;

    __quex_assert_no_passage();
_2003: /* (2003 from 1984) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2003);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2003, 2232);
        case 0x3D: goto _2073;

    }
_2232:
    __quex_debug_drop_out(2003);

goto _2121; /* TERMINAL_FAILURE */

    __quex_assert_no_passage();
_2004: /* (2004 from 1984) */

    ++(me->buffer._input_p);
    __quex_debug_state(2004);
    __quex_debug_drop_out(2004);
goto TERMINAL_1443;

    __quex_assert_no_passage();
_2005: /* (2005 from 1984) */

    ++(me->buffer._input_p);
    __quex_debug_state(2005);
    __quex_debug_drop_out(2005);
goto TERMINAL_1444;

    __quex_assert_no_passage();
_2007: /* (2007 from 1984) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2007);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2007, 2235);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: goto _2006;
        case 0x72: goto _2072;
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2235:
    __quex_debug_drop_out(2007);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2008: /* (2008 from 1984) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2008);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2008, 2236);
        case 0x3D: goto _2071;

    }
_2236:
    __quex_debug_drop_out(2008);
goto TERMINAL_1423;

    __quex_assert_no_passage();
_2009: /* (2009 from 1984) */

    ++(me->buffer._input_p);
    __quex_debug_state(2009);
    __quex_debug_drop_out(2009);
goto TERMINAL_1430;

    __quex_assert_no_passage();
_2010: /* (2010 from 1984) */

    ++(me->buffer._input_p);
    __quex_debug_state(2010);
    __quex_debug_drop_out(2010);
goto TERMINAL_1445;

    __quex_assert_no_passage();
_2011: /* (2011 from 1984) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2011);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2011, 2239);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: goto _2006;
        case 0x68: goto _2067;
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2239:
    __quex_debug_drop_out(2011);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2012: /* (2012 from 1984) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2012);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2012, 2240);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: goto _2006;
        case 0x72: goto _2063;
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2240:
    __quex_debug_drop_out(2012);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2013: /* (2013 from 1984) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2013);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2013, 2241);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: goto _2006;
        case 0x6E: goto _2059;
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2241:
    __quex_debug_drop_out(2013);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2014: /* (2014 from 1984) */

    ++(me->buffer._input_p);
    __quex_debug_state(2014);
    __quex_debug_drop_out(2014);
goto TERMINAL_1394;

    __quex_assert_no_passage();
_2015: /* (2015 from 1984) */

    ++(me->buffer._input_p);
    __quex_debug_state(2015);
    __quex_debug_drop_out(2015);
goto TERMINAL_1395;

    __quex_assert_no_passage();
_2016: /* (2016 from 1984) */

    ++(me->buffer._input_p);
    __quex_debug_state(2016);
    __quex_debug_drop_out(2016);
goto TERMINAL_1440;

    __quex_assert_no_passage();
_2017: /* (2017 from 1984) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2017);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2017, 2245);
        case 0x2E: goto _2054;
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: goto _2126;

    }
_2245:
    __quex_debug_drop_out(2017);
goto TERMINAL_1439;

    __quex_assert_no_passage();
_2018: /* (2018 from 1984) */

    ++(me->buffer._input_p);
    __quex_debug_state(2018);
    __quex_debug_drop_out(2018);
goto TERMINAL_1396;

    __quex_assert_no_passage();
_2019: /* (2019 from 1984) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2019);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2019, 2247);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: goto _2006;
        case 0x6C: goto _2049;
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2247:
    __quex_debug_drop_out(2019);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2020: /* (2020 from 1984) */

    ++(me->buffer._input_p);
    __quex_debug_state(2020);
    __quex_debug_drop_out(2020);
goto TERMINAL_1441;

    __quex_assert_no_passage();
_2021: /* (2021 from 1984) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2021);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2021, 2249);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: goto _2006;
        case 0x61: goto _2041;
        case 0x62: 
        case 0x63: 
        case 0x64: goto _2006;
        case 0x65: goto _2043;
        case 0x66: 
        case 0x67: 
        case 0x68: goto _2006;
        case 0x69: goto _2040;
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: goto _2006;
        case 0x6F: goto _2042;
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2249:
    __quex_debug_drop_out(2021);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2022: /* (2022 from 1984) */

    ++(me->buffer._input_p);
    __quex_debug_state(2022);
    __quex_debug_drop_out(2022);
goto TERMINAL_1390;

    __quex_assert_no_passage();
_2023: /* (2023 from 1984) */

    ++(me->buffer._input_p);
    __quex_debug_state(2023);
    __quex_debug_drop_out(2023);
goto TERMINAL_1442;

    __quex_assert_no_passage();
_2024: /* (2024 from 1984) */

    ++(me->buffer._input_p);
    __quex_debug_state(2024);
    __quex_debug_drop_out(2024);
goto TERMINAL_1391;

    __quex_assert_no_passage();
_2025: /* (2025 from 1984) */

    ++(me->buffer._input_p);
    __quex_debug_state(2025);
    __quex_debug_drop_out(2025);
goto TERMINAL_1435;

    __quex_assert_no_passage();
_2026: /* (2026 from 1984) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2026);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2026, 2254);
        case 0x2A: goto _2038;
        case 0x2F: goto _2039;

    }
_2254:
    __quex_debug_drop_out(2026);
goto TERMINAL_1433;

    __quex_assert_no_passage();
_2027: /* (2027 from 1984) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2027);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2027, 2255);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x47: 
        case 0x48: 
        case 0x49: 
        case 0x4A: 
        case 0x4B: 
        case 0x4C: 
        case 0x4D: 
        case 0x4E: 
        case 0x4F: 
        case 0x50: 
        case 0x51: 
        case 0x52: 
        case 0x53: 
        case 0x54: 
        case 0x55: 
        case 0x56: 
        case 0x57: 
        case 0x58: 
        case 0x59: 
        case 0x5A: 
        case 0x5F: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: goto _2006;
        case 0x65: goto _2029;
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: 
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2006;

    }
_2255:
    __quex_debug_drop_out(2027);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2028: /* (2028 from 1984) */

    ++(me->buffer._input_p);
    __quex_debug_state(2028);
    __quex_debug_drop_out(2028);
goto TERMINAL_1436;
    /* (*) Terminal states _______________________________________________________
     *
     * States that implement actions of the 'winner patterns.                     */

    /* Lexeme setup: 
     *
     * There is a temporary zero stored at the end of each lexeme, if the action 
     * references to the 'Lexeme'. 'LexemeNull' provides a reference to an empty
     * zero terminated string.                                                    */
#if defined(QUEX_OPTION_ASSERTS)
#   define Lexeme       QUEX_NAME(access_Lexeme)((const char*)__FILE__, (size_t)__LINE__, &me->buffer)
#   define LexemeBegin  QUEX_NAME(access_LexemeBegin)((const char*)__FILE__, (size_t)__LINE__, &me->buffer)
#   define LexemeL      QUEX_NAME(access_LexemeL)((const char*)__FILE__, (size_t)__LINE__, &me->buffer)
#   define LexemeEnd    QUEX_NAME(access_LexemeEnd)((const char*)__FILE__, (size_t)__LINE__, &me->buffer)
#else
#   define Lexeme       (me->buffer._lexeme_start_p)
#   define LexemeBegin  Lexeme
#   define LexemeL      ((size_t)(me->buffer._input_p - me->buffer._lexeme_start_p))
#   define LexemeEnd    me->buffer._input_p
#endif

#define LexemeNull      (&QUEX_LEXEME_NULL)

TERMINAL_1389:
    __quex_debug("* terminal 1389:   <skip: ... (check also base modes)>\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 53 "lexer.qx"
    goto __SKIP;
    
#   line 7754 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1390:
    __quex_debug("* terminal 1390:   <skip>\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_end &= ~ ((size_t)0x3));
__QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_end += 4);

    {
__SKIP:
    /* Character Set Skipper: ''\t', '\r', ' '' */
    QUEX_BUFFER_ASSERT_CONSISTENCY(&me->buffer);
__QUEX_IF_COUNT_COLUMNS(reference_p = me->buffer._input_p);
    while( 1 + 1 == 2 ) {
_1472:
        if( (*me->buffer._input_p) < 0xD ) {
            switch( (*me->buffer._input_p) ) {
                case 0x0: QUEX_GOTO_RELOAD(_1474, 1472, 1475);
                case 0x1:
                case 0x2:
                case 0x3:
                case 0x4:
                case 0x5:
                case 0x6:
                case 0x7:
                case 0x8: __QUEX_IF_COUNT_COLUMNS_ADD((size_t)(((me->buffer._input_p) - reference_p)));
                goto __REENTRY;
                case 0x9:             __QUEX_IF_COUNT_COLUMNS_ADD((size_t)(((me->buffer._input_p) - reference_p)));
            __QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_end &= ~ ((size_t)0x3));
            __QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_end += 4);
            __QUEX_IF_COUNT_COLUMNS(reference_p = (me->buffer._input_p) + 1);
                    ++((me->buffer._input_p));
                continue;
                case 0xA:
                case 0xB:
                case 0xC: __QUEX_IF_COUNT_COLUMNS_ADD((size_t)(((me->buffer._input_p) - reference_p)));
                goto __REENTRY;

            }
        } else {
            if( (*me->buffer._input_p) == 0xD ) {
                        ++((me->buffer._input_p));
                continue;
            } else if( (*me->buffer._input_p) < 0x20 ) {
                __QUEX_IF_COUNT_COLUMNS_ADD((size_t)(((me->buffer._input_p) - reference_p)));
                goto __REENTRY;
            } else if( (*me->buffer._input_p) == 0x20 ) {
                        ++((me->buffer._input_p));
                continue;
            } else {
                __QUEX_IF_COUNT_COLUMNS_ADD((size_t)(((me->buffer._input_p) - reference_p)));
                goto __REENTRY;
            }
        }

    __quex_assert_no_passage();
_1474:

    __quex_debug1("__RELOAD_FORWARD");
    __quex_assert(*((me->buffer._input_p)) == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( me->buffer._memory._end_of_file_p == 0x0 ) {
__QUEX_IF_COUNT_COLUMNS_ADD((size_t)(((me->buffer._input_p) - reference_p)));
me->buffer._lexeme_start_p = (me->buffer._input_p);

        __quex_debug_reload_before(); /* Leave macro here to report source position. */
        QUEX_NAME(buffer_reload_forward)(&me->buffer, (QUEX_TYPE_CHARACTER_POSITION*)position, PositionRegisterN);
        ++((me->buffer._input_p));
__QUEX_IF_COUNT_COLUMNS(reference_p = (me->buffer._input_p));

        __quex_debug_reload_after();
        QUEX_GOTO_STATE(target_state_index);
    }
    __quex_debug("reload impossible\n");
    QUEX_GOTO_STATE(target_state_else_index);
    }

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1391:
    __quex_debug("* terminal 1391:   \"#\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
        /*                          Delimiter: '\n',  */
    
        text_end = QUEX_NAME(Buffer_text_end)(&me->buffer);
    
    
    _1477:
    
        QUEX_BUFFER_ASSERT_CONSISTENCY(&me->buffer);
        __quex_assert(QUEX_NAME(Buffer_content_size)(&me->buffer) >= Skipper1476L );
    
        /* NOTE: If _input_p == end of buffer, then it will drop out immediately out of the
            *       loop below and drop into the buffer reload procedure.                      */
    
        /* Loop eating characters: Break-out as soon as the First Character of the Delimiter
            * (FCD) is reached. Thus, the FCD plays also the role of the Buffer Limit Code. There
            * are two reasons for break-out:
            *    (1) we reached a limit (end-of-file or buffer-limit)
            *    (2) there was really the FCD in the character stream
            * This must be distinguished after the loop was exited. But, during the 'swallowing' we
            * are very fast, because we do not have to check for two different characters.        */
        *text_end = Skipper1476[0]; /* Overwrite BufferLimitCode (BLC).  */
    _1476_LOOP:
                input = *(me->buffer._input_p);
    
                if( input == Skipper1476[0] ) {
    
                        goto _1476_LOOP_EXIT;
                }
    
        ++(me->buffer._input_p); /* Now, BLC cannot occur. See above. */
        goto _1476_LOOP;
    _1476_LOOP_EXIT:
    
        *text_end = QUEX_SETTING_BUFFER_LIMIT_CODE; /* Reset BLC. */
    
        /* Case (1) and (2) from above can be distinguished easily:
            *
            *   (1) Distance to text end == 0:
            *         End-of-File or Buffer-Limit.
            *         => goto to drop-out handling
            *
            *   (2) Else:
            *         First character of delimit reached.
            *         => For the verification of the tail of the delimiter it is
            *            essential that it is loaded completely into the buffer.
            *            For this, it must be required:
            *
            *                Distance to text end >= Delimiter length
            *
            *                _input_p    end
            *                    |        |           end - _input_p >= 3
            *                [ ][R][E][M][#]
            *
            *         The case of reload should be seldom and is costy anyway.
            *         Thus let's say, that in this case we simply enter the drop
            *         out and start the search for the delimiter all over again.
            *
            *         (2.1) Distance to text end < Delimiter length
            *                => goto to drop-out handling
            *         (2.2) Start detection of tail of delimiter
            *
            */
        if( QUEX_NAME(Buffer_distance_input_to_text_end)(&me->buffer) < (ptrdiff_t)Skipper1476L ) {
                /* (2.1) Reload required. */
                goto _1478;
        }
    
        /* (2.2) Test the remaining delimiter, but note, that the check must restart at '_input_p + 1'
            *       if any later check fails. */
        ++(me->buffer._input_p);
        /* Example: Delimiter = '*', '/'; if we get ...[*][*][/]... then the the first "*" causes
            *          a drop out out of the 'swallowing loop' and the second "*" will mismatch
            *          the required "/". But, then the second "*" must be presented to the
            *          swallowing loop and the letter after it completes the 'match'.
            * (The whole discussion, of course, is superflous if the range delimiter has length 1.)  */
    
        {
                /* NOTE: The initial state does not increment the input_p. When it detects that
                    * it is located on a buffer border, it automatically triggers a reload. No
                    * need here to reload the buffer. */
                __QUEX_IF_COUNT_COLUMNS_SET((size_t)1);
                __QUEX_IF_COUNT_LINES_ADD((size_t)1);
    
                /* No need for re-entry preparation. Acceptance flags and modes are untouched after skipping. */
                goto __REENTRY; /* End of range reached. */
        }
    
    _1478:
        QUEX_BUFFER_ASSERT_CONSISTENCY_LIGHT(&me->buffer);
        /* -- When loading new content it is checked that the beginning of the lexeme
            *    is not 'shifted' out of the buffer. In the case of skipping, we do not care about
            *    the lexeme at all, so do not restrict the load procedure and set the lexeme start
            *    to the actual input position.                                                    */
        me->buffer._lexeme_start_p = me->buffer._input_p;
    
    
        /* -- According to case (2.1) is is possible that the _input_p does not point to the end
            *    of the buffer, thus we record the current position in the lexeme start pointer and
            *    recover it after the loading. */
        me->buffer._input_p = text_end;
        if( QUEX_NAME(Buffer_is_end_of_file)(&me->buffer) == false ) {
                QUEX_NAME(buffer_reload_forward)(&me->buffer, (QUEX_TYPE_CHARACTER_POSITION*)position, PositionRegisterN);
                /* Recover '_input_p' from lexeme start
                    * (inverse of what we just did before the loading) */
                me->buffer._input_p = me->buffer._lexeme_start_p;
                /* After reload, we need to increment _input_p. That's how the game is supposed to be played.
                    * But, we recovered from lexeme start pointer, and this one does not need to be incremented. */
                text_end = QUEX_NAME(Buffer_text_end)(&me->buffer);
    
                QUEX_BUFFER_ASSERT_CONSISTENCY(&me->buffer);
                goto _1477;
        }
        /* Here, either the loading failed or it is not enough space to carry a closing delimiter */
        me->buffer._input_p = me->buffer._lexeme_start_p;
#define Closer "\n"
#   line 71 "lexer.qx"
    
                self_write_token_p()->text = "Warning: Unterminated comment";
                self_send(TK_WARNING);
    
    
#   line 7962 "lexer.cpp"
#undef  Closer
    RETURN;

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1392:
    __quex_debug("* terminal 1392:   \"/*\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
        Skipper1479_Opener_it = (QUEX_TYPE_CHARACTER*)Skipper1479_Opener;
        Skipper1479_Closer_it = (QUEX_TYPE_CHARACTER*)Skipper1479_Closer;
        /* text_end                           = QUEX_NAME(Buffer_text_end)(&me->buffer); */
        __QUEX_IF_COUNT_COLUMNS(reference_p = QUEX_NAME(Buffer_tell_memory_adr)(&me->buffer));
    
    
    _1480:
    
        QUEX_BUFFER_ASSERT_CONSISTENCY(&me->buffer);
        __quex_assert(QUEX_NAME(Buffer_content_size)(&me->buffer) >= 2 );
    
        /* NOTE: If _input_p == end of buffer, then it will drop out immediately out of the
            *       loop below and drop into the buffer reload procedure.                      */
    
        /* Loop eating characters: Break-out as soon as the First Character of the Delimiter
            * (FCD) is reached. Thus, the FCD plays also the role of the Buffer Limit Code. There
            * are two reasons for break-out:
            *    (1) we reached a limit (end-of-file or buffer-limit)
            *    (2) there was really the FCD in the character stream
            * This must be distinguished after the loop was exited. But, during the 'swallowing'
            * we are very fast, because we do not have to check for two different characters.  */
        while( 1 + 1 == 2 ) {
                input = *(me->buffer._input_p);
    
                if( input == QUEX_SETTING_BUFFER_LIMIT_CODE ) {
                        goto _1481;
                }
                if( input == *Skipper1479_Closer_it ) {
                        ++Skipper1479_Closer_it;
                        if( Skipper1479_Closer_it == Skipper1479_CloserEnd ) {
                            if( counter == 0 ) {
                                /* NOTE: The initial state does not increment the input_p. When it detects that
                                    * it is located on a buffer border, it automatically triggers a reload. No
                                    * need here to reload the buffer. */
                                ++(me->buffer._input_p); /* Now, BLC cannot occur. See above. */
                                        __QUEX_IF_COUNT_COLUMNS_ADD((size_t)(QUEX_NAME(Buffer_tell_memory_adr)(&me->buffer)
                                                - reference_p));
    
                                /* No need for re-entry preparation. Acceptance flags and modes are untouched after skipping. */
                                goto __REENTRY; /* End of range reached. */
                            }
                            --counter;
                            Skipper1479_Opener_it = (QUEX_TYPE_CHARACTER*)Skipper1479_Opener;
                            Skipper1479_Closer_it = (QUEX_TYPE_CHARACTER*)Skipper1479_Closer;
                            goto CONTINUE_1479;
                        }
                } else {
                        Skipper1479_Closer_it = (QUEX_TYPE_CHARACTER*)Skipper1479_Closer;
                }
                if( input == *Skipper1479_Opener_it ) {
                        ++Skipper1479_Opener_it;
                        if( Skipper1479_Opener_it == Skipper1479_OpenerEnd ) {
                            ++counter;
                            Skipper1479_Opener_it = (QUEX_TYPE_CHARACTER*)Skipper1479_Opener;
                            Skipper1479_Closer_it = (QUEX_TYPE_CHARACTER*)Skipper1479_Closer;
                            goto CONTINUE_1479;
                        }
                } else {
                        Skipper1479_Opener_it = (QUEX_TYPE_CHARACTER*)Skipper1479_Opener;
                }
    CONTINUE_1479:
    
        __QUEX_IF_COUNT_IF( input == (QUEX_TYPE_CHARACTER)'\n' ) {
                __QUEX_IF_COUNT_LINES_ADD((size_t)1);
                __QUEX_IF_COUNT_COLUMNS_SET((size_t)0);
                __QUEX_IF_COUNT_COLUMNS(reference_p = QUEX_NAME(Buffer_tell_memory_adr)(&me->buffer));
        }
    
                ++(me->buffer._input_p); /* Now, BLC cannot occur. See above. */
        }
    
    _1481:
        QUEX_BUFFER_ASSERT_CONSISTENCY_LIGHT(&me->buffer);
        /* -- When loading new content it is checked that the beginning of the lexeme
            *    is not 'shifted' out of the buffer. In the case of skipping, we do not care about
            *    the lexeme at all, so do not restrict the load procedure and set the lexeme start
            *    to the actual input position.                                                    */
        me->buffer._lexeme_start_p = me->buffer._input_p;
    
        __QUEX_IF_COUNT_COLUMNS_ADD((size_t)(QUEX_NAME(Buffer_tell_memory_adr)(&me->buffer)
                                            - reference_p));
    
        if( QUEX_NAME(Buffer_is_end_of_file)(&me->buffer) == false ) {
                QUEX_NAME(buffer_reload_forward)(&me->buffer, (QUEX_TYPE_CHARACTER_POSITION*)position,
                                                    PositionRegisterN);
                /* Recover '_input_p' from lexeme start
                    * (inverse of what we just did before the loading) */
                me->buffer._input_p = me->buffer._lexeme_start_p;
                /* After reload, we need to increment _input_p. That's how the game is supposed to be played.
                    * But, we recovered from lexeme start pointer, and this one does not need to be incremented. */
                /* text_end = QUEX_NAME(Buffer_text_end)(&me->buffer); */
                __QUEX_IF_COUNT_COLUMNS(reference_p = QUEX_NAME(Buffer_tell_memory_adr)(&me->buffer));
    
                QUEX_BUFFER_ASSERT_CONSISTENCY(&me->buffer);
                goto _1480; /* End of range reached.             */
        }
        /* Here, either the loading failed or it is not enough space to carry a closing delimiter */
        me->buffer._input_p = me->buffer._lexeme_start_p;
#define Closer "*/"
#   line 71 "lexer.qx"
    
                self_write_token_p()->text = "Warning: Unterminated comment";
                self_send(TK_WARNING);
    
    
#   line 8079 "lexer.cpp"
#undef  Closer
    RETURN;

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1393:
    __quex_debug("* terminal 1393:   \"//\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
        /*                          Delimiter: '\n',  */
    
        text_end = QUEX_NAME(Buffer_text_end)(&me->buffer);
    
    
    _1483:
    
        QUEX_BUFFER_ASSERT_CONSISTENCY(&me->buffer);
        __quex_assert(QUEX_NAME(Buffer_content_size)(&me->buffer) >= Skipper1482L );
    
        /* NOTE: If _input_p == end of buffer, then it will drop out immediately out of the
            *       loop below and drop into the buffer reload procedure.                      */
    
        /* Loop eating characters: Break-out as soon as the First Character of the Delimiter
            * (FCD) is reached. Thus, the FCD plays also the role of the Buffer Limit Code. There
            * are two reasons for break-out:
            *    (1) we reached a limit (end-of-file or buffer-limit)
            *    (2) there was really the FCD in the character stream
            * This must be distinguished after the loop was exited. But, during the 'swallowing' we
            * are very fast, because we do not have to check for two different characters.        */
        *text_end = Skipper1482[0]; /* Overwrite BufferLimitCode (BLC).  */
    _1482_LOOP:
                input = *(me->buffer._input_p);
    
                if( input == Skipper1482[0] ) {
    
                        goto _1482_LOOP_EXIT;
                }
    
        ++(me->buffer._input_p); /* Now, BLC cannot occur. See above. */
        goto _1482_LOOP;
    _1482_LOOP_EXIT:
    
        *text_end = QUEX_SETTING_BUFFER_LIMIT_CODE; /* Reset BLC. */
    
        /* Case (1) and (2) from above can be distinguished easily:
            *
            *   (1) Distance to text end == 0:
            *         End-of-File or Buffer-Limit.
            *         => goto to drop-out handling
            *
            *   (2) Else:
            *         First character of delimit reached.
            *         => For the verification of the tail of the delimiter it is
            *            essential that it is loaded completely into the buffer.
            *            For this, it must be required:
            *
            *                Distance to text end >= Delimiter length
            *
            *                _input_p    end
            *                    |        |           end - _input_p >= 3
            *                [ ][R][E][M][#]
            *
            *         The case of reload should be seldom and is costy anyway.
            *         Thus let's say, that in this case we simply enter the drop
            *         out and start the search for the delimiter all over again.
            *
            *         (2.1) Distance to text end < Delimiter length
            *                => goto to drop-out handling
            *         (2.2) Start detection of tail of delimiter
            *
            */
        if( QUEX_NAME(Buffer_distance_input_to_text_end)(&me->buffer) < (ptrdiff_t)Skipper1482L ) {
                /* (2.1) Reload required. */
                goto _1484;
        }
    
        /* (2.2) Test the remaining delimiter, but note, that the check must restart at '_input_p + 1'
            *       if any later check fails. */
        ++(me->buffer._input_p);
        /* Example: Delimiter = '*', '/'; if we get ...[*][*][/]... then the the first "*" causes
            *          a drop out out of the 'swallowing loop' and the second "*" will mismatch
            *          the required "/". But, then the second "*" must be presented to the
            *          swallowing loop and the letter after it completes the 'match'.
            * (The whole discussion, of course, is superflous if the range delimiter has length 1.)  */
    
        {
                /* NOTE: The initial state does not increment the input_p. When it detects that
                    * it is located on a buffer border, it automatically triggers a reload. No
                    * need here to reload the buffer. */
                __QUEX_IF_COUNT_COLUMNS_SET((size_t)1);
                __QUEX_IF_COUNT_LINES_ADD((size_t)1);
    
                /* No need for re-entry preparation. Acceptance flags and modes are untouched after skipping. */
                goto __REENTRY; /* End of range reached. */
        }
    
    _1484:
        QUEX_BUFFER_ASSERT_CONSISTENCY_LIGHT(&me->buffer);
        /* -- When loading new content it is checked that the beginning of the lexeme
            *    is not 'shifted' out of the buffer. In the case of skipping, we do not care about
            *    the lexeme at all, so do not restrict the load procedure and set the lexeme start
            *    to the actual input position.                                                    */
        me->buffer._lexeme_start_p = me->buffer._input_p;
    
    
        /* -- According to case (2.1) is is possible that the _input_p does not point to the end
            *    of the buffer, thus we record the current position in the lexeme start pointer and
            *    recover it after the loading. */
        me->buffer._input_p = text_end;
        if( QUEX_NAME(Buffer_is_end_of_file)(&me->buffer) == false ) {
                QUEX_NAME(buffer_reload_forward)(&me->buffer, (QUEX_TYPE_CHARACTER_POSITION*)position, PositionRegisterN);
                /* Recover '_input_p' from lexeme start
                    * (inverse of what we just did before the loading) */
                me->buffer._input_p = me->buffer._lexeme_start_p;
                /* After reload, we need to increment _input_p. That's how the game is supposed to be played.
                    * But, we recovered from lexeme start pointer, and this one does not need to be incremented. */
                text_end = QUEX_NAME(Buffer_text_end)(&me->buffer);
    
                QUEX_BUFFER_ASSERT_CONSISTENCY(&me->buffer);
                goto _1483;
        }
        /* Here, either the loading failed or it is not enough space to carry a closing delimiter */
        me->buffer._input_p = me->buffer._lexeme_start_p;
#define Closer "\n"
#   line 71 "lexer.qx"
    
                self_write_token_p()->text = "Warning: Unterminated comment";
                self_send(TK_WARNING);
    
    
#   line 8212 "lexer.cpp"
#undef  Closer
    RETURN;

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1394:
    __quex_debug("* terminal 1394:   \"\\n\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_LINES_ADD(1);
__QUEX_IF_COUNT_COLUMNS_SET(1);
    {
#   line 76 "lexer.qx"
    self_send(TK_NL);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8229 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1395:
    __quex_debug("* terminal 1395:   \";\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 77 "lexer.qx"
    self_send(TK_SCOLON);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8243 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1396:
    __quex_debug("* terminal 1396:   \"\\\"\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 82 "lexer.qx"
        self.string_delimiter='\"'; self << STRING;
    
#   line 8256 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1397:
    __quex_debug("* terminal 1397:   '\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 83 "lexer.qx"
        self.string_delimiter='\''; self << STRING;
    
#   line 8269 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1398:
    __quex_debug("* terminal 1398:   def\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(3);
    {
#   line 86 "lexer.qx"
    self_send(TK_DEF);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8283 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1399:
    __quex_debug("* terminal 1399:   class\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(5);
    {
#   line 87 "lexer.qx"
    self_send(TK_CLASS);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8297 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1400:
    __quex_debug("* terminal 1400:   do\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 88 "lexer.qx"
    self_send(TK_DO);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8311 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1401:
    __quex_debug("* terminal 1401:   end\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(3);
    {
#   line 89 "lexer.qx"
    self_send(TK_END);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8325 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1402:
    __quex_debug("* terminal 1402:   if\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 91 "lexer.qx"
    self_send(TK_IF);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8339 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1403:
    __quex_debug("* terminal 1403:   then\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(4);
    {
#   line 92 "lexer.qx"
    self_send(TK_THEN);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8353 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1404:
    __quex_debug("* terminal 1404:   else\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(4);
    {
#   line 93 "lexer.qx"
    self_send(TK_ELSE);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8367 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1405:
    __quex_debug("* terminal 1405:   elif\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(4);
    {
#   line 94 "lexer.qx"
    self_send(TK_ELSEIF);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8381 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1406:
    __quex_debug("* terminal 1406:   while\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(5);
    {
#   line 95 "lexer.qx"
    self_send(TK_WHILE);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8395 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1407:
    __quex_debug("* terminal 1407:   for\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(3);
    {
#   line 96 "lexer.qx"
    self_send(TK_FOR);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8409 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1408:
    __quex_debug("* terminal 1408:   in\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 97 "lexer.qx"
    self_send(TK_IN);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8423 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1409:
    __quex_debug("* terminal 1409:   repeat\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(6);
    {
#   line 98 "lexer.qx"
    self_send(TK_REPEAT);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8437 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1410:
    __quex_debug("* terminal 1410:   until\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(5);
    {
#   line 99 "lexer.qx"
    self_send(TK_UNTIL);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8451 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1411:
    __quex_debug("* terminal 1411:   return\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(6);
    {
#   line 101 "lexer.qx"
    self_send(TK_RETURN);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8465 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1412:
    __quex_debug("* terminal 1412:   break\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(5);
    {
#   line 102 "lexer.qx"
    self_send(TK_BREAK);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8479 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1413:
    __quex_debug("* terminal 1413:   next\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(4);
    {
#   line 103 "lexer.qx"
    self_send(TK_NEXT);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8493 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1414:
    __quex_debug("* terminal 1414:   local\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(5);
    {
#   line 105 "lexer.qx"
    self_send(TK_LOCAL);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8507 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1415:
    __quex_debug("* terminal 1415:   global\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(6);
    {
#   line 106 "lexer.qx"
    self_send(TK_GLOBAL);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8521 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1416:
    __quex_debug("* terminal 1416:   nil\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(3);
    {
#   line 108 "lexer.qx"
    self_send(TK_NIL);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8535 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1417:
    __quex_debug("* terminal 1417:   true\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(4);
    {
#   line 109 "lexer.qx"
    self_send(TK_TRUE);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8549 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1418:
    __quex_debug("* terminal 1418:   false\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(5);
    {
#   line 110 "lexer.qx"
    self_send(TK_FALSE);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8563 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1419:
    __quex_debug("* terminal 1419:   or\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 113 "lexer.qx"
    self_send(TK_OR);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8577 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1420:
    __quex_debug("* terminal 1420:   and\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(3);
    {
#   line 114 "lexer.qx"
    self_send(TK_AND);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8591 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1421:
    __quex_debug("* terminal 1421:   not\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(3);
    {
#   line 115 "lexer.qx"
    self_send(TK_NOT);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8605 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1422:
    __quex_debug("* terminal 1422:   <\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 116 "lexer.qx"
    self_send(TK_L);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8619 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1423:
    __quex_debug("* terminal 1423:   >\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 117 "lexer.qx"
    self_send(TK_G);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8633 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1424:
    __quex_debug("* terminal 1424:   <=\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 118 "lexer.qx"
    self_send(TK_LEQ);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8647 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1425:
    __quex_debug("* terminal 1425:   >=\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 119 "lexer.qx"
    self_send(TK_GEQ);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8661 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1426:
    __quex_debug("* terminal 1426:   !=\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 120 "lexer.qx"
    self_send(TK_NEQ);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8675 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1427:
    __quex_debug("* terminal 1427:   <>\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 121 "lexer.qx"
    self_send(TK_NEQ);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8689 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1428:
    __quex_debug("* terminal 1428:   ==\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 122 "lexer.qx"
    self_send(TK_EQ);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8703 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1429:
    __quex_debug("* terminal 1429:   \"..\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 124 "lexer.qx"
    self_send(TK_RANGEOP);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8717 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1430:
    __quex_debug("* terminal 1430:   \"+\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 125 "lexer.qx"
    self_send(TK_PLUS);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8731 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1431:
    __quex_debug("* terminal 1431:   \"-\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 126 "lexer.qx"
    self_send(TK_MINUS);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8745 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1432:
    __quex_debug("* terminal 1432:   \"*\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 127 "lexer.qx"
    self_send(TK_MUL);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8759 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1433:
    __quex_debug("* terminal 1433:   \"/\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 128 "lexer.qx"
    self_send(TK_DIV);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8773 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1434:
    __quex_debug("* terminal 1434:   \"%\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 129 "lexer.qx"
    self_send(TK_MOD);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8787 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1435:
    __quex_debug("* terminal 1435:   \"|\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 130 "lexer.qx"
    self_send(TK_PIPE);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8801 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1436:
    __quex_debug("* terminal 1436:   \"^\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 131 "lexer.qx"
    self_send(TK_EXP);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8815 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1437:
    __quex_debug("* terminal 1437:   \"=\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 132 "lexer.qx"
    self_send(TK_ASSIG);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8829 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1438:
    __quex_debug("* terminal 1438:   \",\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 135 "lexer.qx"
    self_send(TK_COMMA);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8843 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1439:
    __quex_debug("* terminal 1439:   \".\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 136 "lexer.qx"
    self_send(TK_DOT);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8857 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1440:
    __quex_debug("* terminal 1440:   \"[\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 138 "lexer.qx"
    self_send(TK_SBL);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8871 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1441:
    __quex_debug("* terminal 1441:   \"]\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 139 "lexer.qx"
    self_send(TK_SBR);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8885 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1442:
    __quex_debug("* terminal 1442:   \"{\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 140 "lexer.qx"
    self_send(TK_CBL);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8899 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1443:
    __quex_debug("* terminal 1443:   \"}\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 141 "lexer.qx"
    self_send(TK_CBR);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8913 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1444:
    __quex_debug("* terminal 1444:   \"(\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 142 "lexer.qx"
    self_send(TK_PL);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8927 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1445:
    __quex_debug("* terminal 1445:   \")\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 143 "lexer.qx"
    self_send(TK_PR);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8941 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1446:
    __quex_debug("* terminal 1446:   0[0-7]*\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(LexemeL);
    QUEX_LEXEME_TERMINATING_ZERO_SET(&me->buffer);
    {
#   line 147 "lexer.qx"
    self_write_token_p()->content.integer = stoi(Lexeme,8);
    self_send(TK_INT);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8957 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1447:
    __quex_debug("* terminal 1447:   [1-9][0-9]*\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(LexemeL);
    QUEX_LEXEME_TERMINATING_ZERO_SET(&me->buffer);
    {
#   line 148 "lexer.qx"
    self_write_token_p()->content.integer = stoi(Lexeme,10);
    self_send(TK_INT);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8973 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1448:
    __quex_debug("* terminal 1448:   0[xX][:xdigit:]+\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(LexemeL);
    QUEX_LEXEME_TERMINATING_ZERO_SET(&me->buffer);
    {
#   line 149 "lexer.qx"
    self_write_token_p()->content.integer = stoi(Lexeme,16);
    self_send(TK_INT);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8989 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1449:
    __quex_debug("* terminal 1449:   [0-9]*\\.?[0-9]+([eE][\\-+]?[0-9]+)?\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(LexemeL);
    QUEX_LEXEME_TERMINATING_ZERO_SET(&me->buffer);
    {
#   line 151 "lexer.qx"
    self_write_token_p()->content.real = atof((char*)(Lexeme));
    self_send(TK_REAL);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 9005 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1450:
    __quex_debug("* terminal 1450:   nan\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(3);
    {
#   line 152 "lexer.qx"
    self_write_token_p()->content.real = NAN;
    self_send(TK_REAL);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 9020 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1451:
    __quex_debug("* terminal 1451:   inf\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(3);
    {
#   line 154 "lexer.qx"
    
        self_write_token_p()->content.real = INFINITY;
        self_send(TK_REAL);
    
    
#   line 9036 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1452:
    __quex_debug("* terminal 1452:   {ualpha}{ualnum}*\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(LexemeL);
    {
#   line 159 "lexer.qx"
    QUEX_NAME_TOKEN(take_text)(self_write_token_p(), &self, self.buffer._lexeme_start_p, self.buffer._input_p);
    self_send(TK_IDENT);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 9051 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;


_2121: /* TERMINAL: FAILURE */
    if(QUEX_NAME(Buffer_is_end_of_file)(&me->buffer)) {
        /* Init state is going to detect 'input == buffer limit code', and
         * enter the reload procedure, which will decide about 'end of stream'. */
    } else {
        /* In init state 'input = *input_p' and we need to increment
         * in order to avoid getting stalled. Else, input = *(input_p - 1),
         * so 'input_p' points already to the next character.                   */
        if( me->buffer._input_p == me->buffer._lexeme_start_p ) {
            /* Step over non-matching character */
            ++(me->buffer._input_p);
        }
    }
    __QUEX_COUNT_VOID(&self, LexemeBegin, LexemeEnd);
    {
#   line 60 "lexer.qx"
    
        std::ostringstream ss;
        ss << "Syntax error: Unexpected symbol: \"" <<
            std::string(LexemeBegin, LexemeEnd) <<
            "\" at line " <<
            self.line_number() <<
            " column " <<
            self.column_number();
        throw ParseError(ss.str());
    
    
#   line 9084 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION_2;


/* TERMINAL: END_OF_STREAM */
_1475:
__QUEX_IF_COUNT_SHIFT_VALUES();
    {
#   line 78 "lexer.qx"
    self_send(TK_EOS);
    
#   line 9097 "lexer.cpp"

    }
    /* End of Stream causes a return from the lexical analyzer, so that no
     * tokens can be filled after the termination token.                    */
    RETURN;

__REENTRY_PREPARATION:
    /* (*) Common point for **restarting** lexical analysis.
     *     at each time when CONTINUE is called at the end of a pattern.     */
 

    /* FAILURE needs not to run through 'on_after_match'. It enters here.    */
__REENTRY_PREPARATION_2:

#   undef Lexeme
#   undef LexemeBegin
#   undef LexemeEnd
#   undef LexemeNull
#   undef LexemeL

#   ifndef __QUEX_OPTION_PLAIN_ANALYZER_OBJECT
#   ifdef  QUEX_OPTION_TOKEN_POLICY_QUEUE
    if( QUEX_NAME(TokenQueue_is_full)(&self._token_queue) ) {
        return;
    }
#   else
    if( self_token_get_id() != __QUEX_SETTING_TOKEN_ID_UNINITIALIZED) {
        return __self_result_token_id;
    }
#   endif
#   endif


    /* Post context positions do not have to be reset or initialized. If a state
     * is reached which is associated with 'end of post context' it is clear what
     * post context is meant. This results from the ways the state machine is 
     * constructed. Post context position's live cycle:
     *
     * (1)   unitialized (don't care)
     * (1.b) on buffer reload it may, or may not be adapted (don't care)
     * (2)   when a post context begin state is passed, then it is **SET** (now: take care)
     * (2.b) on buffer reload it **is adapted**.
     * (3)   when a terminal state of the post context is reached (which can only be reached
     *       for that particular post context), then the post context position is used
     *       to reset the input position.                                              */

    /*  If a mode change happened, then the function must first return and
     *  indicate that another mode function is to be called. At this point, 
     *  we to force a 'return' on a mode change. 
     *
     *  Pseudo Code: if( previous_mode != current_mode ) {
     *                   return 0;
     *               }
     *
     *  When the analyzer returns, the caller function has to watch if a mode 
     *  change occurred. If not it can call this function again.             */
#   if    defined(QUEX_OPTION_AUTOMATIC_ANALYSIS_CONTINUATION_ON_MODE_CHANGE)        || defined(QUEX_OPTION_ASSERTS)
    if( me->DEBUG_analyzer_function_at_entry != me->current_analyzer_function ) 
#   endif
    { 
#       if defined(QUEX_OPTION_AUTOMATIC_ANALYSIS_CONTINUATION_ON_MODE_CHANGE)
        self_token_set_id(__QUEX_SETTING_TOKEN_ID_UNINITIALIZED);
        __QUEX_PURE_RETURN;
#       elif defined(QUEX_OPTION_ASSERTS)
        QUEX_ERROR_EXIT("Mode change without immediate return from the lexical analyzer.");
#       endif
    }

    goto __REENTRY;

    __quex_assert_no_passage();
__RELOAD_FORWARD:

    __quex_debug1("__RELOAD_FORWARD");
    __quex_assert(*(me->buffer._input_p) == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( me->buffer._memory._end_of_file_p == 0x0 ) {

        __quex_debug_reload_before(); /* Leave macro here to report source position. */
        QUEX_NAME(buffer_reload_forward)(&me->buffer, (QUEX_TYPE_CHARACTER_POSITION*)position, PositionRegisterN);

        __quex_debug_reload_after();
        QUEX_GOTO_STATE(target_state_index);
    }
    __quex_debug("reload impossible\n");
    QUEX_GOTO_STATE(target_state_else_index);
#   ifndef QUEX_OPTION_COMPUTED_GOTOS
    __quex_assert_no_passage();
__STATE_ROUTER:
    switch( target_state_index ) {
        case 1472: { goto _1472; }
        case 1474: { goto _1474; }
        case 1475: { goto _1475; }
        case 1477: { goto _1477; }
        case 1480: { goto _1480; }
        case 1483: { goto _1483; }
        case 1984: { goto _1984; }
        case 1985: { goto _1985; }
        case 1986: { goto _1986; }
        case 1987: { goto _1987; }
        case 1988: { goto _1988; }
        case 1989: { goto _1989; }
        case 1990: { goto _1990; }
        case 1991: { goto _1991; }
        case 1992: { goto _1992; }
        case 1993: { goto _1993; }
        case 1994: { goto _1994; }
        case 1995: { goto _1995; }
        case 1996: { goto _1996; }
        case 1997: { goto _1997; }
        case 1998: { goto _1998; }
        case 1999: { goto _1999; }
        case 2000: { goto _2000; }
        case 2001: { goto _2001; }
        case 2002: { goto _2002; }
        case 2003: { goto _2003; }
        case 2004: { goto _2004; }
        case 2005: { goto _2005; }
        case 2006: { goto _2006; }
        case 2007: { goto _2007; }
        case 2008: { goto _2008; }
        case 2009: { goto _2009; }
        case 2010: { goto _2010; }
        case 2011: { goto _2011; }
        case 2012: { goto _2012; }
        case 2013: { goto _2013; }
        case 2014: { goto _2014; }
        case 2015: { goto _2015; }
        case 2016: { goto _2016; }
        case 2017: { goto _2017; }
        case 2018: { goto _2018; }
        case 2019: { goto _2019; }
        case 2020: { goto _2020; }
        case 2021: { goto _2021; }
        case 2022: { goto _2022; }
        case 2023: { goto _2023; }
        case 2024: { goto _2024; }
        case 2025: { goto _2025; }
        case 2026: { goto _2026; }
        case 2027: { goto _2027; }
        case 2028: { goto _2028; }
        case 2029: { goto _2029; }
        case 2030: { goto _2030; }
        case 2031: { goto _2031; }
        case 2032: { goto _2032; }
        case 2033: { goto _2033; }
        case 2034: { goto _2034; }
        case 2035: { goto _2035; }
        case 2036: { goto _2036; }
        case 2037: { goto _2037; }
        case 2038: { goto _2038; }
        case 2039: { goto _2039; }
        case 2040: { goto _2040; }
        case 2041: { goto _2041; }
        case 2042: { goto _2042; }
        case 2043: { goto _2043; }
        case 2044: { goto _2044; }
        case 2045: { goto _2045; }
        case 2046: { goto _2046; }
        case 2047: { goto _2047; }
        case 2048: { goto _2048; }
        case 2049: { goto _2049; }
        case 2050: { goto _2050; }
        case 2051: { goto _2051; }
        case 2052: { goto _2052; }
        case 2053: { goto _2053; }
        case 2054: { goto _2054; }
        case 2055: { goto _2055; }
        case 2056: { goto _2056; }
        case 2057: { goto _2057; }
        case 2058: { goto _2058; }
        case 2059: { goto _2059; }
        case 2060: { goto _2060; }
        case 2061: { goto _2061; }
        case 2062: { goto _2062; }
        case 2063: { goto _2063; }
        case 2064: { goto _2064; }
        case 2065: { goto _2065; }
        case 2066: { goto _2066; }
        case 2067: { goto _2067; }
        case 2068: { goto _2068; }
        case 2069: { goto _2069; }
        case 2070: { goto _2070; }
        case 2071: { goto _2071; }
        case 2072: { goto _2072; }
        case 2073: { goto _2073; }
        case 2074: { goto _2074; }
        case 2075: { goto _2075; }
        case 2076: { goto _2076; }
        case 2077: { goto _2077; }
        case 2078: { goto _2078; }
        case 2079: { goto _2079; }
        case 2080: { goto _2080; }
        case 2081: { goto _2081; }
        case 2082: { goto _2082; }
        case 2083: { goto _2083; }
        case 2084: { goto _2084; }
        case 2085: { goto _2085; }
        case 2086: { goto _2086; }
        case 2087: { goto _2087; }
        case 2088: { goto _2088; }
        case 2089: { goto _2089; }
        case 2090: { goto _2090; }
        case 2091: { goto _2091; }
        case 2092: { goto _2092; }
        case 2093: { goto _2093; }
        case 2094: { goto _2094; }
        case 2095: { goto _2095; }
        case 2096: { goto _2096; }
        case 2097: { goto _2097; }
        case 2098: { goto _2098; }
        case 2099: { goto _2099; }
        case 2100: { goto _2100; }
        case 2101: { goto _2101; }
        case 2102: { goto _2102; }
        case 2103: { goto _2103; }
        case 2104: { goto _2104; }
        case 2105: { goto _2105; }
        case 2106: { goto _2106; }
        case 2107: { goto _2107; }
        case 2108: { goto _2108; }
        case 2109: { goto _2109; }
        case 2110: { goto _2110; }
        case 2111: { goto _2111; }
        case 2112: { goto _2112; }
        case 2113: { goto _2113; }
        case 2114: { goto _2114; }
        case 2115: { goto _2115; }
        case 2116: { goto _2116; }
        case 2118: { goto _2118; }
        case 2119: { goto _2119; }
        case 2122: { goto _2122; }
        case 2123: { goto _2123; }
        case 2124: { goto _2124; }
        case 2125: { goto _2125; }
        case 2126: { goto _2126; }
        case 2127: { goto _2127; }
        case 2128: { goto _2128; }
        case 2129: { goto _2129; }
        case 2130: { goto _2130; }
        case 2131: { goto _2131; }
        case 2132: { goto _2132; }
        case 2133: { goto _2133; }
        case 2134: { goto _2134; }
        case 2135: { goto _2135; }
        case 2136: { goto _2136; }
        case 2137: { goto _2137; }
        case 2138: { goto _2138; }
        case 2139: { goto _2139; }
        case 2140: { goto _2140; }
        case 2142: { goto _2142; }
        case 2143: { goto _2143; }
        case 2144: { goto _2144; }
        case 2145: { goto _2145; }
        case 2146: { goto _2146; }
        case 2147: { goto _2147; }
        case 2148: { goto _2148; }
        case 2149: { goto _2149; }
        case 2150: { goto _2150; }
        case 2151: { goto _2151; }
        case 2152: { goto _2152; }
        case 2153: { goto _2153; }
        case 2155: { goto _2155; }
        case 2157: { goto _2157; }
        case 2158: { goto _2158; }
        case 2159: { goto _2159; }
        case 2160: { goto _2160; }
        case 2161: { goto _2161; }
        case 2162: { goto _2162; }
        case 2163: { goto _2163; }
        case 2164: { goto _2164; }
        case 2165: { goto _2165; }
        case 2166: { goto _2166; }
        case 2167: { goto _2167; }
        case 2168: { goto _2168; }
        case 2169: { goto _2169; }
        case 2170: { goto _2170; }
        case 2171: { goto _2171; }
        case 2172: { goto _2172; }
        case 2173: { goto _2173; }
        case 2174: { goto _2174; }
        case 2175: { goto _2175; }
        case 2176: { goto _2176; }
        case 2177: { goto _2177; }
        case 2178: { goto _2178; }
        case 2179: { goto _2179; }
        case 2180: { goto _2180; }
        case 2181: { goto _2181; }
        case 2182: { goto _2182; }
        case 2183: { goto _2183; }
        case 2184: { goto _2184; }
        case 2185: { goto _2185; }
        case 2186: { goto _2186; }
        case 2187: { goto _2187; }
        case 2190: { goto _2190; }
        case 2191: { goto _2191; }
        case 2192: { goto _2192; }
        case 2193: { goto _2193; }
        case 2195: { goto _2195; }
        case 2196: { goto _2196; }
        case 2197: { goto _2197; }
        case 2198: { goto _2198; }
        case 2199: { goto _2199; }
        case 2200: { goto _2200; }
        case 2201: { goto _2201; }
        case 2202: { goto _2202; }
        case 2203: { goto _2203; }
        case 2204: { goto _2204; }
        case 2207: { goto _2207; }
        case 2208: { goto _2208; }
        case 2209: { goto _2209; }
        case 2210: { goto _2210; }
        case 2211: { goto _2211; }
        case 2212: { goto _2212; }
        case 2213: { goto _2213; }
        case 2214: { goto _2214; }
        case 2215: { goto _2215; }
        case 2216: { goto _2216; }
        case 2217: { goto _2217; }
        case 2219: { goto _2219; }
        case 2221: { goto _2221; }
        case 2223: { goto _2223; }
        case 2225: { goto _2225; }
        case 2226: { goto _2226; }
        case 2228: { goto _2228; }
        case 2229: { goto _2229; }
        case 2230: { goto _2230; }
        case 2232: { goto _2232; }
        case 2235: { goto _2235; }
        case 2236: { goto _2236; }
        case 2239: { goto _2239; }
        case 2240: { goto _2240; }
        case 2241: { goto _2241; }
        case 2245: { goto _2245; }
        case 2247: { goto _2247; }
        case 2249: { goto _2249; }
        case 2254: { goto _2254; }
        case 2255: { goto _2255; }

        default:
            __QUEX_STD_fprintf(stderr, "State router: index = %i\n", (int)target_state_index);
            QUEX_ERROR_EXIT("State router: unknown index.\n");
    }
#   endif /* QUEX_OPTION_COMPUTED_GOTOS */

    /* Prevent compiler warning 'unused variable': use variables once in a part of the code*/
    /* that is never reached (and deleted by the compiler anyway).*/
    (void)QUEX_LEXEME_NULL;
    (void)QUEX_NAME_TOKEN(DumpedTokenIdObject);
    QUEX_ERROR_EXIT("Unreachable code has been reached.\n");
#   undef MAIN
#   undef STRING
#   undef self
}
#include <quex/code_base/temporary_macros_off>
#ifdef      __QUEX_COUNT_VOID
#   undef   __QUEX_COUNT_VOID
#endif
#ifdef      __QUEX_OPTION_COUNTER
#    define __QUEX_COUNT_VOID(ME, BEGIN, END) \
            do {                              \
                QUEX_NAME(MAIN_counter)((ME), (BEGIN), (END));     \
                __quex_debug_counter();       \
            } while(0)
#else
#    define __QUEX_COUNT_VOID(ME, BEGIN, END) /* empty */
#endif

#include <quex/code_base/analyzer/member/basic>
#include <quex/code_base/buffer/Buffer>
#ifdef QUEX_OPTION_TOKEN_POLICY_QUEUE
#   include <quex/code_base/token/TokenQueue>
#endif

#ifdef    CONTINUE
#   undef CONTINUE
#endif
#define   CONTINUE goto __REENTRY_PREPARATION; 

#ifdef    RETURN
#   undef RETURN
#endif

#define RETURN    __QUEX_PURE_RETURN;
#include <quex/code_base/temporary_macros_on>

__QUEX_TYPE_ANALYZER_RETURN_VALUE  
QUEX_NAME(STRING_analyzer_function)(QUEX_TYPE_ANALYZER* me) 
{
    /* NOTE: Different modes correspond to different analyzer functions. The 
     *       analyzer functions are all located inside the main class as static
     *       functions. That means, they are something like 'globals'. They 
     *       receive a pointer to the lexical analyzer, since static members do
     *       not have access to the 'this' pointer.                          */
#   if defined(QUEX_OPTION_TOKEN_POLICY_SINGLE)
    register QUEX_TYPE_TOKEN_ID __self_result_token_id 
           = (QUEX_TYPE_TOKEN_ID)__QUEX_SETTING_TOKEN_ID_UNINITIALIZED;
#   endif
#   ifdef     self
#       undef self
#   endif
#   define self (*((QUEX_TYPE_ANALYZER*)me))
    QUEX_TYPE_CHARACTER_POSITION   position[1]                    = { 0};
    QUEX_TYPE_GOTO_LABEL           target_state_else_index        = QUEX_GOTO_LABEL_VOID;
    const size_t                   PositionRegisterN              = (size_t)1;
    QUEX_TYPE_CHARACTER            input                          = (QUEX_TYPE_CHARACTER)(0x00);
    QUEX_TYPE_GOTO_LABEL           target_state_index             = QUEX_GOTO_LABEL_VOID;
#   ifndef QUEX_OPTION_COMPUTED_GOTOS
#   endif /* QUEX_OPTION_COMPUTED_GOTOS */
#   define MAIN      (QUEX_NAME(MAIN))
#   define STRING    (QUEX_NAME(STRING))

    /* Post context positions do not have to be reset or initialized. If a state
     * is reached which is associated with 'end of post context' it is clear what
     * post context is meant. This results from the ways the state machine is 
     * constructed. Post context position's live cycle:
     *
     * (1)   unitialized (don't care)
     * (1.b) on buffer reload it may, or may not be adapted (don't care)
     * (2)   when a post context begin state is passed, then it is **SET** (now: take care)
     * (2.b) on buffer reload it **is adapted**.
     * (3)   when a terminal state of the post context is reached (which can only be reached
     *       for that particular post context), then the post context position is used
     *       to reset the input position.                                              */
#   if    defined(QUEX_OPTION_AUTOMATIC_ANALYSIS_CONTINUATION_ON_MODE_CHANGE) \
       || defined(QUEX_OPTION_ASSERTS)
    me->DEBUG_analyzer_function_at_entry = me->current_analyzer_function;
#   endif
__REENTRY:
    me->buffer._lexeme_start_p = me->buffer._input_p;
    QUEX_LEXEME_TERMINATING_ZERO_UNDO(&me->buffer);
_2431: /* INIT_STATE_TRANSITION_BLOCK */
    input = *(me->buffer._input_p);
    __quex_debug("Init State\n");
    __quex_debug_state(2399);
    if( input < 0x23 ) {
        switch( input ) {
            case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2399, 1475);
            case 0x2: 
            case 0x3: 
            case 0x4: 
            case 0x5: 
            case 0x6: 
            case 0x7: 
            case 0x8: 
            case 0x9: 
            case 0xA: 
            case 0xB: 
            case 0xC: 
            case 0xD: 
            case 0xE: 
            case 0xF: 
            case 0x10: 
            case 0x11: 
            case 0x12: 
            case 0x13: 
            case 0x14: 
            case 0x15: 
            case 0x16: 
            case 0x17: 
            case 0x18: 
            case 0x19: 
            case 0x1A: 
            case 0x1B: 
            case 0x1C: 
            case 0x1D: 
            case 0x1E: 
            case 0x1F: 
            case 0x20: 
            case 0x21: goto _2403;
            case 0x22: goto _2400;

        }
    } else {
        if( input < 0x27 ) {
            goto _2403;
        } else if( input == 0x27 ) {
            goto _2401;
        } else if( input < 0x5C ) {
            goto _2403;
        } else if( input == 0x5C ) {
            goto _2402;
        } else {
            goto _2403;
        }
    }
    __quex_debug_drop_out(2399);

goto _2121; /* TERMINAL_FAILURE */

_2399:


    ++(me->buffer._input_p);
    goto _2431;


    __quex_assert_no_passage();
_2433: /* (2427 from 2401) */
    position[0] = me->buffer._input_p; __quex_debug("position[0] = input_p;\n");

_2427: /* (2427 from 2427) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2427);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2427, 2434);
        case 0x9: 
        case 0xA: 
        case 0xD: 
        case 0x20: goto _2427;
        case 0x27: goto _2428;

    }
_2434:
    __quex_debug_drop_out(2427);
__quex_assert(position[0] != 0x0);
me->buffer._input_p = position[0];

goto TERMINAL_1456;

    __quex_assert_no_passage();
_2435: /* (2429 from 2400) */
    position[0] = me->buffer._input_p; __quex_debug("position[0] = input_p;\n");

_2429: /* (2429 from 2429) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2429);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2429, 2436);
        case 0x9: 
        case 0xA: 
        case 0xD: 
        case 0x20: goto _2429;
        case 0x22: goto _2430;

    }
_2436:
    __quex_debug_drop_out(2429);
__quex_assert(position[0] != 0x0);
me->buffer._input_p = position[0];

goto TERMINAL_1455;

    __quex_assert_no_passage();
_2403: /* (2403 from 2403) (2403 from 2399) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2403);
    if( input < 0x23 ) {
        switch( input ) {
            case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2403, 2437);
            case 0x2: 
            case 0x3: 
            case 0x4: 
            case 0x5: 
            case 0x6: 
            case 0x7: 
            case 0x8: 
            case 0x9: 
            case 0xA: 
            case 0xB: 
            case 0xC: 
            case 0xD: 
            case 0xE: 
            case 0xF: 
            case 0x10: 
            case 0x11: 
            case 0x12: 
            case 0x13: 
            case 0x14: 
            case 0x15: 
            case 0x16: 
            case 0x17: 
            case 0x18: 
            case 0x19: 
            case 0x1A: 
            case 0x1B: 
            case 0x1C: 
            case 0x1D: 
            case 0x1E: 
            case 0x1F: 
            case 0x20: 
            case 0x21: goto _2403;

        }
    } else {
        if( input < 0x27 ) {
            goto _2403;
        } else if( input == 0x27 ) {

        } else if( input < 0x5C ) {
            goto _2403;
        } else if( input == 0x5C ) {

        } else {
            goto _2403;
        }
    }
_2437:
    __quex_debug_drop_out(2403);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2419: /* (2419 from 2413) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2419);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2419, 2438);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: goto _2420;

    }
_2438:
    __quex_debug_drop_out(2419);
goto TERMINAL_1467;

    __quex_assert_no_passage();
_2420: /* (2420 from 2419) */

    ++(me->buffer._input_p);
    __quex_debug_state(2420);
    __quex_debug_drop_out(2420);
goto TERMINAL_1467;

    __quex_assert_no_passage();
_2421: /* (2421 from 2412) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2421);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2421, 2440);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: goto _2422;

    }
_2440:
    __quex_debug_drop_out(2421);
goto TERMINAL_1468;

    __quex_assert_no_passage();
_2422: /* (2422 from 2421) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2422);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2422, 2441);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: goto _2423;

    }
_2441:
    __quex_debug_drop_out(2422);
goto TERMINAL_1468;

    __quex_assert_no_passage();
_2423: /* (2423 from 2422) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2423);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2423, 2442);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: goto _2424;

    }
_2442:
    __quex_debug_drop_out(2423);
goto TERMINAL_1468;

    __quex_assert_no_passage();
_2424: /* (2424 from 2423) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2424);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2424, 2443);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: goto _2425;

    }
_2443:
    __quex_debug_drop_out(2424);
goto TERMINAL_1468;

    __quex_assert_no_passage();
_2425: /* (2425 from 2424) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2425);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2425, 2444);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: goto _2426;

    }
_2444:
    __quex_debug_drop_out(2425);
goto TERMINAL_1468;

    __quex_assert_no_passage();
_2426: /* (2426 from 2425) */

    ++(me->buffer._input_p);
    __quex_debug_state(2426);
    __quex_debug_drop_out(2426);
goto TERMINAL_1468;

    __quex_assert_no_passage();
_2428: /* (2428 from 2427) (2428 from 2401) */

    ++(me->buffer._input_p);
    __quex_debug_state(2428);
    __quex_debug_drop_out(2428);
goto TERMINAL_1454;

    __quex_assert_no_passage();
_2430: /* (2430 from 2429) (2430 from 2400) */

    ++(me->buffer._input_p);
    __quex_debug_state(2430);
    __quex_debug_drop_out(2430);
goto TERMINAL_1453;

    __quex_assert_no_passage();
_2404: /* (2404 from 2402) */

    ++(me->buffer._input_p);
    __quex_debug_state(2404);
    __quex_debug_drop_out(2404);
goto TERMINAL_1458;

    __quex_assert_no_passage();
_2405: /* (2405 from 2402) */

    ++(me->buffer._input_p);
    __quex_debug_state(2405);
    __quex_debug_drop_out(2405);
goto TERMINAL_1469;

    __quex_assert_no_passage();
_2406: /* (2406 from 2402) */

    ++(me->buffer._input_p);
    __quex_debug_state(2406);
    __quex_debug_drop_out(2406);
goto TERMINAL_1460;

    __quex_assert_no_passage();
_2407: /* (2407 from 2402) */

    ++(me->buffer._input_p);
    __quex_debug_state(2407);
    __quex_debug_drop_out(2407);
goto TERMINAL_1462;

    __quex_assert_no_passage();
_2408: /* (2408 from 2402) */

    ++(me->buffer._input_p);
    __quex_debug_state(2408);
    __quex_debug_drop_out(2408);
goto TERMINAL_1464;

    __quex_assert_no_passage();
_2409: /* (2409 from 2402) */

    ++(me->buffer._input_p);
    __quex_debug_state(2409);
    __quex_debug_drop_out(2409);
goto TERMINAL_1470;

    __quex_assert_no_passage();
_2410: /* (2410 from 2402) */

    ++(me->buffer._input_p);
    __quex_debug_state(2410);
    __quex_debug_drop_out(2410);
goto TERMINAL_1463;

    __quex_assert_no_passage();
_2411: /* (2411 from 2402) */

    ++(me->buffer._input_p);
    __quex_debug_state(2411);
    __quex_debug_drop_out(2411);
goto TERMINAL_1465;

    __quex_assert_no_passage();
_2412: /* (2412 from 2402) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2412);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2412, 2456);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: goto _2421;

    }
_2456:
    __quex_debug_drop_out(2412);

goto _2121; /* TERMINAL_FAILURE */

    __quex_assert_no_passage();
_2413: /* (2413 from 2402) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2413);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2413, 2457);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: 
        case 0x41: 
        case 0x42: 
        case 0x43: 
        case 0x44: 
        case 0x45: 
        case 0x46: 
        case 0x61: 
        case 0x62: 
        case 0x63: 
        case 0x64: 
        case 0x65: 
        case 0x66: goto _2419;

    }
_2457:
    __quex_debug_drop_out(2413);

goto _2121; /* TERMINAL_FAILURE */

    __quex_assert_no_passage();
_2414: /* (2414 from 2402) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2414);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2414, 2458);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: goto _2417;

    }
_2458:
    __quex_debug_drop_out(2414);
goto TERMINAL_1466;

    __quex_assert_no_passage();
_2415: /* (2415 from 2402) */

    ++(me->buffer._input_p);
    __quex_debug_state(2415);
    __quex_debug_drop_out(2415);
goto TERMINAL_1459;

    __quex_assert_no_passage();
_2416: /* (2416 from 2402) */

    ++(me->buffer._input_p);
    __quex_debug_state(2416);
    __quex_debug_drop_out(2416);
goto TERMINAL_1461;

    __quex_assert_no_passage();
_2417: /* (2417 from 2414) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2417);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2417, 2461);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: goto _2418;

    }
_2461:
    __quex_debug_drop_out(2417);
goto TERMINAL_1466;

    __quex_assert_no_passage();
_2418: /* (2418 from 2417) */

    ++(me->buffer._input_p);
    __quex_debug_state(2418);
    __quex_debug_drop_out(2418);
goto TERMINAL_1466;

    __quex_assert_no_passage();
_2400: /* (2400 from 2399) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2400);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2400, 2463);
        case 0x9: 
        case 0xA: 
        case 0xD: 
        case 0x20: goto _2435;
        case 0x22: goto _2430;

    }
_2463:
    __quex_debug_drop_out(2400);
goto TERMINAL_1455;

    __quex_assert_no_passage();
_2401: /* (2401 from 2399) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2401);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2401, 2464);
        case 0x9: 
        case 0xA: 
        case 0xD: 
        case 0x20: goto _2433;
        case 0x27: goto _2428;

    }
_2464:
    __quex_debug_drop_out(2401);
goto TERMINAL_1456;

    __quex_assert_no_passage();
_2402: /* (2402 from 2399) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2402);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2402, 2465);
        case 0x22: goto _2409;
        case 0x27: goto _2405;
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: goto _2414;
        case 0x5C: goto _2411;
        case 0x61: goto _2406;
        case 0x62: goto _2416;
        case 0x66: goto _2407;
        case 0x6E: goto _2404;
        case 0x72: goto _2410;
        case 0x74: goto _2415;
        case 0x75: goto _2412;
        case 0x76: goto _2408;
        case 0x78: goto _2413;

    }
_2465:
    __quex_debug_drop_out(2402);

goto _2121; /* TERMINAL_FAILURE */
    /* (*) Terminal states _______________________________________________________
     *
     * States that implement actions of the 'winner patterns.                     */

    /* Lexeme setup: 
     *
     * There is a temporary zero stored at the end of each lexeme, if the action 
     * references to the 'Lexeme'. 'LexemeNull' provides a reference to an empty
     * zero terminated string.                                                    */
#if defined(QUEX_OPTION_ASSERTS)
#   define Lexeme       QUEX_NAME(access_Lexeme)((const char*)__FILE__, (size_t)__LINE__, &me->buffer)
#   define LexemeBegin  QUEX_NAME(access_LexemeBegin)((const char*)__FILE__, (size_t)__LINE__, &me->buffer)
#   define LexemeL      QUEX_NAME(access_LexemeL)((const char*)__FILE__, (size_t)__LINE__, &me->buffer)
#   define LexemeEnd    QUEX_NAME(access_LexemeEnd)((const char*)__FILE__, (size_t)__LINE__, &me->buffer)
#else
#   define Lexeme       (me->buffer._lexeme_start_p)
#   define LexemeBegin  Lexeme
#   define LexemeL      ((size_t)(me->buffer._input_p - me->buffer._lexeme_start_p))
#   define LexemeEnd    me->buffer._input_p
#endif

#define LexemeNull      (&QUEX_LEXEME_NULL)

TERMINAL_1453:
    __quex_debug("* terminal 1453:   \\\"[:space:]*\\\"\n");
    __QUEX_COUNT_VOID(&self, LexemeBegin, LexemeEnd);
    {
#   line 176 "lexer.qx"
    
        if(self.string_delimiter != '\"')
            self_accumulator_add(LexemeBegin, LexemeEnd);
    
    
#   line 10263 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1454:
    __quex_debug("* terminal 1454:   '[:space:]*'\n");
    __QUEX_COUNT_VOID(&self, LexemeBegin, LexemeEnd);
    {
#   line 182 "lexer.qx"
    
        if(self.string_delimiter != '\'')
            self_accumulator_add(LexemeBegin, LexemeEnd);
    
    
#   line 10278 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1455:
    __quex_debug("* terminal 1455:   \\\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 188 "lexer.qx"
    
        if (self.string_delimiter == '\"')
        {
            self_accumulator_flush(TK_STRING);
            self << MAIN;
        }
        else
        {
            self_accumulator_add_character('\"');
        }
    
    
#   line 10301 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1456:
    __quex_debug("* terminal 1456:   '\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 200 "lexer.qx"
    
        if (self.string_delimiter == '\'')
        {
            self_accumulator_flush(TK_STRING);
            self << MAIN;
        }
        else
        {
            self_accumulator_add_character('\'');
        }
    
    
#   line 10324 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1457:
    __quex_debug("* terminal 1457:   [^\\\\\\\"']+\n");
    __QUEX_COUNT_VOID(&self, LexemeBegin, LexemeEnd);
    {
#   line 212 "lexer.qx"
        self_accumulator_add(LexemeBegin, LexemeEnd);
    
#   line 10336 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1458:
    __quex_debug("* terminal 1458:   \\\\n\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 215 "lexer.qx"
        self_accumulator_add_character('\n');
    
#   line 10349 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1459:
    __quex_debug("* terminal 1459:   \\\\t\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 216 "lexer.qx"
        self_accumulator_add_character('\t');
    
#   line 10362 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1460:
    __quex_debug("* terminal 1460:   \\\\a\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 217 "lexer.qx"
        self_accumulator_add_character('\a');
    
#   line 10375 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1461:
    __quex_debug("* terminal 1461:   \\\\b\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 218 "lexer.qx"
        self_accumulator_add_character('\b');
    
#   line 10388 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1462:
    __quex_debug("* terminal 1462:   \\\\f\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 219 "lexer.qx"
        self_accumulator_add_character('\f');
    
#   line 10401 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1463:
    __quex_debug("* terminal 1463:   \\\\r\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 220 "lexer.qx"
        self_accumulator_add_character('\r');
    
#   line 10414 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1464:
    __quex_debug("* terminal 1464:   \\\\v\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 221 "lexer.qx"
        self_accumulator_add_character('\v');
    
#   line 10427 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1465:
    __quex_debug("* terminal 1465:   \\\\\\\\\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 222 "lexer.qx"
        self_accumulator_add_character('\\');
    
#   line 10440 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1466:
    __quex_debug("* terminal 1466:   \\\\[0-7]{1,3}\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(LexemeL);
    QUEX_LEXEME_TERMINATING_ZERO_SET(&me->buffer);
    {
#   line 224 "lexer.qx"
        self_accumulator_add_character((QUEX_TYPE_CHARACTER)stoi(Lexeme+1,8));
    
#   line 10454 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1467:
    __quex_debug("* terminal 1467:   \\\\x[:xdigit:]{1,2}\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(LexemeL);
    QUEX_LEXEME_TERMINATING_ZERO_SET(&me->buffer);
    {
#   line 225 "lexer.qx"
        self_accumulator_add_character((QUEX_TYPE_CHARACTER)stoi(Lexeme+2,16));
    
#   line 10468 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1468:
    __quex_debug("* terminal 1468:   \\\\u[:xdigit:]{1,6}\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(LexemeL);
    QUEX_LEXEME_TERMINATING_ZERO_SET(&me->buffer);
    {
#   line 227 "lexer.qx"
    
        static_assert (sizeof(QUEX_TYPE_CHARACTER) == 1, "QUEX_TYPE_CHARACTER incompatible with utf-8" );
    
        long code = stoi(Lexeme+2,16); // code point
    
        //utf-8 encode:
        if(code < 0x0080) // code as ASCII
            self_accumulator_add_character((QUEX_TYPE_CHARACTER)code);
        else
        {
            //byte 1        byte 2   ... byte n
            //1...10x...x   10xxxxxx ... 10xxxxxx
            // n    8-n-1
    
            QUEX_TYPE_CHARACTER _char[4]; // character representation
            int len = 1; // char representation length-1
            if(code > 0x0800) ++len;
            if(code > 0x10000) ++len;
            if(code > 0x10FFFF) {
                    std::ostringstream ss;
                    ss << "Syntax error: Invalid code point: " <<
                        std::hex << code <<
                        " in string at line " <<
                        self.line_number() <<
                        " column " <<
                        self.column_number();
                    throw ParseError(ss.str());
            }
    
            for(int i=len; i>0; --i)
            {
                _char[i] = (code & 0b111111) | (1<<7);
                code >>= 6;
            }
            int mask = (0b111111 >> len);
            _char[0] = (code & mask) | (~(0b01000000>>len)^mask);
    
            self_accumulator_add(_char, _char+len+1);
        }
    
    
#   line 10521 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1469:
    __quex_debug("* terminal 1469:   \\\\'\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 268 "lexer.qx"
        self_accumulator_add_character('\'');
    
#   line 10534 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1470:
    __quex_debug("* terminal 1470:   \\\\\\\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 269 "lexer.qx"
        self_accumulator_add_character('\"');
    
#   line 10547 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;


_2121: /* TERMINAL: FAILURE */
    if(QUEX_NAME(Buffer_is_end_of_file)(&me->buffer)) {
        /* Init state is going to detect 'input == buffer limit code', and
         * enter the reload procedure, which will decide about 'end of stream'. */
    } else {
        /* In init state 'input = *input_p' and we need to increment
         * in order to avoid getting stalled. Else, input = *(input_p - 1),
         * so 'input_p' points already to the next character.                   */
        if( me->buffer._input_p == me->buffer._lexeme_start_p ) {
            /* Step over non-matching character */
            ++(me->buffer._input_p);
        }
    }
    __QUEX_COUNT_VOID(&self, LexemeBegin, LexemeEnd);
    QUEX_LEXEME_TERMINATING_ZERO_SET(&me->buffer);
    {
QUEX_ERROR_EXIT("\n    Match failure in mode 'STRING'.\n"
    "    No 'on_failure' section provided for this mode.\n"
    "    Proposal: Define 'on_failure' and analyze 'Lexeme'.\n");

    }
    goto __REENTRY_PREPARATION_2;


/* TERMINAL: END_OF_STREAM */
_1475:
__QUEX_IF_COUNT_SHIFT_VALUES();
    {
#   line 170 "lexer.qx"
    
        self << MAIN;
        throw ParseError("Syntax error: Unterminated string");
    
    
#   line 10587 "lexer.cpp"

    }
    /* End of Stream causes a return from the lexical analyzer, so that no
     * tokens can be filled after the termination token.                    */
    RETURN;

__REENTRY_PREPARATION:
    /* (*) Common point for **restarting** lexical analysis.
     *     at each time when CONTINUE is called at the end of a pattern.     */
 

    /* FAILURE needs not to run through 'on_after_match'. It enters here.    */
__REENTRY_PREPARATION_2:

#   undef Lexeme
#   undef LexemeBegin
#   undef LexemeEnd
#   undef LexemeNull
#   undef LexemeL

#   ifndef __QUEX_OPTION_PLAIN_ANALYZER_OBJECT
#   ifdef  QUEX_OPTION_TOKEN_POLICY_QUEUE
    if( QUEX_NAME(TokenQueue_is_full)(&self._token_queue) ) {
        return;
    }
#   else
    if( self_token_get_id() != __QUEX_SETTING_TOKEN_ID_UNINITIALIZED) {
        return __self_result_token_id;
    }
#   endif
#   endif


    /* Post context positions do not have to be reset or initialized. If a state
     * is reached which is associated with 'end of post context' it is clear what
     * post context is meant. This results from the ways the state machine is 
     * constructed. Post context position's live cycle:
     *
     * (1)   unitialized (don't care)
     * (1.b) on buffer reload it may, or may not be adapted (don't care)
     * (2)   when a post context begin state is passed, then it is **SET** (now: take care)
     * (2.b) on buffer reload it **is adapted**.
     * (3)   when a terminal state of the post context is reached (which can only be reached
     *       for that particular post context), then the post context position is used
     *       to reset the input position.                                              */

    /*  If a mode change happened, then the function must first return and
     *  indicate that another mode function is to be called. At this point, 
     *  we to force a 'return' on a mode change. 
     *
     *  Pseudo Code: if( previous_mode != current_mode ) {
     *                   return 0;
     *               }
     *
     *  When the analyzer returns, the caller function has to watch if a mode 
     *  change occurred. If not it can call this function again.             */
#   if    defined(QUEX_OPTION_AUTOMATIC_ANALYSIS_CONTINUATION_ON_MODE_CHANGE)        || defined(QUEX_OPTION_ASSERTS)
    if( me->DEBUG_analyzer_function_at_entry != me->current_analyzer_function ) 
#   endif
    { 
#       if defined(QUEX_OPTION_AUTOMATIC_ANALYSIS_CONTINUATION_ON_MODE_CHANGE)
        self_token_set_id(__QUEX_SETTING_TOKEN_ID_UNINITIALIZED);
        __QUEX_PURE_RETURN;
#       elif defined(QUEX_OPTION_ASSERTS)
        QUEX_ERROR_EXIT("Mode change without immediate return from the lexical analyzer.");
#       endif
    }

    goto __REENTRY;

    __quex_assert_no_passage();
__RELOAD_FORWARD:

    __quex_debug1("__RELOAD_FORWARD");
    __quex_assert(*(me->buffer._input_p) == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( me->buffer._memory._end_of_file_p == 0x0 ) {

        __quex_debug_reload_before(); /* Leave macro here to report source position. */
        QUEX_NAME(buffer_reload_forward)(&me->buffer, (QUEX_TYPE_CHARACTER_POSITION*)position, PositionRegisterN);

        __quex_debug_reload_after();
        QUEX_GOTO_STATE(target_state_index);
    }
    __quex_debug("reload impossible\n");
    QUEX_GOTO_STATE(target_state_else_index);
#   ifndef QUEX_OPTION_COMPUTED_GOTOS
    __quex_assert_no_passage();
__STATE_ROUTER:
    switch( target_state_index ) {
        case 1475: { goto _1475; }
        case 2399: { goto _2399; }
        case 2400: { goto _2400; }
        case 2401: { goto _2401; }
        case 2402: { goto _2402; }
        case 2403: { goto _2403; }
        case 2404: { goto _2404; }
        case 2405: { goto _2405; }
        case 2406: { goto _2406; }
        case 2407: { goto _2407; }
        case 2408: { goto _2408; }
        case 2409: { goto _2409; }
        case 2410: { goto _2410; }
        case 2411: { goto _2411; }
        case 2412: { goto _2412; }
        case 2413: { goto _2413; }
        case 2414: { goto _2414; }
        case 2415: { goto _2415; }
        case 2416: { goto _2416; }
        case 2417: { goto _2417; }
        case 2418: { goto _2418; }
        case 2419: { goto _2419; }
        case 2420: { goto _2420; }
        case 2421: { goto _2421; }
        case 2422: { goto _2422; }
        case 2423: { goto _2423; }
        case 2424: { goto _2424; }
        case 2425: { goto _2425; }
        case 2426: { goto _2426; }
        case 2427: { goto _2427; }
        case 2428: { goto _2428; }
        case 2429: { goto _2429; }
        case 2430: { goto _2430; }
        case 2433: { goto _2433; }
        case 2434: { goto _2434; }
        case 2435: { goto _2435; }
        case 2436: { goto _2436; }
        case 2437: { goto _2437; }
        case 2438: { goto _2438; }
        case 2440: { goto _2440; }
        case 2441: { goto _2441; }
        case 2442: { goto _2442; }
        case 2443: { goto _2443; }
        case 2444: { goto _2444; }
        case 2456: { goto _2456; }
        case 2457: { goto _2457; }
        case 2458: { goto _2458; }
        case 2461: { goto _2461; }
        case 2463: { goto _2463; }
        case 2464: { goto _2464; }
        case 2465: { goto _2465; }

        default:
            __QUEX_STD_fprintf(stderr, "State router: index = %i\n", (int)target_state_index);
            QUEX_ERROR_EXIT("State router: unknown index.\n");
    }
#   endif /* QUEX_OPTION_COMPUTED_GOTOS */

    /* Prevent compiler warning 'unused variable': use variables once in a part of the code*/
    /* that is never reached (and deleted by the compiler anyway).*/
    (void)QUEX_LEXEME_NULL;
    (void)QUEX_NAME_TOKEN(DumpedTokenIdObject);
    QUEX_ERROR_EXIT("Unreachable code has been reached.\n");
#   undef MAIN
#   undef STRING
#   undef self
}
#include <quex/code_base/temporary_macros_off>
QUEX_NAMESPACE_MAIN_CLOSE


QUEX_NAMESPACE_TOKEN_OPEN

const char*
QUEX_NAME_TOKEN(map_id_to_name)(const QUEX_TYPE_TOKEN_ID TokenID)
{
   static char  error_string[64];
   static const char  uninitialized_string[] = "<UNINITIALIZED>";
   static const char  termination_string[]   = "<TERMINATION>";
#  if defined(QUEX_OPTION_INDENTATION_TRIGGER)
   static const char  indent_string[]        = "<INDENT>";
   static const char  dedent_string[]        = "<DEDENT>";
   static const char  nodent_string[]        = "<NODENT>";
#  endif
   static const char  token_id_str_AND[]           = "AND";
   static const char  token_id_str_ASSIG[]         = "ASSIG";
   static const char  token_id_str_BREAK[]         = "BREAK";
   static const char  token_id_str_CBL[]           = "CBL";
   static const char  token_id_str_CBR[]           = "CBR";
   static const char  token_id_str_CLASS[]         = "CLASS";
   static const char  token_id_str_COMMA[]         = "COMMA";
   static const char  token_id_str_DEF[]           = "DEF";
   static const char  token_id_str_DIV[]           = "DIV";
   static const char  token_id_str_DO[]            = "DO";
   static const char  token_id_str_DOT[]           = "DOT";
   static const char  token_id_str_ELSE[]          = "ELSE";
   static const char  token_id_str_ELSEIF[]        = "ELSEIF";
   static const char  token_id_str_END[]           = "END";
   static const char  token_id_str_EOS[]           = "EOS";
   static const char  token_id_str_EQ[]            = "EQ";
   static const char  token_id_str_EXP[]           = "EXP";
   static const char  token_id_str_FALSE[]         = "FALSE";
   static const char  token_id_str_FOR[]           = "FOR";
   static const char  token_id_str_G[]             = "G";
   static const char  token_id_str_GEQ[]           = "GEQ";
   static const char  token_id_str_GLOBAL[]        = "GLOBAL";
   static const char  token_id_str_IDENT[]         = "IDENT";
   static const char  token_id_str_IF[]            = "IF";
   static const char  token_id_str_IN[]            = "IN";
   static const char  token_id_str_INT[]           = "INT";
   static const char  token_id_str_L[]             = "L";
   static const char  token_id_str_LEQ[]           = "LEQ";
   static const char  token_id_str_LOCAL[]         = "LOCAL";
   static const char  token_id_str_MINUS[]         = "MINUS";
   static const char  token_id_str_MOD[]           = "MOD";
   static const char  token_id_str_MUL[]           = "MUL";
   static const char  token_id_str_NEQ[]           = "NEQ";
   static const char  token_id_str_NEXT[]          = "NEXT";
   static const char  token_id_str_NIL[]           = "NIL";
   static const char  token_id_str_NL[]            = "NL";
   static const char  token_id_str_NOT[]           = "NOT";
   static const char  token_id_str_OR[]            = "OR";
   static const char  token_id_str_PIPE[]          = "PIPE";
   static const char  token_id_str_PL[]            = "PL";
   static const char  token_id_str_PLUS[]          = "PLUS";
   static const char  token_id_str_PR[]            = "PR";
   static const char  token_id_str_RANGEOP[]       = "RANGEOP";
   static const char  token_id_str_REAL[]          = "REAL";
   static const char  token_id_str_REPEAT[]        = "REPEAT";
   static const char  token_id_str_RETURN[]        = "RETURN";
   static const char  token_id_str_SBL[]           = "SBL";
   static const char  token_id_str_SBR[]           = "SBR";
   static const char  token_id_str_SCOLON[]        = "SCOLON";
   static const char  token_id_str_STRING[]        = "STRING";
   static const char  token_id_str_THEN[]          = "THEN";
   static const char  token_id_str_TRUE[]          = "TRUE";
   static const char  token_id_str_UNTIL[]         = "UNTIL";
   static const char  token_id_str_WARNING[]       = "WARNING";
   static const char  token_id_str_WHILE[]         = "WHILE";
       

   /* NOTE: This implementation works only for token id types that are 
    *       some type of integer or enum. In case an alien type is to
    *       used, this function needs to be redefined.                  */
   switch( TokenID ) {
   default: {
       __QUEX_STD_sprintf(error_string, "<UNKNOWN TOKEN-ID: %i>", (int)TokenID);
       return error_string;
   }
   case TK_TERMINATION:    return termination_string;
   case TK_UNINITIALIZED:  return uninitialized_string;
#  if defined(QUEX_OPTION_INDENTATION_TRIGGER)
   case TK_INDENT:         return indent_string;
   case TK_DEDENT:         return dedent_string;
   case TK_NODENT:         return nodent_string;
#  endif
   case TK_AND:           return token_id_str_AND;
   case TK_ASSIG:         return token_id_str_ASSIG;
   case TK_BREAK:         return token_id_str_BREAK;
   case TK_CBL:           return token_id_str_CBL;
   case TK_CBR:           return token_id_str_CBR;
   case TK_CLASS:         return token_id_str_CLASS;
   case TK_COMMA:         return token_id_str_COMMA;
   case TK_DEF:           return token_id_str_DEF;
   case TK_DIV:           return token_id_str_DIV;
   case TK_DO:            return token_id_str_DO;
   case TK_DOT:           return token_id_str_DOT;
   case TK_ELSE:          return token_id_str_ELSE;
   case TK_ELSEIF:        return token_id_str_ELSEIF;
   case TK_END:           return token_id_str_END;
   case TK_EOS:           return token_id_str_EOS;
   case TK_EQ:            return token_id_str_EQ;
   case TK_EXP:           return token_id_str_EXP;
   case TK_FALSE:         return token_id_str_FALSE;
   case TK_FOR:           return token_id_str_FOR;
   case TK_G:             return token_id_str_G;
   case TK_GEQ:           return token_id_str_GEQ;
   case TK_GLOBAL:        return token_id_str_GLOBAL;
   case TK_IDENT:         return token_id_str_IDENT;
   case TK_IF:            return token_id_str_IF;
   case TK_IN:            return token_id_str_IN;
   case TK_INT:           return token_id_str_INT;
   case TK_L:             return token_id_str_L;
   case TK_LEQ:           return token_id_str_LEQ;
   case TK_LOCAL:         return token_id_str_LOCAL;
   case TK_MINUS:         return token_id_str_MINUS;
   case TK_MOD:           return token_id_str_MOD;
   case TK_MUL:           return token_id_str_MUL;
   case TK_NEQ:           return token_id_str_NEQ;
   case TK_NEXT:          return token_id_str_NEXT;
   case TK_NIL:           return token_id_str_NIL;
   case TK_NL:            return token_id_str_NL;
   case TK_NOT:           return token_id_str_NOT;
   case TK_OR:            return token_id_str_OR;
   case TK_PIPE:          return token_id_str_PIPE;
   case TK_PL:            return token_id_str_PL;
   case TK_PLUS:          return token_id_str_PLUS;
   case TK_PR:            return token_id_str_PR;
   case TK_RANGEOP:       return token_id_str_RANGEOP;
   case TK_REAL:          return token_id_str_REAL;
   case TK_REPEAT:        return token_id_str_REPEAT;
   case TK_RETURN:        return token_id_str_RETURN;
   case TK_SBL:           return token_id_str_SBL;
   case TK_SBR:           return token_id_str_SBR;
   case TK_SCOLON:        return token_id_str_SCOLON;
   case TK_STRING:        return token_id_str_STRING;
   case TK_THEN:          return token_id_str_THEN;
   case TK_TRUE:          return token_id_str_TRUE;
   case TK_UNTIL:         return token_id_str_UNTIL;
   case TK_WARNING:       return token_id_str_WARNING;
   case TK_WHILE:         return token_id_str_WHILE;

   }
}

QUEX_NAMESPACE_TOKEN_CLOSE

