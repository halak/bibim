#include <Bibim/Config.h>
#include <Bibim/Performance.h>
#include <Bibim/Assert.h>
#include <Bibim/Clock.h>

namespace Bibim
{
    static Performance::SampleCollection PerformanceSamples;
    static int PerformanceDepth = 0;
    static int PerformanceCurrent = -1;

    void Performance::Reset()
    {
        if (PerformanceSamples.capacity() < 256)
            PerformanceSamples.reserve(256);

        PerformanceSamples.clear();
        PerformanceDepth = 0;
        PerformanceCurrent = -1;
    }

    const Performance::SampleCollection& Performance::GetSamples()
    {
        return PerformanceSamples;
    }

    void Performance::Open(const char* function, const char* filename, int line)
    {
        PerformanceSamples.push_back(Sample(PerformanceCurrent,
                                            PerformanceDepth,
                                            function,
                                            filename,
                                            line));
        PerformanceDepth++;
        PerformanceCurrent = static_cast<int>(PerformanceSamples.size()) - 1;
        PerformanceSamples.back().StartTime = Clock::GetCurrentMicroSeconds();
    }

    void Performance::Close()
    {
        BBAssertDebug(PerformanceSamples.empty() == false);

        Sample& sample = PerformanceSamples.back();
        sample.EndTime = Clock::GetCurrentMicroSeconds();
        PerformanceDepth--;
        PerformanceCurrent = sample.Parent;
    }
}