#pragma once
#ifndef __BIBIM_ICLASSQUERYABLE_H__
#define __BIBIM_ICLASSQUERYABLE_H__

#   include <Bibim/Foundation.h>

    namespace Bibim
    {
        class IClassQueryable
        {
            public:
                virtual ~IClassQueryable() { }

                virtual       void* QueryClass(uint32 classID) = 0;
                virtual const void* QueryClass(uint32 classID) const;
        };
    }

#endif