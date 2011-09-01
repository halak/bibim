#pragma once
#ifndef __BIBIM_SHAREDOBJECTLIFE_H__
#define __BIBIM_SHAREDOBJECTLIFE_H__

#   include <Bibim/Foundation.h>

    namespace Bibim
    {
        class SharedObjectLife;
        class SharedObject;

        class SharedObjectLife
        {
            BBThisIsNoncopyableClass(SharedObjectLife);
            public:
#               if (defined(BIBIM_PLATFORM_WINDOWS))
                    typedef long IntType;
#               else
                    typedef int IntType;
#               endif

            public:
                inline SharedObjectLife(SharedObject* pointee);

                void IncreaseStrongCount();
                bool DecreaseStrongCount();
                void IncreaseWeakCount();
                void DecreaseWeakCount();

                inline int GetStrong() const;
                inline int GetWeak() const;

                inline bool IsAlive() const;

            private:
                SharedObject* pointee;
                IntType strong;
                IntType weak;
        };
    }

#   include <Bibim/SharedObjectLife.inl>

#endif