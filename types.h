#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include <stdint.h>

#define TOKEN_T quex::Token

#include <string>

#ifndef DEBUG
    #define NDEBUG
#endif
#include<cassert>

namespace AYA
{
    typedef std::string IDENT_T;

    typedef long INT_T;
    typedef double REAL_T;
    typedef std::string STRING_T;

    /// Basic Type
    struct BType
    {
        enum
        {
            NIL = 0,

            /// Numbers
            NUMBER  = 010,

            INT     = 010,
            REAL    = 011,

            /// Function bindings
            CFUNC   = 020,

            /// ManagedMemory objects:
            MANAGED = 040,

            /// *Objects
            REF     = 0140,

            OBJ     = 0140,
            TYPE    = 0141,
            FUNC    = 0142,
            STR     = 0143,
            LIST    = 0144,
            DICT    = 0145,
            FILE    = 0146,

            // User-defined
            USR     = 0147,

            /// *Prototypes
            PROTO   = 0240
        };
    };
}

#endif // TYPES_H_INCLUDED
