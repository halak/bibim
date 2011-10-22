#pragma once
#ifndef __BIBIM_EVALUABLESEQUENCEBASE_H__
#define __BIBIM_EVALUABLESEQUENCEBASE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Evaluables.h>

    namespace Bibim
    {
        template <typename T>
        class EvaluableSequenceBase : public EvaluableTemplate<T>
        {
            BBAbstractComponentClass(EvaluableSequenceBase, EvaluableTemplate<T>);
            public:
                EvaluableSequenceBase();
                virtual ~EvaluableSequenceBase();

                void Update(float dt, uint timestamp);

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
                uint lastTimestamp;
        };
    }

#   include <Bibim/EvaluableSequenceBase.inl>

#endif