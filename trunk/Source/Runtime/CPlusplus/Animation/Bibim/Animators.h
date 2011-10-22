#pragma once
#ifndef __BIBIM_ANIMATORS_H__
#define __BIBIM_ANIMATORS_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameComponent.h>

    namespace Bibim
    {
        class Animator : public Component
        {
            BBAbstractComponentClass(Animator, Component);
            public:
                Animator();
                virtual ~Animator();

                virtual void Update(float dt);
        };

        template <typename T> class AnimatorTemplate : public Animator
        {
            BBAbstractComponentClass(AnimatorTemplate, Animator);
            public:
                AnimatorTemplate();
                virtual ~AnimatorTemplate();
        };
    }

#   include <Bibim/Animators.inl>

#endif