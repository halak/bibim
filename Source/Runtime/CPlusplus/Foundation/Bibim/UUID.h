#pragma once
#ifndef __BIBIM_UUID_H__
#define __BIBIM_UUID_H__

#   include <Bibim/Foundation.h>

    namespace Bibim
    {
        struct UUID
        {
            dword Values[4];

            inline UUID();
            inline UUID(const UUID& original);

            inline UUID& operator = (const UUID& right);
            inline bool operator == (const UUID& right) const;
            inline bool operator != (const UUID& right) const;

            inline bool operator < (const UUID& right) const;

            static const UUID Empty;
        };
    }

#   include <Bibim/UUID.inl>

#endif