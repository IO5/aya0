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
        std::map<ManagedMemory*, size_t> entries;
//        std::set<upManagedMemory> objects;
        VM& owner;
    public:
        GarbageCollector(VM* _owner)
        : owner(*_owner) {}

        static const uint64_t NO_LIMIT = UINT64_MAX;
        static const int KILOBYTE = 1024;

        /// DO NOT CALL collect() WHILE PARSING
        /// objects created during code generation are not reachable until they've been loaded into VM
        /// segfaults, satan, etc
        void collect();

        bool testIfItFits(size_t size)
        {
            return memoryLimit == NO_LIMIT || (memoryUsed + (uint64_t)size <= memoryLimit);
        }

        bool isRegistered(ManagedMemory* p)
        {
            return (entries.find(p) != entries.end());
        }

        void registerObj(ManagedMemory* p, size_t objSize)
        {
            if (memoryLimit != NO_LIMIT)
            {
                if (memoryUsed + objSize > memoryLimit)
                    throw RuntimeError("Memory limit reached.");
                else
                    memoryUsed += objSize;
            }

            //objects.insert(std::move(upManagedMemory(p)));
            entries.insert(
                       std::make_pair(p, objSize)
                       );
        }

        void updateObj(ManagedMemory* p, size_t sizeChange)
        {
            if (memoryLimit != NO_LIMIT)
            {
                if (memoryUsed + sizeChange > memoryLimit)
                    throw RuntimeError("Memory limit reached");
                else
                    memoryUsed += sizeChange;
            }

            entries[p] += sizeChange;
        }

        void setMemoryLimit(uint64_t newLimit /*in Kb*/)
        {
            collect();

            memoryLimit = (newLimit == NO_LIMIT) ? NO_LIMIT : newLimit*KILOBYTE;

            if (memoryUsed > memoryLimit)
                throw RuntimeError("Memory limit reached.");
        }
    private:
        uint64_t memoryUsed = 0;
        uint64_t memoryLimit = NO_LIMIT;
    };

}

#endif // GC_H_INCLUDED
