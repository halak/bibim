#pragma once
#ifndef __BIBIM_CCPARTICLEEMITTER_H__
#define __BIBIM_CCPARTICLEEMITTER_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Vector2.h>
#   include <Bibim/Vector4.h>
#   include <vector>

    namespace Bibim
    {
        struct CCParticle
        {
            Vector2 pos;
            Vector2 startPos;

            Vector4 color;
            Vector4 deltaColor;

            float size;
            float deltaSize;

            float rotation;
            float deltaRotation;

            float timeToLive;

            int atlasIndex;

            struct {
                Vector2 dir;
                float radialAccel;
                float tangentialAccel;
            } modeA;

            struct Radius {
                float angle;
                float degreesPerSecond;
                float radius;
                float deltaRadius;
            } modeB;
        };

        class CCParticleEmitter
        {
            public:
                CCParticleEmitter(CCParticleSystem* system);
                virtual ~CCParticleEmitter();

                void Reset();
                void Stop();

                bool Update(float dt, int timestamp);

                inline float GetGlobalAngle() const;
                inline void  SetGlobalAngle(float value);
                inline const CCParticle* GetParticles() const;
                inline int GetNumberOfParticles() const;

            protected:
                bool Emit();

            private:
                static inline float Generate(float base, float variance);
                static inline float GenerateGTE0(float base, float variance);
                static inline Vector2 Generate(Vector2 base, Vector2 variance);
                static inline Vector4 Generate(Vector4 base, Vector4 variance);

            private:
                CCParticleSystem* system;
                float globalAngle;
                float elapsedTime;
                std::vector<CCParticle> particles;
                float emitCounter;
                int particleIndex;
                int particleCount;
                bool isActive;
        };

        float CCParticleEmitter::GetGlobalAngle() const
        {
            return globalAngle;
        }

        void CCParticleEmitter::SetGlobalAngle(float value)
        {
            globalAngle = value;
        }

        const CCParticle* CCParticleEmitter::GetParticles() const
        {
            return &particles[0];
        }

        int CCParticleEmitter::GetNumberOfParticles() const
        {
            return particleCount;
        }
    }

#endif