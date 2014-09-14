#include "gc.h"
#include "vm.h"


namespace AYA
{
        void* ManagedMemory::operator new (size_t s, GarbageCollector& gc)
	{
            gc.request(s);
            auto p = (::operator new(s));
            gc.registerObj(static_cast<ManagedMemory*>(p), s);

            return p;
	}

        void GarbageCollector::collect()
        {
            owner.mark();

            for(auto it = objects.begin(); it != objects.end(); )
            {
                if((*it)->sweep())
		    objects.erase(it++);
                else
                    ++it;
            }
        }
}
