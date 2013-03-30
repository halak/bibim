#pragma once
#ifndef __BIBIM_THREAD_WINDOWS_H__
#define __BIBIM_THREAD_WINDOWS_H__

#   include <Bibim/FWD.h>
#   include <Bibim/ThreadBase.h>

    namespace Bibim
    {
        class Thread : public ThreadBase
        {
            BBThisIsNoncopyableClass(Thread);
            public:
                Thread();
                virtual ~Thread();

                virtual void Start();
                void Join();

            public:
                static void Sleep();
                static void Sleep(int milliSeconds);

            protected:
                void Exit();

                virtual void OnWork() = 0;

            private:
                void* handle;

                struct Internal;
        };
    }

#endif