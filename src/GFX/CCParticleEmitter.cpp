#include <Bibim/Config.h>
#include <Bibim/CCParticleEmitter.h>
#include <Bibim/CCParticleSystem.h>
#include <Bibim/Math.h>

namespace Bibim
{
    CCParticleEmitter::CCParticleEmitter(CCParticleSystem* system)
        : system(system),
          elapsedTime(0.0f),
          emitCounter(0.0f),
          particleIndex(0),
          particleCount(0),
          isActive(true)
    {
        particles.resize(system->GetMaxParticles());
    }

    CCParticleEmitter::~CCParticleEmitter()
    {
    }

    void CCParticleEmitter::Reset()
    {
        isActive = true;
        elapsedTime = 0.0f;
    }

    void CCParticleEmitter::Stop()
    {
        isActive = false;
        elapsedTime = system->GetDuration();
        emitCounter = 0.0f;
    }

    bool CCParticleEmitter::Update(float dt, int /*timestamp*/)
    {
        if (isActive && system->GetEmissionRate() > 0.0f)
        {
            const int totalParticles = system->GetMaxParticles();
            if (particleCount < totalParticles)
                emitCounter += dt;

            const float rate = 1.0f / system->GetEmissionRate();
            while (emitCounter > rate && particleCount < totalParticles)
            {
                Emit();
                emitCounter -= rate;
            }

            elapsedTime += dt;

            if (system->GetDuration() != -1.0f && system->GetDuration() < elapsedTime)
                Stop();
        }

        /*
        CCPoint currentPosition = CCPointZero;
        if (m_ePositionType == kCCPositionTypeFree)
        {
            currentPosition = this->convertToWorldSpace(CCPointZero);
        }
        else if (m_ePositionType == kCCPositionTypeRelative)
        {
            currentPosition = m_obPosition;
        }
        */

        const bool thisIsGravityMode = system->GetMode() == CCParticleSystem::GravityMode;
        const Vector2 gravity = system->GetGravity();
        Vector2 radial = Vector2::Zero;
        Vector2 tangential = Vector2::Zero;

        for (int i = 0; i < particleCount; i++)
        {
            CCParticle* p = &particles[i];

            p->timeToLive -= dt;

            if (p->timeToLive > 0.0f)
            {
                if (thisIsGravityMode) 
                {
                    if (p->pos.X != 0.0f || p->pos.Y != 0.0f)
                    {
                        radial = p->pos;
                        radial.Normalize();
                        tangential.X = +radial.Y;
                        tangential.Y = -radial.X;
                        radial *= p->modeA.radialAccel;
                        tangential *= p->modeA.tangentialAccel;
                        p->modeA.dir += (radial + tangential + gravity) * dt;
                    }
                    else
                        p->modeA.dir += gravity * dt;

                    p->pos += p->modeA.dir * dt;
                }
                else
                {
                    p->modeB.angle -= p->modeB.degreesPerSecond * dt;
                    p->modeB.radius += p->modeB.deltaRadius * dt;

                    p->pos.X = Math::Cos(p->modeB.angle) * p->modeB.radius;
                    p->pos.Y = Math::Sin(p->modeB.angle) * p->modeB.radius;
                }

                p->color += p->deltaColor * dt;
                p->size = Math::Max(p->size + p->deltaSize * dt, 0.0f);
                p->rotation += (p->deltaRotation * dt);

                //
                // update values in quad
                //

                /*
                CCPoint    newPos;

                if (m_ePositionType == kCCPositionTypeFree || m_ePositionType == kCCPositionTypeRelative) 
                {
                    CCPoint diff = ccpSub( currentPosition, p->startPos );
                    newPos = ccpSub(p->pos, diff);
                } 
                else
                {
                    newPos = p->pos;
                }

                // translate newPos to correct position, since matrix transform isn't performed in batchnode
                // don't update the particle with the new position information, it will interfere with the radius and tangential calculations
                if (m_pBatchNode)
                {
                    newPos.x+=m_obPosition.x;
                    newPos.y+=m_obPosition.y;
                }

                updateQuadWithParticle(p, newPos);
                //updateParticleImp(self, updateParticleSel, p, newPos);

                // update particle counter
                ++m_uParticleIdx;
                */
            } 
            else 
            {
                if (i != particleCount - 1)
                    particles[i] = particles[particleCount - 1];

                particleCount--;

                if (particleCount == 0)
                    return false;
            }
        }

        return true;
    }

    float CCParticleEmitter::Generate(float base, float variance)
    {
        return base + variance * Math::Random(-1.0f, +1.0f);
    }

    float CCParticleEmitter::GenerateGTE0(float base, float variance)
    {
        return Math::Max(Generate(base, variance), 0.0f);
    }

    Vector2 CCParticleEmitter::Generate(Vector2 base, Vector2 variance)
    {
        return Vector2(Generate(base.X, variance.X),
                       Generate(base.Y, variance.Y));
    }

    Vector4 CCParticleEmitter::Generate(Vector4 base, Vector4 variance)
    {
        return Vector4(Generate(base.X, variance.X),
                       Generate(base.Y, variance.Y),
                       Generate(base.Z, variance.Z),
                       Generate(base.W, variance.W));
    }

    bool CCParticleEmitter::Emit()
    {
        if (particleCount == static_cast<int>(particles.size()))
            return false;

        CCParticle* p = &particles[particleCount];
        p->timeToLive = GenerateGTE0(system->GetParticleLifespan(), system->GetParticleLifespanVariance());
        p->pos = Generate(system->GetSourcePosition(), system->GetSourcePositionVariance());

        const Vector4 start = Vector4(Math::Clamp(system->GetStartColor().X + system->GetStartColorVariance().X * Math::Random(-1.0f, +1.0f)),
                                      Math::Clamp(system->GetStartColor().Y + system->GetStartColorVariance().Y * Math::Random(-1.0f, +1.0f)),
                                      Math::Clamp(system->GetStartColor().Z + system->GetStartColorVariance().Z * Math::Random(-1.0f, +1.0f)),
                                      Math::Clamp(system->GetStartColor().W + system->GetStartColorVariance().W * Math::Random(-1.0f, +1.0f)));
        const Vector4 end = Vector4(Math::Clamp(system->GetFinishColor().X + system->GetFinishColorVariance().X * Math::Random(-1.0f, +1.0f)),
                                    Math::Clamp(system->GetFinishColor().Y + system->GetFinishColorVariance().Y * Math::Random(-1.0f, +1.0f)),
                                    Math::Clamp(system->GetFinishColor().Z + system->GetFinishColorVariance().Z * Math::Random(-1.0f, +1.0f)),
                                    Math::Clamp(system->GetFinishColor().W + system->GetFinishColorVariance().W * Math::Random(-1.0f, +1.0f)));
        p->color = start;
        p->deltaColor = (end - start) / p->timeToLive;

        p->size = GenerateGTE0(system->GetStartParticleSize(), system->GetStartParticleSizeVariance());

        if (system->GetFinishParticleSize() == -1.0f)
            p->deltaSize = 0.0f;
        else
            p->deltaSize = (GenerateGTE0(system->GetFinishParticleSize(), system->GetFinishParticleSizeVariance()) - p->size) / p->timeToLive;

        p->rotation = Math::ToRadian(Generate(system->GetStartParticleRotation(), system->GetStartParticleRotationVariance()));
        p->deltaRotation = (Math::ToRadian(Generate(system->GetFinishParticleRotation(), system->GetFinishParticleRotationVariance()) - p->rotation)) / p->timeToLive;

        // position
        /*
        if( m_ePositionType == kCCPositionTypeFree )
        {
            particle->startPos = this->convertToWorldSpace(CCPointZero);
        }
        else if ( m_ePositionType == kCCPositionTypeRelative )
        {
            particle->startPos = m_obPosition;
        }
        */

        const float angle = -Math::ToRadian(Generate(system->GetAngle(), system->GetAngleVariance()));
        if (system->GetMode() == CCParticleSystem::GravityMode) 
        {
            const float speed = Generate(system->GetSpeed(), system->GetSpeedVariance());
            p->modeA.dir = Vector2(Math::Cos(angle), Math::Sin(angle)) * speed;
            p->modeA.radialAccel = Generate(system->GetRadialAcceleration(), system->GetRadialAccelVariance());
            p->modeA.tangentialAccel = Generate(system->GetTangentialAcceleration(), system->GetTangentialAccelVariance());

            if (system->GetRotationIsDirection())
                p->rotation = angle;
        }
        else // if (system->GetMode() == CCParticleSystem::RadiusMode)
        {
            p->modeB.radius = Generate(system->GetMaxRadius(), system->GetMaxRadiusVariance());
            if (system->GetMinRadius() == -1.0f)
                p->modeB.deltaRadius = 0.0f;
            else
                p->modeB.deltaRadius = (Generate(system->GetMinRadius(), system->GetMinRadiusVariance()) - p->modeB.radius) / p->timeToLive;

            p->modeB.angle = angle;
            p->modeB.degreesPerSecond = Math::ToRadian(Generate(system->GetSpin(), system->GetSpinVariance()));
        }    

        particleCount++;

        return true;
    }
}