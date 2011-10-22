#pragma once
#ifndef __BIBIM_ANIMATORGROUP_H__
#define __BIBIM_ANIMATORGROUP_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Animator.h>

    namespace Bibim
    {
        class AnimatorGroup : public Animator
        {
            BBComponentClass(AnimatorGroup, Animator);
            public:
                AnimatorGroup();
                virtual ~AnimatorGroup();

            private:
        };
    }

#   include <Bibim/AnimatorGroup.inl>

#endif