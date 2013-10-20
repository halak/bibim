#pragma once
#ifndef __BIBIM_CCPARTICLESYSTEM_H__
#define __BIBIM_CCPARTICLESYSTEM_H__

#include <Bibim/FWD.h>
#include <Bibim/GameAsset.h>
#include <Bibim/String.h>
#include <Bibim/Vector2.h>
#include <Bibim/Vector4.h>
#include <vector>

namespace Bibim
{
    class CCParticleSystem : public GameAsset
    {
        BBSerializableAssetClass(CCParticleSystem, GameAsset, 'A', 'S', 'P', 'S');
        public:
            enum EmitterMode
            {
                GravityMode,
                RadiusMode,
            };

        public:
            CCParticleSystem();
            virtual ~CCParticleSystem();

            inline float GetAngle() const { return angle; }
            inline float GetAngleVariance() const { return angleVariance; }
            // inline int GetImage() const { return blendFunctionDestination; }
            // inline int GetImage() const { return blendFunctionSource; }
            inline float GetDuration() const { return duration; }
            inline EmitterMode GetMode() const { return mode; }
            inline Vector4 GetFinishColor() const { return finishColor; }
            inline Vector4 GetFinishColorVariance() const { return finishColorVariance; }
            inline float GetFinishParticleRotation() const { return finishParticleRotation; }
            inline float GetFinishParticleRotationVariance() const { return finishParticleRotationVariance; }
            inline float GetFinishParticleSize() const { return finishParticleSize; }
            inline float GetFinishParticleSizeVariance() const { return finishParticleSizeVariance; }
            inline Vector2 GetGravity() const { return gravity; }
            inline int GetMaxParticles() const { return maxParticles; }
            inline float GetMaxRadius() const { return maxRadius; }
            inline float GetMaxRadiusVariance() const { return maxRadiusVariance; }
            inline float GetMinRadius() const { return minRadius; }
            inline float GetParticleLifespan() const { return particleLifespan; }
            inline float GetParticleLifespanVariance() const { return particleLifespanVariance; }
            inline float GetRadialAccelVariance() const { return radialAccelVariance; }
            inline float GetRadialAcceleration() const { return radialAcceleration; }
            inline float GetSpin() const { return spin; }
            inline float GetSpinVariance() const { return spinVariance; }
            inline bool GetRotationIsDirection() const { return rotationIsDirection; }
            inline Vector2 GetSourcePosition() const { return sourcePosition; }
            inline Vector2 GetSourcePositionVariance() const { return sourcePositionVariance; }
            inline float GetSpeed() const { return speed; }
            inline float GetSpeedVariance() const { return speedVariance; }
            inline Vector4 GetStartColor() const { return startColor; }
            inline Vector4 GetStartColorVariance() const { return startColorVariance; }
            inline float GetStartParticleRotation() const { return startParticleRotation; }
            inline float GetStartParticleRotationVariance() const { return startParticleRotationVariance; }
            inline float GetStartParticleSize() const { return startParticleSize; }
            inline float GetStartParticleSizeVariance() const { return startParticleSizeVariance; }
            inline float GetTangentialAccelVariance() const { return tangentialAccelVariance; }
            inline float GetTangentialAcceleration() const { return tangentialAcceleration; }
            inline Image* GetImage() const { return image; }
            inline float GetEmissionRate() const { return emissionRate; }

        private:
            float angle;
            float angleVariance;
            int blendFunctionDestination;
            int blendFunctionSource;
            float duration;
            EmitterMode mode;
            Vector4 finishColor;
            Vector4 finishColorVariance;
            float finishParticleRotation;
            float finishParticleRotationVariance;
            float finishParticleSize;
            float finishParticleSizeVariance;
            Vector2 gravity;
            int maxParticles;
            float maxRadius;
            float maxRadiusVariance;
            float minRadius;
            float particleLifespan;
            float particleLifespanVariance;
            float radialAccelVariance;
            float radialAcceleration;
            float spin;
            float spinVariance;
            bool rotationIsDirection;
            Vector2 sourcePosition;
            Vector2 sourcePositionVariance;
            float speed;
            float speedVariance;
            Vector4 startColor;
            Vector4 startColorVariance;
            float startParticleRotation;
            float startParticleRotationVariance;
            float startParticleSize;
            float startParticleSizeVariance;
            float tangentialAccelVariance;
            float tangentialAcceleration;
            ImagePtr image;
            float emissionRate;
    };
}

#endif