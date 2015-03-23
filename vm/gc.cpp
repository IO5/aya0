#include "gc.h"
#include "vm.h"


namespace AYA
{
    void* ManagedMemory::operator new (size_t s, GarbageCollector& gc)
    {
        if(gc.request(s))
        {
            auto p = (::operator new(s));
            gc.registerObj(static_cast<ManagedMemory*>(p), s);

            return p;
        }
        else
            throw RuntimeError("Memory limit reached.");
    }

    void GarbageCollector::collect()
    {
        owner.mark();

        if(memoryLimit != NO_LIMIT)
        {
            for(auto it = entries.begin(); it != entries.end(); )
            {
                if(it->first->sweep())
                {
                    memoryLimit += it->second;
                    entries.erase(it++);
                }
                else
                    ++it;
            }
        }
        else
        {
            for(auto it = entries.begin(); it != entries.end(); )
            {
                if(it->first->sweep())
                    entries.erase(it++);
                else
                    ++it;
            }
        }
    }
}
