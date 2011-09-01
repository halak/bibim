#include <Bibim/PCH.h>
#include <Bibim/Clock.h>

#if (defined(BIBIM_PLATFORM_WINDOWS))

#    include <windows.h>

    namespace Bibim
    {
        struct WindowsClock
        {
            static WindowsClock StaticInstance;

            __int64 StartTime;
            double Frequency;
            double FrequencyMilliSeconds;
            bool IsHighResolution;

            WindowsClock()
            {
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
            }

            double GetCurrent()
            {
                if (IsHighResolution)
                {
                    LARGE_INTEGER countInteger;
                    QueryPerformanceCounter(&countInteger);
                    return static_cast<double>(countInteger.QuadPart - StartTime) * Frequency;
                }
                else
                    return static_cast<double>(timeGetTime()) * 0.001f;
            }

            __int64 GetCurrentMilliSeconds()
            {
                if (IsHighResolution)
                {
                    LARGE_INTEGER countInteger;
                    QueryPerformanceCounter(&countInteger);
                    return static_cast<__int64>(static_cast<double>(countInteger.QuadPart - StartTime) * FrequencyMilliSeconds);
                }
                else
                    return static_cast<__int64>(timeGetTime());
            }
        };

        WindowsClock WindowsClock::StaticInstance;

        float Clock::GetCurrent()
        {
            return static_cast<float>(WindowsClock::StaticInstance.GetCurrent());
        }

        uint Clock::GetCurrentMilliSeconds()
        {
            return static_cast<uint>(WindowsClock::StaticInstance.GetCurrentMilliSeconds());
        }

        bool Clock::IsHighResolution()
        {
            return WindowsClock::StaticInstance.IsHighResolution;
        }
    }

#endif