#pragma once
#ifndef __BIBIM_PARTICLESPAWNPOINTS_H__
#define __BIBIM_PARTICLESPAWNPOINTS_H__

#   include <Bibim/FWD.h>
#   include <Bibim/ICloneable.h>
#   include <Bibim/Quaternion.h>
#   include <Bibim/Vector3.h>

    namespace Bibim
    {
        class ParticleSpawnPoint : public ICloneable
        {
            public:
                ParticleSpawnPoint();
                ParticleSpawnPoint(const ParticleSpawnPoint& original);
                virtual ~ParticleSpawnPoint();

                virtual ParticleSpawnPoint* Clone() const;
                virtual ParticleSpawnPoint* CloneWith(CloningContext& context) const;

                virtual Vector3 Spawn(Vector3 position, Quaternion rotation, float scale) const;
        };

        class ParticleSpawnSegment : public ParticleSpawnPoint
        {
            public:
                ParticleSpawnSegment();
                virtual ~ParticleSpawnSegment();

                virtual Vector3 Spawn(Vector3 position, Quaternion rotation, float scale) const;
        };

        class ParticleSpawnBox : public ParticleSpawnPoint
        {
            public:
                ParticleSpawnBox();
                virtual ~ParticleSpawnBox();

                virtual Vector3 Spawn(Vector3 position, Quaternion rotation, float scale) const;
        };

        class ParticleSpawnSphere : public ParticleSpawnPoint
        {
            public:
                ParticleSpawnSphere();
                ParticleSpawnSphere(float radius);
                ParticleSpawnSphere(const ParticleSpawnSphere& original);
                virtual ~ParticleSpawnSphere();

                virtual ParticleSpawnSphere* Clone() const;
                virtual ParticleSpawnSphere* CloneWith(CloningContext& context) const;

                virtual Vector3 Spawn(Vector3 position, Quaternion rotation, float scale) const;

                float GetRadius() const;
                void  SetRadius(float value);

            private:
                float radius;
        };
    }

#endif