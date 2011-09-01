#include <Bibim/Timer.h>
#include <Bibim/Math.h>

namespace Bibim
{
    Timer::Timer()
        : time(0.0f),
          duration(0.0f)
    {
    }

    Timer::Timer(float duration)
        : time(0.0f),
          duration(Math::Max(duration, 0.0f))
    {
    }

    Timer::~Timer()
    {
    }

    void Timer::Update(float dt, uint timestamp)
    {
        if (Seal(timestamp) || time == duration)
            return;

        time += dt;

        if (time >= duration)
        {
            time = duration;
            OnTick();
        }
    }

    void Timer::SetDuration(float value)
    {
        duration = Math::Max(value, 0.0f);
    }
}