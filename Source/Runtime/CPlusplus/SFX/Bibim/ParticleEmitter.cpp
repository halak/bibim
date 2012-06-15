#include <Bibim/PCH.h>
#include <Bibim/ParticleEmitter.h>
#include <Bibim/CloningContext.h>
#include <Bibim/IFloatEvaluable.h>
#include <Bibim/ISpatial.h>
#include <Bibim/ParticleSpawnPoints.h>

namespace Bibim
{
    ParticleEmitter::ParticleEmitter()
        : origin(nullptr),
          spawnPeriod(nullptr),
          spawnPoint(nullptr),
          spawnTime(0.0f)
    {
    }

    ///^ParticleEmitter::ParticleEmitter(const ParticleEmitter& original, CloningContext& context)
    ///^    : origin(context.Clone(original.origin)),
    ///^      spawnPeriod(context.Clone(original.spawnPeriod)),
    ///^      spawnPoint(original.spawnPoint ? original.spawnPoint->Clone() : nullptr),
    ///^      spawnTime(original.spawnTime)
    ///^{
    ///^}
    
    ParticleEmitter::~ParticleEmitter()
    {
        delete spawnPoint;
    }
    
    void ParticleEmitter::Update(float dt, uint timestamp)
    {
        if (spawnPeriod == nullptr || origin == nullptr)
            return;
        if (updateableSpawnPeriod)
            updateableSpawnPeriod->Update(dt, timestamp);

        const Vector3 position = origin->GetPosition();
        const Quaternion rotation = origin->GetRotation();
        const float scale = origin->GetScale();
        const float spawnPeriodValue = spawnPeriod->Evaluate();

        spawnTime += dt;
        while (spawnTime > spawnPeriodValue)
        {
            spawnTime -= spawnPeriodValue;
            Spawn(spawnTime, spawnPoint ? spawnPoint->Spawn(position, rotation, scale) : position);
        }
    }

    ISpatial* ParticleEmitter::GetOrigin() const
    {
        return origin;
    }

    void ParticleEmitter::SetOrigin(ISpatialPtr value)
    {
        origin = value;
    }

    IFloatEvaluable* ParticleEmitter::GetSpawnPeriod() const
    {
        return spawnPeriod;
    }

    void ParticleEmitter::SetSpawnPeriod(IFloatEvaluablePtr value)
    {
        if (spawnPeriod != value)
        {
            spawnPeriod = value;
            updateableSpawnPeriod = DynamicCast<IUpdateable>(value);
        }
    }

    ParticleSpawnPoint* ParticleEmitter::GetSpawnPonit() const
    {
        return spawnPoint;
    }

    void ParticleEmitter::SetSpawnPoint(ParticleSpawnPoint* value)
    {
        ParticleSpawnPoint* deletingSpawnPoint = spawnPoint;
        spawnPoint = value;
        delete deletingSpawnPoint;
    }
}