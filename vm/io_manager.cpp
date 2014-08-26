#include "io_manager.h"

#include "vm.h"

#include "boost/format.hpp"

namespace AYA
{
    using boost::format;
    using boost::io::group;

    void IOManager::write(const STRING_T& str)
    {
        printf("%s", str.c_str());
    }

    template<char sparator>
    int IOManager::printValues(VM* state)
    {
        int count = AYA_getArgCount(state);
        IOManager& io = state->io;

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

            switch(AYA_getArgType(state, i))
            {
                case BType::NIL:
                    io.write("NIL");
                    break;
                case BType::INT:
                {
                    INT_T arg;
                    AYA_getIntArg(state, i, &arg);
                    io.write(str(format("%1%") % arg));
                    break;
                }
                case BType::REAL:
                {
                    REAL_T arg;
                    AYA_getRealArg(state, i, &arg);
                    io.write(str(format("%1%") % arg));
                    break;
                }
                case BType::REF:
                {
                    Variant& v = *(state->evalStack.cCallFrame.frameBottom() + i);
                    int type = state->getBuildInType(v);

                    if(type == BType::STR)
                    {
                        io.write(state->getStr(v));
                    }
                    else
                    {
                        AYA_setErrorMsg(state, "not implemented");
                        return -1;
//                        Object* obj = v.value.ref;
//
//                        const Variant& to_s_func = obj->getReadOnly("to_s");
//
//                        // welp welp welp
//                        if(to_s_func.isCFUNC())
//                        {
//                            to_s_func.value.cfunc(state);
//                        }
//                        else
//                        {
//                            // TODO
//                            AYA_setErrorMsg(state, "not implemented");
//                            return -1;
//                        }
                    }

                    break;
                }
                default:
                    //printf("%d\n", AYA_getArgType(state, i));
                    AYA_setErrorMsg(state, "unknown type");
                    return -1;
            }
        }

        // puts
        if(sparator == '\n')
        {
            io.write("\n");
        }

        return 0;

    }

    int IOManager::print(VM* state)
    {
        return printValues<','>(state);
    }

    int IOManager::puts(VM* state)
    {
        return printValues<'\n'>(state);
    }
}
