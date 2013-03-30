#pragma once
#ifndef __BIBIM_PARTICLERENDERER_H__
#define __BIBIM_PARTICLERENDERER_H__

#   include <Bibim/FWD.h>
#   include <Bibim/IDrawable.h>

    namespace Bibim
    {
        class ParticleRenderer : public SharedObject, public IDrawable
        {
            public:
                ParticleRenderer();
                virtual ~ParticleRenderer();

                ParticleEmitterPtr GetTargetPointee() const;
                void SetTarget(ParticleEmitterPtr value);

            protected:
                virtual void OnTargetChanged(ParticleEmitterPtr old);

            private:
                ParticleEmitterPtr target;
        };
    }

#   include <Bibim/ParticleRenderer.inl>

#endif