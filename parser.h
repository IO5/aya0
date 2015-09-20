#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include "types.h"
#include "lexer"

#include "parser/lit_node.h"
#include "parser/ident_node.h"

#include "vm/function_prototype.h"

#include <cstdlib>

void* LemonAlloc(void* (*allocProc)(size_t));
void  Lemon(void*, int, AYA::Node*, AYA::Node**);
void  LemonFree(void*, void(*freeProc)(void*));

namespace AYA
{
    class VM;

    class Parser
    {
        void* pParser;
        Node* AST;
        VM& target;

    public:
        Parser(VM& _target)
        :
            AST(NULL),
            target(_target)
        {
            pParser = LemonAlloc(malloc);
        }

        ~Parser()
        {
            LemonFree(pParser, free);
            if (AST)
                delete AST;
        }

        void parse(TOKEN_T* tkn)
        {
            assert(tkn);

            Node* semInfo;

            switch (tkn->type_id())
            {
            case TK_NIL:
                semInfo = new NilLitNode();
                break;
            case TK_INT:
                semInfo = new IntLitNode(tkn->get_integer());
                break;
            case TK_REAL:
                semInfo = new RealLitNode(tkn->get_real());
                break;
            case TK_STRING:
                semInfo = new StringLitNode(tkn->get_text());
                break;
            case TK_IDENT: //TODO
                semInfo = new IdentNode(tkn->get_text());
                break;
            default:
                semInfo = NULL;
            }

            Lemon(pParser, tkn->type_id(), semInfo, NULL);
        }

        const FunctionPrototype* generateCode()
        {
            Lemon(pParser, 0, NULL, &AST);

            assert(AST);

            FunctionBuilder builder(target);

            AST->gen(builder);

            builder.addInst(Inst::LNIL); // TODO see func_node.h
            builder.addInst(Inst::RET);

            delete AST;
            AST = NULL;

            return builder.getResult();
        }
    };

}

#endif // PARSER_H_INCLUDED
