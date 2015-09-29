#include "gc.h"
#include "vm.h"

namespace AYA
{
    void* ManagedMemory::operator new (size_t s, GarbageCollector& gc)
    {
        auto p = (::operator new(s));
        gc.registerObj(static_cast<ManagedMemory*>(p), s);

        return p;
    }

    void GarbageCollector::collect()
    {
        owner.mark();

        for(auto it = entries.begin(); it != entries.end(); )
        {
            if(it->first->sweep())
            {
                memoryUsed -= it->second;
                delete it->first;
                entries.erase(it++);
            }
            else
            {
                ++it;
            }
        }
    }
}
