#include <Bibim/Config.h>
#if (defined(BIBIM_PLATFORM_UNIX))

#include <Bibim/Clock.h>
#include <sys/time.h>

static Bibim::int64 GetTimeOfDay()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000) + tv.tv_usec;
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

        double GetCurrent() const
        {
            return static_cast<double>(GetTimeOfDay() - startTime) * 0.000001;
        }

        int64 GetCurrentMicroSeconds() const
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
        return static_cast<int>(UnixClock::StaticInstance.GetCurrentMicroSeconds() / 1000);
    }

    int64 Clock::GetCurrentMicroSeconds()
    {
        return UnixClock::StaticInstance.GetCurrentMicroSeconds();
    }
}

#endif