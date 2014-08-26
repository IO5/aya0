#ifndef PARSE_ERROR_H_INCLUDED
#define PARSE_ERROR_H_INCLUDED

#include <iostream>

#include <exception>
#include <string>

namespace AYA
{
    struct ProtoError : public std::exception
    {
        ProtoError(const char* _msg) : msg(_msg) {}
        ProtoError(const std::string& _msg) : msg(_msg) {}
        const char* what() const noexcept { return msg.c_str(); }
    protected:
        std::string msg;
    };

    struct ParseError : public ProtoError
    {
        using ProtoError::ProtoError;
    };

    struct RuntimeError : public ProtoError
    {
        using ProtoError::ProtoError;
    };
}

#endif // PARSE_ERROR_H_INCLUDED
