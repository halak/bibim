#include <Bibim/PCH.h>
#include <Bibim/Clock.h>
#include <time.h>

namespace Bibim
{
    struct UnixClock
    {
        static UnixClock StaticInstance;
        int64 startTime;

        UnixClock()
        {
            struct timeval tv;
            gettimeofday(&tv, NULL);
            startTime = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
        }

        double GetCurrent()
        {
            return static_cast<double>(GetCurrentMilliSeconds()) * 0.001;
        }

        int64 GetCurrentMilliSeconds()
        {
            struct timeval tv;
            gettimeofday(&tv, NULL);
            return static_cast<int64>((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - startTime;
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