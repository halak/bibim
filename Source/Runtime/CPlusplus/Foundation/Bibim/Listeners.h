#pragma once
#ifndef __BIBIM_LISTENERS_H__
#define __BIBIM_LISTENERS_H__

#   include <Bibim/FWD.h>
#   include <vector>

    namespace Bibim
    {
        template <typename T> class Listeners
        {
            public:
                typedef typename std::vector<T*>::const_iterator Iterator;

            public:
                Listeners();
                Listeners(int capacity);
                ~Listeners();

                void Add(T* item);
                void Add(T* item, SharedObject* obj);
                bool Remove(T* item);
                void Clear();

                Iterator Begin() const;
                Iterator End() const;

            private:
                std::vector<T*> items;
                std::vector<SharedObjectPtr> objects;
        };
    }

#   include <Bibim/Listeners.inl>

#endif