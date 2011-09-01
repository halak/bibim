#include <Bibim/PCH.h>
#include <Bibim/SequentialParticleEmitter.h>
#include <Bibim/ColorRangeSequence.h>
#include <Bibim/Delete.h>
#include <Bibim/FloatRangeSequence.h>
#include <Bibim/IFloatRangeEvaluable.h>
#include <Bibim/Math.h>
#include <Bibim/SpriteSequence.h>
#include <Bibim/Vector2RangeSequence.h>
#include <Bibim/Vector3RangeSequence.h>

namespace Bibim
{
    SequentialParticleEmitter::SequentialParticleEmitter()
        : ParticleEmitter(),
          localCoordinates(false),
          ratioKeepScale(false),
          lastEvaluatedLifespan(0.0f, 0.0f),
          lastTimestamp(0)
    {
    }

    SequentialParticleEmitter::~SequentialParticleEmitter()
    {
        DeleteAll(particles);
    }

    template <typename ValueType, typename SequenceType>
    void SequentialParticleEmitter::UpdateParticleSequence(ValueType& outValue, SequenceType* sequence, float age, ValueType* range, short& inOutLastKeyframeIndex)
    {
        const short keyframeIndex = static_cast<short>(sequence->GetKeyframeIndex(age, static_cast<int>(inOutLastKeyframeIndex)));

        if (keyframeIndex < sequence->GetNumberOfKeyframes() - 1)
        {
            const SequenceType::KeyframeType& kf1 = sequence->GetKeyframe(keyframeIndex);
            if (keyframeIndex != inOutLastKeyframeIndex)
            {
                const SequenceType::KeyframeType& kf2 = sequence->GetKeyframe(keyframeIndex + 1);
                if (inOutLastKeyframeIndex + 1 == keyframeIndex)
                {
                    range[0] = range[1];
                    range[1] = Math::Random(kf2.Value.Min, kf2.Value.Max);
                }
                else
                {
                    range[0] = Math::Random(kf1.Value.Min, kf1.Value.Max);
                    range[1] = Math::Random(kf2.Value.Min, kf2.Value.Max);
                }
            }

            outValue = Math::Interpolate(range[0], range[1], (age - kf1.StartTime) / kf1.Duration);
        }
        else
            outValue = range[1];

        inOutLastKeyframeIndex = keyframeIndex;
    }

    void SequentialParticleEmitter::UpdateParticle(SequentialParticle* particle, float dt)
    {
        SpriteSequence* spriteSequence = spriteSequences[particle->SpriteSequenceIndex].GetPointee();

        UpdateParticleSequence(particle->LinearVelocity, velocitySequence.GetPointee(),
                               particle->Age, particle->LastLinearVelocityRange, particle->LastLinearVelocityKeyrameIndex);
        UpdateParticleSequence(particle->Rotation, rotationSequence.GetPointee(),
                               particle->Age, particle->LastRotationRange, particle->LastRotationKeyframeIndex);
        UpdateParticleSequence(particle->Scale, scaleSequence.GetPointee(),
                               particle->Age, particle->LastScaleRange, particle->LastScaleKeyframeIndex);
        UpdateParticleSequence(particle->Tint, tintSequence.GetPointee(),
                               particle->Age, particle->LastTintRange, particle->LastTintKeyframeIndex);

        const int spriteKeyframeIndex = spriteSequence->GetKeyframeIndex(particle->Age, particle->LastSpriteKeyframeIndex);
        if (spriteKeyframeIndex < spriteSequence->GetNumberOfKeyframes() - 1)
            particle->SpriteInstance = spriteSequence->GetKeyframe(spriteKeyframeIndex).Value;
        else
            particle->SpriteInstance = spriteSequence->GetKeyframe(spriteSequence->GetNumberOfKeyframes() - 1).Value;

        particle->Position += particle->LinearVelocity * dt;
        particle->LastSpriteKeyframeIndex = static_cast<short>(spriteKeyframeIndex);
    }

    void SequentialParticleEmitter::Update(float dt, uint timestamp)
    {
        if (lastTimestamp == timestamp)
            return;
        lastTimestamp = timestamp;

        if (lifespan == nullptr ||
            velocitySequence == nullptr || velocitySequence->GetNumberOfKeyframes() == 0 ||
            rotationSequence == nullptr || rotationSequence->GetNumberOfKeyframes() == 0 ||
            scaleSequence == nullptr || scaleSequence->GetNumberOfKeyframes() == 0 ||
            tintSequence  == nullptr || tintSequence->GetNumberOfKeyframes() == 0 ||
            spriteSequences.empty())
            return;

        if (updateableLifespan)
            updateableLifespan->Update(dt, timestamp);

        lastEvaluatedLifespan = lifespan->Evaluate();

        for (ParticleCollection::iterator it = particles.begin(); it != particles.end();)
        {
            SequentialParticle* item = (*it);
            item->Age += dt;
            if (item->Age < item->Lifespan)
            {
                UpdateParticle(item, dt);
                it++;
            }
            else
            {
                particles.erase(it++);
                delete item;
            }
        }

        ParticleEmitter::Update(dt, timestamp);
    }

    void SequentialParticleEmitter::Spawn(float age, Vector3 position)
    {
        const float selecteLlifespan = Math::Random(lastEvaluatedLifespan.Min, lastEvaluatedLifespan.Max);
        if (age >= selecteLlifespan)
            return;

        const int spriteSequenceIndex = Math::Random(0, static_cast<int>(spriteSequences.size() - 1));
        SequentialParticle* particle = new SequentialParticle(selecteLlifespan, position, spriteSequenceIndex);
        particles.push_back(particle);
        const Vector3RangeKeyframe& kf1 = velocitySequence->GetKeyframe(0);
        const FloatRangeKeyframe&   kf2 = rotationSequence->GetKeyframe(0);
        const Vector2RangeKeyframe& kf3 = scaleSequence->GetKeyframe(0);
        const ColorRangeKeyframe&   kf4 = tintSequence->GetKeyframe(0);
        particle->LastLinearVelocityRange[0] = Math::Random(kf1.Value.Min, kf1.Value.Max);
        particle->LastLinearVelocityRange[1] = particle->LastLinearVelocityRange[0];
        particle->LastRotationRange[0] = Math::Random(kf2.Value.Min, kf2.Value.Max);
        particle->LastRotationRange[1] = particle->LastRotationRange[0];
        particle->LastScaleRange[0] = Math::Random(kf3.Value.Min, kf3.Value.Max);
        particle->LastScaleRange[1] = particle->LastScaleRange[0];
        particle->LastTintRange[0] = Math::Random(kf4.Value.Min, kf4.Value.Max);
        particle->LastTintRange[1] = particle->LastTintRange[0];
        UpdateParticle(particle, age);
    }

    IFloatRangeEvaluablePtr SequentialParticleEmitter::GetLifespan() const
    {
        return lifespan;
    }

    void SequentialParticleEmitter::SetLifespan(IFloatRangeEvaluablePtr value)
    {
        if (lifespan != value)
        {
            lifespan = value;
            updateableLifespan = DynamicCast<IUpdateable>(lifespan);
        }
    }

    Vector3RangeSequencePtr SequentialParticleEmitter::GetLinearVelocitySequence() const
    {
        return velocitySequence;
    }

    void SequentialParticleEmitter::SetLinearVelocitySequence(Vector3RangeSequencePtr value)
    {
        velocitySequence = value;
    }

    FloatRangeSequencePtr SequentialParticleEmitter::GetRotationSequence() const
    {
        return rotationSequence;
    }

    void SequentialParticleEmitter::SetRotationSequence(FloatRangeSequencePtr value)
    {
        rotationSequence = value;
    }

    Vector2RangeSequencePtr SequentialParticleEmitter::GetScaleSequence() const
    {
        return scaleSequence;
    }

    void SequentialParticleEmitter::SetScaleSequence(Vector2RangeSequencePtr value)
    {
        scaleSequence = value;
    }

    ColorRangeSequencePtr SequentialParticleEmitter::GetTintSequence() const
    {
        return tintSequence;
    }

    void SequentialParticleEmitter::SetTintSequence(ColorRangeSequencePtr value)
    {
        tintSequence = value;
    }

    const SequentialParticleEmitter::SpriteSequenceCollection& SequentialParticleEmitter::GetSpriteSequences() const
    {
        return spriteSequences;
    }

    void SequentialParticleEmitter::SetSpriteSequences(const SpriteSequenceCollection& value)
    {
        spriteSequences = value;
    }

    bool SequentialParticleEmitter::GetLocalCoordinates() const
    {
        return localCoordinates;
    }

    void SequentialParticleEmitter::SetLocalCoordinates(bool value)
    {
        localCoordinates = value;
    }

    bool SequentialParticleEmitter::GetRatioKeepScale() const
    {
        return ratioKeepScale;
    }

    void SequentialParticleEmitter::SetRatioKeepScale(bool value)
    {
        ratioKeepScale = value;
    }

    const SequentialParticleEmitter::ParticleCollection& SequentialParticleEmitter::GetParticles() const
    {
        return particles;
    }
}