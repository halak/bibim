#include <Bibim/Config.h>
#if (defined(BIBIM_PLATFORM_UNIX))

#include <Bibim/Thread.Unix.h>
#include <unistd.h>

namespace Bibim
{
    // bool Thread::IsInitialized = false;
    struct Thread::Internal
    {
        static void* Procedure(void* parameters)
        {
            static_cast<Thread*>(parameters)->OnWork();
            return nullptr;
        }
    };

    Thread::Thread()
        : handle(0)
    {
    }

    Thread::~Thread()
    {
        if (handle)
            pthread_detach(handle);
    }

    void Thread::Start()
    {
        if (handle)
            return;

        pthread_create(&handle, nullptr, Internal::Procedure, this);
    }

    void Thread::Join()
    {
        if (handle)
        {
            pthread_join(handle, nullptr);
            pthread_detach(handle);
            handle = 0;
        }
    }

    void Thread::Sleep()
    {
        usleep(1000);
    }

    void Thread::Sleep(int milliSeconds)
    {
        usleep(milliSeconds * 1000);
    }

    void Thread::Exit()
    {
        pthread_exit(nullptr);
    }
}

#endif