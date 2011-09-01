#pragma once
#ifndef __BIBIM_SEQUENTIALPARTICLEEMITTER_H__
#define __BIBIM_SEQUENTIALPARTICLEEMITTER_H__

#   include <Bibim/FWD.h>
#   include <Bibim/ParticleEmitter.h>
#   include <Bibim/Range.h>
#   include <Bibim/SequentialParticle.h>
#   include <list>
#   include <vector>

    namespace Bibim
    {
        class SequentialParticleEmitter : public ParticleEmitter
        {
            public:
                typedef std::list<SequentialParticle*> ParticleCollection;
                typedef std::vector<SpriteSequencePtr> SpriteSequenceCollection;

            public:
                SequentialParticleEmitter();
                virtual ~SequentialParticleEmitter();

                virtual void Update(float dt, uint timestamp);

                IFloatRangeEvaluablePtr GetLifespan() const;
                void SetLifespan(IFloatRangeEvaluablePtr value);

                Vector3RangeSequencePtr GetLinearVelocitySequence() const;
                void SetLinearVelocitySequence(Vector3RangeSequencePtr value);

                FloatRangeSequencePtr GetRotationSequence() const;
                void SetRotationSequence(FloatRangeSequencePtr value);

                Vector2RangeSequencePtr GetScaleSequence() const;
                void SetScaleSequence(Vector2RangeSequencePtr value);

                ColorRangeSequencePtr GetTintSequence() const;
                void SetTintSequence(ColorRangeSequencePtr value);

                const SpriteSequenceCollection& GetSpriteSequences() const;
                void SetSpriteSequences(const SpriteSequenceCollection& value);

                bool GetLocalCoordinates() const;
                void SetLocalCoordinates(bool value);

                bool GetRatioKeepScale() const;
                void SetRatioKeepScale(bool value);

                const ParticleCollection& GetParticles() const;

            protected:
                inline void UpdateParticle(SequentialParticle* particle, float dt);
                template <typename ValueType, typename SequenceType>
                inline void UpdateParticleSequence(ValueType& outValue, SequenceType* sequence, float age, ValueType* range, short& inOutLastKeyframeIndex);
                virtual void Spawn(float age, Vector3 position);

            private:
                IFloatRangeEvaluablePtr lifespan;
                IUpdateablePtr updateableLifespan;
                FloatRange lastEvaluatedLifespan;

                Vector3RangeSequencePtr velocitySequence;
                FloatRangeSequencePtr   rotationSequence;
                Vector2RangeSequencePtr scaleSequence;
                ColorRangeSequencePtr   tintSequence;
                SpriteSequenceCollection spriteSequences;
                bool localCoordinates;
                bool ratioKeepScale;

                ParticleCollection particles;

                uint lastTimestamp;
        };
    }

#endif