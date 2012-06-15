#include <Bibim/PCH.h>
#include <Bibim/SimpleParticleEmitter.h>
#include <Bibim/Delete.h>
#include <Bibim/Math.h>

namespace Bibim
{
    SimpleParticleEmitter::SimpleParticleEmitter()
        : localCoordinates(0),
          ratioKeepScale(0),
          lastTimestamp(0)
    {
        lifespans[0] = lifespans[1] = 0.0f;
        linearVelocities[0] = linearVelocities[1] = Vector3::Zero;
        linearAccelerationForces[0] = linearAccelerationForces[1] = 0.0f;
        rotations[0] = rotations[1] = 0.0f;
        angularVelocities[0] = angularVelocities[1] = 0.0f;
        angularAccelerationForces[0] = angularAccelerationForces[1] = 0.0f;
        scales[0] = scales[1] = Vector2::One;
        strainVelocities[0] = strainVelocities[1] = Vector2::Zero;
        strainAccelerationForces[0] = strainAccelerationForces[1] = 0.0f;
        startTints[0] = startTints[1] = Vector4::One;
        endTints[0] = endTints[1] = Vector4::One;
    }

    SimpleParticleEmitter::~SimpleParticleEmitter()
    {
        DeleteAll(particles);
    }

    void SimpleParticleEmitter::UpdateParticle(SimpleParticle* particle, float dt)
    {
        const float ageRate = particle->Age / particle->Lifespan;
        particle->LinearVelocity += particle->LinearAcceleration * dt;
        particle->Position += particle->LinearVelocity * dt;
        particle->AngularVelocity += particle->AngularAcceleration * dt;
        particle->Rotation += particle->AngularVelocity * dt;
        particle->StrainVelocity += particle->StrainAcceleration * dt;
        particle->Scale += particle->StrainVelocity * dt;
        if (particle->Scale.X < 0.0f || particle->Scale.Y < 0.0f)
        {
            particle->Scale.X = 0.0f;
            particle->Scale.Y = 0.0f;
        }
        if (particle->StartTint != particle->EndTint)
            particle->Tint = Color(particle->StartTint + (particle->EndTint - particle->StartTint) * ageRate);
    }

    void SimpleParticleEmitter::Update(float dt, uint timestamp)
    {
        if (lastTimestamp == timestamp)
            return;
        lastTimestamp = timestamp;

        for (ParticleCollection::iterator it = particles.begin(); it != particles.end();)
        {
            SimpleParticle* item = (*it);
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

    void SimpleParticleEmitter::Spawn(float age, Vector3 position)
    {
        const float lifespan = Math::Random(lifespans[0], lifespans[1]);
        if (age >= lifespan)
            return;

        Vector3 linearVelocityDirection = Math::Random(linearVelocities[0], linearVelocities[1]);
        float   linearSpeed = linearVelocityDirection != Vector3::Zero ? linearVelocityDirection.Normalize() : 0.0f;

        float angularVelocityDirection = Math::Random(angularVelocities[0], angularVelocities[1]);
        float angularSpeed = Math::Abs(angularVelocityDirection);
        if (angularSpeed != 0.0f)
            angularVelocityDirection /= angularSpeed;

        Vector2 scale = Vector2::Zero;
        Vector2 strainVelocityDirection = Vector2::Zero;
        if (ratioKeepScale)
        {
            scale.X = Math::Random(scales[0].X, scales[1].X);
            scale.Y = scale.X;
            strainVelocityDirection.X = Math::Random(strainVelocities[0].X, strainVelocities[1].X);
            strainVelocityDirection.Y = strainVelocityDirection.X;
        }
        else
        {
            scale = Math::Random(scales[0], scales[1]);
            strainVelocityDirection = Math::Random(strainVelocities[0], strainVelocities[1]);
        }
        float strainSpeed = strainVelocityDirection != Vector2::Zero ? strainVelocityDirection.Normalize() : 0.0f;

        SimpleParticle* particle = new SimpleParticle(lifespan,
                                                      position,
                                                      linearVelocityDirection * linearSpeed,
                                                      linearVelocityDirection * Math::Random(linearAccelerationForces[0], linearAccelerationForces[1]),
                                                      Math::Random(rotations[0], rotations[1]),
                                                      angularVelocityDirection * angularSpeed,
                                                      angularVelocityDirection * Math::Random(angularAccelerationForces[0], angularAccelerationForces[1]),
                                                      scale,
                                                      strainVelocityDirection * strainSpeed,
                                                      strainVelocityDirection * Math::Random(strainAccelerationForces[0], strainAccelerationForces[1]),
                                                      Math::Random(startTints[0], startTints[1]),
                                                      Math::Random(endTints[0], endTints[1]),
                                                      sprites[Math::Random(0, sprites.size() - 1)]);
        particles.push_back(particle);
        UpdateParticle(particle, age);
    }

    float SimpleParticleEmitter::GetLifespan1() const
    {
        return lifespans[0];
    }

    void SimpleParticleEmitter::SetLifespan1(float value)
    {
        lifespans[0] = value;
    }

    float SimpleParticleEmitter::GetLifespan2() const
    {
        return lifespans[1];
    }

    void SimpleParticleEmitter::SetLifespan2(float value)
    {
        lifespans[1] = value;
    }

    Vector3 SimpleParticleEmitter::GetLinearVelocity1() const
    {
        return linearVelocities[0];
    }

    void SimpleParticleEmitter::SetLinearVelocity1(Vector3 value)
    {
        linearVelocities[0] = value;
    }

    Vector3 SimpleParticleEmitter::GetLinearVelocity2() const
    {
        return linearVelocities[1];
    }

    void SimpleParticleEmitter::SetLinearVelocity2(Vector3 value)
    {
        linearVelocities[1] = value;
    }

    float SimpleParticleEmitter::GetLinearAccelerationForce1() const
    {
        return linearAccelerationForces[0];
    }

    void SimpleParticleEmitter::SetLinearAccelerationForce1(float value)
    {
        linearAccelerationForces[0] = value;
    }

    float SimpleParticleEmitter::GetLinearAccelerationForce2() const
    {
        return linearAccelerationForces[1];
    }

    void SimpleParticleEmitter::SetLinearAccelerationForce2(float value)
    {
        linearAccelerationForces[1] = value;
    }

    float SimpleParticleEmitter::GetRotation1() const
    {
        return rotations[0];
    }

    void SimpleParticleEmitter::SetRotation1(float value)
    {
        rotations[0] = value;
    }

    float SimpleParticleEmitter::GetRotation2() const
    {
        return rotations[1];
    }

    void SimpleParticleEmitter::SetRotation2(float value)
    {
        rotations[1] = value;
    }

    float SimpleParticleEmitter::GetAngularVelocity1() const
    {
        return angularVelocities[0];
    }

    void SimpleParticleEmitter::SetAngularVelocity1(float value)
    {
        angularVelocities[0] = value;
    }

    float SimpleParticleEmitter::GetAngularVelocity2() const
    {
        return angularVelocities[1];
    }

    void SimpleParticleEmitter::SetAngularVelocity2(float value)
    {
        angularVelocities[1] = value;
    }

    float SimpleParticleEmitter::GetAngularAccelerationForce1() const
    {
        return angularAccelerationForces[0];
    }

    void SimpleParticleEmitter::SetAngularAccelerationForce1(float value)
    {
        angularAccelerationForces[0] = value;
    }

    float SimpleParticleEmitter::GetAngularAccelerationForce2() const
    {
        return angularAccelerationForces[1];
    }

    void SimpleParticleEmitter::SetAngularAccelerationForce2(float value)
    {
        angularAccelerationForces[1] = value;
    }

    Vector2 SimpleParticleEmitter::GetScale1() const
    {
        return scales[0];
    }

    void SimpleParticleEmitter::SetScale1(Vector2 value)
    {
        scales[0] = value;
    }

    Vector2 SimpleParticleEmitter::GetScale2() const
    {
        return scales[1];
    }

    void SimpleParticleEmitter::SetScale2(Vector2 value)
    {
        scales[1] = value;
    }

    Vector2 SimpleParticleEmitter::GetStrainVelocity1() const
    {
        return strainVelocities[0];
    }

    void SimpleParticleEmitter::SetStrainVelocity1(Vector2 value)
    {
        strainVelocities[0] = value;
    }

    Vector2 SimpleParticleEmitter::GetStrainVelocity2() const
    {
        return strainVelocities[1];
    }

    void SimpleParticleEmitter::SetStrainVelocity2(Vector2 value)
    {
        strainVelocities[1] = value;
    }

    float SimpleParticleEmitter::GetStrainAccelerationForce1() const
    {
        return strainAccelerationForces[0];
    }

    void SimpleParticleEmitter::SetStrainAccelerationForce1(float value)
    {
        strainAccelerationForces[0] = value;
    }

    float SimpleParticleEmitter::GetStrainAccelerationForce2() const
    {
        return strainAccelerationForces[1];
    }

    void SimpleParticleEmitter::SetStrainAccelerationForce2(float value)
    {
        strainAccelerationForces[1] = value;
    }

    Color SimpleParticleEmitter::GetStartTint1() const
    {
        return Color(startTints[0]);
    }

    void SimpleParticleEmitter::SetStartTint1(Color value)
    {
        startTints[0] = value.ToVector4();
    }

    Color SimpleParticleEmitter::GetStartTint2() const
    {
        return Color(startTints[1]);
    }

    void SimpleParticleEmitter::SetStartTint2(Color value)
    {
        startTints[1] = value.ToVector4();
    }

    Color SimpleParticleEmitter::GetEndTint1() const
    {
        return Color(endTints[0]);
    }

    void SimpleParticleEmitter::SetEndTint1(Color value)
    {
        endTints[0] = value.ToVector4();
    }

    Color SimpleParticleEmitter::GetEndTint2() const
    {
        return Color(endTints[1]);
    }

    void SimpleParticleEmitter::SetEndTint2(Color value)
    {
        endTints[1] = value.ToVector4();
    }

    bool SimpleParticleEmitter::GetLocalCoordinates() const
    {
        return localCoordinates;
    }

    void SimpleParticleEmitter::SetLocalCoordinates(bool value)
    {
        localCoordinates = value;
    }

    bool SimpleParticleEmitter::GetRatioKeepScale() const
    {
        return ratioKeepScale;
    }

    void SimpleParticleEmitter::SetRatioKeepScale(bool value)
    {
        ratioKeepScale = value;
    }

    const SimpleParticleEmitter::SpriteCollection& SimpleParticleEmitter::GetSpritePalette() const
    {
        return sprites;
    }

    void SimpleParticleEmitter::SetSpritePalette(const SpriteCollection& value)
    {
        sprites = value;
    }

    const SimpleParticleEmitter::ParticleCollection& SimpleParticleEmitter::GetParticles() const
    {
        return particles;
    }
}