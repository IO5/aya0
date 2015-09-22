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

            if (count == 1 && state->getBuildInType(args[0]) == BType::STR)
            {
                io.write(state->getStr(args[0]));
            }
            else
            {
                for (int i = 0; i < count; ++i)
                {
                    if (i)
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
            }

            // puts
            if(sparator == '\n')
            {
                io.write("\n");
            }

            AYA_setNilResult(state);

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
        static int range(VM* state);

        static int dictComp(VM* state);
        static int dictLen(VM* state);
        static int flattenDict(VM* state);

        static int open(VM* state);
        static int close(VM* state);
        static int read(VM* state);
        static int readLine(VM* state);
        static int write(VM* state);

        static int exit(VM* state)
        {
            ::exit(0);
        }
    };
}

#endif // BUILD_IN_H_INCLUDED
