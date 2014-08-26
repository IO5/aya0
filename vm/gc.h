#ifndef GC_H_INCLUDED
#define GC_H_INCLUDED

#include <set>
#include <memory>

namespace AYA
{
    /// Managed memory
    class ManagedMemory
    {
        friend class GarbageCollector;
    private:
//        void* operator new     (size_t s)
//        { return (::operator new(s)); }
//
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
                return true;
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

    public:
        GarbageCollector(VM* _owner)
        : owner(*_owner) {}

        void _register(ManagedMemory* p)
        {
            objects.insert(std::move(upManagedMemory(p)));
        }

        void collect()
        {
            //mark()
//            for(auto& p : objects)
//                if(p && p->sweep())
//                {
//                    delete p;
//                    p = NULL;
//                }
            //remove nulls
        }
    };

}

#endif // GC_H_INCLUDED
