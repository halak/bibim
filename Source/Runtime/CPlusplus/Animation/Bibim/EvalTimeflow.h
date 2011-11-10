#pragma once
#ifndef __BIBIM_EVALTIMEFLOW_H__
#define __BIBIM_EVALTIMEFLOW_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Evals.h>

    namespace Bibim
    {
        class EvalTimeflow : public EvalFloat
        {
            BBComponentClass(EvalTimeflow, EvalFloat, 'e', 'T', 'F', 'f');
            public:
                EvalTimeflow();
                virtual ~EvalTimeflow();

                void Update(float dt, int timestamp);

                virtual void Reset();
                virtual float Evaluate(EvalContext& context);

                inline float GetTime() const;
                inline float GetDuration() const;
                void SetDuration(float value);
                inline float GetVelocity() const;
                inline void SetVelocity(float value);
                inline bool GetLooped() const;
                inline void SetLooped(bool value);

            private:
                float time;
                float duration;
                float velocity;
                bool looped;
                int lastTimestamp;
        };

        BBDeclareEvalClass(EvalTimeflow);
    }

#   include <Bibim/EvalTimeflow.inl>

#endif