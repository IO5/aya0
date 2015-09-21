#include "function_prototype.h"

#include "vm.h"

namespace AYA
{
    size_t FunctionBuilder::addConst(const STRING_T& str)
    {
        auto& constTable = proto->constTable;
        // check for existence
        auto pred = [&](const Variant& v)
        {
            if(target.getBuildInType(v) == BType::STR)
            {
                const STRING_T& tmp = target.getStr(v);
                return tmp == str;
            }
            else
                return false;
        };

        auto it = std::find_if(constTable.begin(), constTable.end(), pred);
        if(it == constTable.end())
        {
            constTable.push_back(REF(target.objectFactory.makeString(str)));
            return constTable.size() - 1;
        }
        else
        {
            return it - constTable.begin();
        }
    }

    const FunctionPrototype* FunctionBuilder::getResult()
    {
        auto res = proto;
        proto = NULL;

        target.gc.registerObj(res, sizeof(proto));

        return res;
    }
}
