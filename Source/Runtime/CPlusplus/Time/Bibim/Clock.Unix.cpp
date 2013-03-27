#include <Bibim/PCH.h>
#include <Bibim/Clock.h>
#include <sys/time.h>

static Bibim::int64 GetTimeOfDay()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

namespace Bibim
{
    struct UnixClock
    {
        static UnixClock StaticInstance;
        int64 startTime;

        UnixClock()
        {
            startTime = GetTimeOfDay();
        }

        double GetCurrent()
        {
            return static_cast<double>(GetCurrentMilliSeconds()) * 0.001;
        }

        int64 GetCurrentMilliSeconds()
        {
            return GetTimeOfDay() - startTime;
        }
    };

    UnixClock UnixClock::StaticInstance;

    float Clock::GetCurrent()
    {
        return static_cast<float>(UnixClock::StaticInstance.GetCurrent());
    }

    int Clock::GetCurrentMilliSeconds()
    {
        return static_cast<int>(UnixClock::StaticInstance.GetCurrentMilliSeconds());
    }
}