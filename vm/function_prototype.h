#ifndef FUNCTION_PROTOTYPE_H_INCLUDED
#define FUNCTION_PROTOTYPE_H_INCLUDED

#include "gc.h"
#include "inst.h"
#include "variant.h"

#include <vector>
#include <algorithm>

namespace AYA
{
    typedef std::vector<Inst> InstCode;
    typedef std::vector<Variant> ValueList;

    class FunctionPrototype : public ManagedMemory
    {
        friend class FunctionBuilder;

        friend class Closure;
        friend class FunctionCall;
    protected:
        FunctionPrototype()
        {}

        InstCode code;
        ValueList constTable;

        std::vector<STRING_T> arguments;

    public:
        void mark() const
        {
            if(!marker)
            {
                marker = true;
                for(auto& v : constTable)
                    v.mark();
            }
        }

        #ifdef DEBUG
        const InstCode& getCode() const
        {
            return code;
        }
        #endif
    };

    class VM;

    class FunctionBuilder
    {
    protected:
        FunctionPrototype* proto;
        VM& target;
    public:
        FunctionBuilder(VM& _target)
        :
            target(_target)
        {
            proto = new FunctionPrototype();
        }

        FunctionBuilder(const FunctionBuilder&) = delete;

        FunctionBuilder(FunctionBuilder&& org)
        :
            proto(org.proto),
            target(org.target)
        {
            org.proto = new FunctionPrototype();
        }

        ~FunctionBuilder()
        { delete proto; }

        FunctionBuilder getChild()
        {
            return std::move(FunctionBuilder(target));
        }

        void clear()
        {
            delete proto;
            proto = new FunctionPrototype();
        }

        size_t addInst(const Inst& inst)
        {
            proto->code.push_back(inst);
            return proto->code.size() - 1;
        }

        template<typename... Args>
        size_t addInst(Args... args)
        {
            return addInst(Inst(args...));
        }

        Inst& at(size_t i)
        {
            return proto->code[i];
        }

        size_t current()
        {
            return proto->code.size();
        }

        void addArg(const STRING_T& arg)
        {
            proto->arguments.push_back(arg);
        }

        size_t addConst(const Variant& c)
        {
            auto& constTable = proto->constTable;
            // check for existence
            auto it = std::find(constTable.begin(), constTable.end(), c);
            if(it == constTable.end())
            {
                constTable.push_back(c);
                return constTable.size() - 1;
            }
            else
                return it - constTable.begin();
        }

        size_t addConst(Object* ref)
        {
            Variant tmp = REF(ref);
            return addConst(tmp);
        }

        size_t addConst(const STRING_T& str);


        const FunctionPrototype* getResult();
    };
}

#endif // FUNCTION_PROTOTYPE_H_INCLUDED
