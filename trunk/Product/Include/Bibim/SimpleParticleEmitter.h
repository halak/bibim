#pragma once
#ifndef __BIBIM_SIMPLEPARTICLEEMITTER_H__
#define __BIBIM_SIMPLEPARTICLEEMITTER_H__

#   include <Bibim/FWD.h>
#   include <Bibim/ParticleEmitter.h>
#   include <Bibim/SimpleParticle.h>
#   include <list>
#   include <vector>

    namespace Bibim
    {
        class SimpleParticleEmitter : public ParticleEmitter
        {
            public:
                typedef std::list<SimpleParticle*> ParticleCollection;
                typedef std::vector<Sprite> SpriteCollection;

            public:
                SimpleParticleEmitter();
                virtual ~SimpleParticleEmitter();

                virtual void Update(float dt, uint timestamp);

                float GetLifespan1() const;
                void  SetLifespan1(float value);
                float GetLifespan2() const;
                void  SetLifespan2(float value);

                Vector3 GetLinearVelocity1() const;
                void    SetLinearVelocity1(Vector3 value);
                Vector3 GetLinearVelocity2() const;
                void    SetLinearVelocity2(Vector3 value);

                float GetLinearAccelerationForce1() const;
                void  SetLinearAccelerationForce1(float value);
                float GetLinearAccelerationForce2() const;
                void  SetLinearAccelerationForce2(float value);

                float GetRotation1() const;
                void  SetRotation1(float value);
                float GetRotation2() const;
                void  SetRotation2(float value);

                float GetAngularVelocity1() const;
                void  SetAngularVelocity1(float value);
                float GetAngularVelocity2() const;
                void  SetAngularVelocity2(float value);

                float GetAngularAccelerationForce1() const;
                void  SetAngularAccelerationForce1(float value);
                float GetAngularAccelerationForce2() const;
                void  SetAngularAccelerationForce2(float value);

                Vector2 GetScale1() const;
                void    SetScale1(Vector2 value);
                Vector2 GetScale2() const;
                void    SetScale2(Vector2 value);

                Vector2 GetStrainVelocity1() const;
                void    SetStrainVelocity1(Vector2 value);
                Vector2 GetStrainVelocity2() const;
                void    SetStrainVelocity2(Vector2 value);

                float GetStrainAccelerationForce1() const;
                void  SetStrainAccelerationForce1(float value);
                float GetStrainAccelerationForce2() const;
                void  SetStrainAccelerationForce2(float value);

                Color GetStartTint1() const;
                void  SetStartTint1(Color value);
                Color GetStartTint2() const;
                void  SetStartTint2(Color value);

                Color GetEndTint1() const;
                void  SetEndTint1(Color value);
                Color GetEndTint2() const;
                void  SetEndTint2(Color value);

                bool GetLocalCoordinates() const;
                void SetLocalCoordinates(bool value);

                bool GetRatioKeepScale() const;
                void SetRatioKeepScale(bool value);

                const SpriteCollection& GetSpritePalette() const;
                void SetSpritePalette(const SpriteCollection& value);

                const ParticleCollection& GetParticles() const;

            protected:
                inline  void UpdateParticle(SimpleParticle* particle, float dt);
                virtual void Spawn(float age, Vector3 position);

            private:
                float lifespans[2];
                Vector3 linearVelocities[2];
                float linearAccelerationForces[2];
                float rotations[2];
                float angularVelocities[2];
                float angularAccelerationForces[2];
                Vector2 scales[2];
                Vector2 strainVelocities[2];
                float strainAccelerationForces[2];
                Vector4 startTints[2];
                Vector4 endTints[2];
                bool localCoordinates;
                bool ratioKeepScale;
                SpriteCollection sprites;

                ParticleCollection particles;

                uint lastTimestamp;

            private:
                friend void __Startup__();
                static void __Startup__();
        };
    }

#endif