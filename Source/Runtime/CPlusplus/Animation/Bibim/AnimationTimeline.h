#pragma once
#ifndef __BIBIM_ANIMATIONTIMELINE_H__
#define __BIBIM_ANIMATIONTIMELINE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/TimelineGameModule.h>
#   include <vector>

    namespace Bibim
    {
        class AnimationTimeline : public TimelineGameModule
        {
            BBModuleClass(AnimationTimeline, TimelineGameModule, 'A', 'N', 'T', 'M');
            public:
                typedef std::vector<AnimatorPtr> AnimatorCollection;

            public:
                AnimationTimeline();
                virtual ~AnimationTimeline();

            private:
                void Add(Animator* item); // call in Animator
                void Remove(Animator* item); // call in Animator
                void OnActiveChanged(Animator* item); // call in Animator

            private:
                AnimatorCollection animators;
                AnimatorCollection activeAnimators;

                friend class Animator;
        };
    }

#   include <Bibim/AnimationTimeline.inl>

#endif