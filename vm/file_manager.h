#ifndef FILE_MANAGER_H_INCLUDED
#define FILE_MANAGER_H_INCLUDED

#include "../types.h"

#include "boost/filesystem.hpp"

#include <set>

namespace AYA
{
    using namespace boost::filesystem;

    class FileManager
    {
    public:
        void addToWhitelist(const path& dir)
        {
            whiteList.insert(dir);
        }
        void addToBlacklist(const path& dir)
        {
            blackList.insert(dir);
        }
        void removeFromWhitelist(const path& dir)
        {
            whiteList.erase(dir);
        }
        void removeFromBlacklist(const path& dir)
        {
            blackList.erase(dir);
        }

        bool isFileAccessible(const path& file);
    protected:
        static bool pathContainsFile(path dir, path file);

        typedef std::set<path> PathList;
        PathList whiteList, blackList;
    };
}

#endif // FILE_MANAGER_H_INCLUDED
