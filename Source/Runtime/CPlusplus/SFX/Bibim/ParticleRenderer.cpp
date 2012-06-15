#include <Bibim/PCH.h>
#include <Bibim/ParticleRenderer.h>
#include <Bibim/ParticleEmitter.h>

namespace Bibim
{
    ParticleRenderer::ParticleRenderer()
    {
    }

    ParticleRenderer::~ParticleRenderer()
    {
    }

    ParticleEmitterPtr ParticleRenderer::GetTargetPointee() const
    {
        return target;
    }

    void ParticleRenderer::SetTarget(ParticleEmitterPtr value)
    {
        if (target != value)
        {
            ParticleEmitterPtr old = target;

            target = value;

            OnTargetChanged(old);
        }
    }

    void ParticleRenderer::OnTargetChanged(ParticleEmitterPtr /*old*/)
    {
    }
}