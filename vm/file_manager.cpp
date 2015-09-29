#include "file_manager.h"

#include <algorithm>

namespace AYA
{
    using namespace boost::filesystem;

    bool FileManager::pathContainsFile(path dir, path file)
    {
      if (dir.filename() == ".")
        dir.remove_filename();
      assert(file.has_filename());
      file.remove_filename();

      dir = canonical(dir);
      file = canonical(file);

      auto dir_len = std::distance(dir.begin(), dir.end());
      auto file_len = std::distance(file.begin(), file.end());
      if (dir_len > file_len)
        return false;

      return std::equal(dir.begin(), dir.end(), file.begin());
    }

    bool FileManager::isFileAccessible(const path& file)
    {
        if (file.empty())
            return false;

        auto parent = file.parent_path();
        if (parent.empty())
            parent = path(".");
        if (!exists(parent))
            return false;

        //                  v wtf gcc
        auto pred = [&file, this](const path& dir){ return exists(dir) && pathContainsFile(dir, file); };
        auto isInBlackList = find_if(blackList.begin(), blackList.end(), pred);

        if (isInBlackList != blackList.end())
            return false;

        auto isInWhiteList = find_if(whiteList.begin(), whiteList.end(), pred);

        return isInWhiteList != whiteList.end();
    }
}
