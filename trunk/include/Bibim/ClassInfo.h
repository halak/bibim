#pragma once
#ifndef __BIBIM_CLASSINFO_H__
#define __BIBIM_CLASSINFO_H__

#include <Bibim/Foundation.h>

namespace Bibim
{
    class ClassInfo
    {
        BBThisIsNoncopyableClass(ClassInfo);
        public:
            ClassInfo();
            explicit ClassInfo(int id);
            explicit ClassInfo(ClassInfo* base);
            ClassInfo(int id, ClassInfo* base);
            ~ClassInfo();

            inline int GetID() const;
            inline const ClassInfo* GetBase() const;

            bool IsInstanceOf(const ClassInfo* other) const;

        private:
            const int id;
            const ClassInfo* const base;
    };

    int ClassInfo::GetID() const
    {
        return id;
    }

    const ClassInfo* ClassInfo::GetBase() const
    {
        return base;
    }
}

#endif