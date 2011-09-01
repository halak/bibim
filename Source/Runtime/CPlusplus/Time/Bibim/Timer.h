#pragma once
#ifndef __BIBIM_TIMER_H__
#define __BIBIM_TIMER_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UpdateableObject.h>

    namespace Bibim
    {
        class Timer : public UpdateableObject
        {
            public:
                Timer();
                Timer(float duration);
                virtual ~Timer();

                virtual void Update(float dt, uint timestamp);

                inline float GetTime() const;
                inline float GetDuration() const;
                void  SetDuration(float value);

            protected:
                virtual void OnTick() = 0;

            private:
                float time;
                float duration;
        };
    }

#   include <Bibim/Timer.h>

#endif