#include <Bibim/PCH.h>
#include <Bibim/Thread.Unix.h>

namespace Bibim
{
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
    }

    void Thread::Resume()
    {
    }

    void Thread::Suspend()
    {
    }

    void Thread::Join()
    {
    }

    Thread::Priority Thread::GetPriority() const
    {
        return NormalPriority;
    }

    void Thread::SetPriority(Priority value)
    {
    }

    void Thread::Sleep()
    {
    }

    void Thread::Sleep(int milliSeconds)
    {
    }

    void Thread::Exit()
    {
    }

    void Thread::Construct(bool autoStart)
    {
    }
}