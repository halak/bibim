#include <Bibim/PCH.h>
#include <Bibim/Clock.h>

namespace Bibim
{
    struct AndroidClock
    {
        static AndroidClock StaticInstance;

        AndroidClock()
        {
            /*
            LARGE_INTEGER frequencyInteger;
            if (QueryPerformanceFrequency(&frequencyInteger))
            {
                LARGE_INTEGER startTimeInteger;
                QueryPerformanceCounter(&startTimeInteger);

                StartTime = startTimeInteger.QuadPart;
                Frequency = 1.0 / static_cast<double>(frequencyInteger.QuadPart);
                FrequencyMilliSeconds = Frequency * 1000.0;
                IsHighResolution = true;
            }
            else
            {
                Frequency = 0.0;
                FrequencyMilliSeconds = 0.0;
                IsHighResolution = false;
            }
            */
        }

        double GetCurrent()
        {
            /*
            if (IsHighResolution)
            {
                LARGE_INTEGER countInteger;
                QueryPerformanceCounter(&countInteger);
                return static_cast<double>(countInteger.QuadPart - StartTime) * Frequency;
            }
            else
                return static_cast<double>(timeGetTime()) * 0.001f;
                */
        }

        int64 GetCurrentMilliSeconds()
        {
            /*
            if (IsHighResolution)
            {
                LARGE_INTEGER countInteger;
                QueryPerformanceCounter(&countInteger);
                return static_cast<__int64>(static_cast<double>(countInteger.QuadPart - StartTime) * FrequencyMilliSeconds);
            }
            else
                return static_cast<__int64>(timeGetTime());
                */
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