#include <Bibim/PCH.h>
#include <Bibim/Thread.Windows.h>

#if (defined(BIBIM_PLATFORM_WINDOWS))

#   include <windows.h>

    namespace Bibim
    {
        struct Thread::Internal
        {
            static DWORD WINAPI Procedure(LPVOID parameters)
            {
                static_cast<Thread*>(parameters)->OnWork();
                
                return 0;
            }
        };

        Thread::Thread()
        {
            Construct(true);
        }

        Thread::Thread(bool autoStart)
        {
            Construct(autoStart);
        }

        Thread::~Thread()
        {
            if (handle)
                ::CloseHandle(static_cast<HANDLE>(handle));
        }

        void Thread::Resume()
        {
            ::ResumeThread(static_cast<HANDLE>(handle));
        }

        void Thread::Suspend()
        {
            ::SuspendThread(static_cast<HANDLE>(handle));
        }

        void Thread::Join()
        {
            if (handle)
            {
                ::WaitForSingleObject(static_cast<HANDLE>(handle), INFINITE);
                ::CloseHandle(static_cast<HANDLE>(handle));
                handle = nullptr;
            }
        }

        Thread::Priority Thread::GetPriority() const
        {
            switch (::GetThreadPriority(static_cast<HANDLE>(handle)))
            {
                case THREAD_PRIORITY_LOWEST:
                    return LowestPriority;
                case THREAD_PRIORITY_BELOW_NORMAL:
                    return LowPriority;
                case THREAD_PRIORITY_NORMAL:
                    return NormalPriority;
                case THREAD_PRIORITY_ABOVE_NORMAL:
                    return HighPriority;
                case THREAD_PRIORITY_HIGHEST:
                    return HighestPriority;
                default:
                    return NormalPriority;
            }
        }

        void Thread::SetPriority(Priority value)
        {
            int priority = THREAD_PRIORITY_NORMAL;
            switch (value)
            {
                case LowestPriority:
                    priority = THREAD_PRIORITY_LOWEST;
                    break;
                case LowPriority:
                    priority = THREAD_PRIORITY_BELOW_NORMAL;
                    break;
                case NormalPriority:
                    priority = THREAD_PRIORITY_NORMAL;
                    break;
                case HighestPriority:
                    priority = THREAD_PRIORITY_ABOVE_NORMAL;
                    break;
                case HighPriority:
                    priority = THREAD_PRIORITY_HIGHEST;
                    break;
            }

            ::SetThreadPriority(static_cast<HANDLE>(handle), priority);
        }

        void Thread::Sleep()
        {
            ::Sleep(1);
        }

        void Thread::Sleep(int milliSeconds)
        {
            ::Sleep(static_cast<ULONG>(milliSeconds));
        }

        void Thread::Exit()
        {
            ::ExitThread(0);
        }

        void Thread::Construct(bool autoStart)
        {
            DWORD creationFlags = 0x00000000;
            DWORD threadID = 0x00000000;

            if (autoStart == false)
                creationFlags |= CREATE_SUSPENDED;

            handle = static_cast<void*>(::CreateThread(nullptr, 0, &Thread::Internal::Procedure, this, creationFlags, &threadID));
            id = static_cast<int>(threadID);
        }
    }

#endif