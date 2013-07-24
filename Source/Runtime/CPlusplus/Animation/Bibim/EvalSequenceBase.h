#pragma once
#ifndef __BIBIM_EVALUABLESEQUENCEBASE_H__
#define __BIBIM_EVALUABLESEQUENCEBASE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Evals.h>
#   include <Bibim/ComponentStreamReader.h>

    namespace Bibim
    {
        template <typename T>
        class EvalSequenceBase : public EvalTemplate<T>
        {
            BBAbstractComponentClass(EvalSequenceBase, EvalTemplate<T>);
            public:
                EvalSequenceBase();
                virtual ~EvalSequenceBase();

                void Update(float dt, int timestamp);

                virtual void Start()
                {
                    time = 0.0f;
                    timeChanged = true;
                    lastTimestamp = 0;
                }

                virtual void Stop() { }
                virtual void Reset()
                {
                    time = 0.0f;
                    timeChanged = true;
                    lastTimestamp = 0;
                }

                virtual T Evaluate(EvalContext& context);

                float GetTime() const;

                float GetVelocity() const;
                void  SetVelocity(float value);

                bool GetLooped() const;
                void SetLooped(bool value);

            protected:
                void SetValue(T value);
                virtual void UpdateValue() = 0;

            protected:
                float time;
                float velocity;
                bool looped;
                bool timeChanged;
                T value;
                int lastTimestamp;
        };
    }

#endif