#pragma once
#ifndef __BIBIM_EVALUABLESEQUENCEBASE_H__
#define __BIBIM_EVALUABLESEQUENCEBASE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Evals.h>

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

                T Evaluate(EvaluationContext& context);

                float GetTime() const;

                float GetVelocity() const;
                void  SetVelocity(float value);

                bool GetLooped() const;
                void SetLooped(bool value);

            protected:
                void SetValue(T value);
                virtual void UpdateValue();

            protected:
                float time;
                float velocity;
                bool looped;
                bool timeChanged;
                T value;
                int lastTimestamp;
        };
    }

#   include <Bibim/EvalSequenceBase.inl>

#endif