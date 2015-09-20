#ifndef CLASS_NODE_H_INCLUDED
#define CLASS_NODE_H_INCLUDED

#include "node.h"
#include "../vm/function_prototype.h"

namespace AYA
{
    class ClassNode : public Node
    {
        IDENT_T ident;
        Node* baseClass;
        std::vector<std::pair<IDENT_T, FuncNode*> > defList;
    public:
        ClassNode(Node* _ident, Node* _baseClass, std::vector<std::pair<Node*, Node*> >* _defList)
        {
            assert(dynamic_cast<IdentNode*>(_ident));
            ident = (static_cast<IdentNode*>(_ident))->ident;
            delete _ident;

            // convert to sensible list
            assert(_defList);
            for (auto& p : *_defList)
            {
                assert(dynamic_cast<IdentNode*>(p.first));
                IDENT_T funcIdent = (static_cast<IdentNode*>(p.first))->ident;
                delete p.first;
                assert(dynamic_cast<FuncNode*>(p.second));
                FuncNode* funcDef = (static_cast<FuncNode*>(p.second));

                defList.push_back(std::make_pair(funcIdent, funcDef));
            }

            delete _defList;

            baseClass = _baseClass;
        }

        ~ClassNode()
        {
            delete baseClass;
        }

        void gen(FunctionBuilder& target)
        {
            if(baseClass)
                baseClass->gen(target);
            else
                target.addInst(Inst::LNIL);

            target.addInst(Inst::TYPEC, target.addConst(ident));

            for (auto& p : defList)
            {
                // make closure
                p.second->gen(target);
                // store in type
                target.addInst(Inst::STORET, target.addConst(p.first));
            }

            target.addInst(Inst::POP, target.addConst(ident));
        }
    };
}

#endif // CLASS_NODE_H_INCLUDED
