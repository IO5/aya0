#ifndef EVAL_STACK_H_INCLUDED
#define EVAL_STACK_H_INCLUDED

#include "variant.h"

#include <vector>

namespace AYA
{
    /// Evaluation stack
    class EvalStack
    {
    protected:
        std::vector<Variant> c;

    public:
        Variant self = NIL();
        Variant lastExpr;

        /// For communication between C functions and VM
        class CCallFrame
        {
            friend class EvalStack;

            size_t      _argCount;
            Variant*    _frameTop;
            Variant*    _frameBottom;
            Variant     _self;
            STRING_T    _errorMsg;

        public:
            // getters
            size_t argCount()
            { return _argCount; }

            Variant* frameTop()
            { return _frameTop; }

            Variant* frameBottom()
            { return _frameBottom; }

            Variant& self()
            { return _self; }

            const char* errorMsg()
            { return _errorMsg.c_str(); }

            void setErrorMsg(const char* msg)
            { _errorMsg = msg; }

        } cCallFrame;

        /// Empty the stack
        void clear()
        {
            c.clear();
        }

        void push(const Variant& arg)
        {
            c.push_back(arg);
        }

        Variant pop()
        {
            assert(!c.empty());

            Variant res = c.back();

            c.pop_back();

            return res;
        }

        /// Pop count values
        void pop(size_t count)
        {
            assert(count <= c.size());
            assert(count >= 0);

            c.erase(c.end()-count, c.end());
        }

        Variant& peek()
        {
            assert(!c.empty());

            return c.back();
        }

        /// Get n-th value counting from top
        Variant& peek(size_t n)
        {
            assert(n <= c.size());
            assert(n > 0);

            return *(c.end()-n);
        }

        CCallFrame& prepareCallFrame(size_t argCount, Variant self)
        {
            assert(argCount <= c.size());

            cCallFrame._argCount = argCount;
            cCallFrame._self = self;
            cCallFrame._errorMsg.clear();

            if(argCount == 0)
            {
                //make space for result
                push(NIL());
                ++argCount;
            }

            Variant* tmp = c.data() + c.size();
            cCallFrame._frameTop    = tmp;
            cCallFrame._frameBottom = tmp - argCount;

            return cCallFrame;
        }

        void clearCallFrame()
        {
            pop(cCallFrame._frameTop - cCallFrame._frameBottom - 1);
        }
    };
}

#endif // EVAL_STACK_H_INCLUDED
