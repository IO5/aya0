#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include "types.h"
#include "lexer"

#include "parser/lit_node.h"

#include <cstdlib>

void* LemonAlloc(void* (*allocProc)(size_t));
void  Lemon(void*, int, AYA::Node*);
void  LemonFree(void*, void(*freeProc)(void*));

namespace AYA
{
    class Parser
    {
        void* pParser;

    public:
        Parser()
        { pParser = LemonAlloc(malloc); }
        ~Parser()
        { LemonFree(pParser, free); }

        void parse(TOKEN_T* tkn)
        {
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
                break;
            default:
                semInfo = NULL;
            }

            Lemon(pParser, tkn->type_id(), semInfo);
        }
    };

}

#endif // PARSER_H_INCLUDED
