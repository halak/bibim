#pragma once
#ifndef __BIBIM_PERFORMANCE_H__
#define __BIBIM_PERFORMANCE_H__

#include <Bibim/FWD.h>
#include <Bibim/Clock.h>

namespace Bibim
{
#   if (defined(BIBIM_PLATFORM_WINDOWS))
#       define BBPerfFunc() PerformanceAutoSampler sampler(__FUNCTION__, __FILE__, __LINE__);
#   else
#       define BBPerfFunc() PerformanceAutoSampler sampler(__func__, __FILE__, __LINE__);
#   endif

    class Performance
    {
        BBThisIsStaticClass(Performance);
        public:
            struct Sample
            {
                const char* Function;
                const char* Filename;
                int Line;
                int64 StartTime;
                int64 EndTime;

                inline Sample();
                inline Sample(const char* function, const char* filename, int line, int64 start);
                inline Sample(const Sample& original);
            };

            static void Report(const Sample& sample);
    };

    class PerformanceAutoSampler
    {
        BBThisIsNoncopyableClass(PerformanceAutoSampler);
        public:
            inline PerformanceAutoSampler(const char* function, const char* filename, int line);
            inline ~PerformanceAutoSampler();

        private:
            Performance::Sample sample;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    Performance::Sample::Sample()
        : Function(nullptr),
          Filename(nullptr),
          Line(0),
          StartTime(0),
          EndTime(0)
    {
    }

    Performance::Sample::Sample(const char* function, const char* filename, int line, int64 startTime)
        : Function(function),
          Filename(filename),
          Line(line),
          StartTime(startTime),
          EndTime(startTime)
    {
    }

    Performance::Sample::Sample(const Sample& original)
        : Function(original.Function),
          Filename(original.Filename),
          Line(original.Line),
          StartTime(original.StartTime),
          EndTime(original.EndTime)
    {
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    PerformanceAutoSampler::PerformanceAutoSampler(const char* function, const char* filename, int line)
        : sample(function, filename, line, Clock::GetCurrentMicroSeconds())
    {
    }

    PerformanceAutoSampler::~PerformanceAutoSampler()
    {
        sample.EndTime = Clock::GetCurrentMicroSeconds();
        Performance::Report(sample);
    }
}

#endif