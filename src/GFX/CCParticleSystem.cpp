#include <Bibim/Config.h>
#include <Bibim/CCParticleSystem.h>
#include <Bibim/AssetStreamReader.h>
#include <Bibim/Image.h>

namespace Bibim
{
    CCParticleSystem::CCParticleSystem()
    {
    }

    CCParticleSystem::~CCParticleSystem()
    {
    }

    GameAsset* CCParticleSystem::Create(StreamReader& reader, GameAsset* /*existingInstance*/)
    {
        CCParticleSystem* instance = new CCParticleSystem();
        instance->angle = reader.ReadFloat();
        instance->angleVariance = reader.ReadFloat();
        instance->blendFunctionDestination = reader.ReadInt();
        instance->blendFunctionSource = reader.ReadInt();
        instance->duration = reader.ReadFloat();
        instance->mode = static_cast<EmitterMode>(reader.ReadByte());
        instance->finishColor = reader.ReadVector4();
        instance->finishColorVariance = reader.ReadVector4();
        instance->finishParticleRotation = reader.ReadFloat();
        instance->finishParticleRotationVariance = reader.ReadFloat();
        instance->finishParticleSize = reader.ReadFloat();
        instance->finishParticleSizeVariance = reader.ReadFloat();
        instance->gravity = reader.ReadVector2();
        instance->maxParticles = reader.ReadInt();
        instance->maxRadius = reader.ReadFloat();
        instance->maxRadiusVariance = reader.ReadFloat();
        instance->minRadius = reader.ReadFloat();
        instance->particleLifespan = reader.ReadFloat();
        instance->particleLifespanVariance = reader.ReadFloat();
        instance->radialAccelVariance = reader.ReadFloat();
        instance->radialAcceleration = reader.ReadFloat();
        instance->spin = reader.ReadFloat();
        instance->spinVariance = reader.ReadFloat();
        instance->rotationIsDirection = reader.ReadBool();
        instance->sourcePosition = reader.ReadVector2();
        instance->sourcePositionVariance = reader.ReadVector2();
        instance->speed = reader.ReadFloat();
        instance->speedVariance = reader.ReadFloat();
        instance->startColor = reader.ReadVector4();
        instance->startColorVariance = reader.ReadVector4();
        instance->startParticleRotation = reader.ReadFloat();
        instance->startParticleRotationVariance = reader.ReadFloat();
        instance->startParticleSize = reader.ReadFloat();
        instance->startParticleSizeVariance = reader.ReadFloat();
        instance->tangentialAccelVariance = reader.ReadFloat();
        instance->tangentialAcceleration = reader.ReadFloat();
        instance->image = Image::Create(reader, nullptr);
        instance->emissionRate = instance->maxParticles / instance->particleLifespan;

        instance->sourcePosition = Vector2::Zero;

        return instance;
    }
}