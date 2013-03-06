#include <Bibim/PCH.h>
#include <Bibim/Clock.h>
#include <time.h>

namespace Bibim
{
    struct AndroidClock
    {
        static AndroidClock StaticInstance;
        int64 startTime;

        AndroidClock()
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

    AndroidClock AndroidClock::StaticInstance;

    float Clock::GetCurrent()
    {
        return static_cast<float>(AndroidClock::StaticInstance.GetCurrent());
    }

    int Clock::GetCurrentMilliSeconds()
    {
        return static_cast<int>(AndroidClock::StaticInstance.GetCurrentMilliSeconds());
    }
}