#pragma once
#ifndef __BIBIM_OBJECT_H__
#define __BIBIM_OBJECT_H__

#include <Bibim/Foundation.h>
#include <Bibim/Class.h>

namespace Bibim
{
    class Object
    {
        public:
            virtual ~Object() { }

            virtual int GetClassID() const;

            template <typename T> bool IsInstanceOf() const
            {
                return GetClassID() == T::ClassID;
            }

        protected:
            Object();
    };
}

#endif