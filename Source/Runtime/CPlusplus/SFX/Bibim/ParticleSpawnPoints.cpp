#include <Bibim/PCH.h>
#include <Bibim/ParticleSpawnPoints.h>
#include <Bibim/Math.h>

namespace Bibim
{
    ParticleSpawnPoint::ParticleSpawnPoint()
    {
    }

    ParticleSpawnPoint::ParticleSpawnPoint(const ParticleSpawnPoint& /*original*/)
    {
    }

    ParticleSpawnPoint::~ParticleSpawnPoint()
    {
    }

    ParticleSpawnPoint* ParticleSpawnPoint::Clone() const
    {
        return new ParticleSpawnPoint(*this);
    }

    ParticleSpawnPoint* ParticleSpawnPoint::CloneWith(CloningContext& /*context*/) const
    {
        return new ParticleSpawnPoint(*this);
    }
    
    Vector3 ParticleSpawnPoint::Spawn(Vector3 position, Quaternion /*rotation*/, float /*scale*/) const
    {
        return position;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    ParticleSpawnSegment::ParticleSpawnSegment()
    {
    }

    ParticleSpawnSegment::~ParticleSpawnSegment()
    {
    }

    Vector3 ParticleSpawnSegment::Spawn(Vector3 /*position*/, Quaternion /*rotation*/, float /*scale*/) const
    {
        return Vector3::Zero;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    ParticleSpawnBox::ParticleSpawnBox()
    {
    }

    ParticleSpawnBox::~ParticleSpawnBox()
    {
    }

    Vector3 ParticleSpawnBox::Spawn(Vector3 /*position*/, Quaternion /*rotation*/, float /*scale*/) const
    {
        return Vector3::Zero;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    ParticleSpawnSphere::ParticleSpawnSphere()
        : ParticleSpawnPoint(),
          radius(0.0f)
    {
    }

    ParticleSpawnSphere::ParticleSpawnSphere(float radius)
        : ParticleSpawnPoint(),
          radius(Math::Max(radius, 0.0f))
    {
    }

    ParticleSpawnSphere::ParticleSpawnSphere(const ParticleSpawnSphere& original)
        : ParticleSpawnPoint(original),
          radius(original.radius)
    {
    }

    ParticleSpawnSphere::~ParticleSpawnSphere()
    {
    }

    ParticleSpawnSphere* ParticleSpawnSphere::Clone() const
    {
        return new ParticleSpawnSphere(*this);
    }

    ParticleSpawnSphere* ParticleSpawnSphere::CloneWith(CloningContext& /*context*/) const
    {
        return new ParticleSpawnSphere(*this);
    }

    Vector3 ParticleSpawnSphere::Spawn(Vector3 position, Quaternion /*rotation*/, float scale) const
    {
        const float yaw   = Math::Random(0.0f, Math::TwoPi);
        const float pitch = Math::Random(0.0f, Math::TwoPi);

        // Rotated Vector by yaw
        // ryX = Vector3::UnitX.X * cos(yaw) - Vector3::UnitX.Y * sin(yaw) => 1.0f * cosw - 0.0f * sin(yaw) => cos(yaw)
        // ryY = Vector3::UnitX.X * sin(yaw) + Vector3::UnitX.Y * cos(yaw) => 1.0f * sinw + 0.0f * cos(yaw) => sin(yaw)
        // ryz = Vector3::UnitX.Z * 1.0f => 0.0f * 1.0f => 0.0f
        const float x = Math::Cos(yaw);
        const float y = Math::Sin(yaw);

        // Rotated Vector by pitch
        // rpX = ryx * cos(pitch) + ryz * sin(pitch) => ryx * cos(pitch) + 0.0f * sin(pitch) => ryx * cos(pitch)
        // rpY = ryy
        // rpZ = -ryx * sin(pitch) + ryz * cos(pitch) => -ryx * sin(pitch) + 0.0f * cos(pitch) => -ryx * sin(pitch)
        const Vector3 direction = Vector3(+x * Math::Cos(pitch), y, -x * Math::Sin(pitch));

        return position + (direction * Math::Random(0.0f, radius * scale));
    }

    float ParticleSpawnSphere::GetRadius() const
    {
        return radius;
    }

    void ParticleSpawnSphere::SetRadius(float value)
    {
        radius = Math::Max(value, 0.0f);
    }
}