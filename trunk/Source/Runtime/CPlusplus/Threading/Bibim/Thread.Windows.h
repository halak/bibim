#pragma once
#ifndef __BIBIM_THREAD_WINDOWS_H__
#define __BIBIM_THREAD_WINDOWS_H__

#   include <Bibim/FWD.h>

    namespace Bibim
    {
        class Thread
        {
            BBThisIsNoncopyableClass(Thread);
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
                Thread();
                Thread(bool autoStart);
                virtual ~Thread();

                void Resume();
                void Suspend();
                void Join();

                Priority GetPriority() const;
                void SetPriority(Priority value);

                inline uint GetID() const;

            public:
                static void Sleep();
                static void Sleep(uint milliSeconds);

            protected:
                void Exit();

                virtual void OnWork() = 0;

            private:
                void Construct(bool autoStart);

            private:
                uint id;
                void* handle;

                struct Internal;
        };
    }

#   include <Bibim/Thread.Windows.inl>

#endif