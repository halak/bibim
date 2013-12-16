#pragma once
#ifndef __BIBIM_CLASSHIERARCHY_H__
#define __BIBIM_CLASSHIERARCHY_H__

#include <Bibim/FWD.h>

namespace Bibim
{
    class ClassInfo;
    class ClassHierarchy
    {
        public:
            static const ClassInfo* Find(int id);

        private:
            static void Add(const ClassInfo* item);

            friend class ClassInfo;
    };
}

#endif