#pragma once
#ifndef __BIBIM_CLASSHIERARCHY_H__
#define __BIBIM_CLASSHIERARCHY_H__

#include <Bibim/FWD.h>

namespace Bibim
{
    class Class;
    class ClassHierarchy
    {
        public:
            static const Class* Find(int id);

        private:
            static void Add(const Class* item);

            friend class Class;
    };
}

#endif