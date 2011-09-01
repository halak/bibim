#include <Bibim/PCH.h>
#include <Bibim/ParallelTimeline.Windows.h>

#if (defined(BIBIM_PLATFORM_WINDOWS))

    namespace Bibim
    {
        ParallelTimeline::ParallelTimeline()
        {
        }

        ParallelTimeline::ParallelTimeline(uint32 id)
            : Timeline(id)
        {
        }
        
        ParallelTimeline::~ParallelTimeline()
        {
        }

        void ParallelTimeline::OnStatusChanged(Status /*old*/)
        {
        }
    }

#endif