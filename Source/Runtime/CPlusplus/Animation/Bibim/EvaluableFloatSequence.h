#pragma once
#ifndef __BIBIM_EVALUABLEFLOATSEQUENCE_H__
#define __BIBIM_EVALUABLEFLOATSEQUENCE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/SharedObject.h>
#   include <Bibim/IFloatEvaluable.h>
#   include <Bibim/IUpdateable.h>

    namespace Bibim
    {
        class EvaluableFloatSequence : public SharedObject, public IFloatEvaluable, public IUpdateable
        {
            typedef FloatSequencePtr SharedSequencePointerType;
            public:
                EvaluableFloatSequence();
                virtual ~EvaluableFloatSequence();

                virtual void Update(float dt, uint timestamp);

                virtual float Evaluate();

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