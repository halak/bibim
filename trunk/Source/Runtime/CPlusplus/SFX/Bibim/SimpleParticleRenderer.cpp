#include <Bibim/PCH.h>
#include <Bibim/SimpleParticleRenderer.h>
#include <Bibim/Assert.h>
#include <Bibim/DrawingContext.h>
#include <Bibim/SimpleParticleEmitter.h>
#include <Bibim/SpriteRenderer.h>
#include <stdexcept>

namespace Bibim
{
    SimpleParticleRenderer::SimpleParticleRenderer()
    {
    }

    SimpleParticleRenderer::~SimpleParticleRenderer()
    {
    }

    void SimpleParticleRenderer::Draw(DrawingContext& context)
    {
        BBAssertDebug(context.GetSpriteRenderer());
        if (GetTargetPointee() == nullptr)
            return;

        SpriteRenderer* renderer = context.GetSpriteRenderer();
        const SimpleParticleEmitter* castedTarget = static_cast<const SimpleParticleEmitter*>(GetTargetPointee().GetPointee());
        const SimpleParticleEmitter::ParticleCollection& particles = castedTarget->GetParticles();
        for (SimpleParticleEmitter::ParticleCollection::const_reverse_iterator it = particles.rbegin(); it != particles.rend(); it++)
        {
            const SimpleParticle* item = (*it);
            renderer->Draw(item->Position, Vector3(0.0f, 0.0f, item->Rotation), item->Scale, item->SpriteInstance, item->Tint);
        }
    }

    void SimpleParticleRenderer::DrawDebugInformation(DrawingContext& /*context*/)
    {
        //BBAssertDebug(context.GetSpriteRenderer());
        //if (GetTargetPointee() == nullptr)
        //    return;

        //SpriteRenderer* renderer = context.GetSpriteRenderer();
        //const SimpleParticleEmitter* castedTarget = static_cast<const SimpleParticleEmitter*>(GetTargetPointee().GetPointee());
        //const SimpleParticleEmitter::ParticleCollection& particles = castedTarget->GetParticles();
        //for (SimpleParticleEmitter::ParticleCollection::const_reverse_iterator it = particles.rbegin(); it != particles.rend(); it++)
        //{
        //    const SimpleParticle* item = (*it);
        //    renderer->Draw(item->Position, Vector3(0.0f, 0.0f, item->Rotation), item->Scale, item->SpriteInstance, item->Tint);
        //}
    }

    void SimpleParticleRenderer::OnTargetChanged(ParticleEmitterPtr old)
    {
        if (dynamic_cast<SimpleParticleEmitter*>(GetTargetPointee().GetPointee()) == nullptr)
            throw std::bad_typeid("SimpleParticleRenderer::OnTargetChanged(ParticleEmitterPtr)");
    }
}