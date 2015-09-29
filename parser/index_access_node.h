#ifndef INDEX_ACCESS_NODE_H_INCLUDED
#define INDEX_ACCESS_NODE_H_INCLUDED

#include "node.h"

namespace AYA
{
    class IndexAccessNode : public Node
    {
        Node* collection;
        Node* index;
        friend class AssignNode;
    public:
        IndexAccessNode(Node* _collection, Node* _index)
        :
            collection(_collection),
            index(_index)
        {
            assert(collection);
            assert(index);
        }

        ~IndexAccessNode()
        {
            delete collection;
            delete index;
        }

        void gen(FunctionBuilder& target)
        {
            collection->gen(target);
            index->gen(target);
            target.addInst(Inst::LOADC);
        }
    };
}

#endif // INDEX_ACCESS_NODE_H_INCLUDED
