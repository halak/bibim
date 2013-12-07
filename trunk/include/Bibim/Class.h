#pragma once
#ifndef __BIBIM_CLASS_H__
#define __BIBIM_CLASS_H__

#include <Bibim/Foundation.h>

namespace Bibim
{
    class Class
    {
        BBThisIsNoncopyableClass(Class);
        public:
            explicit Class(int id);
            Class(int id, int baseID);
            ~Class();

            inline int GetID() const;
            const Class* GetBase() const;

            bool IsInstanceOf(const Class* other) const;
            bool IsInstanceOf(int id) const;

        private:
            const int id;
            const Class mutable* base;
            const int baseID;
    };

    int Class::GetID() const
    {
        return id;
    }
}

#endif