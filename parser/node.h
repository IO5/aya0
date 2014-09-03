#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include <vector>

namespace AYA
{
    class FunctionBuilder;

    class Node
    {
    public:
        virtual ~Node() {}

        virtual void gen(FunctionBuilder& target) =0; //Code gen
    };

    template <class N = Node>
    using NodeList = std::vector<N*>;
}

#endif // NODE_H_INCLUDED
