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
    const QUEX_TYPE_CHARACTER      Skipper1427_Closer[2]          = { 0x2A, 0x2F,  };
    const QUEX_TYPE_CHARACTER      Skipper1427_Opener[2]          = { 0x2F, 0x2A,  };
    const QUEX_TYPE_CHARACTER*     Skipper1427_CloserEnd          = Skipper1427_Closer + (ptrdiff_t)2;
    const QUEX_TYPE_CHARACTER      Skipper1430[1]                 = { 0xA,  };
    void*                          position                       = (void*)0x0;
    const QUEX_TYPE_CHARACTER*     Skipper1427_Closer_it          = 0x0;
    size_t                         counter                        = 0;
    const QUEX_TYPE_CHARACTER      Skipper1424[1]                 = { 0xA,  };
    QUEX_TYPE_CHARACTER_POSITION   reference_p                    = (QUEX_TYPE_CHARACTER_POSITION)0x0;
    QUEX_TYPE_GOTO_LABEL           target_state_else_index        = QUEX_GOTO_LABEL_VOID;
    QUEX_TYPE_ACCEPTANCE_ID        last_acceptance               /* un-initilized */;
    const QUEX_TYPE_CHARACTER*     Skipper1427_OpenerEnd          = Skipper1427_Opener + (ptrdiff_t)2;
    const size_t                   Skipper1424L                   = 1;
    const size_t                   PositionRegisterN              = (size_t)0;
    QUEX_TYPE_CHARACTER*           text_end                       = (QUEX_TYPE_CHARACTER*)0x0;
    const QUEX_TYPE_CHARACTER*     Skipper1427_Opener_it          = 0x0;
    const size_t                   Skipper1430L                   = 1;
    QUEX_TYPE_GOTO_LABEL           target_state_index             = QUEX_GOTO_LABEL_VOID;
    QUEX_TYPE_CHARACTER            input                          = (QUEX_TYPE_CHARACTER)(0x00);
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
_2042: /* INIT_STATE_TRANSITION_BLOCK */
    input = *(me->buffer._input_p);
    __quex_debug("Init State\n");
    __quex_debug_state(1915);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1915, 1423);
        case 0x9: goto _1957;
        case 0xA: goto _1950;
        case 0xD: 
        case 0x20: goto _1954;
        case 0x21: goto _1927;
        case 0x22: goto _1936;
        case 0x23: goto _1959;
        case 0x25: goto _1919;
        case 0x27: goto _1938;
        case 0x28: goto _1953;
        case 0x29: goto _1920;
        case 0x2A: goto _1932;
        case 0x2B: goto _1928;
        case 0x2C: goto _1958;
        case 0x2D: goto _1930;
        case 0x2E: goto _1926;
        case 0x2F: goto _1942;
        case 0x30: goto _2043;
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: goto _2044;
        case 0x3A: goto _1925;
        case 0x3B: goto _1933;
        case 0x3C: goto _1937;
        case 0x3D: goto _1935;
        case 0x3E: goto _1939;
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
        case 0x5A: goto _1955;
        case 0x5B: goto _1916;
        case 0x5D: goto _1946;
        case 0x5E: goto _1923;
        case 0x5F: goto _1955;
        case 0x61: goto _1931;
        case 0x62: goto _1929;
        case 0x63: goto _1944;
        case 0x64: goto _1949;
        case 0x65: goto _1948;
        case 0x66: goto _1934;
        case 0x67: 
        case 0x68: goto _1955;
        case 0x69: goto _1943;
        case 0x6A: 
        case 0x6B: goto _1955;
        case 0x6C: goto _1917;
        case 0x6D: goto _1955;
        case 0x6E: goto _1951;
        case 0x6F: goto _1956;
        case 0x70: 
        case 0x71: goto _1955;
        case 0x72: goto _1945;
        case 0x73: goto _1955;
        case 0x74: goto _1922;
        case 0x75: goto _1941;
        case 0x76: goto _1955;
        case 0x77: goto _1947;
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _1955;
        case 0x7B: goto _1940;
        case 0x7C: goto _1918;
        case 0x7D: goto _1952;

    }
    __quex_debug_drop_out(1915);

goto _2046; /* TERMINAL_FAILURE */

_1915:


    ++(me->buffer._input_p);
    goto _2042;


    __quex_assert_no_passage();
_1955: /* (1955 from 1955) (1955 from 1956) (1955 from 1951) (1955 from 1963) (1955 from 1964) (1955 from 1965) (1955 from 1966) (1955 from 1960) (1955 from 1961) (1955 from 1962) (1955 from 1971) (1955 from 1972) (1955 from 1973) (1955 from 1974) (1955 from 1967) (1955 from 1968) (1955 from 1969) (1955 from 1970) (1955 from 1979) (1955 from 1980) (1955 from 1981) (1955 from 1982) (1955 from 1975) (1955 from 1976) (1955 from 1977) (1955 from 1978) (1955 from 1922) (1955 from 1931) (1955 from 1934) (1955 from 1929) (1955 from 1941) (1955 from 1947) (1955 from 1948) (1955 from 1949) (1955 from 1943) (1955 from 1944) (1955 from 1945) (1955 from 2019) (1955 from 2020) (1955 from 2021) (1955 from 2015) (1955 from 2016) (1955 from 2017) (1955 from 2018) (1955 from 2028) (1955 from 2029) (1955 from 2030) (1955 from 2038) (1955 from 2031) (1955 from 2032) (1955 from 2033) (1955 from 1915) (1955 from 1917) (1955 from 2039) (1955 from 2040) (1955 from 2041) (1955 from 1987) (1955 from 1988) (1955 from 1989) (1955 from 1990) (1955 from 1983) (1955 from 1984) (1955 from 1985) (1955 from 1986) (1955 from 1995) (1955 from 1996) (1955 from 1997) (1955 from 1998) (1955 from 1991) (1955 from 1992) (1955 from 1993) (1955 from 1994) (1955 from 2003) (1955 from 2004) (1955 from 2005) (1955 from 1999) (1955 from 2002) (1955 from 2011) (1955 from 2012) (1955 from 2013) (1955 from 2014) (1955 from 2010) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1955);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1955, 2047);
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
        case 0x7A: goto _1955;

    }
_2047:
    __quex_debug_drop_out(1955);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_2024: /* (2024 from 2036) (2024 from 1921) (2024 from 1924) (2024 from 2035) (2024 from 2023) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2024);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2024, 2048);
        case 0x2B: 
        case 0x2D: goto _2025;
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: goto _2026;

    }
_2048:
    __quex_debug_drop_out(2024);
switch( last_acceptance ) {
    case 1394: me->buffer._input_p -= 1;  goto TERMINAL_1394;
    case 1395: me->buffer._input_p -= 1;  goto TERMINAL_1395;
    case 1397: me->buffer._input_p -= 1;  goto TERMINAL_1397;

}

    __quex_assert_no_passage();
_2037: /* (2037 from 2037) (2037 from 2034) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2037);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2037, 2049);
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
        case 0x66: goto _2037;

    }
_2049:
    __quex_debug_drop_out(2037);
goto TERMINAL_1396;

    __quex_assert_no_passage();
_2027: /* (2027 from 2035) (2027 from 1924) (2027 from 1921) (2027 from 2036) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2027);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2027, 2050);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: goto _2051;

    }
_2050:
    __quex_debug_drop_out(2027);
switch( last_acceptance ) {
    case 1394: me->buffer._input_p -= 1;  goto TERMINAL_1394;
    case 1395: me->buffer._input_p -= 1;  goto TERMINAL_1395;
    case 1397: me->buffer._input_p -= 1;  goto TERMINAL_1397;

}

    __quex_assert_no_passage();
_2051: /* (2023 from 2023) (2023 from 2027) (2023 from 1926) */
    { last_acceptance = 1397; __quex_debug("last_acceptance = 1397\n"); }

_2023:

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2023);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2023, 2052);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: goto _2051;
        case 0x45: 
        case 0x65: goto _2024;

    }
_2052:
    __quex_debug_drop_out(2023);
goto TERMINAL_1397;

    __quex_assert_no_passage();
_2026: /* (2026 from 2026) (2026 from 2025) (2026 from 2024) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2026);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2026, 2053);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: goto _2026;

    }
_2053:
    __quex_debug_drop_out(2026);
goto TERMINAL_1397;

    __quex_assert_no_passage();
_2054: /* (2036 from 2036) (2036 from 2035) (2036 from 1921) */
    { last_acceptance = 1397; __quex_debug("last_acceptance = 1397\n"); }

_2036:

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2036);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2036, 2055);
        case 0x2E: goto _2027;
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: goto _2054;
        case 0x45: 
        case 0x65: goto _2024;

    }
_2055:
    __quex_debug_drop_out(2036);
goto TERMINAL_1397;

    __quex_assert_no_passage();
_2025: /* (2025 from 2024) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2025);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2025, 2056);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: goto _2026;

    }
_2056:
    __quex_debug_drop_out(2025);
switch( last_acceptance ) {
    case 1394: me->buffer._input_p -= 2;  goto TERMINAL_1394;
    case 1395: me->buffer._input_p -= 2;  goto TERMINAL_1395;
    case 1397: me->buffer._input_p -= 2;  goto TERMINAL_1397;

}

    __quex_assert_no_passage();
_2034: /* (2034 from 1921) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2034);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2034, 2057);
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
        case 0x66: goto _2037;

    }
_2057:
    __quex_debug_drop_out(2034);
me->buffer._input_p -= 1; 
goto TERMINAL_1394;

    __quex_assert_no_passage();
_2058: /* (2035 from 2035) (2035 from 1921) */
    { last_acceptance = 1394; __quex_debug("last_acceptance = 1394\n"); }

_2035:

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2035);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2035, 2059);
        case 0x2E: goto _2027;
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: goto _2058;
        case 0x38: 
        case 0x39: goto _2054;
        case 0x45: 
        case 0x65: goto _2024;

    }
_2059:
    __quex_debug_drop_out(2035);
goto TERMINAL_1394;

    __quex_assert_no_passage();
_2044: /* (1924 from 1924) (1924 from 1915) */
    { last_acceptance = 1395; __quex_debug("last_acceptance = 1395\n"); }

_1924:

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1924);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1924, 2060);
        case 0x2E: goto _2027;
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: goto _2044;
        case 0x45: 
        case 0x65: goto _2024;

    }
_2060:
    __quex_debug_drop_out(1924);
goto TERMINAL_1395;

    __quex_assert_no_passage();
_1960: /* (1960 from 1956) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1960);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1960, 2061);
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
        case 0x7A: goto _1955;

    }
_2061:
    __quex_debug_drop_out(1960);
goto TERMINAL_1367;

    __quex_assert_no_passage();
_1961: /* (1961 from 1951) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1961);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1961, 2062);
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
        case 0x73: goto _1955;
        case 0x74: goto _1969;
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _1955;

    }
_2062:
    __quex_debug_drop_out(1961);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_1962: /* (1962 from 1951) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1962);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1962, 2063);
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
        case 0x6B: goto _1955;
        case 0x6C: goto _1968;
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
        case 0x7A: goto _1955;

    }
_2063:
    __quex_debug_drop_out(1962);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_1963: /* (1963 from 1951) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1963);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1963, 2064);
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
        case 0x6D: goto _1955;
        case 0x6E: goto _1967;
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
        case 0x7A: goto _1955;

    }
_2064:
    __quex_debug_drop_out(1963);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_1964: /* (1964 from 1951) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1964);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1964, 2065);
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
        case 0x77: goto _1955;
        case 0x78: goto _1965;
        case 0x79: 
        case 0x7A: goto _1955;

    }
_2065:
    __quex_debug_drop_out(1964);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_1965: /* (1965 from 1964) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1965);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1965, 2066);
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
        case 0x73: goto _1955;
        case 0x74: goto _1966;
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _1955;

    }
_2066:
    __quex_debug_drop_out(1965);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_1966: /* (1966 from 1965) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1966);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1966, 2067);
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
        case 0x7A: goto _1955;

    }
_2067:
    __quex_debug_drop_out(1966);
goto TERMINAL_1362;

    __quex_assert_no_passage();
_1967: /* (1967 from 1963) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1967);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1967, 2068);
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
        case 0x7A: goto _1955;

    }
_2068:
    __quex_debug_drop_out(1967);
goto TERMINAL_1398;

    __quex_assert_no_passage();
_1968: /* (1968 from 1962) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1968);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1968, 2069);
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
        case 0x7A: goto _1955;

    }
_2069:
    __quex_debug_drop_out(1968);
goto TERMINAL_1364;

    __quex_assert_no_passage();
_1969: /* (1969 from 1961) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1969);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1969, 2070);
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
        case 0x7A: goto _1955;

    }
_2070:
    __quex_debug_drop_out(1969);
goto TERMINAL_1369;

    __quex_assert_no_passage();
_1970: /* (1970 from 1949) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1970);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1970, 2071);
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
        case 0x7A: goto _1955;

    }
_2071:
    __quex_debug_drop_out(1970);
goto TERMINAL_1349;

    __quex_assert_no_passage();
_1971: /* (1971 from 1949) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1971);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1971, 2072);
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
        case 0x65: goto _1955;
        case 0x66: goto _1972;
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
        case 0x7A: goto _1955;

    }
_2072:
    __quex_debug_drop_out(1971);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_1972: /* (1972 from 1971) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1972);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1972, 2073);
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
        case 0x7A: goto _1955;

    }
_2073:
    __quex_debug_drop_out(1972);
goto TERMINAL_1347;

    __quex_assert_no_passage();
_1973: /* (1973 from 1948) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1973);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1973, 2074);
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
        case 0x63: goto _1955;
        case 0x64: goto _1979;
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
        case 0x7A: goto _1955;

    }
_2074:
    __quex_debug_drop_out(1973);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_1974: /* (1974 from 1948) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1974);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1974, 2075);
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
        case 0x68: goto _1955;
        case 0x69: goto _1975;
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: 
        case 0x72: goto _1955;
        case 0x73: goto _1976;
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _1955;

    }
_2075:
    __quex_debug_drop_out(1974);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_1975: /* (1975 from 1974) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1975);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1975, 2076);
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
        case 0x65: goto _1955;
        case 0x66: goto _1978;
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
        case 0x7A: goto _1955;

    }
_2076:
    __quex_debug_drop_out(1975);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_1976: /* (1976 from 1974) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1976);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1976, 2077);
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
        case 0x64: goto _1955;
        case 0x65: goto _1977;
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
        case 0x7A: goto _1955;

    }
_2077:
    __quex_debug_drop_out(1976);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_1977: /* (1977 from 1976) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1977);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1977, 2078);
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
        case 0x7A: goto _1955;

    }
_2078:
    __quex_debug_drop_out(1977);
goto TERMINAL_1353;

    __quex_assert_no_passage();
_1978: /* (1978 from 1975) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1978);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1978, 2079);
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
        case 0x7A: goto _1955;

    }
_2079:
    __quex_debug_drop_out(1978);
goto TERMINAL_1354;

    __quex_assert_no_passage();
_1979: /* (1979 from 1973) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1979);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1979, 2080);
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
        case 0x7A: goto _1955;

    }
_2080:
    __quex_debug_drop_out(1979);
goto TERMINAL_1350;

    __quex_assert_no_passage();
_1980: /* (1980 from 1947) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1980);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1980, 2081);
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
        case 0x68: goto _1955;
        case 0x69: goto _1981;
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
        case 0x7A: goto _1955;

    }
_2081:
    __quex_debug_drop_out(1980);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_1981: /* (1981 from 1980) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1981);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1981, 2082);
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
        case 0x6B: goto _1955;
        case 0x6C: goto _1982;
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
        case 0x7A: goto _1955;

    }
_2082:
    __quex_debug_drop_out(1981);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_1982: /* (1982 from 1981) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1982);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1982, 2083);
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
        case 0x64: goto _1955;
        case 0x65: goto _1983;
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
        case 0x7A: goto _1955;

    }
_2083:
    __quex_debug_drop_out(1982);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_1983: /* (1983 from 1982) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1983);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1983, 2084);
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
        case 0x7A: goto _1955;

    }
_2084:
    __quex_debug_drop_out(1983);
goto TERMINAL_1355;

    __quex_assert_no_passage();
_1984: /* (1984 from 1945) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1984);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1984, 2085);
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
        case 0x6F: goto _1955;
        case 0x70: goto _1985;
        case 0x71: 
        case 0x72: 
        case 0x73: goto _1955;
        case 0x74: goto _1986;
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _1955;

    }
_2085:
    __quex_debug_drop_out(1984);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_1985: /* (1985 from 1984) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1985);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1985, 2086);
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
        case 0x64: goto _1955;
        case 0x65: goto _1990;
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
        case 0x7A: goto _1955;

    }
_2086:
    __quex_debug_drop_out(1985);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_1986: /* (1986 from 1984) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1986);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1986, 2087);
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
        case 0x74: goto _1955;
        case 0x75: goto _1987;
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _1955;

    }
_2087:
    __quex_debug_drop_out(1986);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_1987: /* (1987 from 1986) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1987);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1987, 2088);
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
        case 0x71: goto _1955;
        case 0x72: goto _1988;
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _1955;

    }
_2088:
    __quex_debug_drop_out(1987);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_1988: /* (1988 from 1987) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1988);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1988, 2089);
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
        case 0x6D: goto _1955;
        case 0x6E: goto _1989;
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
        case 0x7A: goto _1955;

    }
_2089:
    __quex_debug_drop_out(1988);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_1989: /* (1989 from 1988) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1989);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1989, 2090);
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
        case 0x7A: goto _1955;

    }
_2090:
    __quex_debug_drop_out(1989);
goto TERMINAL_1360;

    __quex_assert_no_passage();
_1990: /* (1990 from 1985) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1990);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1990, 2091);
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
        case 0x5F: goto _1955;
        case 0x61: goto _1991;
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
        case 0x7A: goto _1955;

    }
_2091:
    __quex_debug_drop_out(1990);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_1991: /* (1991 from 1990) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1991);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1991, 2092);
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
        case 0x73: goto _1955;
        case 0x74: goto _1992;
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _1955;

    }
_2092:
    __quex_debug_drop_out(1991);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_1992: /* (1992 from 1991) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1992);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1992, 2093);
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
        case 0x7A: goto _1955;

    }
_2093:
    __quex_debug_drop_out(1992);
goto TERMINAL_1358;

    __quex_assert_no_passage();
_1993: /* (1993 from 1944) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1993);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1993, 2094);
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
        case 0x5F: goto _1955;
        case 0x61: goto _1994;
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
        case 0x7A: goto _1955;

    }
_2094:
    __quex_debug_drop_out(1993);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_1994: /* (1994 from 1993) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1994);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1994, 2095);
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
        case 0x72: goto _1955;
        case 0x73: goto _1995;
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _1955;

    }
_2095:
    __quex_debug_drop_out(1994);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_1995: /* (1995 from 1994) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1995);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1995, 2096);
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
        case 0x72: goto _1955;
        case 0x73: goto _1996;
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _1955;

    }
_2096:
    __quex_debug_drop_out(1995);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_1996: /* (1996 from 1995) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1996);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1996, 2097);
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
        case 0x7A: goto _1955;

    }
_2097:
    __quex_debug_drop_out(1996);
goto TERMINAL_1348;

    __quex_assert_no_passage();
_1997: /* (1997 from 1943) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1997);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1997, 2098);
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
        case 0x7A: goto _1955;

    }
_2098:
    __quex_debug_drop_out(1997);
goto TERMINAL_1351;

    __quex_assert_no_passage();
_1998: /* (1998 from 1943) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1998);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1998, 2099);
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
        case 0x65: goto _1955;
        case 0x66: goto _1999;
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
        case 0x7A: goto _1955;

    }
_2099:
    __quex_debug_drop_out(1998);
goto TERMINAL_1357;

    __quex_assert_no_passage();
_1999: /* (1999 from 1998) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1999);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1999, 2100);
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
        case 0x7A: goto _1955;

    }
_2100:
    __quex_debug_drop_out(1999);
goto TERMINAL_1399;

    __quex_assert_no_passage();
_2000: /* (2000 from 1942) */

    ++(me->buffer._input_p);
    __quex_debug_state(2000);
    __quex_debug_drop_out(2000);
goto TERMINAL_1341;

    __quex_assert_no_passage();
_2001: /* (2001 from 1942) */

    ++(me->buffer._input_p);
    __quex_debug_state(2001);
    __quex_debug_drop_out(2001);
goto TERMINAL_1342;

    __quex_assert_no_passage();
_2002: /* (2002 from 1941) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2002);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2002, 2103);
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
        case 0x73: goto _1955;
        case 0x74: goto _2003;
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _1955;

    }
_2103:
    __quex_debug_drop_out(2002);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_2003: /* (2003 from 2002) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2003);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2003, 2104);
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
        case 0x68: goto _1955;
        case 0x69: goto _2004;
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
        case 0x7A: goto _1955;

    }
_2104:
    __quex_debug_drop_out(2003);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_2004: /* (2004 from 2003) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2004);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2004, 2105);
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
        case 0x6B: goto _1955;
        case 0x6C: goto _2005;
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
        case 0x7A: goto _1955;

    }
_2105:
    __quex_debug_drop_out(2004);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_2005: /* (2005 from 2004) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2005);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2005, 2106);
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
        case 0x7A: goto _1955;

    }
_2106:
    __quex_debug_drop_out(2005);
goto TERMINAL_1359;

    __quex_assert_no_passage();
_2006: /* (2006 from 1939) */

    ++(me->buffer._input_p);
    __quex_debug_state(2006);
    __quex_debug_drop_out(2006);
goto TERMINAL_1373;

    __quex_assert_no_passage();
_2007: /* (2007 from 1937) */

    ++(me->buffer._input_p);
    __quex_debug_state(2007);
    __quex_debug_drop_out(2007);
goto TERMINAL_1372;

    __quex_assert_no_passage();
_2008: /* (2008 from 1937) */

    ++(me->buffer._input_p);
    __quex_debug_state(2008);
    __quex_debug_drop_out(2008);
goto TERMINAL_1375;

    __quex_assert_no_passage();
_2009: /* (2009 from 1935) */

    ++(me->buffer._input_p);
    __quex_debug_state(2009);
    __quex_debug_drop_out(2009);
goto TERMINAL_1376;

    __quex_assert_no_passage();
_2010: /* (2010 from 1934) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2010);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2010, 2111);
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
        case 0x71: goto _1955;
        case 0x72: goto _2015;
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _1955;

    }
_2111:
    __quex_debug_drop_out(2010);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_2011: /* (2011 from 1934) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2011);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2011, 2112);
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
        case 0x6B: goto _1955;
        case 0x6C: goto _2012;
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
        case 0x7A: goto _1955;

    }
_2112:
    __quex_debug_drop_out(2011);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_2012: /* (2012 from 2011) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2012);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2012, 2113);
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
        case 0x72: goto _1955;
        case 0x73: goto _2013;
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _1955;

    }
_2113:
    __quex_debug_drop_out(2012);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_2013: /* (2013 from 2012) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2013);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2013, 2114);
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
        case 0x64: goto _1955;
        case 0x65: goto _2014;
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
        case 0x7A: goto _1955;

    }
_2114:
    __quex_debug_drop_out(2013);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_2014: /* (2014 from 2013) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2014);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2014, 2115);
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
        case 0x7A: goto _1955;

    }
_2115:
    __quex_debug_drop_out(2014);
goto TERMINAL_1366;

    __quex_assert_no_passage();
_2015: /* (2015 from 2010) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2015);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2015, 2116);
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
        case 0x7A: goto _1955;

    }
_2116:
    __quex_debug_drop_out(2015);
goto TERMINAL_1356;

    __quex_assert_no_passage();
_2016: /* (2016 from 1931) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2016);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2016, 2117);
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
        case 0x63: goto _1955;
        case 0x64: goto _2017;
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
        case 0x7A: goto _1955;

    }
_2117:
    __quex_debug_drop_out(2016);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_2017: /* (2017 from 2016) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2017);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2017, 2118);
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
        case 0x7A: goto _1955;

    }
_2118:
    __quex_debug_drop_out(2017);
goto TERMINAL_1368;

    __quex_assert_no_passage();
_2018: /* (2018 from 1929) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2018);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2018, 2119);
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
        case 0x64: goto _1955;
        case 0x65: goto _2019;
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
        case 0x7A: goto _1955;

    }
_2119:
    __quex_debug_drop_out(2018);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_2019: /* (2019 from 2018) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2019);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2019, 2120);
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
        case 0x5F: goto _1955;
        case 0x61: goto _2020;
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
        case 0x7A: goto _1955;

    }
_2120:
    __quex_debug_drop_out(2019);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_2020: /* (2020 from 2019) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2020);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2020, 2121);
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
        case 0x6A: goto _1955;
        case 0x6B: goto _2021;
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
        case 0x7A: goto _1955;

    }
_2121:
    __quex_debug_drop_out(2020);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_2021: /* (2021 from 2020) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2021);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2021, 2122);
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
        case 0x7A: goto _1955;

    }
_2122:
    __quex_debug_drop_out(2021);
goto TERMINAL_1361;

    __quex_assert_no_passage();
_2022: /* (2022 from 1927) */

    ++(me->buffer._input_p);
    __quex_debug_state(2022);
    __quex_debug_drop_out(2022);
goto TERMINAL_1374;

    __quex_assert_no_passage();
_2028: /* (2028 from 1922) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2028);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2028, 2124);
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
        case 0x74: goto _1955;
        case 0x75: goto _2032;
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _1955;

    }
_2124:
    __quex_debug_drop_out(2028);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_2029: /* (2029 from 1922) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2029);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2029, 2125);
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
        case 0x64: goto _1955;
        case 0x65: goto _2030;
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
        case 0x7A: goto _1955;

    }
_2125:
    __quex_debug_drop_out(2029);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_2030: /* (2030 from 2029) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2030);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2030, 2126);
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
        case 0x6D: goto _1955;
        case 0x6E: goto _2031;
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
        case 0x7A: goto _1955;

    }
_2126:
    __quex_debug_drop_out(2030);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_2031: /* (2031 from 2030) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2031);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2031, 2127);
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
        case 0x7A: goto _1955;

    }
_2127:
    __quex_debug_drop_out(2031);
goto TERMINAL_1352;

    __quex_assert_no_passage();
_2032: /* (2032 from 2028) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2032);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2032, 2128);
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
        case 0x64: goto _1955;
        case 0x65: goto _2033;
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
        case 0x7A: goto _1955;

    }
_2128:
    __quex_debug_drop_out(2032);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_2033: /* (2033 from 2032) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2033);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2033, 2129);
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
        case 0x7A: goto _1955;

    }
_2129:
    __quex_debug_drop_out(2033);
goto TERMINAL_1365;

    __quex_assert_no_passage();
_2038: /* (2038 from 1917) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2038);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2038, 2130);
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
        case 0x62: goto _1955;
        case 0x63: goto _2039;
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
        case 0x7A: goto _1955;

    }
_2130:
    __quex_debug_drop_out(2038);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_2039: /* (2039 from 2038) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2039);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2039, 2131);
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
        case 0x5F: goto _1955;
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
        case 0x7A: goto _1955;

    }
_2131:
    __quex_debug_drop_out(2039);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_2040: /* (2040 from 2039) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2040);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2040, 2132);
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
        case 0x6B: goto _1955;
        case 0x6C: goto _2041;
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
        case 0x7A: goto _1955;

    }
_2132:
    __quex_debug_drop_out(2040);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_2041: /* (2041 from 2040) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2041);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2041, 2133);
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
        case 0x7A: goto _1955;

    }
_2133:
    __quex_debug_drop_out(2041);
goto TERMINAL_1363;

    __quex_assert_no_passage();
_1916: /* (1916 from 1915) */

    ++(me->buffer._input_p);
    __quex_debug_state(1916);
    __quex_debug_drop_out(1916);
goto TERMINAL_1388;

    __quex_assert_no_passage();
_1917: /* (1917 from 1915) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1917);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1917, 2135);
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
        case 0x6E: goto _1955;
        case 0x6F: goto _2038;
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
        case 0x7A: goto _1955;

    }
_2135:
    __quex_debug_drop_out(1917);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_1918: /* (1918 from 1915) */

    ++(me->buffer._input_p);
    __quex_debug_state(1918);
    __quex_debug_drop_out(1918);
goto TERMINAL_1383;

    __quex_assert_no_passage();
_1919: /* (1919 from 1915) */

    ++(me->buffer._input_p);
    __quex_debug_state(1919);
    __quex_debug_drop_out(1919);
goto TERMINAL_1382;

    __quex_assert_no_passage();
_1920: /* (1920 from 1915) */

    ++(me->buffer._input_p);
    __quex_debug_state(1920);
    __quex_debug_drop_out(1920);
goto TERMINAL_1393;

    __quex_assert_no_passage();
_2043: /* (1921 from 1915) */
    { last_acceptance = 1394; __quex_debug("last_acceptance = 1394\n"); }

_1921:

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1921);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1921, 2139);
        case 0x2E: goto _2027;
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: goto _2058;
        case 0x38: 
        case 0x39: goto _2054;
        case 0x45: goto _2024;
        case 0x58: goto _2034;
        case 0x65: goto _2024;
        case 0x78: goto _2034;

    }
_2139:
    __quex_debug_drop_out(1921);
goto TERMINAL_1394;

    __quex_assert_no_passage();
_1922: /* (1922 from 1915) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1922);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1922, 2140);
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
        case 0x67: goto _1955;
        case 0x68: goto _2029;
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: 
        case 0x6F: 
        case 0x70: 
        case 0x71: goto _1955;
        case 0x72: goto _2028;
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _1955;

    }
_2140:
    __quex_debug_drop_out(1922);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_1923: /* (1923 from 1915) */

    ++(me->buffer._input_p);
    __quex_debug_state(1923);
    __quex_debug_drop_out(1923);
goto TERMINAL_1384;

    __quex_assert_no_passage();
_1925: /* (1925 from 1915) */

    ++(me->buffer._input_p);
    __quex_debug_state(1925);
    __quex_debug_drop_out(1925);
goto TERMINAL_1377;

    __quex_assert_no_passage();
_1926: /* (1926 from 1915) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1926);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1926, 2143);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: 
        case 0x38: 
        case 0x39: goto _2051;

    }
_2143:
    __quex_debug_drop_out(1926);
goto TERMINAL_1387;

    __quex_assert_no_passage();
_1927: /* (1927 from 1915) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1927);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1927, 2144);
        case 0x3D: goto _2022;

    }
_2144:
    __quex_debug_drop_out(1927);

goto _2046; /* TERMINAL_FAILURE */

    __quex_assert_no_passage();
_1928: /* (1928 from 1915) */

    ++(me->buffer._input_p);
    __quex_debug_state(1928);
    __quex_debug_drop_out(1928);
goto TERMINAL_1378;

    __quex_assert_no_passage();
_1929: /* (1929 from 1915) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1929);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1929, 2146);
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
        case 0x71: goto _1955;
        case 0x72: goto _2018;
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _1955;

    }
_2146:
    __quex_debug_drop_out(1929);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_1930: /* (1930 from 1915) */

    ++(me->buffer._input_p);
    __quex_debug_state(1930);
    __quex_debug_drop_out(1930);
goto TERMINAL_1379;

    __quex_assert_no_passage();
_1931: /* (1931 from 1915) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1931);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1931, 2148);
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
        case 0x6D: goto _1955;
        case 0x6E: goto _2016;
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
        case 0x7A: goto _1955;

    }
_2148:
    __quex_debug_drop_out(1931);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_1932: /* (1932 from 1915) */

    ++(me->buffer._input_p);
    __quex_debug_state(1932);
    __quex_debug_drop_out(1932);
goto TERMINAL_1380;

    __quex_assert_no_passage();
_1933: /* (1933 from 1915) */

    ++(me->buffer._input_p);
    __quex_debug_state(1933);
    __quex_debug_drop_out(1933);
goto TERMINAL_1344;

    __quex_assert_no_passage();
_1934: /* (1934 from 1915) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1934);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1934, 2151);
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
        case 0x5F: goto _1955;
        case 0x61: goto _2011;
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
        case 0x6E: goto _1955;
        case 0x6F: goto _2010;
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
        case 0x7A: goto _1955;

    }
_2151:
    __quex_debug_drop_out(1934);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_1935: /* (1935 from 1915) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1935);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1935, 2152);
        case 0x3D: goto _2009;

    }
_2152:
    __quex_debug_drop_out(1935);
goto TERMINAL_1385;

    __quex_assert_no_passage();
_1936: /* (1936 from 1915) */

    ++(me->buffer._input_p);
    __quex_debug_state(1936);
    __quex_debug_drop_out(1936);
goto TERMINAL_1345;

    __quex_assert_no_passage();
_1937: /* (1937 from 1915) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1937);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1937, 2154);
        case 0x3D: goto _2007;
        case 0x3E: goto _2008;

    }
_2154:
    __quex_debug_drop_out(1937);
goto TERMINAL_1370;

    __quex_assert_no_passage();
_1938: /* (1938 from 1915) */

    ++(me->buffer._input_p);
    __quex_debug_state(1938);
    __quex_debug_drop_out(1938);
goto TERMINAL_1346;

    __quex_assert_no_passage();
_1939: /* (1939 from 1915) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1939);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1939, 2156);
        case 0x3D: goto _2006;

    }
_2156:
    __quex_debug_drop_out(1939);
goto TERMINAL_1371;

    __quex_assert_no_passage();
_1940: /* (1940 from 1915) */

    ++(me->buffer._input_p);
    __quex_debug_state(1940);
    __quex_debug_drop_out(1940);
goto TERMINAL_1390;

    __quex_assert_no_passage();
_1941: /* (1941 from 1915) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1941);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1941, 2158);
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
        case 0x6D: goto _1955;
        case 0x6E: goto _2002;
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
        case 0x7A: goto _1955;

    }
_2158:
    __quex_debug_drop_out(1941);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_1942: /* (1942 from 1915) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1942);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1942, 2159);
        case 0x2A: goto _2000;
        case 0x2F: goto _2001;

    }
_2159:
    __quex_debug_drop_out(1942);
goto TERMINAL_1381;

    __quex_assert_no_passage();
_1943: /* (1943 from 1915) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1943);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1943, 2160);
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
        case 0x65: goto _1955;
        case 0x66: goto _1997;
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: goto _1955;
        case 0x6E: goto _1998;
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
        case 0x7A: goto _1955;

    }
_2160:
    __quex_debug_drop_out(1943);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_1944: /* (1944 from 1915) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1944);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1944, 2161);
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
        case 0x6B: goto _1955;
        case 0x6C: goto _1993;
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
        case 0x7A: goto _1955;

    }
_2161:
    __quex_debug_drop_out(1944);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_1945: /* (1945 from 1915) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1945);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1945, 2162);
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
        case 0x64: goto _1955;
        case 0x65: goto _1984;
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
        case 0x7A: goto _1955;

    }
_2162:
    __quex_debug_drop_out(1945);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_1946: /* (1946 from 1915) */

    ++(me->buffer._input_p);
    __quex_debug_state(1946);
    __quex_debug_drop_out(1946);
goto TERMINAL_1389;

    __quex_assert_no_passage();
_1947: /* (1947 from 1915) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1947);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1947, 2164);
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
        case 0x67: goto _1955;
        case 0x68: goto _1980;
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
        case 0x7A: goto _1955;

    }
_2164:
    __quex_debug_drop_out(1947);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_1948: /* (1948 from 1915) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1948);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1948, 2165);
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
        case 0x6B: goto _1955;
        case 0x6C: goto _1974;
        case 0x6D: goto _1955;
        case 0x6E: goto _1973;
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
        case 0x7A: goto _1955;

    }
_2165:
    __quex_debug_drop_out(1948);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_1949: /* (1949 from 1915) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1949);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1949, 2166);
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
        case 0x64: goto _1955;
        case 0x65: goto _1971;
        case 0x66: 
        case 0x67: 
        case 0x68: 
        case 0x69: 
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: goto _1955;
        case 0x6F: goto _1970;
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
        case 0x7A: goto _1955;

    }
_2166:
    __quex_debug_drop_out(1949);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_1950: /* (1950 from 1915) */

    ++(me->buffer._input_p);
    __quex_debug_state(1950);
    __quex_debug_drop_out(1950);
goto TERMINAL_1343;

    __quex_assert_no_passage();
_1951: /* (1951 from 1915) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1951);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1951, 2168);
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
        case 0x5F: goto _1955;
        case 0x61: goto _1963;
        case 0x62: 
        case 0x63: 
        case 0x64: goto _1955;
        case 0x65: goto _1964;
        case 0x66: 
        case 0x67: 
        case 0x68: goto _1955;
        case 0x69: goto _1962;
        case 0x6A: 
        case 0x6B: 
        case 0x6C: 
        case 0x6D: 
        case 0x6E: goto _1955;
        case 0x6F: goto _1961;
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
        case 0x7A: goto _1955;

    }
_2168:
    __quex_debug_drop_out(1951);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_1952: /* (1952 from 1915) */

    ++(me->buffer._input_p);
    __quex_debug_state(1952);
    __quex_debug_drop_out(1952);
goto TERMINAL_1391;

    __quex_assert_no_passage();
_1953: /* (1953 from 1915) */

    ++(me->buffer._input_p);
    __quex_debug_state(1953);
    __quex_debug_drop_out(1953);
goto TERMINAL_1392;

    __quex_assert_no_passage();
_1954: /* (1954 from 1915) */

    ++(me->buffer._input_p);
    __quex_debug_state(1954);
    __quex_debug_drop_out(1954);
goto TERMINAL_1338;

    __quex_assert_no_passage();
_1956: /* (1956 from 1915) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(1956);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 1956, 2172);
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
        case 0x71: goto _1955;
        case 0x72: goto _1960;
        case 0x73: 
        case 0x74: 
        case 0x75: 
        case 0x76: 
        case 0x77: 
        case 0x78: 
        case 0x79: 
        case 0x7A: goto _1955;

    }
_2172:
    __quex_debug_drop_out(1956);
goto TERMINAL_1400;

    __quex_assert_no_passage();
_1957: /* (1957 from 1915) */

    ++(me->buffer._input_p);
    __quex_debug_state(1957);
    __quex_debug_drop_out(1957);
goto TERMINAL_1339;

    __quex_assert_no_passage();
_1958: /* (1958 from 1915) */

    ++(me->buffer._input_p);
    __quex_debug_state(1958);
    __quex_debug_drop_out(1958);
goto TERMINAL_1386;

    __quex_assert_no_passage();
_1959: /* (1959 from 1915) */

    ++(me->buffer._input_p);
    __quex_debug_state(1959);
    __quex_debug_drop_out(1959);
goto TERMINAL_1340;
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

TERMINAL_1338:
    __quex_debug("* terminal 1338:   <skip: ... (check also base modes)>\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 56 "lexer.qx"
    goto __SKIP;
    
#   line 7292 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1339:
    __quex_debug("* terminal 1339:   <skip>\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_end &= ~ ((size_t)0x3));
__QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_end += 4);

    {
__SKIP:
    /* Character Set Skipper: ''\t', '\r', ' '' */
    QUEX_BUFFER_ASSERT_CONSISTENCY(&me->buffer);
__QUEX_IF_COUNT_COLUMNS(reference_p = me->buffer._input_p);
    while( 1 + 1 == 2 ) {
_1420:
        if( (*me->buffer._input_p) < 0xD ) {
            switch( (*me->buffer._input_p) ) {
                case 0x0: QUEX_GOTO_RELOAD(_1422, 1420, 1423);
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
_1422:

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

TERMINAL_1340:
    __quex_debug("* terminal 1340:   \"#\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
        /*                          Delimiter: '\n',  */
    
        text_end = QUEX_NAME(Buffer_text_end)(&me->buffer);
    
    
    _1425:
    
        QUEX_BUFFER_ASSERT_CONSISTENCY(&me->buffer);
        __quex_assert(QUEX_NAME(Buffer_content_size)(&me->buffer) >= Skipper1424L );
    
        /* NOTE: If _input_p == end of buffer, then it will drop out immediately out of the
            *       loop below and drop into the buffer reload procedure.                      */
    
        /* Loop eating characters: Break-out as soon as the First Character of the Delimiter
            * (FCD) is reached. Thus, the FCD plays also the role of the Buffer Limit Code. There
            * are two reasons for break-out:
            *    (1) we reached a limit (end-of-file or buffer-limit)
            *    (2) there was really the FCD in the character stream
            * This must be distinguished after the loop was exited. But, during the 'swallowing' we
            * are very fast, because we do not have to check for two different characters.        */
        *text_end = Skipper1424[0]; /* Overwrite BufferLimitCode (BLC).  */
    _1424_LOOP:
                input = *(me->buffer._input_p);
    
                if( input == Skipper1424[0] ) {
    
                        goto _1424_LOOP_EXIT;
                }
    
        ++(me->buffer._input_p); /* Now, BLC cannot occur. See above. */
        goto _1424_LOOP;
    _1424_LOOP_EXIT:
    
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
        if( QUEX_NAME(Buffer_distance_input_to_text_end)(&me->buffer) < (ptrdiff_t)Skipper1424L ) {
                /* (2.1) Reload required. */
                goto _1426;
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
    
    _1426:
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
                goto _1425;
        }
        /* Here, either the loading failed or it is not enough space to carry a closing delimiter */
        me->buffer._input_p = me->buffer._lexeme_start_p;
#define Closer "\n"
#   line 74 "lexer.qx"
    
                self_write_token_p()->text = "Warning: Unterminated comment";
                self_send(TK_WARNING);
    
    
#   line 7500 "lexer.cpp"
#undef  Closer
    RETURN;

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1341:
    __quex_debug("* terminal 1341:   \"/*\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
        Skipper1427_Opener_it = (QUEX_TYPE_CHARACTER*)Skipper1427_Opener;
        Skipper1427_Closer_it = (QUEX_TYPE_CHARACTER*)Skipper1427_Closer;
        /* text_end                           = QUEX_NAME(Buffer_text_end)(&me->buffer); */
        __QUEX_IF_COUNT_COLUMNS(reference_p = QUEX_NAME(Buffer_tell_memory_adr)(&me->buffer));
    
    
    _1428:
    
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
                        goto _1429;
                }
                if( input == *Skipper1427_Closer_it ) {
                        ++Skipper1427_Closer_it;
                        if( Skipper1427_Closer_it == Skipper1427_CloserEnd ) {
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
                            Skipper1427_Opener_it = (QUEX_TYPE_CHARACTER*)Skipper1427_Opener;
                            Skipper1427_Closer_it = (QUEX_TYPE_CHARACTER*)Skipper1427_Closer;
                            goto CONTINUE_1427;
                        }
                } else {
                        Skipper1427_Closer_it = (QUEX_TYPE_CHARACTER*)Skipper1427_Closer;
                }
                if( input == *Skipper1427_Opener_it ) {
                        ++Skipper1427_Opener_it;
                        if( Skipper1427_Opener_it == Skipper1427_OpenerEnd ) {
                            ++counter;
                            Skipper1427_Opener_it = (QUEX_TYPE_CHARACTER*)Skipper1427_Opener;
                            Skipper1427_Closer_it = (QUEX_TYPE_CHARACTER*)Skipper1427_Closer;
                            goto CONTINUE_1427;
                        }
                } else {
                        Skipper1427_Opener_it = (QUEX_TYPE_CHARACTER*)Skipper1427_Opener;
                }
    CONTINUE_1427:
    
        __QUEX_IF_COUNT_IF( input == (QUEX_TYPE_CHARACTER)'\n' ) {
                __QUEX_IF_COUNT_LINES_ADD((size_t)1);
                __QUEX_IF_COUNT_COLUMNS_SET((size_t)0);
                __QUEX_IF_COUNT_COLUMNS(reference_p = QUEX_NAME(Buffer_tell_memory_adr)(&me->buffer));
        }
    
                ++(me->buffer._input_p); /* Now, BLC cannot occur. See above. */
        }
    
    _1429:
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
                goto _1428; /* End of range reached.             */
        }
        /* Here, either the loading failed or it is not enough space to carry a closing delimiter */
        me->buffer._input_p = me->buffer._lexeme_start_p;
#define Closer "*/"
#   line 74 "lexer.qx"
    
                self_write_token_p()->text = "Warning: Unterminated comment";
                self_send(TK_WARNING);
    
    
#   line 7617 "lexer.cpp"
#undef  Closer
    RETURN;

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1342:
    __quex_debug("* terminal 1342:   \"//\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
        /*                          Delimiter: '\n',  */
    
        text_end = QUEX_NAME(Buffer_text_end)(&me->buffer);
    
    
    _1431:
    
        QUEX_BUFFER_ASSERT_CONSISTENCY(&me->buffer);
        __quex_assert(QUEX_NAME(Buffer_content_size)(&me->buffer) >= Skipper1430L );
    
        /* NOTE: If _input_p == end of buffer, then it will drop out immediately out of the
            *       loop below and drop into the buffer reload procedure.                      */
    
        /* Loop eating characters: Break-out as soon as the First Character of the Delimiter
            * (FCD) is reached. Thus, the FCD plays also the role of the Buffer Limit Code. There
            * are two reasons for break-out:
            *    (1) we reached a limit (end-of-file or buffer-limit)
            *    (2) there was really the FCD in the character stream
            * This must be distinguished after the loop was exited. But, during the 'swallowing' we
            * are very fast, because we do not have to check for two different characters.        */
        *text_end = Skipper1430[0]; /* Overwrite BufferLimitCode (BLC).  */
    _1430_LOOP:
                input = *(me->buffer._input_p);
    
                if( input == Skipper1430[0] ) {
    
                        goto _1430_LOOP_EXIT;
                }
    
        ++(me->buffer._input_p); /* Now, BLC cannot occur. See above. */
        goto _1430_LOOP;
    _1430_LOOP_EXIT:
    
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
        if( QUEX_NAME(Buffer_distance_input_to_text_end)(&me->buffer) < (ptrdiff_t)Skipper1430L ) {
                /* (2.1) Reload required. */
                goto _1432;
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
    
    _1432:
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
                goto _1431;
        }
        /* Here, either the loading failed or it is not enough space to carry a closing delimiter */
        me->buffer._input_p = me->buffer._lexeme_start_p;
#define Closer "\n"
#   line 74 "lexer.qx"
    
                self_write_token_p()->text = "Warning: Unterminated comment";
                self_send(TK_WARNING);
    
    
#   line 7750 "lexer.cpp"
#undef  Closer
    RETURN;

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1343:
    __quex_debug("* terminal 1343:   \"\\n\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_LINES_ADD(1);
__QUEX_IF_COUNT_COLUMNS_SET(1);
    {
#   line 79 "lexer.qx"
    self_send(TK_NL);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 7767 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1344:
    __quex_debug("* terminal 1344:   \";\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 80 "lexer.qx"
    self_send(TK_SCOLON);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 7781 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1345:
    __quex_debug("* terminal 1345:   \"\\\"\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 85 "lexer.qx"
        self.string_delimiter='\"'; self << STRING;
    
#   line 7794 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1346:
    __quex_debug("* terminal 1346:   '\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 86 "lexer.qx"
        self.string_delimiter='\''; self << STRING;
    
#   line 7807 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1347:
    __quex_debug("* terminal 1347:   def\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(3);
    {
#   line 89 "lexer.qx"
    self_send(TK_DEF);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 7821 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1348:
    __quex_debug("* terminal 1348:   class\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(5);
    {
#   line 90 "lexer.qx"
    self_send(TK_CLASS);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 7835 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1349:
    __quex_debug("* terminal 1349:   do\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 91 "lexer.qx"
    self_send(TK_DO);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 7849 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1350:
    __quex_debug("* terminal 1350:   end\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(3);
    {
#   line 92 "lexer.qx"
    self_send(TK_END);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 7863 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1351:
    __quex_debug("* terminal 1351:   if\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 94 "lexer.qx"
    self_send(TK_IF);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 7877 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1352:
    __quex_debug("* terminal 1352:   then\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(4);
    {
#   line 95 "lexer.qx"
    self_send(TK_THEN);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 7891 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1353:
    __quex_debug("* terminal 1353:   else\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(4);
    {
#   line 96 "lexer.qx"
    self_send(TK_ELSE);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 7905 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1354:
    __quex_debug("* terminal 1354:   elif\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(4);
    {
#   line 97 "lexer.qx"
    self_send(TK_ELSEIF);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 7919 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1355:
    __quex_debug("* terminal 1355:   while\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(5);
    {
#   line 98 "lexer.qx"
    self_send(TK_WHILE);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 7933 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1356:
    __quex_debug("* terminal 1356:   for\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(3);
    {
#   line 99 "lexer.qx"
    self_send(TK_FOR);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 7947 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1357:
    __quex_debug("* terminal 1357:   in\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 100 "lexer.qx"
    self_send(TK_IN);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 7961 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1358:
    __quex_debug("* terminal 1358:   repeat\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(6);
    {
#   line 101 "lexer.qx"
    self_send(TK_REPEAT);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 7975 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1359:
    __quex_debug("* terminal 1359:   until\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(5);
    {
#   line 102 "lexer.qx"
    self_send(TK_UNTIL);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 7989 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1360:
    __quex_debug("* terminal 1360:   return\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(6);
    {
#   line 104 "lexer.qx"
    self_send(TK_RETURN);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8003 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1361:
    __quex_debug("* terminal 1361:   break\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(5);
    {
#   line 105 "lexer.qx"
    self_send(TK_BREAK);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8017 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1362:
    __quex_debug("* terminal 1362:   next\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(4);
    {
#   line 106 "lexer.qx"
    self_send(TK_NEXT);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8031 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1363:
    __quex_debug("* terminal 1363:   local\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(5);
    {
#   line 108 "lexer.qx"
    self_send(TK_LOCAL);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8045 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1364:
    __quex_debug("* terminal 1364:   nil\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(3);
    {
#   line 110 "lexer.qx"
    self_send(TK_NIL);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8059 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1365:
    __quex_debug("* terminal 1365:   true\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(4);
    {
#   line 111 "lexer.qx"
    self_send(TK_TRUE);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8073 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1366:
    __quex_debug("* terminal 1366:   false\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(5);
    {
#   line 112 "lexer.qx"
    self_send(TK_FALSE);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8087 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1367:
    __quex_debug("* terminal 1367:   or\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 115 "lexer.qx"
    self_send(TK_OR);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8101 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1368:
    __quex_debug("* terminal 1368:   and\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(3);
    {
#   line 116 "lexer.qx"
    self_send(TK_AND);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8115 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1369:
    __quex_debug("* terminal 1369:   not\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(3);
    {
#   line 117 "lexer.qx"
    self_send(TK_NOT);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8129 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1370:
    __quex_debug("* terminal 1370:   <\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 118 "lexer.qx"
    self_send(TK_L);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8143 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1371:
    __quex_debug("* terminal 1371:   >\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 119 "lexer.qx"
    self_send(TK_G);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8157 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1372:
    __quex_debug("* terminal 1372:   <=\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 120 "lexer.qx"
    self_send(TK_LEQ);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8171 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1373:
    __quex_debug("* terminal 1373:   >=\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 121 "lexer.qx"
    self_send(TK_GEQ);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8185 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1374:
    __quex_debug("* terminal 1374:   !=\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 122 "lexer.qx"
    self_send(TK_NEQ);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8199 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1375:
    __quex_debug("* terminal 1375:   <>\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 123 "lexer.qx"
    self_send(TK_NEQ);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8213 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1376:
    __quex_debug("* terminal 1376:   ==\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 124 "lexer.qx"
    self_send(TK_EQ);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8227 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1377:
    __quex_debug("* terminal 1377:   \":\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 126 "lexer.qx"
    self_send(TK_COLON);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8241 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1378:
    __quex_debug("* terminal 1378:   \"+\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 127 "lexer.qx"
    self_send(TK_PLUS);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8255 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1379:
    __quex_debug("* terminal 1379:   \"-\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 128 "lexer.qx"
    self_send(TK_MINUS);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8269 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1380:
    __quex_debug("* terminal 1380:   \"*\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 129 "lexer.qx"
    self_send(TK_MUL);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8283 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1381:
    __quex_debug("* terminal 1381:   \"/\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 130 "lexer.qx"
    self_send(TK_DIV);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8297 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1382:
    __quex_debug("* terminal 1382:   \"%\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 131 "lexer.qx"
    self_send(TK_MOD);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8311 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1383:
    __quex_debug("* terminal 1383:   \"|\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 132 "lexer.qx"
    self_send(TK_PIPE);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8325 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1384:
    __quex_debug("* terminal 1384:   \"^\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 133 "lexer.qx"
    self_send(TK_EXP);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8339 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1385:
    __quex_debug("* terminal 1385:   \"=\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 134 "lexer.qx"
    self_send(TK_ASSIG);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8353 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1386:
    __quex_debug("* terminal 1386:   \",\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 137 "lexer.qx"
    self_send(TK_COMMA);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8367 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1387:
    __quex_debug("* terminal 1387:   \".\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 138 "lexer.qx"
    self_send(TK_DOT);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8381 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1388:
    __quex_debug("* terminal 1388:   \"[\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 140 "lexer.qx"
    self_send(TK_SBL);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8395 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1389:
    __quex_debug("* terminal 1389:   \"]\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 141 "lexer.qx"
    self_send(TK_SBR);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8409 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1390:
    __quex_debug("* terminal 1390:   \"{\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 142 "lexer.qx"
    self_send(TK_CBL);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8423 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1391:
    __quex_debug("* terminal 1391:   \"}\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 143 "lexer.qx"
    self_send(TK_CBR);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8437 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1392:
    __quex_debug("* terminal 1392:   \"(\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 144 "lexer.qx"
    self_send(TK_PL);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8451 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1393:
    __quex_debug("* terminal 1393:   \")\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 145 "lexer.qx"
    self_send(TK_PR);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8465 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1394:
    __quex_debug("* terminal 1394:   0[0-7]*\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(LexemeL);
    QUEX_LEXEME_TERMINATING_ZERO_SET(&me->buffer);
    {
#   line 149 "lexer.qx"
    self_write_token_p()->content.integer = stoi(Lexeme,8);
    self_send(TK_INT);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8481 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1395:
    __quex_debug("* terminal 1395:   [1-9][0-9]*\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(LexemeL);
    QUEX_LEXEME_TERMINATING_ZERO_SET(&me->buffer);
    {
#   line 150 "lexer.qx"
    self_write_token_p()->content.integer = stoi(Lexeme,10);
    self_send(TK_INT);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8497 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1396:
    __quex_debug("* terminal 1396:   0[xX][:xdigit:]+\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(LexemeL);
    QUEX_LEXEME_TERMINATING_ZERO_SET(&me->buffer);
    {
#   line 151 "lexer.qx"
    self_write_token_p()->content.integer = stoi(Lexeme,16);
    self_send(TK_INT);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8513 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1397:
    __quex_debug("* terminal 1397:   [0-9]*\\.?[0-9]+([eE][\\-+]?[0-9]+)?\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(LexemeL);
    QUEX_LEXEME_TERMINATING_ZERO_SET(&me->buffer);
    {
#   line 153 "lexer.qx"
    self_write_token_p()->content.real = atof((char*)(Lexeme));
    self_send(TK_REAL);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8529 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1398:
    __quex_debug("* terminal 1398:   nan\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(3);
    {
#   line 154 "lexer.qx"
    self_write_token_p()->content.real = NAN;
    self_send(TK_REAL);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8544 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1399:
    __quex_debug("* terminal 1399:   inf\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(3);
    {
#   line 156 "lexer.qx"
    
        self_write_token_p()->content.real = INFINITY;
        self_send(TK_REAL);
    
    
#   line 8560 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1400:
    __quex_debug("* terminal 1400:   {ualpha}{ualnum}*\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(LexemeL);
    {
#   line 161 "lexer.qx"
    QUEX_NAME_TOKEN(take_text)(self_write_token_p(), &self, self.buffer._lexeme_start_p, self.buffer._input_p);
    self_send(TK_IDENT);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 8575 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;


_2046: /* TERMINAL: FAILURE */
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
    
    
#   line 8608 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION_2;


/* TERMINAL: END_OF_STREAM */
_1423:
__QUEX_IF_COUNT_SHIFT_VALUES();
    {
#   line 81 "lexer.qx"
    self_send(TK_EOS);
    
#   line 8621 "lexer.cpp"

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
        case 1420: { goto _1420; }
        case 1422: { goto _1422; }
        case 1423: { goto _1423; }
        case 1425: { goto _1425; }
        case 1428: { goto _1428; }
        case 1431: { goto _1431; }
        case 1915: { goto _1915; }
        case 1916: { goto _1916; }
        case 1917: { goto _1917; }
        case 1918: { goto _1918; }
        case 1919: { goto _1919; }
        case 1920: { goto _1920; }
        case 1921: { goto _1921; }
        case 1922: { goto _1922; }
        case 1923: { goto _1923; }
        case 1924: { goto _1924; }
        case 1925: { goto _1925; }
        case 1926: { goto _1926; }
        case 1927: { goto _1927; }
        case 1928: { goto _1928; }
        case 1929: { goto _1929; }
        case 1930: { goto _1930; }
        case 1931: { goto _1931; }
        case 1932: { goto _1932; }
        case 1933: { goto _1933; }
        case 1934: { goto _1934; }
        case 1935: { goto _1935; }
        case 1936: { goto _1936; }
        case 1937: { goto _1937; }
        case 1938: { goto _1938; }
        case 1939: { goto _1939; }
        case 1940: { goto _1940; }
        case 1941: { goto _1941; }
        case 1942: { goto _1942; }
        case 1943: { goto _1943; }
        case 1944: { goto _1944; }
        case 1945: { goto _1945; }
        case 1946: { goto _1946; }
        case 1947: { goto _1947; }
        case 1948: { goto _1948; }
        case 1949: { goto _1949; }
        case 1950: { goto _1950; }
        case 1951: { goto _1951; }
        case 1952: { goto _1952; }
        case 1953: { goto _1953; }
        case 1954: { goto _1954; }
        case 1955: { goto _1955; }
        case 1956: { goto _1956; }
        case 1957: { goto _1957; }
        case 1958: { goto _1958; }
        case 1959: { goto _1959; }
        case 1960: { goto _1960; }
        case 1961: { goto _1961; }
        case 1962: { goto _1962; }
        case 1963: { goto _1963; }
        case 1964: { goto _1964; }
        case 1965: { goto _1965; }
        case 1966: { goto _1966; }
        case 1967: { goto _1967; }
        case 1968: { goto _1968; }
        case 1969: { goto _1969; }
        case 1970: { goto _1970; }
        case 1971: { goto _1971; }
        case 1972: { goto _1972; }
        case 1973: { goto _1973; }
        case 1974: { goto _1974; }
        case 1975: { goto _1975; }
        case 1976: { goto _1976; }
        case 1977: { goto _1977; }
        case 1978: { goto _1978; }
        case 1979: { goto _1979; }
        case 1980: { goto _1980; }
        case 1981: { goto _1981; }
        case 1982: { goto _1982; }
        case 1983: { goto _1983; }
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
        case 2043: { goto _2043; }
        case 2044: { goto _2044; }
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
        case 2103: { goto _2103; }
        case 2104: { goto _2104; }
        case 2105: { goto _2105; }
        case 2106: { goto _2106; }
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
        case 2135: { goto _2135; }
        case 2139: { goto _2139; }
        case 2140: { goto _2140; }
        case 2143: { goto _2143; }
        case 2144: { goto _2144; }
        case 2146: { goto _2146; }
        case 2148: { goto _2148; }
        case 2151: { goto _2151; }
        case 2152: { goto _2152; }
        case 2154: { goto _2154; }
        case 2156: { goto _2156; }
        case 2158: { goto _2158; }
        case 2159: { goto _2159; }
        case 2160: { goto _2160; }
        case 2161: { goto _2161; }
        case 2162: { goto _2162; }
        case 2164: { goto _2164; }
        case 2165: { goto _2165; }
        case 2166: { goto _2166; }
        case 2168: { goto _2168; }
        case 2172: { goto _2172; }

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
_2350: /* INIT_STATE_TRANSITION_BLOCK */
    input = *(me->buffer._input_p);
    __quex_debug("Init State\n");
    __quex_debug_state(2318);
    if( input < 0x23 ) {
        switch( input ) {
            case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2318, 1423);
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
            case 0x21: goto _2321;
            case 0x22: goto _2322;

        }
    } else {
        if( input < 0x27 ) {
            goto _2321;
        } else if( input == 0x27 ) {
            goto _2320;
        } else if( input < 0x5C ) {
            goto _2321;
        } else if( input == 0x5C ) {
            goto _2319;
        } else {
            goto _2321;
        }
    }
    __quex_debug_drop_out(2318);

goto _2046; /* TERMINAL_FAILURE */

_2318:


    ++(me->buffer._input_p);
    goto _2350;


    __quex_assert_no_passage();
_2352: /* (2324 from 2322) */
    position[0] = me->buffer._input_p; __quex_debug("position[0] = input_p;\n");

_2324: /* (2324 from 2324) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2324);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2324, 2353);
        case 0x9: 
        case 0xA: 
        case 0xD: 
        case 0x20: goto _2324;
        case 0x22: goto _2323;

    }
_2353:
    __quex_debug_drop_out(2324);
__quex_assert(position[0] != 0x0);
me->buffer._input_p = position[0];

goto TERMINAL_1403;

    __quex_assert_no_passage();
_2354: /* (2326 from 2320) */
    position[0] = me->buffer._input_p; __quex_debug("position[0] = input_p;\n");

_2326: /* (2326 from 2326) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2326);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2326, 2355);
        case 0x9: 
        case 0xA: 
        case 0xD: 
        case 0x20: goto _2326;
        case 0x27: goto _2325;

    }
_2355:
    __quex_debug_drop_out(2326);
__quex_assert(position[0] != 0x0);
me->buffer._input_p = position[0];

goto TERMINAL_1404;

    __quex_assert_no_passage();
_2321: /* (2321 from 2321) (2321 from 2318) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2321);
    if( input < 0x23 ) {
        switch( input ) {
            case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2321, 2356);
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
            case 0x21: goto _2321;

        }
    } else {
        if( input < 0x27 ) {
            goto _2321;
        } else if( input == 0x27 ) {

        } else if( input < 0x5C ) {
            goto _2321;
        } else if( input == 0x5C ) {

        } else {
            goto _2321;
        }
    }
_2356:
    __quex_debug_drop_out(2321);
goto TERMINAL_1405;

    __quex_assert_no_passage();
_2342: /* (2342 from 2328) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2342);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2342, 2357);
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
        case 0x66: goto _2343;

    }
_2357:
    __quex_debug_drop_out(2342);
goto TERMINAL_1415;

    __quex_assert_no_passage();
_2343: /* (2343 from 2342) */

    ++(me->buffer._input_p);
    __quex_debug_state(2343);
    __quex_debug_drop_out(2343);
goto TERMINAL_1415;

    __quex_assert_no_passage();
_2344: /* (2344 from 2327) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2344);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2344, 2359);
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
        case 0x66: goto _2345;

    }
_2359:
    __quex_debug_drop_out(2344);
goto TERMINAL_1416;

    __quex_assert_no_passage();
_2345: /* (2345 from 2344) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2345);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2345, 2360);
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
        case 0x66: goto _2346;

    }
_2360:
    __quex_debug_drop_out(2345);
goto TERMINAL_1416;

    __quex_assert_no_passage();
_2346: /* (2346 from 2345) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2346);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2346, 2361);
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
        case 0x66: goto _2347;

    }
_2361:
    __quex_debug_drop_out(2346);
goto TERMINAL_1416;

    __quex_assert_no_passage();
_2347: /* (2347 from 2346) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2347);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2347, 2362);
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
        case 0x66: goto _2348;

    }
_2362:
    __quex_debug_drop_out(2347);
goto TERMINAL_1416;

    __quex_assert_no_passage();
_2348: /* (2348 from 2347) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2348);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2348, 2363);
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
        case 0x66: goto _2349;

    }
_2363:
    __quex_debug_drop_out(2348);
goto TERMINAL_1416;

    __quex_assert_no_passage();
_2349: /* (2349 from 2348) */

    ++(me->buffer._input_p);
    __quex_debug_state(2349);
    __quex_debug_drop_out(2349);
goto TERMINAL_1416;

    __quex_assert_no_passage();
_2323: /* (2323 from 2324) (2323 from 2322) */

    ++(me->buffer._input_p);
    __quex_debug_state(2323);
    __quex_debug_drop_out(2323);
goto TERMINAL_1401;

    __quex_assert_no_passage();
_2325: /* (2325 from 2326) (2325 from 2320) */

    ++(me->buffer._input_p);
    __quex_debug_state(2325);
    __quex_debug_drop_out(2325);
goto TERMINAL_1402;

    __quex_assert_no_passage();
_2327: /* (2327 from 2319) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2327);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2327, 2367);
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
        case 0x66: goto _2344;

    }
_2367:
    __quex_debug_drop_out(2327);

goto _2046; /* TERMINAL_FAILURE */

    __quex_assert_no_passage();
_2328: /* (2328 from 2319) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2328);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2328, 2368);
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
        case 0x66: goto _2342;

    }
_2368:
    __quex_debug_drop_out(2328);

goto _2046; /* TERMINAL_FAILURE */

    __quex_assert_no_passage();
_2329: /* (2329 from 2319) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2329);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2329, 2369);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: goto _2340;

    }
_2369:
    __quex_debug_drop_out(2329);
goto TERMINAL_1414;

    __quex_assert_no_passage();
_2330: /* (2330 from 2319) */

    ++(me->buffer._input_p);
    __quex_debug_state(2330);
    __quex_debug_drop_out(2330);
goto TERMINAL_1407;

    __quex_assert_no_passage();
_2331: /* (2331 from 2319) */

    ++(me->buffer._input_p);
    __quex_debug_state(2331);
    __quex_debug_drop_out(2331);
goto TERMINAL_1406;

    __quex_assert_no_passage();
_2332: /* (2332 from 2319) */

    ++(me->buffer._input_p);
    __quex_debug_state(2332);
    __quex_debug_drop_out(2332);
goto TERMINAL_1417;

    __quex_assert_no_passage();
_2333: /* (2333 from 2319) */

    ++(me->buffer._input_p);
    __quex_debug_state(2333);
    __quex_debug_drop_out(2333);
goto TERMINAL_1408;

    __quex_assert_no_passage();
_2334: /* (2334 from 2319) */

    ++(me->buffer._input_p);
    __quex_debug_state(2334);
    __quex_debug_drop_out(2334);
goto TERMINAL_1410;

    __quex_assert_no_passage();
_2335: /* (2335 from 2319) */

    ++(me->buffer._input_p);
    __quex_debug_state(2335);
    __quex_debug_drop_out(2335);
goto TERMINAL_1412;

    __quex_assert_no_passage();
_2336: /* (2336 from 2319) */

    ++(me->buffer._input_p);
    __quex_debug_state(2336);
    __quex_debug_drop_out(2336);
goto TERMINAL_1418;

    __quex_assert_no_passage();
_2337: /* (2337 from 2319) */

    ++(me->buffer._input_p);
    __quex_debug_state(2337);
    __quex_debug_drop_out(2337);
goto TERMINAL_1409;

    __quex_assert_no_passage();
_2338: /* (2338 from 2319) */

    ++(me->buffer._input_p);
    __quex_debug_state(2338);
    __quex_debug_drop_out(2338);
goto TERMINAL_1411;

    __quex_assert_no_passage();
_2339: /* (2339 from 2319) */

    ++(me->buffer._input_p);
    __quex_debug_state(2339);
    __quex_debug_drop_out(2339);
goto TERMINAL_1413;

    __quex_assert_no_passage();
_2340: /* (2340 from 2329) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2340);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2340, 2380);
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: goto _2341;

    }
_2380:
    __quex_debug_drop_out(2340);
goto TERMINAL_1414;

    __quex_assert_no_passage();
_2341: /* (2341 from 2340) */

    ++(me->buffer._input_p);
    __quex_debug_state(2341);
    __quex_debug_drop_out(2341);
goto TERMINAL_1414;

    __quex_assert_no_passage();
_2319: /* (2319 from 2318) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2319);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2319, 2382);
        case 0x22: goto _2336;
        case 0x27: goto _2332;
        case 0x30: 
        case 0x31: 
        case 0x32: 
        case 0x33: 
        case 0x34: 
        case 0x35: 
        case 0x36: 
        case 0x37: goto _2329;
        case 0x5C: goto _2339;
        case 0x61: goto _2333;
        case 0x62: goto _2337;
        case 0x66: goto _2334;
        case 0x6E: goto _2331;
        case 0x72: goto _2338;
        case 0x74: goto _2330;
        case 0x75: goto _2327;
        case 0x76: goto _2335;
        case 0x78: goto _2328;

    }
_2382:
    __quex_debug_drop_out(2319);

goto _2046; /* TERMINAL_FAILURE */

    __quex_assert_no_passage();
_2320: /* (2320 from 2318) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2320);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2320, 2383);
        case 0x9: 
        case 0xA: 
        case 0xD: 
        case 0x20: goto _2354;
        case 0x27: goto _2325;

    }
_2383:
    __quex_debug_drop_out(2320);
goto TERMINAL_1404;

    __quex_assert_no_passage();
_2322: /* (2322 from 2318) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(2322);
    switch( input ) {
        case 0x0: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 2322, 2384);
        case 0x9: 
        case 0xA: 
        case 0xD: 
        case 0x20: goto _2352;
        case 0x22: goto _2323;

    }
_2384:
    __quex_debug_drop_out(2322);
goto TERMINAL_1403;
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

TERMINAL_1401:
    __quex_debug("* terminal 1401:   \\\"[:space:]*\\\"\n");
    __QUEX_COUNT_VOID(&self, LexemeBegin, LexemeEnd);
    {
#   line 178 "lexer.qx"
    
        if(self.string_delimiter != '\"')
            self_accumulator_add(LexemeBegin, LexemeEnd);
    
    
#   line 9775 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1402:
    __quex_debug("* terminal 1402:   '[:space:]*'\n");
    __QUEX_COUNT_VOID(&self, LexemeBegin, LexemeEnd);
    {
#   line 184 "lexer.qx"
    
        if(self.string_delimiter != '\'')
            self_accumulator_add(LexemeBegin, LexemeEnd);
    
    
#   line 9790 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1403:
    __quex_debug("* terminal 1403:   \\\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 190 "lexer.qx"
    
        if (self.string_delimiter == '\"')
        {
            self_accumulator_flush(TK_STRING);
            self << MAIN;
        }
        else
        {
            self_accumulator_add_character('\"');
        }
    
    
#   line 9813 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1404:
    __quex_debug("* terminal 1404:   '\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 202 "lexer.qx"
    
        if (self.string_delimiter == '\'')
        {
            self_accumulator_flush(TK_STRING);
            self << MAIN;
        }
        else
        {
            self_accumulator_add_character('\'');
        }
    
    
#   line 9836 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1405:
    __quex_debug("* terminal 1405:   [^\\\\\\\"']+\n");
    __QUEX_COUNT_VOID(&self, LexemeBegin, LexemeEnd);
    {
#   line 214 "lexer.qx"
        self_accumulator_add(LexemeBegin, LexemeEnd);
    
#   line 9848 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1406:
    __quex_debug("* terminal 1406:   \\\\n\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 217 "lexer.qx"
        self_accumulator_add_character('\n');
    
#   line 9861 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1407:
    __quex_debug("* terminal 1407:   \\\\t\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 218 "lexer.qx"
        self_accumulator_add_character('\t');
    
#   line 9874 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1408:
    __quex_debug("* terminal 1408:   \\\\a\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 219 "lexer.qx"
        self_accumulator_add_character('\a');
    
#   line 9887 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1409:
    __quex_debug("* terminal 1409:   \\\\b\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 220 "lexer.qx"
        self_accumulator_add_character('\b');
    
#   line 9900 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1410:
    __quex_debug("* terminal 1410:   \\\\f\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 221 "lexer.qx"
        self_accumulator_add_character('\f');
    
#   line 9913 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1411:
    __quex_debug("* terminal 1411:   \\\\r\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 222 "lexer.qx"
        self_accumulator_add_character('\r');
    
#   line 9926 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1412:
    __quex_debug("* terminal 1412:   \\\\v\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 223 "lexer.qx"
        self_accumulator_add_character('\v');
    
#   line 9939 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1413:
    __quex_debug("* terminal 1413:   \\\\\\\\\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 224 "lexer.qx"
        self_accumulator_add_character('\\');
    
#   line 9952 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1414:
    __quex_debug("* terminal 1414:   \\\\[0-7]{1,3}\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(LexemeL);
    QUEX_LEXEME_TERMINATING_ZERO_SET(&me->buffer);
    {
#   line 226 "lexer.qx"
        self_accumulator_add_character((QUEX_TYPE_CHARACTER)stoi(Lexeme+1,8));
    
#   line 9966 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1415:
    __quex_debug("* terminal 1415:   \\\\x[:xdigit:]{1,2}\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(LexemeL);
    QUEX_LEXEME_TERMINATING_ZERO_SET(&me->buffer);
    {
#   line 227 "lexer.qx"
        self_accumulator_add_character((QUEX_TYPE_CHARACTER)stoi(Lexeme+2,16));
    
#   line 9980 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1416:
    __quex_debug("* terminal 1416:   \\\\u[:xdigit:]{1,6}\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(LexemeL);
    QUEX_LEXEME_TERMINATING_ZERO_SET(&me->buffer);
    {
#   line 229 "lexer.qx"
    
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
    
    
#   line 10033 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1417:
    __quex_debug("* terminal 1417:   \\\\'\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 270 "lexer.qx"
        self_accumulator_add_character('\'');
    
#   line 10046 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_1418:
    __quex_debug("* terminal 1418:   \\\\\\\"\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(2);
    {
#   line 271 "lexer.qx"
        self_accumulator_add_character('\"');
    
#   line 10059 "lexer.cpp"

    }
    goto __REENTRY_PREPARATION;


_2046: /* TERMINAL: FAILURE */
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
_1423:
__QUEX_IF_COUNT_SHIFT_VALUES();
    {
#   line 172 "lexer.qx"
    
        self << MAIN;
        throw ParseError("Syntax error: Unterminated string");
    
    
#   line 10099 "lexer.cpp"

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
        case 1423: { goto _1423; }
        case 2318: { goto _2318; }
        case 2319: { goto _2319; }
        case 2320: { goto _2320; }
        case 2321: { goto _2321; }
        case 2322: { goto _2322; }
        case 2323: { goto _2323; }
        case 2324: { goto _2324; }
        case 2325: { goto _2325; }
        case 2326: { goto _2326; }
        case 2327: { goto _2327; }
        case 2328: { goto _2328; }
        case 2329: { goto _2329; }
        case 2330: { goto _2330; }
        case 2331: { goto _2331; }
        case 2332: { goto _2332; }
        case 2333: { goto _2333; }
        case 2334: { goto _2334; }
        case 2335: { goto _2335; }
        case 2336: { goto _2336; }
        case 2337: { goto _2337; }
        case 2338: { goto _2338; }
        case 2339: { goto _2339; }
        case 2340: { goto _2340; }
        case 2341: { goto _2341; }
        case 2342: { goto _2342; }
        case 2343: { goto _2343; }
        case 2344: { goto _2344; }
        case 2345: { goto _2345; }
        case 2346: { goto _2346; }
        case 2347: { goto _2347; }
        case 2348: { goto _2348; }
        case 2349: { goto _2349; }
        case 2352: { goto _2352; }
        case 2353: { goto _2353; }
        case 2354: { goto _2354; }
        case 2355: { goto _2355; }
        case 2356: { goto _2356; }
        case 2357: { goto _2357; }
        case 2359: { goto _2359; }
        case 2360: { goto _2360; }
        case 2361: { goto _2361; }
        case 2362: { goto _2362; }
        case 2363: { goto _2363; }
        case 2367: { goto _2367; }
        case 2368: { goto _2368; }
        case 2369: { goto _2369; }
        case 2380: { goto _2380; }
        case 2382: { goto _2382; }
        case 2383: { goto _2383; }
        case 2384: { goto _2384; }

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

