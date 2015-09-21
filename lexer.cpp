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
    const QUEX_TYPE_CHARACTER      Skipper1484_Closer[2]          = { 0x2A, 0x2F,  };
    const QUEX_TYPE_CHARACTER      Skipper1484_Opener[2]          = { 0x2F, 0x2A,  };
    const size_t                   Skipper1481L                   = 1;
    const QUEX_TYPE_CHARACTER*     Skipper1484_OpenerEnd          = Skipper1484_Opener + (ptrdiff_t)2;
    const QUEX_TYPE_CHARACTER      Skipper1481[1]                 = { 0xA,  };
    const QUEX_TYPE_CHARACTER*     Skipper1484_Opener_it          = 0x0;
    size_t                         counter                        = 0;
    QUEX_TYPE_CHARACTER_POSITION   reference_p                    = (QUEX_TYPE_CHARACTER_POSITION)0x0;
    const size_t                   PositionRegisterN              = (size_t)0;
    const QUEX_TYPE_CHARACTER      Skipper1487[1]                 = { 0xA,  };
    QUEX_TYPE_ACCEPTANCE_ID        last_acceptance               /* un-initilized */;
    const size_t                   Skipper1487L                   = 1;
    void*                          position                       = (void*)0x0;
    QUEX_TYPE_GOTO_LABEL           target_state_else_index        = QUEX_GOTO_LABEL_VOID;
    const QUEX_TYPE_CHARACTER*     Skipper1484_CloserEnd          = Skipper1484_Closer + (ptrdiff_t)2;
    QUEX_TYPE_CHARACTER*           text_end                       = (QUEX_TYPE_CHARACTER*)0x0;
    QUEX_TYPE_CHARACTER            input                          = (QUEX_TYPE_CHARACTER)(0x00);
    const QUEX_TYPE_CHARACTER*     Skipper1484_Closer_it          = 0x0;
    QUEX_TYPE_GOTO_LABEL           target_state_index             = QUEX_GOTO_LABEL_VOID;
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
_2128: /* INIT_STATE_TRANSITION_BLOCK */
    input = *(me->buffer._input_p);
    __quex_debug("Init State\n");
    __quex_debug_state(1994);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1994, 1480);
        case 0x9: goto _2025;
        case 0xA: goto _2018;
        case 0xD: 
        case 0x20: goto _1995;
        case 0x21: goto _2009;
        case 0x22: goto _2023;
        case 0x23: goto _2029;
        case 0x25: goto _2031;
        case 0x27: goto _2007;
        case 0x28: goto _2014;
        case 0x29: goto _2016;
        case 0x2A: goto _1997;
        case 0x2B: goto _2036;
        case 0x2C: goto _2020;
        case 0x2D: goto _2037;
        case 0x2E: goto _2013;
        case 0x2F: goto _2005;
        case 0x30: goto _2129;
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: goto _2130;
        case 0x3A: goto _1999;
        case 0x3B: goto _2021;
        case 0x3C: goto _2032;
        case 0x3D: goto _2026;
        case 0x3E: goto _1996;
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
        case 0x5A: goto _2017;
        case 0x5B: goto _2024;
        case 0x5D: goto _2027;
        case 0x5E: goto _2035;
        case 0x5F: goto _2017;
        case 0x61: goto _2006;
        case 0x62: goto _2034;
        case 0x63: goto _2015;
        case 0x64: goto _2008;
        case 0x65: goto _2028;
        case 0x66: goto _2039;
        case 0x67: goto _1998;
        case 0x68: goto _2017;
        case 0x69: goto _2001;
        case 0x6A: 
        case 0x6B: goto _2017;
        case 0x6C: goto _2002;
        case 0x6D: goto _2017;
        case 0x6E: goto _2038;
        case 0x6F: goto _2003;
        case 0x70: 
        case 0x71: goto _2017;
        case 0x72: goto _2030;
        case 0x73: goto _2017;
        case 0x74: goto _2019;
        case 0x75: goto _2000;
        case 0x76: goto _2017;
        case 0x77: goto _2004;
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2017;
        case 0x7B: goto _2010;
        case 0x7C: goto _2033;
        case 0x7D: goto _2012;

    }
    __quex_debug_drop_out(1994);

goto _2132; /* TERMINAL_FAILURE */

_1994:


    ++(me->buffer._input_p);
    goto _2128;


    __quex_assert_no_passage();
_2017: /* (2017 from 2017) (2017 from 2015) (2017 from 2019) (2017 from 2030) (2017 from 2028) (2017 from 2034) (2017 from 2038) (2017 from 2041) (2017 from 2042) (2017 from 2039) (2017 from 2040) (2017 from 2045) (2017 from 2046) (2017 from 2043) (2017 from 2044) (2017 from 1994) (2017 from 1998) (2017 from 2001) (2017 from 2002) (2017 from 2000) (2017 from 2006) (2017 from 2003) (2017 from 2004) (2017 from 2008) (2017 from 2113) (2017 from 2114) (2017 from 2111) (2017 from 2112) (2017 from 2117) (2017 from 2118) (2017 from 2115) (2017 from 2116) (2017 from 2121) (2017 from 2122) (2017 from 2119) (2017 from 2120) (2017 from 2125) (2017 from 2126) (2017 from 2123) (2017 from 2124) (2017 from 2089) (2017 from 2090) (2017 from 2087) (2017 from 2088) (2017 from 2093) (2017 from 2094) (2017 from 2091) (2017 from 2092) (2017 from 2095) (2017 from 2096) (2017 from 2101) (2017 from 2102) (2017 from 2099) (2017 from 2100) (2017 from 2106) (2017 from 2103) (2017 from 2109) (2017 from 2110) (2017 from 2107) (2017 from 2108) (2017 from 2049) (2017 from 2050) (2017 from 2047) (2017 from 2048) (2017 from 2053) (2017 from 2054) (2017 from 2051) (2017 from 2052) (2017 from 2057) (2017 from 2058) (2017 from 2055) (2017 from 2056) (2017 from 2061) (2017 from 2062) (2017 from 2065) (2017 from 2066) (2017 from 2063) (2017 from 2064) (2017 from 2069) (2017 from 2070) (2017 from 2067) (2017 from 2068) (2017 from 2073) (2017 from 2074) (2017 from 2071) (2017 from 2072) (2017 from 2075) (2017 from 2076) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2017);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2017, 2133);
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
        case 0x7A: goto _2017;

    }
_2133:
    __quex_debug_drop_out(2017);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2082: /* (2082 from 2081) (2082 from 2080) (2082 from 2022) (2082 from 2086) (2082 from 2011) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2082);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2082, 2134);
        case 0x2B: 
        case 0x2D: goto _2084;
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: goto _2083;

    }
_2134:
    __quex_debug_drop_out(2082);
switch( last_acceptance ) {
    case 1451: me->buffer._input_p -= 1;  goto TERMINAL_1451;
    case 1452: me->buffer._input_p -= 1;  goto TERMINAL_1452;
    case 1454: me->buffer._input_p -= 1;  goto TERMINAL_1454;

}

    __quex_assert_no_passage();
_2085: /* (2085 from 2085) (2085 from 2079) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2085);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2085, 2135);
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
        case 0x66: goto _2085;

    }
_2135:
    __quex_debug_drop_out(2085);
goto TERMINAL_1453;

    __quex_assert_no_passage();
_2078: /* (2078 from 2022) (2078 from 2011) (2078 from 2081) (2078 from 2080) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2078);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2078, 2136);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: goto _2137;

    }
_2136:
    __quex_debug_drop_out(2078);
switch( last_acceptance ) {
    case 1451: me->buffer._input_p -= 1;  goto TERMINAL_1451;
    case 1452: me->buffer._input_p -= 1;  goto TERMINAL_1452;
    case 1454: me->buffer._input_p -= 1;  goto TERMINAL_1454;

}

    __quex_assert_no_passage();
_2138: /* (2081 from 2081) (2081 from 2080) (2081 from 2022) */
    { last_acceptance = 1454; __quex_debug("last_acceptance = 1454\n"); }

_2081:

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2081);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2081, 2139);
        case 0x2E: goto _2078;
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: goto _2138;
        case 0x45: 
        case 0x65: goto _2082;

    }
_2139:
    __quex_debug_drop_out(2081);
goto TERMINAL_1454;

    __quex_assert_no_passage();
_2083: /* (2083 from 2083) (2083 from 2084) (2083 from 2082) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2083);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2083, 2140);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: goto _2083;

    }
_2140:
    __quex_debug_drop_out(2083);
goto TERMINAL_1454;

    __quex_assert_no_passage();
_2137: /* (2086 from 2086) (2086 from 2078) (2086 from 2013) */
    { last_acceptance = 1454; __quex_debug("last_acceptance = 1454\n"); }

_2086:

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2086);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2086, 2141);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: goto _2137;
        case 0x45: 
        case 0x65: goto _2082;

    }
_2141:
    __quex_debug_drop_out(2086);
goto TERMINAL_1454;

    __quex_assert_no_passage();
_2079: /* (2079 from 2022) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2079);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2079, 2142);
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
        case 0x66: goto _2085;

    }
_2142:
    __quex_debug_drop_out(2079);
me->buffer._input_p -= 1; 
goto TERMINAL_1451;

    __quex_assert_no_passage();
_2143: /* (2080 from 2080) (2080 from 2022) */
    { last_acceptance = 1451; __quex_debug("last_acceptance = 1451\n"); }

_2080:

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2080);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2080, 2144);
        case 0x2E: goto _2078;
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: goto _2143;
        case 0x38: 
        case 0x39: goto _2138;
        case 0x45: 
        case 0x65: goto _2082;

    }
_2144:
    __quex_debug_drop_out(2080);
goto TERMINAL_1451;

    __quex_assert_no_passage();
_2084: /* (2084 from 2082) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2084);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2084, 2145);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: goto _2083;

    }
_2145:
    __quex_debug_drop_out(2084);
switch( last_acceptance ) {
    case 1451: me->buffer._input_p -= 2;  goto TERMINAL_1451;
    case 1452: me->buffer._input_p -= 2;  goto TERMINAL_1452;
    case 1454: me->buffer._input_p -= 2;  goto TERMINAL_1454;

}

    __quex_assert_no_passage();
_2048: /* (2048 from 2038) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2048);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2048, 2146);
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
        case 0x77: goto _2017;
        case 0x78: goto _2051;
        case 0x79: 
        case 0x7A: goto _2017;

    }
_2146:
    __quex_debug_drop_out(2048);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2049: /* (2049 from 2038) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2049);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2049, 2147);
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
        case 0x73: goto _2017;
        case 0x74: goto _2050;
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2017;

    }
_2147:
    __quex_debug_drop_out(2049);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2050: /* (2050 from 2049) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2050);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2050, 2148);
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
        case 0x7A: goto _2017;

    }
_2148:
    __quex_debug_drop_out(2050);
goto TERMINAL_1425;

    __quex_assert_no_passage();
_2051: /* (2051 from 2048) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2051);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2051, 2149);
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
        case 0x73: goto _2017;
        case 0x74: goto _2052;
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2017;

    }
_2149:
    __quex_debug_drop_out(2051);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2052: /* (2052 from 2051) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2052);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2052, 2150);
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
        case 0x7A: goto _2017;

    }
_2150:
    __quex_debug_drop_out(2052);
goto TERMINAL_1417;

    __quex_assert_no_passage();
_2053: /* (2053 from 2047) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2053);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2053, 2151);
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
        case 0x7A: goto _2017;

    }
_2151:
    __quex_debug_drop_out(2053);
goto TERMINAL_1455;

    __quex_assert_no_passage();
_2054: /* (2054 from 2046) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2054);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2054, 2152);
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
        case 0x7A: goto _2017;

    }
_2152:
    __quex_debug_drop_out(2054);
goto TERMINAL_1420;

    __quex_assert_no_passage();
_2055: /* (2055 from 2034) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2055);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2055, 2153);
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
        case 0x64: goto _2017;
        case 0x65: goto _2056;
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
        case 0x7A: goto _2017;

    }
_2153:
    __quex_debug_drop_out(2055);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2056: /* (2056 from 2055) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2056);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2056, 2154);
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
        case 0x5F: goto _2017;
        case 0x61: goto _2057;
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
        case 0x7A: goto _2017;

    }
_2154:
    __quex_debug_drop_out(2056);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2057: /* (2057 from 2056) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2057);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2057, 2155);
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
        case 0x6A: goto _2017;
        case 0x6B: goto _2058;
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
        case 0x7A: goto _2017;

    }
_2155:
    __quex_debug_drop_out(2057);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2058: /* (2058 from 2057) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2058);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2058, 2156);
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
        case 0x7A: goto _2017;

    }
_2156:
    __quex_debug_drop_out(2058);
goto TERMINAL_1416;

    __quex_assert_no_passage();
_2059: /* (2059 from 2032) */

    ++(me->buffer._input_p);
    __quex_debug_state(2059);
    __quex_debug_drop_out(2059);
goto TERMINAL_1431;

    __quex_assert_no_passage();
_2060: /* (2060 from 2032) */

    ++(me->buffer._input_p);
    __quex_debug_state(2060);
    __quex_debug_drop_out(2060);
goto TERMINAL_1428;

    __quex_assert_no_passage();
_2061: /* (2061 from 2030) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2061);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2061, 2159);
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
        case 0x6F: goto _2017;
        case 0x70: goto _2063;
        case 0x71: 
        case 0x72: 
        case 0x73: goto _2017;
        case 0x74: goto _2062;
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2017;

    }
_2159:
    __quex_debug_drop_out(2061);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2062: /* (2062 from 2061) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2062);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2062, 2160);
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
        case 0x74: goto _2017;
        case 0x75: goto _2067;
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2017;

    }
_2160:
    __quex_debug_drop_out(2062);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2063: /* (2063 from 2061) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2063);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2063, 2161);
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
        case 0x64: goto _2017;
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
        case 0x7A: goto _2017;

    }
_2161:
    __quex_debug_drop_out(2063);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2064: /* (2064 from 2063) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2064);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2064, 2162);
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
        case 0x5F: goto _2017;
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
        case 0x7A: goto _2017;

    }
_2162:
    __quex_debug_drop_out(2064);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2065: /* (2065 from 2064) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2065);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2065, 2163);
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
        case 0x73: goto _2017;
        case 0x74: goto _2066;
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2017;

    }
_2163:
    __quex_debug_drop_out(2065);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2066: /* (2066 from 2065) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2066);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2066, 2164);
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
        case 0x7A: goto _2017;

    }
_2164:
    __quex_debug_drop_out(2066);
goto TERMINAL_1413;

    __quex_assert_no_passage();
_2067: /* (2067 from 2062) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2067);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2067, 2165);
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
        case 0x71: goto _2017;
        case 0x72: goto _2068;
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2017;

    }
_2165:
    __quex_debug_drop_out(2067);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2068: /* (2068 from 2067) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2068);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2068, 2166);
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
        case 0x6D: goto _2017;
        case 0x6E: goto _2069;
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
        case 0x7A: goto _2017;

    }
_2166:
    __quex_debug_drop_out(2068);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2069: /* (2069 from 2068) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2069);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2069, 2167);
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
        case 0x7A: goto _2017;

    }
_2167:
    __quex_debug_drop_out(2069);
goto TERMINAL_1415;

    __quex_assert_no_passage();
_2070: /* (2070 from 2028) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2070);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2070, 2168);
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
        case 0x63: goto _2017;
        case 0x64: goto _2076;
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
        case 0x7A: goto _2017;

    }
_2168:
    __quex_debug_drop_out(2070);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2071: /* (2071 from 2028) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2071);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2071, 2169);
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
        case 0x68: goto _2017;
        case 0x69: goto _2072;
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: goto _2017;
        case 0x73: goto _2073;
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2017;

    }
_2169:
    __quex_debug_drop_out(2071);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2072: /* (2072 from 2071) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2072);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2072, 2170);
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
        case 0x65: goto _2017;
        case 0x66: goto _2075;
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
        case 0x7A: goto _2017;

    }
_2170:
    __quex_debug_drop_out(2072);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2073: /* (2073 from 2071) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2073);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2073, 2171);
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
        case 0x64: goto _2017;
        case 0x65: goto _2074;
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
        case 0x7A: goto _2017;

    }
_2171:
    __quex_debug_drop_out(2073);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2074: /* (2074 from 2073) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2074);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2074, 2172);
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
        case 0x7A: goto _2017;

    }
_2172:
    __quex_debug_drop_out(2074);
goto TERMINAL_1408;

    __quex_assert_no_passage();
_2075: /* (2075 from 2072) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2075);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2075, 2173);
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
        case 0x7A: goto _2017;

    }
_2173:
    __quex_debug_drop_out(2075);
goto TERMINAL_1409;

    __quex_assert_no_passage();
_2076: /* (2076 from 2070) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2076);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2076, 2174);
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
        case 0x7A: goto _2017;

    }
_2174:
    __quex_debug_drop_out(2076);
goto TERMINAL_1405;

    __quex_assert_no_passage();
_2077: /* (2077 from 2026) */

    ++(me->buffer._input_p);
    __quex_debug_state(2077);
    __quex_debug_drop_out(2077);
goto TERMINAL_1432;

    __quex_assert_no_passage();
_2087: /* (2087 from 2019) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2087);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2087, 2176);
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
        case 0x64: goto _2017;
        case 0x65: goto _2091;
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
        case 0x7A: goto _2017;

    }
_2176:
    __quex_debug_drop_out(2087);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2088: /* (2088 from 2019) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2088);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2088, 2177);
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
        case 0x74: goto _2017;
        case 0x75: goto _2089;
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2017;

    }
_2177:
    __quex_debug_drop_out(2088);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2089: /* (2089 from 2088) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2089);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2089, 2178);
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
        case 0x64: goto _2017;
        case 0x65: goto _2090;
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
        case 0x7A: goto _2017;

    }
_2178:
    __quex_debug_drop_out(2089);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2090: /* (2090 from 2089) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2090);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2090, 2179);
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
        case 0x7A: goto _2017;

    }
_2179:
    __quex_debug_drop_out(2090);
goto TERMINAL_1421;

    __quex_assert_no_passage();
_2091: /* (2091 from 2087) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2091);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2091, 2180);
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
        case 0x6D: goto _2017;
        case 0x6E: goto _2092;
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
        case 0x7A: goto _2017;

    }
_2180:
    __quex_debug_drop_out(2091);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2092: /* (2092 from 2091) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2092);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2092, 2181);
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
        case 0x7A: goto _2017;

    }
_2181:
    __quex_debug_drop_out(2092);
goto TERMINAL_1407;

    __quex_assert_no_passage();
_2093: /* (2093 from 2015) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2093);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2093, 2182);
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
        case 0x5F: goto _2017;
        case 0x61: goto _2094;
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
        case 0x7A: goto _2017;

    }
_2182:
    __quex_debug_drop_out(2093);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2094: /* (2094 from 2093) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2094);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2094, 2183);
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
        case 0x72: goto _2017;
        case 0x73: goto _2095;
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2017;

    }
_2183:
    __quex_debug_drop_out(2094);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2095: /* (2095 from 2094) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2095);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2095, 2184);
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
        case 0x72: goto _2017;
        case 0x73: goto _2096;
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2017;

    }
_2184:
    __quex_debug_drop_out(2095);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2096: /* (2096 from 2095) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2096);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2096, 2185);
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
        case 0x7A: goto _2017;

    }
_2185:
    __quex_debug_drop_out(2096);
goto TERMINAL_1403;

    __quex_assert_no_passage();
_2097: /* (2097 from 2013) */

    ++(me->buffer._input_p);
    __quex_debug_state(2097);
    __quex_debug_drop_out(2097);
goto TERMINAL_1434;

    __quex_assert_no_passage();
_2098: /* (2098 from 2009) */

    ++(me->buffer._input_p);
    __quex_debug_state(2098);
    __quex_debug_drop_out(2098);
goto TERMINAL_1430;

    __quex_assert_no_passage();
_2099: /* (2099 from 2008) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2099);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2099, 2188);
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
        case 0x7A: goto _2017;

    }
_2188:
    __quex_debug_drop_out(2099);
goto TERMINAL_1404;

    __quex_assert_no_passage();
_2100: /* (2100 from 2008) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2100);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2100, 2189);
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
        case 0x65: goto _2017;
        case 0x66: goto _2101;
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
        case 0x7A: goto _2017;

    }
_2189:
    __quex_debug_drop_out(2100);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2101: /* (2101 from 2100) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2101);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2101, 2190);
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
        case 0x7A: goto _2017;

    }
_2190:
    __quex_debug_drop_out(2101);
goto TERMINAL_1402;

    __quex_assert_no_passage();
_2102: /* (2102 from 2006) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2102);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2102, 2191);
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
        case 0x63: goto _2017;
        case 0x64: goto _2103;
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
        case 0x7A: goto _2017;

    }
_2191:
    __quex_debug_drop_out(2102);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2103: /* (2103 from 2102) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2103);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2103, 2192);
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
        case 0x7A: goto _2017;

    }
_2192:
    __quex_debug_drop_out(2103);
goto TERMINAL_1424;

    __quex_assert_no_passage();
_2104: /* (2104 from 2005) */

    ++(me->buffer._input_p);
    __quex_debug_state(2104);
    __quex_debug_drop_out(2104);
goto TERMINAL_1396;

    __quex_assert_no_passage();
_2105: /* (2105 from 2005) */

    ++(me->buffer._input_p);
    __quex_debug_state(2105);
    __quex_debug_drop_out(2105);
goto TERMINAL_1397;

    __quex_assert_no_passage();
_2106: /* (2106 from 2004) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2106);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2106, 2195);
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
        case 0x68: goto _2017;
        case 0x69: goto _2107;
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
        case 0x7A: goto _2017;

    }
_2195:
    __quex_debug_drop_out(2106);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2107: /* (2107 from 2106) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2107);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2107, 2196);
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
        case 0x6B: goto _2017;
        case 0x6C: goto _2108;
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
        case 0x7A: goto _2017;

    }
_2196:
    __quex_debug_drop_out(2107);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2108: /* (2108 from 2107) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2108);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2108, 2197);
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
        case 0x64: goto _2017;
        case 0x65: goto _2109;
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
        case 0x7A: goto _2017;

    }
_2197:
    __quex_debug_drop_out(2108);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2109: /* (2109 from 2108) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2109);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2109, 2198);
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
        case 0x7A: goto _2017;

    }
_2198:
    __quex_debug_drop_out(2109);
goto TERMINAL_1410;

    __quex_assert_no_passage();
_2110: /* (2110 from 2003) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2110);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2110, 2199);
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
        case 0x7A: goto _2017;

    }
_2199:
    __quex_debug_drop_out(2110);
goto TERMINAL_1423;

    __quex_assert_no_passage();
_2111: /* (2111 from 2002) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2111);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2111, 2200);
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
        case 0x62: goto _2017;
        case 0x63: goto _2112;
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
        case 0x7A: goto _2017;

    }
_2200:
    __quex_debug_drop_out(2111);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2112: /* (2112 from 2111) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2112);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2112, 2201);
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
        case 0x5F: goto _2017;
        case 0x61: goto _2113;
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
        case 0x7A: goto _2017;

    }
_2201:
    __quex_debug_drop_out(2112);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2113: /* (2113 from 2112) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2113);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2113, 2202);
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
        case 0x6B: goto _2017;
        case 0x6C: goto _2114;
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
        case 0x7A: goto _2017;

    }
_2202:
    __quex_debug_drop_out(2113);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2114: /* (2114 from 2113) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2114);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2114, 2203);
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
        case 0x7A: goto _2017;

    }
_2203:
    __quex_debug_drop_out(2114);
goto TERMINAL_1418;

    __quex_assert_no_passage();
_2115: /* (2115 from 2001) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2115);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2115, 2204);
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
        case 0x65: goto _2017;
        case 0x66: goto _2117;
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
        case 0x7A: goto _2017;

    }
_2204:
    __quex_debug_drop_out(2115);
goto TERMINAL_1412;

    __quex_assert_no_passage();
_2116: /* (2116 from 2001) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2116);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2116, 2205);
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
        case 0x7A: goto _2017;

    }
_2205:
    __quex_debug_drop_out(2116);
goto TERMINAL_1406;

    __quex_assert_no_passage();
_2117: /* (2117 from 2115) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2117);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2117, 2206);
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
        case 0x7A: goto _2017;

    }
_2206:
    __quex_debug_drop_out(2117);
goto TERMINAL_1456;

    __quex_assert_no_passage();
_2118: /* (2118 from 2000) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2118);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2118, 2207);
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
        case 0x73: goto _2017;
        case 0x74: goto _2119;
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2017;

    }
_2207:
    __quex_debug_drop_out(2118);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2119: /* (2119 from 2118) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2119);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2119, 2208);
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
        case 0x68: goto _2017;
        case 0x69: goto _2120;
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
        case 0x7A: goto _2017;

    }
_2208:
    __quex_debug_drop_out(2119);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2120: /* (2120 from 2119) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2120);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2120, 2209);
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
        case 0x6B: goto _2017;
        case 0x6C: goto _2121;
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
        case 0x7A: goto _2017;

    }
_2209:
    __quex_debug_drop_out(2120);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2121: /* (2121 from 2120) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2121);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2121, 2210);
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
        case 0x7A: goto _2017;

    }
_2210:
    __quex_debug_drop_out(2121);
goto TERMINAL_1414;

    __quex_assert_no_passage();
_2122: /* (2122 from 1998) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2122);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2122, 2211);
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
        case 0x6E: goto _2017;
        case 0x6F: goto _2123;
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
        case 0x7A: goto _2017;

    }
_2211:
    __quex_debug_drop_out(2122);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2123: /* (2123 from 2122) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2123);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2123, 2212);
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
        case 0x61: goto _2017;
        case 0x62: goto _2124;
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
        case 0x7A: goto _2017;

    }
_2212:
    __quex_debug_drop_out(2123);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2124: /* (2124 from 2123) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2124);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2124, 2213);
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
        case 0x5F: goto _2017;
        case 0x61: goto _2125;
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
        case 0x7A: goto _2017;

    }
_2213:
    __quex_debug_drop_out(2124);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2125: /* (2125 from 2124) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2125);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2125, 2214);
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
        case 0x6B: goto _2017;
        case 0x6C: goto _2126;
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
        case 0x7A: goto _2017;

    }
_2214:
    __quex_debug_drop_out(2125);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2126: /* (2126 from 2125) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2126);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2126, 2215);
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
        case 0x7A: goto _2017;

    }
_2215:
    __quex_debug_drop_out(2126);
goto TERMINAL_1419;

    __quex_assert_no_passage();
_2127: /* (2127 from 1996) */

    ++(me->buffer._input_p);
    __quex_debug_state(2127);
    __quex_debug_drop_out(2127);
goto TERMINAL_1429;

    __quex_assert_no_passage();
_2130: /* (2011 from 2011) (2011 from 1994) */
    { last_acceptance = 1452; __quex_debug("last_acceptance = 1452\n"); }

_2011:

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2011);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2011, 2217);
        case 0x2E: goto _2078;
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: goto _2130;
        case 0x45: 
        case 0x65: goto _2082;

    }
_2217:
    __quex_debug_drop_out(2011);
goto TERMINAL_1452;

    __quex_assert_no_passage();
_2040: /* (2040 from 2039) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2040);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2040, 2218);
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
        case 0x6B: goto _2017;
        case 0x6C: goto _2043;
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
        case 0x7A: goto _2017;

    }
_2218:
    __quex_debug_drop_out(2040);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2041: /* (2041 from 2039) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2041);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2041, 2219);
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
        case 0x71: goto _2017;
        case 0x72: goto _2042;
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2017;

    }
_2219:
    __quex_debug_drop_out(2041);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2042: /* (2042 from 2041) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2042);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2042, 2220);
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
        case 0x7A: goto _2017;

    }
_2220:
    __quex_debug_drop_out(2042);
goto TERMINAL_1411;

    __quex_assert_no_passage();
_2043: /* (2043 from 2040) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2043);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2043, 2221);
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
        case 0x72: goto _2017;
        case 0x73: goto _2044;
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2017;

    }
_2221:
    __quex_debug_drop_out(2043);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2044: /* (2044 from 2043) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2044);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2044, 2222);
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
        case 0x64: goto _2017;
        case 0x65: goto _2045;
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
        case 0x7A: goto _2017;

    }
_2222:
    __quex_debug_drop_out(2044);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2045: /* (2045 from 2044) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2045);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2045, 2223);
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
        case 0x7A: goto _2017;

    }
_2223:
    __quex_debug_drop_out(2045);
goto TERMINAL_1422;

    __quex_assert_no_passage();
_2046: /* (2046 from 2038) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2046);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2046, 2224);
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
        case 0x6B: goto _2017;
        case 0x6C: goto _2054;
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
        case 0x7A: goto _2017;

    }
_2224:
    __quex_debug_drop_out(2046);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2047: /* (2047 from 2038) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2047);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2047, 2225);
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
        case 0x6D: goto _2017;
        case 0x6E: goto _2053;
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
        case 0x7A: goto _2017;

    }
_2225:
    __quex_debug_drop_out(2047);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_1995: /* (1995 from 1994) */

    ++(me->buffer._input_p);
    __quex_debug_state(1995);
    __quex_debug_drop_out(1995);
goto TERMINAL_1393;

    __quex_assert_no_passage();
_1996: /* (1996 from 1994) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1996);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1996, 2227);
        case 0x3D: goto _2127;

    }
_2227:
    __quex_debug_drop_out(1996);
goto TERMINAL_1427;

    __quex_assert_no_passage();
_1997: /* (1997 from 1994) */

    ++(me->buffer._input_p);
    __quex_debug_state(1997);
    __quex_debug_drop_out(1997);
goto TERMINAL_1437;

    __quex_assert_no_passage();
_1998: /* (1998 from 1994) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1998);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1998, 2229);
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
        case 0x6B: goto _2017;
        case 0x6C: goto _2122;
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
        case 0x7A: goto _2017;

    }
_2229:
    __quex_debug_drop_out(1998);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_1999: /* (1999 from 1994) */

    ++(me->buffer._input_p);
    __quex_debug_state(1999);
    __quex_debug_drop_out(1999);
goto TERMINAL_1433;

    __quex_assert_no_passage();
_2000: /* (2000 from 1994) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2000);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2000, 2231);
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
        case 0x6D: goto _2017;
        case 0x6E: goto _2118;
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
        case 0x7A: goto _2017;

    }
_2231:
    __quex_debug_drop_out(2000);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2001: /* (2001 from 1994) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2001);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2001, 2232);
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
        case 0x65: goto _2017;
        case 0x66: goto _2116;
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: goto _2017;
        case 0x6E: goto _2115;
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
        case 0x7A: goto _2017;

    }
_2232:
    __quex_debug_drop_out(2001);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2002: /* (2002 from 1994) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2002);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2002, 2233);
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
        case 0x6E: goto _2017;
        case 0x6F: goto _2111;
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
        case 0x7A: goto _2017;

    }
_2233:
    __quex_debug_drop_out(2002);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2003: /* (2003 from 1994) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2003);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2003, 2234);
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
        case 0x71: goto _2017;
        case 0x72: goto _2110;
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2017;

    }
_2234:
    __quex_debug_drop_out(2003);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2004: /* (2004 from 1994) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2004);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2004, 2235);
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
        case 0x67: goto _2017;
        case 0x68: goto _2106;
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
        case 0x7A: goto _2017;

    }
_2235:
    __quex_debug_drop_out(2004);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2005: /* (2005 from 1994) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2005);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2005, 2236);
        case 0x2A: goto _2104;
        case 0x2F: goto _2105;

    }
_2236:
    __quex_debug_drop_out(2005);
goto TERMINAL_1438;

    __quex_assert_no_passage();
_2006: /* (2006 from 1994) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2006);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2006, 2237);
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
        case 0x6D: goto _2017;
        case 0x6E: goto _2102;
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
        case 0x7A: goto _2017;

    }
_2237:
    __quex_debug_drop_out(2006);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2007: /* (2007 from 1994) */

    ++(me->buffer._input_p);
    __quex_debug_state(2007);
    __quex_debug_drop_out(2007);
goto TERMINAL_1401;

    __quex_assert_no_passage();
_2008: /* (2008 from 1994) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2008);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2008, 2239);
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
        case 0x64: goto _2017;
        case 0x65: goto _2100;
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: goto _2017;
        case 0x6F: goto _2099;
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
        case 0x7A: goto _2017;

    }
_2239:
    __quex_debug_drop_out(2008);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2009: /* (2009 from 1994) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2009);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2009, 2240);
        case 0x3D: goto _2098;

    }
_2240:
    __quex_debug_drop_out(2009);

goto _2132; /* TERMINAL_FAILURE */

    __quex_assert_no_passage();
_2010: /* (2010 from 1994) */

    ++(me->buffer._input_p);
    __quex_debug_state(2010);
    __quex_debug_drop_out(2010);
goto TERMINAL_1447;

    __quex_assert_no_passage();
_2012: /* (2012 from 1994) */

    ++(me->buffer._input_p);
    __quex_debug_state(2012);
    __quex_debug_drop_out(2012);
goto TERMINAL_1448;

    __quex_assert_no_passage();
_2013: /* (2013 from 1994) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2013);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2013, 2243);
        case 0x2E: goto _2097;
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: goto _2137;

    }
_2243:
    __quex_debug_drop_out(2013);
goto TERMINAL_1444;

    __quex_assert_no_passage();
_2014: /* (2014 from 1994) */

    ++(me->buffer._input_p);
    __quex_debug_state(2014);
    __quex_debug_drop_out(2014);
goto TERMINAL_1449;

    __quex_assert_no_passage();
_2015: /* (2015 from 1994) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2015);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2015, 2245);
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
        case 0x6B: goto _2017;
        case 0x6C: goto _2093;
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
        case 0x7A: goto _2017;

    }
_2245:
    __quex_debug_drop_out(2015);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2016: /* (2016 from 1994) */

    ++(me->buffer._input_p);
    __quex_debug_state(2016);
    __quex_debug_drop_out(2016);
goto TERMINAL_1450;

    __quex_assert_no_passage();
_2018: /* (2018 from 1994) */

    ++(me->buffer._input_p);
    __quex_debug_state(2018);
    __quex_debug_drop_out(2018);
goto TERMINAL_1398;

    __quex_assert_no_passage();
_2019: /* (2019 from 1994) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2019);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2019, 2248);
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
        case 0x67: goto _2017;
        case 0x68: goto _2087;
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: goto _2017;
        case 0x72: goto _2088;
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2017;

    }
_2248:
    __quex_debug_drop_out(2019);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2020: /* (2020 from 1994) */

    ++(me->buffer._input_p);
    __quex_debug_state(2020);
    __quex_debug_drop_out(2020);
goto TERMINAL_1443;

    __quex_assert_no_passage();
_2021: /* (2021 from 1994) */

    ++(me->buffer._input_p);
    __quex_debug_state(2021);
    __quex_debug_drop_out(2021);
goto TERMINAL_1399;

    __quex_assert_no_passage();
_2129: /* (2022 from 1994) */
    { last_acceptance = 1451; __quex_debug("last_acceptance = 1451\n"); }

_2022:

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2022);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2022, 2251);
        case 0x2E: goto _2078;
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: goto _2143;
        case 0x38: 
        case 0x39: goto _2138;
        case 0x45: goto _2082;
        case 0x58: goto _2079;
        case 0x65: goto _2082;
        case 0x78: goto _2079;

    }
_2251:
    __quex_debug_drop_out(2022);
goto TERMINAL_1451;

    __quex_assert_no_passage();
_2023: /* (2023 from 1994) */

    ++(me->buffer._input_p);
    __quex_debug_state(2023);
    __quex_debug_drop_out(2023);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_2024: /* (2024 from 1994) */

    ++(me->buffer._input_p);
    __quex_debug_state(2024);
    __quex_debug_drop_out(2024);
goto TERMINAL_1445;

    __quex_assert_no_passage();
_2025: /* (2025 from 1994) */

    ++(me->buffer._input_p);
    __quex_debug_state(2025);
    __quex_debug_drop_out(2025);
goto TERMINAL_1394;

    __quex_assert_no_passage();
_2026: /* (2026 from 1994) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2026);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2026, 2255);
        case 0x3D: goto _2077;

    }
_2255:
    __quex_debug_drop_out(2026);
goto TERMINAL_1442;

    __quex_assert_no_passage();
_2027: /* (2027 from 1994) */

    ++(me->buffer._input_p);
    __quex_debug_state(2027);
    __quex_debug_drop_out(2027);
goto TERMINAL_1446;

    __quex_assert_no_passage();
_2028: /* (2028 from 1994) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2028);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2028, 2257);
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
        case 0x6B: goto _2017;
        case 0x6C: goto _2071;
        case 0x6D: goto _2017;
        case 0x6E: goto _2070;
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
        case 0x7A: goto _2017;

    }
_2257:
    __quex_debug_drop_out(2028);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2029: /* (2029 from 1994) */

    ++(me->buffer._input_p);
    __quex_debug_state(2029);
    __quex_debug_drop_out(2029);
goto TERMINAL_1395;

    __quex_assert_no_passage();
_2030: /* (2030 from 1994) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2030);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2030, 2259);
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
        case 0x64: goto _2017;
        case 0x65: goto _2061;
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
        case 0x7A: goto _2017;

    }
_2259:
    __quex_debug_drop_out(2030);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2031: /* (2031 from 1994) */

    ++(me->buffer._input_p);
    __quex_debug_state(2031);
    __quex_debug_drop_out(2031);
goto TERMINAL_1439;

    __quex_assert_no_passage();
_2032: /* (2032 from 1994) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2032);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2032, 2261);
        case 0x3D: goto _2060;
        case 0x3E: goto _2059;

    }
_2261:
    __quex_debug_drop_out(2032);
goto TERMINAL_1426;

    __quex_assert_no_passage();
_2033: /* (2033 from 1994) */

    ++(me->buffer._input_p);
    __quex_debug_state(2033);
    __quex_debug_drop_out(2033);
goto TERMINAL_1440;

    __quex_assert_no_passage();
_2034: /* (2034 from 1994) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2034);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2034, 2263);
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
        case 0x71: goto _2017;
        case 0x72: goto _2055;
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _2017;

    }
_2263:
    __quex_debug_drop_out(2034);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2035: /* (2035 from 1994) */

    ++(me->buffer._input_p);
    __quex_debug_state(2035);
    __quex_debug_drop_out(2035);
goto TERMINAL_1441;

    __quex_assert_no_passage();
_2036: /* (2036 from 1994) */

    ++(me->buffer._input_p);
    __quex_debug_state(2036);
    __quex_debug_drop_out(2036);
goto TERMINAL_1435;

    __quex_assert_no_passage();
_2037: /* (2037 from 1994) */

    ++(me->buffer._input_p);
    __quex_debug_state(2037);
    __quex_debug_drop_out(2037);
goto TERMINAL_1436;

    __quex_assert_no_passage();
_2038: /* (2038 from 1994) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2038);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2038, 2267);
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
        case 0x5F: goto _2017;
        case 0x61: goto _2047;
        case 0x62: 
        case 0x63: 
        case 0x64: goto _2017;
        case 0x65: goto _2048;
        case 0x66: 
        case 0x67: 
        case 0x68: goto _2017;
        case 0x69: goto _2046;
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: goto _2017;
        case 0x6F: goto _2049;
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
        case 0x7A: goto _2017;

    }
_2267:
    __quex_debug_drop_out(2038);
goto TERMINAL_1457;

    __quex_assert_no_passage();
_2039: /* (2039 from 1994) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2039);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2039, 2268);
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
        case 0x5F: goto _2017;
        case 0x61: goto _2040;
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
        case 0x6E: goto _2017;
        case 0x6F: goto _2041;
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
        case 0x7A: goto _2017;

    }
_2268:
    __quex_debug_drop_out(2039);
goto TERMINAL_1457;
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

TERMINAL_1393:
    __quex_debug("* terminal 1393:   <skip: ... (check also base modes)>\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 56 "lexer.qx"
    goto __SKIP;
    
#   line 7763 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1394:
    __quex_debug("* terminal 1394:   <skip>\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_end &= ~ ((size_t)0x3));
__QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_end += 4);

    {
__SKIP:
    /* Character Set Skipper: ''\t', '\r', ' '' */
    QUEX_BUFFER_ASSERT_CONSISTENCY(&me->buffer);
__QUEX_IF_COUNT_COLUMNS(reference_p = me->buffer._input_p);
    while( 1 + 1 == 2 ) {
_1477:
        if( (*me->buffer._input_p) < 0xD ) {
            switch( (*me->buffer._input_p) ) {
                case 0x0: QUEX_GOTO_RELOAD(_1479, 1477, 1480);
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
_1479:

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

TERMINAL_1395:
    __quex_debug("* terminal 1395:   \"#\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
        /*                          Delimiter: '\n',  */
    
        text_end = QUEX_NAME(Buffer_text_end)(&me->buffer);
    
    
    _1482:
    
        QUEX_BUFFER_ASSERT_CONSISTENCY(&me->buffer);
        __quex_assert(QUEX_NAME(Buffer_content_size)(&me->buffer) >= Skipper1481L );
    
        /* NOTE: If _input_p == end of buffer, then it will drop out immediately out of the
            *       loop below and drop into the buffer reload procedure.                      */
    
        /* Loop eating characters: Break-out as soon as the First Character of the Delimiter
            * (FCD) is reached. Thus, the FCD plays also the role of the Buffer Limit Code. There
            * are two reasons for break-out:
            *    (1) we reached a limit (end-of-file or buffer-limit)
            *    (2) there was really the FCD in the character stream
            * This must be distinguished after the loop was exited. But, during the 'swallowing' we
            * are very fast, because we do not have to check for two different characters.        */
        *text_end = Skipper1481[0]; /* Overwrite BufferLimitCode (BLC).  */
    _1481_LOOP:
                input = *(me->buffer._input_p);
    
                if( input == Skipper1481[0] ) {
    
                        goto _1481_LOOP_EXIT;
                }
    
        ++(me->buffer._input_p); /* Now, BLC cannot occur. See above. */
        goto _1481_LOOP;
    _1481_LOOP_EXIT:
    
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
        if( QUEX_NAME(Buffer_distance_input_to_text_end)(&me->buffer) < (ptrdiff_t)Skipper1481L ) {
                /* (2.1) Reload required. */
                goto _1483;
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
    
    _1483:
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
                goto _1482;
        }
        /* Here, either the loading failed or it is not enough space to carry a closing delimiter */
        me->buffer._input_p = me->buffer._lexeme_start_p;
#define Closer "\n"
#   line 74 "lexer.qx"
    
                self_write_token_p()->text = "Warning: Unterminated comment";
                self_send(TK_WARNING);
    
    
#   line 7971 "lexer.cpp"
#undef  Closer
    RETURN;

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1396:
    __quex_debug("* terminal 1396:   \"/*\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
        Skipper1484_Opener_it = (QUEX_TYPE_CHARACTER*)Skipper1484_Opener;
        Skipper1484_Closer_it = (QUEX_TYPE_CHARACTER*)Skipper1484_Closer;
        /* text_end                           = QUEX_NAME(Buffer_text_end)(&me->buffer); */
        __QUEX_IF_COUNT_COLUMNS(reference_p = QUEX_NAME(Buffer_tell_memory_adr)(&me->buffer));
    
    
    _1485:
    
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
                        goto _1486;
                }
                if( input == *Skipper1484_Closer_it ) {
                        ++Skipper1484_Closer_it;
                        if( Skipper1484_Closer_it == Skipper1484_CloserEnd ) {
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
                            Skipper1484_Opener_it = (QUEX_TYPE_CHARACTER*)Skipper1484_Opener;
                            Skipper1484_Closer_it = (QUEX_TYPE_CHARACTER*)Skipper1484_Closer;
                            goto CONTINUE_1484;
                        }
                } else {
                        Skipper1484_Closer_it = (QUEX_TYPE_CHARACTER*)Skipper1484_Closer;
                }
                if( input == *Skipper1484_Opener_it ) {
                        ++Skipper1484_Opener_it;
                        if( Skipper1484_Opener_it == Skipper1484_OpenerEnd ) {
                            ++counter;
                            Skipper1484_Opener_it = (QUEX_TYPE_CHARACTER*)Skipper1484_Opener;
                            Skipper1484_Closer_it = (QUEX_TYPE_CHARACTER*)Skipper1484_Closer;
                            goto CONTINUE_1484;
                        }
                } else {
                        Skipper1484_Opener_it = (QUEX_TYPE_CHARACTER*)Skipper1484_Opener;
                }
    CONTINUE_1484:
    
        __QUEX_IF_COUNT_IF( input == (QUEX_TYPE_CHARACTER)'\n' ) {
                __QUEX_IF_COUNT_LINES_ADD((size_t)1);
                __QUEX_IF_COUNT_COLUMNS_SET((size_t)0);
                __QUEX_IF_COUNT_COLUMNS(reference_p = QUEX_NAME(Buffer_tell_memory_adr)(&me->buffer));
        }
    
                ++(me->buffer._input_p); /* Now, BLC cannot occur. See above. */
        }
    
    _1486:
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
                goto _1485; /* End of range reached.             */
        }
        /* Here, either the loading failed or it is not enough space to carry a closing delimiter */
        me->buffer._input_p = me->buffer._lexeme_start_p;
#define Closer "*/"
#   line 74 "lexer.qx"
    
                self_write_token_p()->text = "Warning: Unterminated comment";
                self_send(TK_WARNING);
    
    
#   line 8088 "lexer.cpp"
#undef  Closer
    RETURN;

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1397:
    __quex_debug("* terminal 1397:   \"//\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
        /*                          Delimiter: '\n',  */
    
        text_end = QUEX_NAME(Buffer_text_end)(&me->buffer);
    
    
    _1488:
    
        QUEX_BUFFER_ASSERT_CONSISTENCY(&me->buffer);
        __quex_assert(QUEX_NAME(Buffer_content_size)(&me->buffer) >= Skipper1487L );
    
        /* NOTE: If _input_p == end of buffer, then it will drop out immediately out of the
            *       loop below and drop into the buffer reload procedure.                      */
    
        /* Loop eating characters: Break-out as soon as the First Character of the Delimiter
            * (FCD) is reached. Thus, the FCD plays also the role of the Buffer Limit Code. There
            * are two reasons for break-out:
            *    (1) we reached a limit (end-of-file or buffer-limit)
            *    (2) there was really the FCD in the character stream
            * This must be distinguished after the loop was exited. But, during the 'swallowing' we
            * are very fast, because we do not have to check for two different characters.        */
        *text_end = Skipper1487[0]; /* Overwrite BufferLimitCode (BLC).  */
    _1487_LOOP:
                input = *(me->buffer._input_p);
    
                if( input == Skipper1487[0] ) {
    
                        goto _1487_LOOP_EXIT;
                }
    
        ++(me->buffer._input_p); /* Now, BLC cannot occur. See above. */
        goto _1487_LOOP;
    _1487_LOOP_EXIT:
    
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
        if( QUEX_NAME(Buffer_distance_input_to_text_end)(&me->buffer) < (ptrdiff_t)Skipper1487L ) {
                /* (2.1) Reload required. */
                goto _1489;
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
    
    _1489:
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
                goto _1488;
        }
        /* Here, either the loading failed or it is not enough space to carry a closing delimiter */
        me->buffer._input_p = me->buffer._lexeme_start_p;
#define Closer "\n"
#   line 74 "lexer.qx"
    
                self_write_token_p()->text = "Warning: Unterminated comment";
                self_send(TK_WARNING);
    
    
#   line 8221 "lexer.cpp"
#undef  Closer
    RETURN;

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1398:
    __quex_debug("* terminal 1398:   \"\\n\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_LINES_ADD(1);
__QUEX_IF_COUNT_COLUMNS_SET(1);
    {
#   line 79 "lexer.qx"
    self_send(TK_NL);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8238 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1399:
    __quex_debug("* terminal 1399:   \";\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 80 "lexer.qx"
    self_send(TK_SCOLON);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8252 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1400:
    __quex_debug("* terminal 1400:   \"\\\"\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 85 "lexer.qx"
        self.string_delimiter='\"'; self << STRING;
    
#   line 8265 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1401:
    __quex_debug("* terminal 1401:   '\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 86 "lexer.qx"
        self.string_delimiter='\''; self << STRING;
    
#   line 8278 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1402:
    __quex_debug("* terminal 1402:   def\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(3);
    {
#   line 89 "lexer.qx"
    self_send(TK_DEF);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8292 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1403:
    __quex_debug("* terminal 1403:   class\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(5);
    {
#   line 90 "lexer.qx"
    self_send(TK_CLASS);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8306 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1404:
    __quex_debug("* terminal 1404:   do\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 91 "lexer.qx"
    self_send(TK_DO);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8320 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1405:
    __quex_debug("* terminal 1405:   end\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(3);
    {
#   line 92 "lexer.qx"
    self_send(TK_END);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8334 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1406:
    __quex_debug("* terminal 1406:   if\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 94 "lexer.qx"
    self_send(TK_IF);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8348 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1407:
    __quex_debug("* terminal 1407:   then\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(4);
    {
#   line 95 "lexer.qx"
    self_send(TK_THEN);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8362 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1408:
    __quex_debug("* terminal 1408:   else\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(4);
    {
#   line 96 "lexer.qx"
    self_send(TK_ELSE);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8376 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1409:
    __quex_debug("* terminal 1409:   elif\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(4);
    {
#   line 97 "lexer.qx"
    self_send(TK_ELSEIF);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8390 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1410:
    __quex_debug("* terminal 1410:   while\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(5);
    {
#   line 98 "lexer.qx"
    self_send(TK_WHILE);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8404 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1411:
    __quex_debug("* terminal 1411:   for\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(3);
    {
#   line 99 "lexer.qx"
    self_send(TK_FOR);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8418 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1412:
    __quex_debug("* terminal 1412:   in\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 100 "lexer.qx"
    self_send(TK_IN);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8432 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1413:
    __quex_debug("* terminal 1413:   repeat\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(6);
    {
#   line 101 "lexer.qx"
    self_send(TK_REPEAT);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8446 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1414:
    __quex_debug("* terminal 1414:   until\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(5);
    {
#   line 102 "lexer.qx"
    self_send(TK_UNTIL);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8460 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1415:
    __quex_debug("* terminal 1415:   return\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(6);
    {
#   line 104 "lexer.qx"
    self_send(TK_RETURN);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8474 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1416:
    __quex_debug("* terminal 1416:   break\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(5);
    {
#   line 105 "lexer.qx"
    self_send(TK_BREAK);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8488 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1417:
    __quex_debug("* terminal 1417:   next\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(4);
    {
#   line 106 "lexer.qx"
    self_send(TK_NEXT);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8502 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1418:
    __quex_debug("* terminal 1418:   local\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(5);
    {
#   line 108 "lexer.qx"
    self_send(TK_LOCAL);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8516 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1419:
    __quex_debug("* terminal 1419:   global\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(6);
    {
#   line 109 "lexer.qx"
    self_send(TK_GLOBAL);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8530 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1420:
    __quex_debug("* terminal 1420:   nil\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(3);
    {
#   line 111 "lexer.qx"
    self_send(TK_NIL);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8544 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1421:
    __quex_debug("* terminal 1421:   true\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(4);
    {
#   line 112 "lexer.qx"
    self_send(TK_TRUE);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8558 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1422:
    __quex_debug("* terminal 1422:   false\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(5);
    {
#   line 113 "lexer.qx"
    self_send(TK_FALSE);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8572 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1423:
    __quex_debug("* terminal 1423:   or\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 116 "lexer.qx"
    self_send(TK_OR);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8586 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1424:
    __quex_debug("* terminal 1424:   and\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(3);
    {
#   line 117 "lexer.qx"
    self_send(TK_AND);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8600 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1425:
    __quex_debug("* terminal 1425:   not\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(3);
    {
#   line 118 "lexer.qx"
    self_send(TK_NOT);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8614 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1426:
    __quex_debug("* terminal 1426:   <\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 119 "lexer.qx"
    self_send(TK_L);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8628 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1427:
    __quex_debug("* terminal 1427:   >\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 120 "lexer.qx"
    self_send(TK_G);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8642 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1428:
    __quex_debug("* terminal 1428:   <=\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 121 "lexer.qx"
    self_send(TK_LEQ);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8656 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1429:
    __quex_debug("* terminal 1429:   >=\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 122 "lexer.qx"
    self_send(TK_GEQ);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8670 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1430:
    __quex_debug("* terminal 1430:   !=\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 123 "lexer.qx"
    self_send(TK_NEQ);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8684 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1431:
    __quex_debug("* terminal 1431:   <>\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 124 "lexer.qx"
    self_send(TK_NEQ);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8698 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1432:
    __quex_debug("* terminal 1432:   ==\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 125 "lexer.qx"
    self_send(TK_EQ);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8712 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1433:
    __quex_debug("* terminal 1433:   \":\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 127 "lexer.qx"
    self_send(TK_COLON);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8726 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1434:
    __quex_debug("* terminal 1434:   \"..\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 128 "lexer.qx"
    self_send(TK_RANGEOP);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8740 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1435:
    __quex_debug("* terminal 1435:   \"+\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 129 "lexer.qx"
    self_send(TK_PLUS);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8754 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1436:
    __quex_debug("* terminal 1436:   \"-\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 130 "lexer.qx"
    self_send(TK_MINUS);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8768 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1437:
    __quex_debug("* terminal 1437:   \"*\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 131 "lexer.qx"
    self_send(TK_MUL);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8782 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1438:
    __quex_debug("* terminal 1438:   \"/\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 132 "lexer.qx"
    self_send(TK_DIV);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8796 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1439:
    __quex_debug("* terminal 1439:   \"%\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 133 "lexer.qx"
    self_send(TK_MOD);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8810 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1440:
    __quex_debug("* terminal 1440:   \"|\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 134 "lexer.qx"
    self_send(TK_PIPE);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8824 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1441:
    __quex_debug("* terminal 1441:   \"^\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 135 "lexer.qx"
    self_send(TK_EXP);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8838 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1442:
    __quex_debug("* terminal 1442:   \"=\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 136 "lexer.qx"
    self_send(TK_ASSIG);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8852 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1443:
    __quex_debug("* terminal 1443:   \",\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 139 "lexer.qx"
    self_send(TK_COMMA);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8866 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1444:
    __quex_debug("* terminal 1444:   \".\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 140 "lexer.qx"
    self_send(TK_DOT);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8880 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1445:
    __quex_debug("* terminal 1445:   \"[\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 142 "lexer.qx"
    self_send(TK_SBL);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8894 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1446:
    __quex_debug("* terminal 1446:   \"]\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 143 "lexer.qx"
    self_send(TK_SBR);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8908 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1447:
    __quex_debug("* terminal 1447:   \"{\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 144 "lexer.qx"
    self_send(TK_CBL);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8922 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1448:
    __quex_debug("* terminal 1448:   \"}\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 145 "lexer.qx"
    self_send(TK_CBR);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8936 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1449:
    __quex_debug("* terminal 1449:   \"(\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 146 "lexer.qx"
    self_send(TK_PL);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8950 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1450:
    __quex_debug("* terminal 1450:   \")\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 147 "lexer.qx"
    self_send(TK_PR);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8964 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1451:
    __quex_debug("* terminal 1451:   0[0-7]*\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(LexemeL);
    QUEX_LEXEME_TERMINATING_ZERO_SET(&me->buffer);
    {
#   line 151 "lexer.qx"
    self_write_token_p()->content.integer = stoi(Lexeme,8);
    self_send(TK_INT);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8980 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1452:
    __quex_debug("* terminal 1452:   [1-9][0-9]*\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(LexemeL);
    QUEX_LEXEME_TERMINATING_ZERO_SET(&me->buffer);
    {
#   line 152 "lexer.qx"
    self_write_token_p()->content.integer = stoi(Lexeme,10);
    self_send(TK_INT);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8996 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1453:
    __quex_debug("* terminal 1453:   0[xX][:xdigit:]+\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(LexemeL);
    QUEX_LEXEME_TERMINATING_ZERO_SET(&me->buffer);
    {
#   line 153 "lexer.qx"
    self_write_token_p()->content.integer = stoi(Lexeme,16);
    self_send(TK_INT);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 9012 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1454:
    __quex_debug("* terminal 1454:   [0-9]*\\.?[0-9]+([eE][\\-+]?[0-9]+)?\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(LexemeL);
    QUEX_LEXEME_TERMINATING_ZERO_SET(&me->buffer);
    {
#   line 155 "lexer.qx"
    self_write_token_p()->content.real = atof((char*)(Lexeme));
    self_send(TK_REAL);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 9028 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1455:
    __quex_debug("* terminal 1455:   nan\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(3);
    {
#   line 156 "lexer.qx"
    self_write_token_p()->content.real = NAN;
    self_send(TK_REAL);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 9043 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1456:
    __quex_debug("* terminal 1456:   inf\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(3);
    {
#   line 158 "lexer.qx"
    
        self_write_token_p()->content.real = INFINITY;
        self_send(TK_REAL);
    
    
#   line 9059 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1457:
    __quex_debug("* terminal 1457:   {ualpha}{ualnum}*\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(LexemeL);
    {
#   line 163 "lexer.qx"
    QUEX_NAME_TOKEN(take_text)(self_write_token_p(), &self, self.buffer._lexeme_start_p, self.buffer._input_p);
    self_send(TK_IDENT);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 9074 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;


_2132: /* TERMINAL: FAILURE */
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
#   line 63 "lexer.qx"
    
        std::ostringstream ss;
        ss << "Syntax error: Unexpected symbol: \"" <<
            std::string(LexemeBegin, LexemeEnd) <<
            "\" at line " <<
            self.line_number() <<
            " column " <<
            self.column_number();
        throw ParseError(ss.str());
    
    
#   line 9107 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION_2;


/* TERMINAL: END_OF_STREAM */
_1480:
__QUEX_IF_COUNT_SHIFT_VALUES();
    {
#   line 81 "lexer.qx"
    self_send(TK_EOS);
    
#   line 9120 "lexer.cpp"

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
        case 1477: { goto _1477; }
        case 1479: { goto _1479; }
        case 1480: { goto _1480; }
        case 1482: { goto _1482; }
        case 1485: { goto _1485; }
        case 1488: { goto _1488; }
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
        case 2117: { goto _2117; }
        case 2118: { goto _2118; }
        case 2119: { goto _2119; }
        case 2120: { goto _2120; }
        case 2121: { goto _2121; }
        case 2122: { goto _2122; }
        case 2123: { goto _2123; }
        case 2124: { goto _2124; }
        case 2125: { goto _2125; }
        case 2126: { goto _2126; }
        case 2127: { goto _2127; }
        case 2129: { goto _2129; }
        case 2130: { goto _2130; }
        case 2133: { goto _2133; }
        case 2134: { goto _2134; }
        case 2135: { goto _2135; }
        case 2136: { goto _2136; }
        case 2137: { goto _2137; }
        case 2138: { goto _2138; }
        case 2139: { goto _2139; }
        case 2140: { goto _2140; }
        case 2141: { goto _2141; }
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
        case 2154: { goto _2154; }
        case 2155: { goto _2155; }
        case 2156: { goto _2156; }
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
        case 2188: { goto _2188; }
        case 2189: { goto _2189; }
        case 2190: { goto _2190; }
        case 2191: { goto _2191; }
        case 2192: { goto _2192; }
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
        case 2205: { goto _2205; }
        case 2206: { goto _2206; }
        case 2207: { goto _2207; }
        case 2208: { goto _2208; }
        case 2209: { goto _2209; }
        case 2210: { goto _2210; }
        case 2211: { goto _2211; }
        case 2212: { goto _2212; }
        case 2213: { goto _2213; }
        case 2214: { goto _2214; }
        case 2215: { goto _2215; }
        case 2217: { goto _2217; }
        case 2218: { goto _2218; }
        case 2219: { goto _2219; }
        case 2220: { goto _2220; }
        case 2221: { goto _2221; }
        case 2222: { goto _2222; }
        case 2223: { goto _2223; }
        case 2224: { goto _2224; }
        case 2225: { goto _2225; }
        case 2227: { goto _2227; }
        case 2229: { goto _2229; }
        case 2231: { goto _2231; }
        case 2232: { goto _2232; }
        case 2233: { goto _2233; }
        case 2234: { goto _2234; }
        case 2235: { goto _2235; }
        case 2236: { goto _2236; }
        case 2237: { goto _2237; }
        case 2239: { goto _2239; }
        case 2240: { goto _2240; }
        case 2243: { goto _2243; }
        case 2245: { goto _2245; }
        case 2248: { goto _2248; }
        case 2251: { goto _2251; }
        case 2255: { goto _2255; }
        case 2257: { goto _2257; }
        case 2259: { goto _2259; }
        case 2261: { goto _2261; }
        case 2263: { goto _2263; }
        case 2267: { goto _2267; }
        case 2268: { goto _2268; }

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
_2443: /* INIT_STATE_TRANSITION_BLOCK */
    input = *(me->buffer._input_p);
    __quex_debug("Init State\n");
    __quex_debug_state(2411);
    if( input < 0x23 ) {
        switch( input ) {
            case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2411, 1480);
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
            case 0x21: goto _2413;
            case 0x22: goto _2412;

        }
    } else {
        if( input < 0x27 ) {
            goto _2413;
        } else if( input == 0x27 ) {
            goto _2414;
        } else if( input < 0x5C ) {
            goto _2413;
        } else if( input == 0x5C ) {
            goto _2415;
        } else {
            goto _2413;
        }
    }
    __quex_debug_drop_out(2411);

goto _2132; /* TERMINAL_FAILURE */

_2411:


    ++(me->buffer._input_p);
    goto _2443;


    __quex_assert_no_passage();
_2445: /* (2440 from 2414) */
    position[0] = me->buffer._input_p; __quex_debug("position[0] = input_p;\n");

_2440: /* (2440 from 2440) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2440);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2440, 2446);
        case 0x9: 
        case 0xA: 
        case 0xD: 
        case 0x20: goto _2440;
        case 0x27: goto _2439;

    }
_2446:
    __quex_debug_drop_out(2440);
__quex_assert(position[0] != 0x0);
me->buffer._input_p = position[0];

goto TERMINAL_1461;

    __quex_assert_no_passage();
_2447: /* (2442 from 2412) */
    position[0] = me->buffer._input_p; __quex_debug("position[0] = input_p;\n");

_2442: /* (2442 from 2442) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2442);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2442, 2448);
        case 0x9: 
        case 0xA: 
        case 0xD: 
        case 0x20: goto _2442;
        case 0x22: goto _2441;

    }
_2448:
    __quex_debug_drop_out(2442);
__quex_assert(position[0] != 0x0);
me->buffer._input_p = position[0];

goto TERMINAL_1460;

    __quex_assert_no_passage();
_2413: /* (2413 from 2413) (2413 from 2411) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2413);
    if( input < 0x23 ) {
        switch( input ) {
            case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2413, 2449);
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
            case 0x21: goto _2413;

        }
    } else {
        if( input < 0x27 ) {
            goto _2413;
        } else if( input == 0x27 ) {

        } else if( input < 0x5C ) {
            goto _2413;
        } else if( input == 0x5C ) {

        } else {
            goto _2413;
        }
    }
_2449:
    __quex_debug_drop_out(2413);
goto TERMINAL_1462;

    __quex_assert_no_passage();
_2432: /* (2432 from 2431) */

    ++(me->buffer._input_p);
    __quex_debug_state(2432);
    __quex_debug_drop_out(2432);
goto TERMINAL_1472;

    __quex_assert_no_passage();
_2433: /* (2433 from 2418) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2433);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2433, 2451);
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
        case 0x66: goto _2434;

    }
_2451:
    __quex_debug_drop_out(2433);
goto TERMINAL_1473;

    __quex_assert_no_passage();
_2434: /* (2434 from 2433) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2434);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2434, 2452);
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
        case 0x66: goto _2435;

    }
_2452:
    __quex_debug_drop_out(2434);
goto TERMINAL_1473;

    __quex_assert_no_passage();
_2435: /* (2435 from 2434) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2435);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2435, 2453);
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
        case 0x66: goto _2436;

    }
_2453:
    __quex_debug_drop_out(2435);
goto TERMINAL_1473;

    __quex_assert_no_passage();
_2436: /* (2436 from 2435) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2436);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2436, 2454);
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
        case 0x66: goto _2437;

    }
_2454:
    __quex_debug_drop_out(2436);
goto TERMINAL_1473;

    __quex_assert_no_passage();
_2437: /* (2437 from 2436) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2437);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2437, 2455);
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
        case 0x66: goto _2438;

    }
_2455:
    __quex_debug_drop_out(2437);
goto TERMINAL_1473;

    __quex_assert_no_passage();
_2438: /* (2438 from 2437) */

    ++(me->buffer._input_p);
    __quex_debug_state(2438);
    __quex_debug_drop_out(2438);
goto TERMINAL_1473;

    __quex_assert_no_passage();
_2431: /* (2431 from 2427) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2431);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2431, 2457);
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
        case 0x66: goto _2432;

    }
_2457:
    __quex_debug_drop_out(2431);
goto TERMINAL_1472;

    __quex_assert_no_passage();
_2439: /* (2439 from 2440) (2439 from 2414) */

    ++(me->buffer._input_p);
    __quex_debug_state(2439);
    __quex_debug_drop_out(2439);
goto TERMINAL_1459;

    __quex_assert_no_passage();
_2441: /* (2441 from 2442) (2441 from 2412) */

    ++(me->buffer._input_p);
    __quex_debug_state(2441);
    __quex_debug_drop_out(2441);
goto TERMINAL_1458;

    __quex_assert_no_passage();
_2416: /* (2416 from 2415) */

    ++(me->buffer._input_p);
    __quex_debug_state(2416);
    __quex_debug_drop_out(2416);
goto TERMINAL_1463;

    __quex_assert_no_passage();
_2417: /* (2417 from 2415) */

    ++(me->buffer._input_p);
    __quex_debug_state(2417);
    __quex_debug_drop_out(2417);
goto TERMINAL_1465;

    __quex_assert_no_passage();
_2418: /* (2418 from 2415) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2418);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2418, 2462);
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
        case 0x66: goto _2433;

    }
_2462:
    __quex_debug_drop_out(2418);

goto _2132; /* TERMINAL_FAILURE */

    __quex_assert_no_passage();
_2419: /* (2419 from 2415) */

    ++(me->buffer._input_p);
    __quex_debug_state(2419);
    __quex_debug_drop_out(2419);
goto TERMINAL_1464;

    __quex_assert_no_passage();
_2420: /* (2420 from 2415) */

    ++(me->buffer._input_p);
    __quex_debug_state(2420);
    __quex_debug_drop_out(2420);
goto TERMINAL_1475;

    __quex_assert_no_passage();
_2421: /* (2421 from 2415) */

    ++(me->buffer._input_p);
    __quex_debug_state(2421);
    __quex_debug_drop_out(2421);
goto TERMINAL_1466;

    __quex_assert_no_passage();
_2422: /* (2422 from 2415) */

    ++(me->buffer._input_p);
    __quex_debug_state(2422);
    __quex_debug_drop_out(2422);
goto TERMINAL_1468;

    __quex_assert_no_passage();
_2423: /* (2423 from 2415) */

    ++(me->buffer._input_p);
    __quex_debug_state(2423);
    __quex_debug_drop_out(2423);
goto TERMINAL_1470;

    __quex_assert_no_passage();
_2424: /* (2424 from 2415) */

    ++(me->buffer._input_p);
    __quex_debug_state(2424);
    __quex_debug_drop_out(2424);
goto TERMINAL_1474;

    __quex_assert_no_passage();
_2425: /* (2425 from 2415) */

    ++(me->buffer._input_p);
    __quex_debug_state(2425);
    __quex_debug_drop_out(2425);
goto TERMINAL_1467;

    __quex_assert_no_passage();
_2426: /* (2426 from 2415) */

    ++(me->buffer._input_p);
    __quex_debug_state(2426);
    __quex_debug_drop_out(2426);
goto TERMINAL_1469;

    __quex_assert_no_passage();
_2427: /* (2427 from 2415) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2427);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2427, 2471);
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
        case 0x66: goto _2431;

    }
_2471:
    __quex_debug_drop_out(2427);

goto _2132; /* TERMINAL_FAILURE */

    __quex_assert_no_passage();
_2428: /* (2428 from 2415) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2428);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2428, 2472);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: goto _2429;

    }
_2472:
    __quex_debug_drop_out(2428);
goto TERMINAL_1471;

    __quex_assert_no_passage();
_2429: /* (2429 from 2428) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2429);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2429, 2473);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: goto _2430;

    }
_2473:
    __quex_debug_drop_out(2429);
goto TERMINAL_1471;

    __quex_assert_no_passage();
_2430: /* (2430 from 2429) */

    ++(me->buffer._input_p);
    __quex_debug_state(2430);
    __quex_debug_drop_out(2430);
goto TERMINAL_1471;

    __quex_assert_no_passage();
_2412: /* (2412 from 2411) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2412);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2412, 2475);
        case 0x9: 
        case 0xA: 
        case 0xD: 
        case 0x20: goto _2447;
        case 0x22: goto _2441;

    }
_2475:
    __quex_debug_drop_out(2412);
goto TERMINAL_1460;

    __quex_assert_no_passage();
_2414: /* (2414 from 2411) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2414);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2414, 2476);
        case 0x9: 
        case 0xA: 
        case 0xD: 
        case 0x20: goto _2445;
        case 0x27: goto _2439;

    }
_2476:
    __quex_debug_drop_out(2414);
goto TERMINAL_1461;

    __quex_assert_no_passage();
_2415: /* (2415 from 2411) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2415);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2415, 2477);
        case 0x22: goto _2420;
        case 0x27: goto _2424;
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: goto _2428;
        case 0x5C: goto _2423;
        case 0x61: goto _2417;
        case 0x62: goto _2421;
        case 0x66: goto _2425;
        case 0x6E: goto _2416;
        case 0x72: goto _2422;
        case 0x74: goto _2419;
        case 0x75: goto _2418;
        case 0x76: goto _2426;
        case 0x78: goto _2427;

    }
_2477:
    __quex_debug_drop_out(2415);

goto _2132; /* TERMINAL_FAILURE */
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

TERMINAL_1458:
    __quex_debug("* terminal 1458:   \\\"[:space:]*\\\"\n");
    __QUEX_COUNT_VOID(&self, LexemeBegin, LexemeEnd);
    {
#   line 180 "lexer.qx"
    
        if(self.string_delimiter != '\"')
            self_accumulator_add(LexemeBegin, LexemeEnd);
    
    
#   line 10287 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1459:
    __quex_debug("* terminal 1459:   '[:space:]*'\n");
    __QUEX_COUNT_VOID(&self, LexemeBegin, LexemeEnd);
    {
#   line 186 "lexer.qx"
    
        if(self.string_delimiter != '\'')
            self_accumulator_add(LexemeBegin, LexemeEnd);
    
    
#   line 10302 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1460:
    __quex_debug("* terminal 1460:   \\\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 192 "lexer.qx"
    
        if (self.string_delimiter == '\"')
        {
            self_accumulator_flush(TK_STRING);
            self << MAIN;
        }
        else
        {
            self_accumulator_add_character('\"');
        }
    
    
#   line 10325 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1461:
    __quex_debug("* terminal 1461:   '\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 204 "lexer.qx"
    
        if (self.string_delimiter == '\'')
        {
            self_accumulator_flush(TK_STRING);
            self << MAIN;
        }
        else
        {
            self_accumulator_add_character('\'');
        }
    
    
#   line 10348 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1462:
    __quex_debug("* terminal 1462:   [^\\\\\\\"']+\n");
    __QUEX_COUNT_VOID(&self, LexemeBegin, LexemeEnd);
    {
#   line 216 "lexer.qx"
        self_accumulator_add(LexemeBegin, LexemeEnd);
    
#   line 10360 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1463:
    __quex_debug("* terminal 1463:   \\\\n\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 219 "lexer.qx"
        self_accumulator_add_character('\n');
    
#   line 10373 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1464:
    __quex_debug("* terminal 1464:   \\\\t\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 220 "lexer.qx"
        self_accumulator_add_character('\t');
    
#   line 10386 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1465:
    __quex_debug("* terminal 1465:   \\\\a\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 221 "lexer.qx"
        self_accumulator_add_character('\a');
    
#   line 10399 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1466:
    __quex_debug("* terminal 1466:   \\\\b\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 222 "lexer.qx"
        self_accumulator_add_character('\b');
    
#   line 10412 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1467:
    __quex_debug("* terminal 1467:   \\\\f\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 223 "lexer.qx"
        self_accumulator_add_character('\f');
    
#   line 10425 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1468:
    __quex_debug("* terminal 1468:   \\\\r\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 224 "lexer.qx"
        self_accumulator_add_character('\r');
    
#   line 10438 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1469:
    __quex_debug("* terminal 1469:   \\\\v\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 225 "lexer.qx"
        self_accumulator_add_character('\v');
    
#   line 10451 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1470:
    __quex_debug("* terminal 1470:   \\\\\\\\\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 226 "lexer.qx"
        self_accumulator_add_character('\\');
    
#   line 10464 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1471:
    __quex_debug("* terminal 1471:   \\\\[0-7]{1,3}\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(LexemeL);
    QUEX_LEXEME_TERMINATING_ZERO_SET(&me->buffer);
    {
#   line 228 "lexer.qx"
        self_accumulator_add_character((QUEX_TYPE_CHARACTER)stoi(Lexeme+1,8));
    
#   line 10478 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1472:
    __quex_debug("* terminal 1472:   \\\\x[:xdigit:]{1,2}\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(LexemeL);
    QUEX_LEXEME_TERMINATING_ZERO_SET(&me->buffer);
    {
#   line 229 "lexer.qx"
        self_accumulator_add_character((QUEX_TYPE_CHARACTER)stoi(Lexeme+2,16));
    
#   line 10492 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1473:
    __quex_debug("* terminal 1473:   \\\\u[:xdigit:]{1,6}\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(LexemeL);
    QUEX_LEXEME_TERMINATING_ZERO_SET(&me->buffer);
    {
#   line 231 "lexer.qx"
    
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
    
    
#   line 10545 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1474:
    __quex_debug("* terminal 1474:   \\\\'\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 272 "lexer.qx"
        self_accumulator_add_character('\'');
    
#   line 10558 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1475:
    __quex_debug("* terminal 1475:   \\\\\\\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 273 "lexer.qx"
        self_accumulator_add_character('\"');
    
#   line 10571 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;


_2132: /* TERMINAL: FAILURE */
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
_1480:
__QUEX_IF_COUNT_SHIFT_VALUES();
    {
#   line 174 "lexer.qx"
    
        self << MAIN;
        throw ParseError("Syntax error: Unterminated string");
    
    
#   line 10611 "lexer.cpp"

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
        case 1480: { goto _1480; }
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
        case 2431: { goto _2431; }
        case 2432: { goto _2432; }
        case 2433: { goto _2433; }
        case 2434: { goto _2434; }
        case 2435: { goto _2435; }
        case 2436: { goto _2436; }
        case 2437: { goto _2437; }
        case 2438: { goto _2438; }
        case 2439: { goto _2439; }
        case 2440: { goto _2440; }
        case 2441: { goto _2441; }
        case 2442: { goto _2442; }
        case 2445: { goto _2445; }
        case 2446: { goto _2446; }
        case 2447: { goto _2447; }
        case 2448: { goto _2448; }
        case 2449: { goto _2449; }
        case 2451: { goto _2451; }
        case 2452: { goto _2452; }
        case 2453: { goto _2453; }
        case 2454: { goto _2454; }
        case 2455: { goto _2455; }
        case 2457: { goto _2457; }
        case 2462: { goto _2462; }
        case 2471: { goto _2471; }
        case 2472: { goto _2472; }
        case 2473: { goto _2473; }
        case 2475: { goto _2475; }
        case 2476: { goto _2476; }
        case 2477: { goto _2477; }

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
   static const char  token_id_str_COLON[]         = "COLON";
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
   case TK_COLON:         return token_id_str_COLON;
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

