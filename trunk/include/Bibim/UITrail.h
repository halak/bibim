#pragma once
#ifndef __BIBIM_UITRAIL_H__
#define __BIBIM_UITRAIL_H__

#include <Bibim/FWD.h>
#include <Bibim/UIVisual.h>
#include <Bibim/IUpdateable.h>

namespace Bibim
{
    class UITrail : public UIVisual
    {
        BBComponentClass(UITrail, UIVisual, 'U', 'T', 'R', 'L');
        public:
            UITrail();
            virtual ~UITrail();

            float GetGlobalAngle() const;
            void  SetGlobalAngle(float value);

            inline CCParticleSystem* GetSource() const;
            void SetSource(CCParticleSystem* value);

            inline Timeline* GetTimeline() const;
            void SetTimeline(Timeline* value);

            virtual Vector2 GetContentSize();

        protected:
                    void OnStep(float dt, int timestamp);
            virtual void OnDraw(UIDrawingContext& context);

        private:
            class Updater : public IUpdateable
            {
                public:
                    Updater();
                    virtual ~Updater();

                    virtual void Update(float dt, int timestamp);

                public:
                    UITrail* o;
            };

        private:
            float globalAngle;
            CCParticleSystemPtr source;
            CCParticleEmitter* emitter;
            Timeline* timeline;
            Updater updater;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    CCParticleSystem* UITrail::GetSource() const
    {
        return source;
    }

    Timeline* UITrail::GetTimeline() const
    {
        return timeline;
    }
}

#endif