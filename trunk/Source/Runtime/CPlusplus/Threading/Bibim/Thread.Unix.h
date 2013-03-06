#pragma once
#ifndef __BIBIM_THREAD_UNIX_H__
#define __BIBIM_THREAD_UNIX_H__

#   include <Bibim/FWD.h>
#   include <Bibim/ThreadBase.h>
#   include <pthread.h>

    namespace Bibim
    {
        class Thread : public ThreadBase
        {
            BBThisIsNoncopyableClass(Thread);
            public:
                Thread();
                virtual ~Thread();

                void Start();
                void Join();

            public:
                static void Sleep();
                static void Sleep(int milliSeconds);

            protected:
                void Exit();

                virtual void OnWork() = 0;

            private:
                pthread_t handle;

                struct Internal;

                //static bool IsInitialized;
        };
    }

#endif