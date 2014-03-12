#pragma once
#ifndef __BIBIM_PERFORMANCE_H__
#define __BIBIM_PERFORMANCE_H__

#include <Bibim/FWD.h>
#include <vector>

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
                int Parent;
                int Depth;
                const char* Function;
                const char* Filename;
                int Line;
                int64 StartTime;
                int64 EndTime;

                inline Sample();
                inline Sample(int parent, int depth, const char* function, const char* filename, int line);
                inline Sample(const Sample& original);
            };
            typedef std::vector<Sample> SampleCollection;

            static void Reset();
            static const SampleCollection& GetSamples();

        private:
            static void Open(const char* function, const char* filename, int line);
            static void Close();
            friend class PerformanceAutoSampler;
    };

    class PerformanceAutoSampler
    {
        BBThisIsNoncopyableClass(PerformanceAutoSampler);
        public:
            inline PerformanceAutoSampler(const char* function, const char* filename, int line);
            inline ~PerformanceAutoSampler();
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    Performance::Sample::Sample()
        : Parent(-1),
          Depth(0),
          Function(nullptr),
          Filename(nullptr),
          Line(0),
          StartTime(0),
          EndTime(0)
    {
    }

    Performance::Sample::Sample(int parent, int depth, const char* function, const char* filename, int line)
        : Parent(parent),
          Depth(depth),
          Function(function),
          Filename(filename),
          Line(line),
          StartTime(0),
          EndTime(0)
    {
    }

    Performance::Sample::Sample(const Sample& original)
        : Parent(original.Parent),
          Depth(original.Depth),
          Function(original.Function),
          Filename(original.Filename),
          Line(original.Line),
          StartTime(original.StartTime),
          EndTime(original.EndTime)
    {
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    PerformanceAutoSampler::PerformanceAutoSampler(const char* function, const char* filename, int line)
    {
        Performance::Open(function, filename, line);
    }

    PerformanceAutoSampler::~PerformanceAutoSampler()
    {
        Performance::Close();
    }
}

#endif