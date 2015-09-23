#ifndef BUILD_IN_H_INCLUDED
#define BUILD_IN_H_INCLUDED

#include "vm.h"

#include "boost/format.hpp"

namespace AYA
{
    class BuiltIn
    {
    public:
        template<typename T>
        static void printValue(VM* state, const Variant& val, T printFunc)
        {
            using boost::format;
            using boost::io::group;

            switch(state->getBuildInType(val))
            {
                case BType::NIL:
                    printFunc("nil");
                    break;
                case BType::INT:
                    printFunc(str(format("%1%") % val.value.integer));
                    break;
                case BType::REAL:
                    printFunc(str(format("%1%") % val.value.real));
                    break;
                case BType::CFUNC:
                case BType::FUNC:
                    printFunc("<Function>");
                    break;
                case BType::STR:
                    printFunc("\"" + state->getStr(val) + "\"");
                    break;
                case BType::LIST:
                {
                    printFunc("[");
                    auto& list = static_cast<ListObject*>(val.value.ref)->content;
                    if (list.size() > 0)
                    {
                        printValue(state, list[0], printFunc);
                        for (size_t i = 1; i < list.size(); ++i)
                        {
                            printFunc(", ");
                            printValue(state, list[i], printFunc);
                        }
                    }
                    printFunc("]");
                    break;
                }
                case BType::DICT:
                {
                    printFunc("{");
                    Dict& dict = static_cast<DictObject*>(val.value.ref)->content;
                    Dict::iterator it = dict.begin();
                    if (it != dict.end())
                    {
                        printValue(state, it->first, printFunc);
                        printFunc(": ");
                        printValue(state, it->second, printFunc);
                        ++it;
                        while (it != dict.end())
                        {
                            printFunc(", ");
                            printValue(state, it->first, printFunc);
                            printFunc(": ");
                            printValue(state, it->second, printFunc);
                            ++it;
                        }
                    }
                    printFunc("}");
                    break;
                }
                default:
                {
                    if (state->getBuildInType(val) & BType::REF)
                    {
                        Object* obj = val.value.ref;
                        const Variant* type = obj->get("type");
                        const Variant* tname = type->value.ref->get("name");
                        printFunc("<" + state->getStr(*tname) + ">");
                    }
                    else
                    {
                        printFunc("<unknown>");
                    }
                }
            }
        }

        //puts + print
        template<char sparator>
        static int printValues(VM* state);
        static int print(VM* state);
        static int puts(VM* state);

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

        static int read(VM* state);
        static int readLine(VM* state);

        static int fileOpen(VM* state);
        static int fileClose(VM* state);
        static int fileRead(VM* state);
        static int fileReadLine(VM* state);
        static int fileWrite(VM* state);

        static int loadFile(VM* state);

        static int exit(VM* state)
        {
            ::exit(0);
        }

        static int toInt(VM* state);
        static int ceil(VM* state);
        static int toReal(VM* state);
        static int toString(VM* state);
    };
}

#endif // BUILD_IN_H_INCLUDED
