#pragma once
#ifndef __BIBIM_EVALUABLEPOINTSEQUENCE_H__
#define __BIBIM_EVALUABLEPOINTSEQUENCE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/IPointEvaluable.h>
#   include <Bibim/IUpdateable.h>
#   include <Bibim/Point.h>

    namespace Bibim
    {
        class EvaluablePointSequence : public IPointEvaluable, public IUpdateable
        {
            typedef PointSequencePtr SharedSequencePointerType;
            public:
                EvaluablePointSequence();
                virtual ~EvaluablePointSequence();

                virtual void Update(float dt, uint timestamp);

                virtual Point Evaluate();

                float GetTime() const;

                float GetVelocity() const;
                void  SetVelocity(float value);

                bool GetLooped() const;
                void SetLooped(bool value);

                SharedSequencePointerType GetSource() const;
                void SetSource(SharedSequencePointerType value);

            private:
                EvaluableSequenceTemplate<SharedSequencePointerType>* s;
        };
    }

#endif