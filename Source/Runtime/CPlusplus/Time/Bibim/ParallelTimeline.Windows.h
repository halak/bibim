#pragma once
#ifndef __BIBIM_PARALLELTIMELINE_WINDOWS_H__
#define __BIBIM_PARALLELTIMELINE_WINDOWS_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Timeline.h>

#   if (defined(BIBIM_PLATFORM_WINDOWS))

        namespace Bibim
        {
            class ParallelTimeline : public Timeline
            {
                BBClassFOURCC('P', 'R', 'T', 'L');
                public:
                    ParallelTimeline();
                    explicit ParallelTimeline(uint32 id);
                    virtual ~ParallelTimeline();

                protected:
                    virtual void OnStatusChanged(Status old);

                private:
            };
        }

#       include <Bibim/ParallelTimeline.Windows.inl>

#   endif

#endif