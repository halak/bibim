#pragma once
#ifndef __BIBIM_EvaluableSpriteSequence_H__
#define __BIBIM_EvaluableSpriteSequence_H__

#   include <Bibim/FWD.h>
#   include <Bibim/SharedObject.h>
#   include <Bibim/ISpriteEvaluable.h>
#   include <Bibim/IUpdateable.h>

    namespace Bibim
    {
        class EvaluableSpriteSequence : public SharedObject, public ISpriteEvaluable, public IUpdateable
        {
            typedef SpriteSequencePtr SharedSequencePointerType;
            public:
                EvaluableSpriteSequence();
                virtual ~EvaluableSpriteSequence();

                virtual void Update(float dt, uint timestamp);

                virtual Sprite Evaluate();

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