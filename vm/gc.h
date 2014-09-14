#ifndef GC_H_INCLUDED
#define GC_H_INCLUDED

#include <set>
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
        std::set<upManagedMemory> objects;
        VM& owner;

	static const long NO_LIMIT = -1;
	long memoryLimit = NO_LIMIT;

    public:
        GarbageCollector(VM* _owner)
        : owner(*_owner) {}

        /// DO NOT CALL collect() WHILE PARSING
        /// objects created during code generation are not reachable until they've been loaded into VM
        /// segfaults, satan, etc
        void collect();

    	void request(size_t size)
        {
            if(memoryLimit != NO_LIMIT && memoryLimit - size < 0)
                throw RuntimeError("Memory limit reached.");
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

            objects.insert(std::move(upManagedMemory(p)));
        }

        void unregisterObj(ManagedMemory* p)
        {
//            upManagedMemory wrap(p);
//            std::set<upManagedMemory>::iterator  it = objects.find(wrap);
//            std::move(*it).release();
//            wrap.release();
//
//            objects.erase(it);
        }

    };

}

#endif // GC_H_INCLUDED
