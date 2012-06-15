#pragma once
#ifndef __BIBIM_SIMPLEPARTICLERENDERER_H__
#define __BIBIM_SIMPLEPARTICLERENDERER_H__

#   include <Bibim/FWD.h>
#   include <Bibim/ParticleRenderer.h>

    namespace Bibim
    {
        class SimpleParticleRenderer : public ParticleRenderer
        {
            public:
                SimpleParticleRenderer();
                virtual ~SimpleParticleRenderer();

                virtual void Draw(DrawingContext& context);
                virtual void DrawDebugInformation(DrawingContext& context);

            protected:
                virtual void OnTargetChanged(ParticleEmitterPtr old);                
        };
    }

#endif