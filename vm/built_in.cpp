#include "built_in.h"

#include "boost/format.hpp"

namespace AYA
{
    using boost::format;
    using boost::io::group;

    void BuiltIn::printValue(VM* state, const Variant& val)
    {
        IOManager& io = state->io;
        switch(state->getBuildInType(val))
        {
            case BType::NIL:
                io.write("nil");
                break;
            case BType::INT:
                io.write(str(format("%1%") % val.value.integer));
                break;
            case BType::REAL:
                io.write(str(format("%1%") % val.value.real));
                break;
            case BType::OBJ:
            {
                Object* obj = val.value.ref;
                const Variant* tname = obj->get("typename");
                if (state->getBuildInType(*tname) == BType::STR)
                    io.write("<" + state->getStr(*tname) + ">");
                else
                    io.write("<Object>");
                break;
            }
            case BType::TYPE:
                io.write("<Type>");
                break;
            case BType::CFUNC:
            case BType::FUNC:
                io.write("<Function>");
                break;
            case BType::STR:
                io.write("\"" + state->getStr(val) + "\"");
                break;
            case BType::LIST:
            {
                io.write("[");
                auto list = static_cast<ListObject*>(val.value.ref)->content;
                if (list.size() > 0)
                {
                    printValue(state, list[0]);
                    for (size_t i = 1; i < list.size(); ++i)
                    {
                        io.write(", ");
                        printValue(state, list[i]);
                    }
                }
                io.write("]");
                break;
            }
            case BType::DICT:
                assert(0);
                break;
            default:
                io.write("<Unknown>");
        }
    }

    int BuiltIn::strComp(VM* state)
    {
        AYA_assertArgCount(state, 2);

        Variant* args = state->evalStack.cCallFrame.frameBottom();

        if (state->getBuildInType(args[0]) != BType::STR ||
            state->getBuildInType(args[1]) != BType::STR)
        {
            AYA_setIntResult(state, false);
            return 0;
        }

        const STRING_T &str1 = state->getStr(args[0]);
        const STRING_T &str2 = state->getStr(args[1]);
        AYA_setIntResult(state, str1 == str2);

        return 0;
    }

    int BuiltIn::strConcat(VM* state)
    {
        AYA_assertArgCount(state, 2);

        Variant* args = state->evalStack.cCallFrame.frameBottom();
        if (state->getBuildInType(args[0]) != BType::STR)
        {
            AYA_setErrorMsg(state, "Not a string");
            return -1;
        }
        STRING_T result = state->getStr(args[0]);

        switch(state->getBuildInType(args[1]))
        {
            case BType::NIL:
                AYA_setErrorMsg(state, "cannot concat string object with a nil");
                return -1;
            case BType::INT:
                result += str(format("%1%") % args[1].value.integer);
                break;
            case BType::REAL:
                result += str(format("%1%") % args[1].value.real);
                break;
            case BType::STR:
                result += state->getStr(args[1]);
                break;
            default:
                //printf("%d\n", AYA_getArgType(state, i));
                AYA_setErrorMsg(state, "unable to concatenate to a string");
                return -1;
        }

        AYA_setStrResult(state, result.c_str());

        return 0;
    }

    int BuiltIn::strLen(VM* state)
    {
        AYA_assertArgCount(state, 1);

        Variant& arg = *(state->evalStack.cCallFrame.frameBottom());

        if (state->getBuildInType(arg) != BType::STR)
        {
            AYA_setErrorMsg(state, "not a string");
            return -1;
        }

        const STRING_T &str = state->getStr(arg);
        AYA_setIntResult(state, str.length());

        return 0;
    }

    int BuiltIn::listComp(VM* state)
    {
        AYA_assertArgCount(state, 2);

        Variant* args = state->evalStack.cCallFrame.frameBottom();

        if (state->getBuildInType(args[0]) != BType::LIST ||
            state->getBuildInType(args[1]) != BType::LIST)
        {
            AYA_setIntResult(state, false);
            return 0;
        }

        const auto &lst1 = static_cast<ListObject*>(args[0].value.ref)->content;
        const auto &lst2 = static_cast<ListObject*>(args[1].value.ref)->content;
        AYA_setIntResult(state, lst1 == lst2);

        return 0;
    }

    int BuiltIn::listConcat(VM* state)
    {
        AYA_assertArgCount(state, 2);

        Variant* args = state->evalStack.cCallFrame.frameBottom();
        if (state->getBuildInType(args[0]) != BType::LIST)
        {
            AYA_setErrorMsg(state, "Not a list");
            return -1;
        }
        ListObject* list = static_cast<ListObject*>(args[0].value.ref);

        size_t oldCapacity = list->content.capacity();

        switch(state->getBuildInType(args[1]))
        {
            case BType::LIST:
            {
                ListObject* list2 = static_cast<ListObject*>(args[1].value.ref);
                list->content.insert(list->content.end(), list2->content.begin(), list2->content.end());
                break;
            }
            default:
                //state->gc.updateObj(list, sizeof(args[1]));
                //list->content.push_back(args[1]);
                AYA_setErrorMsg(state, "Cannot concatenate a list with a non-list");
                return -1;
        }

        size_t newCapacity = list->content.capacity();
        state->gc.updateObj(list, sizeof(Variant) * (newCapacity - oldCapacity));

        //return value already in place

        return 0;
    }

    int BuiltIn::listLen(VM* state)
    {
        AYA_assertArgCount(state, 1);

        Variant& arg = *(state->evalStack.cCallFrame.frameBottom());

        if (state->getBuildInType(arg) != BType::LIST)
        {
            AYA_setErrorMsg(state, "not a list");
            return -1;
        }

        auto& list = static_cast<ListObject*>(arg.value.ref)->content;
        AYA_setIntResult(state, list.size());

        return 0;
    }
}
