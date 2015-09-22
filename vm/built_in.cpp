#include "built_in.h"

#include "boost/format.hpp"

#include <sstream>

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
//            case BType::TYPE:
//                io.write("<Type>");
//                break;
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
                auto& list = static_cast<ListObject*>(val.value.ref)->content;
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
            {
                io.write("{");
                Dict& dict = static_cast<DictObject*>(val.value.ref)->content;
                Dict::iterator it = dict.begin();
                if (it != dict.end())
                {
                    printValue(state, it->first);
                    io.write(": ");
                    printValue(state, it->second);
                    ++it;
                    while (it != dict.end())
                    {
                        io.write(", ");
                        printValue(state, it->first);
                        io.write(": ");
                        printValue(state, it->second);
                        ++it;
                    }
                }
                io.write("}");
                break;
            }
            default:
            {
                if (state->getBuildInType(val) & BType::REF)
                {
                    Object* obj = val.value.ref;
                    const Variant* type = obj->get("type");
                    const Variant* tname = type->value.ref->get("name");
                    io.write("<" + state->getStr(*tname) + ">");
                }
                else
                {
                    io.write("<unknown>");
                }
            }
        }
    }

    int BuiltIn::strComp(VM* state)
    {
        if (!AYA_assertArgCount(state, 2))
        {
            AYA_setErrorMsg(state, "Wrong argument count");
            return -1;
        }

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
        if (!AYA_assertArgCount(state, 2))
        {
            AYA_setErrorMsg(state, "Wrong argument count");
            return -1;
        }

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
        if (!AYA_assertArgCount(state, 1))
        {
            AYA_setErrorMsg(state, "Wrong argument count");
            return -1;
        }

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
        if (!AYA_assertArgCount(state, 2))
        {
            AYA_setErrorMsg(state, "Wrong argument count");
            return -1;
        }

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
        if (!AYA_assertArgCount(state, 2))
        {
            AYA_setErrorMsg(state, "Wrong argument count");
            return -1;
        }

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
        if (!AYA_assertArgCount(state, 1))
        {
            AYA_setErrorMsg(state, "Wrong argument count");
            return -1;
        }

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

    int BuiltIn::range(VM* state)
    {
        int argCount = AYA_getArgCount(state);

        INT_T step = 1;
        if (argCount >= 3)
        {
            if (!AYA_getIntArg(state, 2, &step))
            {
                AYA_setErrorMsg(state, "Wrong step");
                return -1;
            }
        }

        INT_T start = 0, end;
        if (argCount >= 2)
        {
            if (!AYA_getIntArg(state, 1, &end))
            {
                AYA_setErrorMsg(state, "Wrong end");
                return -1;
            }
            if (!AYA_getIntArg(state, 0, &start))
            {
                AYA_setErrorMsg(state, "Wrong start");
                return -1;
            }
            if ((step < 0 && end > start) || (step > 0 && end < start))
            {
                AYA_setErrorMsg(state, "Wrong arguments");
                return -1;
            }
        }
        else if (argCount == 1)
        {
            if (!AYA_getIntArg(state, 0, &end))
            {
                AYA_setErrorMsg(state, "Wrong end");
                return -1;
            }
        }
        else
        {
            AYA_setErrorMsg(state, "Not enough arguments");
            return -1;
        }

        std::vector<Variant> range;
        int sign = step < 0 ? -1 : 1;
        for (INT_T i = start; i*sign < end*sign; i += step)
        {
            range.push_back(i);
        }

        Variant& res = state->evalStack.cCallFrame.frameBottom()[0];
        ListObject* list = state->objectFactory.makeList(std::move(range));

        res = REF(list);

        return 0;
    }

    int BuiltIn::flattenDict(VM* state)
    {
//        if (!AYA_assertArgCount(state, 0))
//        {
//            AYA_setErrorMsg(state, "Wrong argument count");
//            return -1;
//        }

        Variant& self = state->evalStack.self;
        Variant& res = *(state->evalStack.cCallFrame.frameBottom());

        if (state->getBuildInType(self) != BType::DICT)
        {
            AYA_setErrorMsg(state, "not a dict");
            return -1;
        }

        auto& dict = static_cast<DictObject*>(self.value.ref)->content;
        std::vector<Variant> list;
        for (auto& pair : dict)
        {
            Object* obj = state->objectFactory.makeObject();
            obj->set("key", pair.first, &state->gc);
            obj->set("val", pair.second, &state->gc);
            list.push_back(REF(obj));
        }

        res = REF(state->objectFactory.makeList(std::move(list)));

        return 0;
    }

    int BuiltIn::dictComp(VM* state)
    {
        if (!AYA_assertArgCount(state, 2))
        {
            AYA_setErrorMsg(state, "Wrong argument count");
            return -1;
        }

        Variant* args = state->evalStack.cCallFrame.frameBottom();

        if (state->getBuildInType(args[0]) != BType::DICT ||
            state->getBuildInType(args[1]) != BType::DICT)
        {
            AYA_setIntResult(state, false);
            return 0;
        }

        const auto &dct1 = static_cast<DictObject*>(args[0].value.ref)->content;
        const auto &dct2 = static_cast<DictObject*>(args[1].value.ref)->content;
        AYA_setIntResult(state, dct1 == dct2);

        return 0;
    }

    int BuiltIn::dictLen(VM* state)
    {
        if (!AYA_assertArgCount(state, 1))
        {
            AYA_setErrorMsg(state, "Wrong argument count");
            return -1;
        }

        Variant& arg = *(state->evalStack.cCallFrame.frameBottom());

        if (state->getBuildInType(arg) != BType::DICT)
        {
            AYA_setErrorMsg(state, "not a dictionary");
            return -1;
        }

        auto& dict = static_cast<DictObject*>(arg.value.ref)->content;
        AYA_setIntResult(state, dict.size());

        return 0;
    }

    int BuiltIn::open(VM* state)
    {
        Variant& arg = *(state->evalStack.cCallFrame.frameBottom());

        if (state->getBuildInType(arg) != BType::STR)
        {
            AYA_setErrorMsg(state, "not a string");
            return -1;
        }

        using namespace boost::filesystem;

        path filename(state->getStr(arg));

        if (exists(filename))
        {
            filename = canonical(filename);

            if (state->files.isFileAccessible(filename))
            {
                arg = REF(state->objectFactory.makeFile(filename.string()));
                return 0;
            }
        }

        AYA_setErrorMsg(state, "failed to open the file, path is not on the whitelist");
        return -1;
    }

    int BuiltIn::close(VM* state)
    {
        Variant& self = state->evalStack.self;
        Variant& res = *(state->evalStack.cCallFrame.frameBottom());

        if (state->getBuildInType(self) != BType::FILE)
        {
            AYA_setErrorMsg(state, "not a file");
            return -1;
        }

        FileObject* file = static_cast<FileObject*>(self.value.ref);
        file->close();

        res = NIL();
        return 0;
    }

    int BuiltIn::read(VM* state)
    {
        Variant& self = state->evalStack.self;
        Variant& arg = *(state->evalStack.cCallFrame.frameBottom());

        if (state->getBuildInType(self) != BType::FILE)
        {
            AYA_setErrorMsg(state, "not a file");
            return -1;
        }

        FileObject* file = static_cast<FileObject*>(self.value.ref);

        STRING_T res;
        if (state->evalStack.cCallFrame.argCount() >= 1)
        {
            if(!arg.isINT())
            {
                AYA_setErrorMsg(state, "expected integer argument");
                return -1;
            }

            res = file->read(arg.value.integer);
        }
        else
        {
            res = file->read();
        }

        arg = REF(state->objectFactory.makeString(res));

        return 0;
    }

    int BuiltIn::readLine(VM* state)
    {
        Variant& self = state->evalStack.self;
        Variant& arg = *(state->evalStack.cCallFrame.frameBottom());

        if (state->getBuildInType(self) != BType::FILE)
        {
            AYA_setErrorMsg(state, "not a file");
            return -1;
        }

        FileObject* file = static_cast<FileObject*>(self.value.ref);

        STRING_T res = file->readLine();

        arg = REF(state->objectFactory.makeString(res));

        return 0;
    }

    int BuiltIn::write(VM* state)
    {
        Variant& self = state->evalStack.self;
        Variant* args = state->evalStack.cCallFrame.frameBottom();
        size_t argCount = state->evalStack.cCallFrame.argCount();

        if (state->getBuildInType(self) != BType::FILE)
        {
            AYA_setErrorMsg(state, "not a file");
            return -1;
        }

        FileObject* file = static_cast<FileObject*>(self.value.ref);

        for (size_t i = 0; i < argCount; ++i)
        {
            if (state->getBuildInType(args[i]) != BType::STR)
            {
                AYA_setErrorMsg(state, "all arguments must be strings");
                return -1;
            }
        }

        for (size_t i = 0; i < argCount; ++i)
        {
            file->write(state->getStr(args[i]));
        }

        args[0] = NIL();

        return 0;
    }

    int BuiltIn::loadFile(VM* state)
    {
        Variant& arg = *(state->evalStack.cCallFrame.frameBottom());

        if (state->getBuildInType(arg) != BType::STR)
        {
            AYA_setErrorMsg(state, "not a string");
            return -1;
        }

        using namespace boost::filesystem;

        path filename(state->getStr(arg));

        if (exists(filename))
        {
            filename = canonical(filename);

            if (state->files.isFileAccessible(filename))
            {
                std::ifstream file(filename.string());

                if (!file.good())
                {
                    AYA_setErrorMsg(state, "failed to open the file");
                    return -1;
                }

                std::stringstream buffer;
                buffer << file.rdbuf();
                buffer << '\n';
                const FunctionPrototype* proto = state->_parse(buffer.str());

                arg = REF(state->objectFactory.makeClosure(proto, state->globalEnv));

                return 0;
            }
        }

        AYA_setErrorMsg(state, "failed to open the file, path is not on the whitelist");
        return -1;
    }
}
