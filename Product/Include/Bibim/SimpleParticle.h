#pragma once
#ifndef __BIBIM_SIMPLEPARTICLE_H__
#define __BIBIM_SIMPLEPARTICLE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Particle.h>
#   include <Bibim/Sprite.h>

    namespace Bibim
    {
        class SimpleParticle : public Particle
        {
            public:
                const Vector3 LinearAcceleration;

                float Rotation;
                float AngularVelocity;
                const float AngularAcceleration;

                Vector2 Scale;
                Vector2 StrainVelocity;
                const Vector2 StrainAcceleration;

                const Vector4 StartTint;
                const Vector4 EndTint;

                const Sprite SpriteInstance;

            public:
                inline SimpleParticle(float lifespan,
                                      Vector3 position, Vector3 linearVelocity, Vector3 linearAcceleration,
                                      float rotation, float angularVelocity, float angularAcceleration,
                                      Vector2 scale, Vector2 strainVelocity, Vector2 strainAcceleration,
                                      Vector4 startTint, Vector4 endTint,
                                      const Sprite& spriteInstance);
                inline ~SimpleParticle();
        };
    }

#   include <Bibim/SimpleParticle.inl>

#endif