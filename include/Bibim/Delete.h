#pragma once
#ifndef __BIBIM_DELETE_H__
#define __BIBIM_DELETE_H__

#   include <Bibim/Foundation.h>

    namespace Bibim
    {
        template <typename T> void DeleteAll(T& container)
        {
            T deletingContainer;
            deletingContainer.swap(container);

            DeleteAll(deletingContainer.begin(), deletingContainer.end());
        }

        template <typename T> void DeleteAll(T begin, T end)
        {
            for (; begin != end; begin++)
                delete (*begin);
        }
    }

#endif