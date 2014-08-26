#ifndef SYMBOL_TABLE_H_INCLUDED
#define SYMBOL_TABLE_H_INCLUDED

#include "variant.h"

#include <map>
#include <unordered_map>

namespace AYA
{
    class SymbolTable
    {
    protected:
        /// ----- Interface -----
        struct ImplInterface
        {
            virtual ~ImplInterface() {}

            virtual bool empty() =0;
            virtual size_t size() =0;
            virtual bool exists(const IDENT_T&) =0;
            virtual Variant* find(const IDENT_T&) =0;
            virtual Variant* insert(const IDENT_T&, const Variant&) =0;
            virtual bool remove(const IDENT_T&) =0;

            virtual bool isMap() =0;

            virtual void mark() =0;
        };

        typedef std::map<IDENT_T, Variant> Map;
        typedef std::unordered_map<IDENT_T, Variant> Hash;

        /// Concrete Implementation
        template<class Container>
        class Impl : public ImplInterface
        {
        protected:
            Container c;
            typedef typename Container::iterator iterator;

        public:
            friend class Impl<Map>;
            friend class Impl<Hash>;

            Impl(){}

            template <class Original>
            Impl(Original* o)
            : c(o->c.begin(), o->c.end()) {}

            bool empty()
            { return c.empty(); }

            size_t size()
            { return c.size(); }

            bool exists(const IDENT_T& key)
            { return c.count(key); }

            Variant* find(const IDENT_T& key)
            {
                auto it = c.find(key);
                return it != c.end() ? &(it->second) : NULL;
            }

            Variant* insert(const IDENT_T& key, const Variant& val)
            { return &(c[key] = val); }

            bool remove(const IDENT_T& key)
            { return c.erase(key); }

            bool isMap();

            void mark()
            {
                for(auto& elem : c)
                    elem.second.mark();
            }
        };

    public:
        SymbolTable(): impl(NULL) {}
        SymbolTable(const SymbolTable& o)
        {
            if(o.impl)
            {
                if(o.impl->isMap())
                    impl = new Impl<Map>(static_cast<Impl<Map>*>(o.impl));
                else
                    impl = new Impl<Hash>(static_cast<Impl<Hash>*>(o.impl));
            }
        }

        ~SymbolTable()
        { delete impl; }

        void mark() const
        {
            if(impl)
                impl->mark();
        }

    protected:
        ImplInterface* impl;

        bool empty()
        { return !impl || impl->empty(); }

        Variant* find(const IDENT_T& key)
        { return impl->find(key); }

        Variant* insert(const IDENT_T& key, const Variant& val)
        {
            if(impl)
            {
                //Move content into hash
                moveToHash();
            }
            else
                impl = new Impl<Map>();

            return impl->insert(key, val);
        }

        bool remove(const IDENT_T& key)
        { return impl->remove(key); }

        void moveToHash()
        {
            if(impl && impl->isMap() && impl->size() >= upper_bound)
            {
                ImplInterface* newImpl = new Impl<Hash>(static_cast<Impl<Map>*>(impl));
                std::swap(impl, newImpl);
            }
        }

        void moveToMap()
        {
            if(impl && !impl->isMap() && impl->size() >= lower_bound)
            {
                ImplInterface* newImpl = new Impl<Map>(static_cast<Impl<Hash>*>(impl));
                std::swap(impl, newImpl);
            }
        }

        /// if size > upper_bound then convert map -> hash
        /// if size < lower_bound then convert hash -> map
        static const size_t upper_bound;
        static const size_t lower_bound;
    };

    template<>
    inline bool SymbolTable::Impl<SymbolTable::Map>::isMap()
    {
        return true;
    }

    template<>
    inline bool SymbolTable::Impl<SymbolTable::Hash>::isMap()
    {
        return false;
    }
}

#endif // SYMBOL_TABLE_H_INCLUDED
