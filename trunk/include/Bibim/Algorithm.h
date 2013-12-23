#pragma once
#ifndef __BIBIM_ALGORITHM_H__
#define __BIBIM_ALGORITHM_H__

#include <Bibim/FWD.h>

namespace Bibim
{
    class Container
    {
        BBThisIsStaticClass(Container);
        public:
            template <typename T>
            static inline bool Contains(const std::vector<SharedPointer<T> >& container, const T* item)
            {
                for (typename std::vector<SharedPointer<T> >::const_iterator it = container.begin(); it != container.end(); it++)
                {
                    if ((*it) == item)
                        return true;
                }

                return false;
            }

            template <typename T>
            static inline bool Remove(std::vector<SharedPointer<T> >& container, const T* item)
            {
                for (typename std::vector<SharedPointer<T> >::iterator it = container.begin(); it != container.end(); it++)
                {
                    if ((*it) == item)
                    {
                        container.erase(it);
                        return true;
                    }
                }

                return false;
            }

            template <typename T>
            static inline bool Remove(std::vector<SharedPointer<T> >& container, const SharedPointer<T>& item)
            {
                return Remove(container, item.GetPointee());
            }
    };
}

#endif