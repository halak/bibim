#pragma once
#ifndef __BIBIM_ANIMATORS_H__
#define __BIBIM_ANIMATORS_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameComponent.h>

    namespace Bibim
    {
        class Animator : public GameComponent
        {
            BBAbstractComponentClass(Animator, GameComponent);
            public:
                Animator();
                virtual ~Animator();

                void Update(float dt);

                void Play();
                void Stop();
                void Pause();

                inline AnimationTimeline* GetTimeline() const;
                void SetTimeline(AnimationTimeline* value);

                inline bool GetActive() const;
                void SetActive(bool value);

            private:
                AnimationTimeline* timeline;
                bool active;
        };
    }

#   include <Bibim/Animator.inl>

#endif