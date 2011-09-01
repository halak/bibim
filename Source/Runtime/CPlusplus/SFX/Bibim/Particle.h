#pragma once
#ifndef __BIBIM_PARTICLE_H__
#define __BIBIM_PARTICLE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Color.h>
#   include <Bibim/Vector3.h>

    namespace Bibim
    {
        class Particle
        {
            public:
                float Age;
                float Lifespan;

                Vector3 Position;
                Vector3 LinearVelocity;
                Color Tint;

            public:
                inline Particle();
                inline Particle(float lifespan, Vector3 position);
                inline Particle(float lifespan, Vector3 position, Vector3 linearVelocity, Color tint);

            protected:
                // Particle* 인채로 delete하지 말라는 의도입니다.
                inline ~Particle();

            private:
                Particle(const Particle&);
                Particle& operator = (const Particle&);
        };
    }

#   include <Bibim/Particle.inl>

#endif