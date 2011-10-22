#pragma once
#ifndef __BIBIM_ANIMATIONTIMELINE_H__
#define __BIBIM_ANIMATIONTIMELINE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/TimelineGameModule.h>

    namespace Bibim
    {
        class AnimationTimeline : public TimelineGameModule
        {
            BBModuleClass(AnimationTimeline, TimelineGameModule, 'A', 'N', 'T', 'M');
            public:
                AnimationTimeline();
                virtual ~AnimationTimeline();

            private:
        };
    }

#   include <Bibim/AnimationTimeline.inl>

#endif