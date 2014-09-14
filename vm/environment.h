#ifndef ENVIRONMENT_H_INCLUDED
#define ENVIRONMENT_H_INCLUDED

#include "symbol_table.h"

#include <memory>

namespace AYA
{
    class Environment;
    typedef std::shared_ptr<Environment> pEnvironment;

    class Environment : public SymbolTable
    {
    protected:
        pEnvironment _parent;

    public:
        explicit Environment(const pEnvironment& parent)
        : SymbolTable(), _parent(parent) {}
        Environment(const Environment&) = delete;

        pEnvironment parent()
        {
            return _parent;
        }

        /// Load variable
        const Variant* get(const IDENT_T& key)
        {
            if(!empty())
            {
                Variant* p = find(key);

                //Found
                if(p)
                    return p;
            }

            //Not found
            if(_parent)
                return _parent->get(key);
            else
                return NULL;
        }

        /// Store variable
        void set(const IDENT_T& key, const Variant& val)
        {
            if(!empty())
            {
                Variant* p = find(key);

                //Found
                if(p)
                {
                    *p = val;
                    return;
                }
            }

            //Not found
            if(_parent)
                _parent->set(key, val);
            else
                this->insert(key, val);
        }

        /// Declare global variable (explicitly or implicitly through first time use)
        Variant* insertGlobal(const IDENT_T& key, const Variant& val)
        {
            if(_parent)
                return _parent->insertGlobal(key, val);
            else
                return this->insert(key, val);
        }

        /// Declare local variable (explicit)
        Variant* insertLocal(const IDENT_T& key, const Variant& val)
        {
            return insert(key, val);
        }

        void declareLocal(const IDENT_T& key)
        {
            Variant* v = find(key);
            if(!v)
                insert(key, NIL());
        }

        /// Set variable to NIL
        /// It only actually removes its entry in the global environment
        void setNil(const IDENT_T& key)
        {
            if(_parent)
                setNil(key);
            else if(!empty())
            {
                remove(key);
                //Move content into map
                moveToMap();
            }
        }

        /// Unset (not supported by language)
        void remove(const IDENT_T& key)
        {
            if(!empty())
            {
                Variant* p = find(key);

                //Not found
                if(!p)
                {
                    if(_parent)
                        _parent->remove(key);
                }
                else
                {
                    remove(key);
                    moveToMap();
                }
            }
            else if(_parent)
                _parent->remove(key);
        }

        void mark() const
        {
            SymbolTable::mark();
            if(_parent)
                _parent->mark();
        }
    };

}

#endif // ENVIRONMENT_H_INCLUDED
