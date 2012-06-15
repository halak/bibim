#pragma once
#ifndef __BIBIM_PARTICLESPACE_H__
#define __BIBIM_PARTICLESPACE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameComponent.h>
#   include <Bibim/IUpdateable.h>
#   include <vector>

    namespace Bibim
    {
        class ParticleSpace : public GameComponent, public IUpdateable
        {
            BBClassFOURCC('P', 'T', 'S', 'P');
            public:
                typedef std::vector<ParticleEmitterPtr> EmitterCollection;

            public:
                ParticleSpace();

                virtual void Update(float dt, uint timestamp);

            protected:
                virtual ~ParticleSpace();

            private:
                EmitterCollection emitters;
        };
    }

#endif