#pragma once
#ifndef __BIBIM_OBJECT_H__
#define __BIBIM_OBJECT_H__

#   include <Bibim/Foundation.h>

    namespace Bibim
    {
        class Object
        {
            public:
                virtual ~Object() { }

            protected:
                Object();
        };
    }

#   include <Bibim/Object.inl>

#endif