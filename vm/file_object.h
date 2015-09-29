#ifndef FILE_OBJECT_H_INCLUDED
#define FILE_OBJECT_H_INCLUDED

#include "object.h"
#include <fstream>

namespace AYA
{
    class FileObject : public Object
    {
        friend class ObjectFactory;
    protected:
        FileObject() = delete;
        FileObject(TypeObject* definition, const STRING_T& filename)
        :
            Object(definition),
            file(filename, std::fstream::in | std::fstream::out )
        {
            if(!file.good())
                throw RuntimeError("failed to open the file");
        }

        FileObject(const FileObject& o) = delete;
        ~FileObject()
        {
            file.close();
        }

        // TODO add to gc
        FileObject* clone() const
        {
            throw RuntimeError("Cannot copy a file object");
        }

        int getBuildInType() const
        {
            return BType::FILE;
        }

        std::fstream file;
    public:
        void mark() const
        {
            Object::mark();
        }

        void write(const STRING_T& str)
        {
            if(!file.good())
                throw RuntimeError("file object is in invalid state");
            file << str;
        }

        void close()
        {
             file.close();
        }

        STRING_T read()
        {
            if(!file.good())
                throw RuntimeError("file object is in invalid state");
            STRING_T str;
            file >> str;
            return str;
        }

        STRING_T read(size_t num)
        {
            if(!file.good())
                throw RuntimeError("file object is in invalid state");
            char buf[num+1];
            file.read(buf, num);
            buf[file.gcount()] = '\0';
            return STRING_T(buf);
        }

        STRING_T readLine()
        {
            if(!file.good())
                throw RuntimeError("file object is in invalid state");
            char buf[256];
            file.getline(buf, 256);
            return STRING_T(buf);
        }
    };
}

#endif // FILE_OBJECT_H_INCLUDED
