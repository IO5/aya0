#ifndef BUILD_IN_H_INCLUDED
#define BUILD_IN_H_INCLUDED

#include "vm.h"

namespace AYA
{
    class BuiltIn
    {
    public:
        static void printValue(VM* state, const Variant& val);

        //puts + print
        template<char sparator>
        static int printValues(VM* state)
        {
            int count = AYA_getArgCount(state);
            IOManager& io = state->io;

            Variant* args = state->evalStack.cCallFrame.frameBottom();

            for(int i = 0; i < count; ++i)
            {
                if(i)
                {
                    if(sparator == ',')
                    {
                        io.write(", ");
                    }
                    else if(sparator == '\n')
                    {
                        io.write("\n");
                    }
                }

                printValue(state, args[i]);
            }

            // puts
            if(sparator == '\n')
            {
                io.write("\n");
            }

            return 0;
        }

        static int print(VM* state)
        {
            return printValues<','>(state);
        }

        static int puts(VM* state)
        {
            return printValues<'\n'>(state);
        }

        static int strComp(VM* state);
        static int strConcat(VM* state);
        static int strLen(VM* state);

        static int listComp(VM* state);
        static int listConcat(VM* state);
        static int listLen(VM* state);
    };
}

#endif // BUILD_IN_H_INCLUDED
