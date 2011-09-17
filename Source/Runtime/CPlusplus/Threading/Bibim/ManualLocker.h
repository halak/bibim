#pragma once
#ifndef __BIBIM_MANUALLOCKER_H__
#define __BIBIM_MANUALLOCKER_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Lock.h>

    namespace Bibim
    {
        class ManualLocker
        {
            BBThisIsNoncopyableClass(ManualLocker);
            public:
                inline ManualLocker(Bibim::Lock& lock);
                ~ManualLocker();

                inline void Lock();
                inline void Unlock();

            private:
                Bibim::Lock& lock;
                int lockCount;
        };
    }

#   include <Bibim/ManualLocker.inl>

#endif