#ifndef GC_H_INCLUDED
#define GC_H_INCLUDED

//#include <set>
#include <map>
#include <memory>

#include "../error.h"

namespace AYA
{
    class GarbageCollector;

    /// Managed memory
    class ManagedMemory
    {
        friend class GarbageCollector;
        friend class ObjectFactory;
    private:


//        void* operator new[]   (size_t);
//        void  operator delete[](void*);
    protected:
        mutable bool marker;

        bool sweep() const
        {
            if(marker)
            {
                marker = false;
                return false;
            }
            else
            {
                return true;
            }
        }

        ManagedMemory()
        : marker(false) {}

        ManagedMemory(const ManagedMemory&)
        : marker(false) {}

    public:
        virtual ~ManagedMemory() {}

        virtual void mark() const
        {
            marker = true;
        }

        static void* operator new     (size_t s)
        { return (::operator new(s)); }

        static void* operator new     (size_t s, GarbageCollector& gc);
//        void* operator new     (size_t s, bool)
//        {
//            return (::operator new(s));
//        }
//
//        void  operator delete  (void* p)
//        {
//            return (::operator delete(p));
//        }
    };

    class VM;

    class GarbageCollector
    {
        typedef std::unique_ptr<ManagedMemory> upManagedMemory;
        std::map<upManagedMemory, size_t> entries;
//        std::set<upManagedMemory> objects;
        VM& owner;
    public:
        GarbageCollector(VM* _owner)
        : owner(*_owner) {}

        static const long NO_LIMIT = -1;

        /// DO NOT CALL collect() WHILE PARSING
        /// objects created during code generation are not reachable until they've been loaded into VM
        /// segfaults, satan, etc
        void collect();

    	bool request(size_t size)
        {
            return (memoryLimit == NO_LIMIT || memoryLimit - (long)size >= 0);
        }

        void registerObj(ManagedMemory* p, size_t size)
        {
            if(memoryLimit != NO_LIMIT)
            {
                if(memoryLimit == 0)
                    throw RuntimeError("Memory limit reached.");
                else
                    memoryLimit -= size;
            }

            //objects.insert(std::move(upManagedMemory(p)));
            entries.insert(
                       std::make_pair(upManagedMemory(p), size)
                       );
        }

        void setMemoryLimit(long limit)
        {
            memoryLimit = limit;
        }
    private:
        long memoryLimit = NO_LIMIT;
    };

}

#endif // GC_H_INCLUDED
