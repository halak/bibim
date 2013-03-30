#pragma once
#ifndef __BIBIM_EVALTIMEFLOW_H__
#define __BIBIM_EVALTIMEFLOW_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Evals.h>
#   include <Bibim/IUpdateable.h>

    namespace Bibim
    {
        class EvalTimeflow : public EvalFloat, public IUpdateable
        {
            BBComponentClass(EvalTimeflow, EvalFloat, 'e', 'T', 'F', 'f');
            public:
                enum Behavior
                {
                    PauseAtStop,
                    ResetAtStop,
                    FinishAtStop,
                };

            public:
                EvalTimeflow();
                virtual ~EvalTimeflow();

                virtual void Update(float dt, int timestamp);

                virtual void Start();
                virtual void Stop();
                virtual void Reset();
                virtual float Evaluate(EvalContext& context);

                inline Timeline* GetTimeline() const;
                void SetTimeline(Timeline* value);
                inline float GetTime() const;
                inline float GetDuration() const;
                void SetDuration(float value);
                inline float GetVelocity() const;
                inline void SetVelocity(float value);
                inline Behavior GetStopBehavior() const;
                inline void SetStopBehavior(Behavior value);
                inline bool GetLooped() const;
                inline void SetLooped(bool value);
                inline bool GetNormalized() const;
                inline void SetNormalized(bool value);

            private:
                float evaluatedTime;
                Timeline* timeline;
                float time;
                float duration;
                float velocity;
                Behavior stopBehavior;
                bool looped;
                bool normalized;
                bool isUpdating;
                int lastTimestamp;
        };

        BBDeclareEvalClass(EvalTimeflow);
    }

#   include <Bibim/EvalTimeflow.inl>

#endif