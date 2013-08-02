#pragma once
#ifndef __BIBIM_THREAD_BASE_H__
#define __BIBIM_THREAD_BASE_H__

#   include <Bibim/FWD.h>

    namespace Bibim
    {
        class ThreadBase
        {
            BBThisIsNoncopyableClass(ThreadBase);
            public:
                enum Priority
                {
                    LowestPriority,
                    LowPriority,
                    NormalPriority,
                    HighestPriority,
                    HighPriority,
                };

            public:
                ThreadBase() { }
        };
    }


#endif