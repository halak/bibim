#pragma once
#ifndef __BIBIM_PARTICLEEMITTER_H__
#define __BIBIM_PARTICLEEMITTER_H__

#   include <Bibim/FWD.h>
#   include <Bibim/ICloneable.h>
#   include <Bibim/IUpdateable.h>

    namespace Bibim
    {
        class ParticleEmitter : public IUpdateable
        {
            public:
                ParticleEmitter();
                ///^ParticleEmitter(const ParticleEmitter& original, CloningContext& context);
                virtual ~ParticleEmitter();

                virtual void Update(float dt, uint timestamp);

                ISpatial* GetOrigin() const;
                void SetOrigin(ISpatialPtr value);

                IFloatEvaluable* GetSpawnPeriod() const;
                void SetSpawnPeriod(IFloatEvaluablePtr value);

                ParticleSpawnPoint* GetSpawnPonit() const;
                void SetSpawnPoint(ParticleSpawnPoint* value);

            protected:
                virtual void Spawn(float age, Vector3 position) = 0;

            private:
                ISpatialPtr origin;

                IFloatEvaluablePtr spawnPeriod;
                IUpdateablePtr updateableSpawnPeriod;
                ParticleSpawnPoint* spawnPoint;

                float spawnTime;
        };
    }

#endif