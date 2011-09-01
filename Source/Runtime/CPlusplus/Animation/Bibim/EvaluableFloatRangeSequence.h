#pragma once
#ifndef __BIBIM_EVALUABLEFLOATRANGESEQUENCE_H__
#define __BIBIM_EVALUABLEFLOATRANGESEQUENCE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/SharedObject.h>
#   include <Bibim/IFloatRangeEvaluable.h>
#   include <Bibim/IUpdateable.h>

    namespace Bibim
    {
        class EvaluableFloatRangeSequence : public SharedObject, public IFloatRangeEvaluable, public IUpdateable
        {
            typedef FloatRangeSequencePtr SharedSequencePointerType;
            public:
                EvaluableFloatRangeSequence();
                virtual ~EvaluableFloatRangeSequence();

                virtual void Update(float dt, uint timestamp);

                virtual FloatRange Evaluate();

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