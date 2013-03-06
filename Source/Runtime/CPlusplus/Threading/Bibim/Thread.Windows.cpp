#include <Bibim/PCH.h>
#include <Bibim/Thread.Windows.h>
#include <windows.h>

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
        : handle(nullptr)
    {
    }

    Thread::~Thread()
    {
        if (handle)
            ::CloseHandle(static_cast<HANDLE>(handle));
    }

    void Thread::Start()
    {
        if (handle)
            return;

        DWORD threadID = 0x00000000;
        handle = static_cast<void*>(::CreateThread(nullptr, 0, &Thread::Internal::Procedure, this, 0x00000000, &threadID));
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
}