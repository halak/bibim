#include <Bibim/PCH.h>
#include <Bibim/SpatialObject2D.h>
#include <Bibim/ComponentStreamReader.h>

namespace Bibim
{
    BBImplementsComponent(SpatialObject2D);

    SpatialObject2D::SpatialObject2D()
        : position(Vector2::Zero),
          rotation(0.0f),
          scale(1.0f),
          direction(Vector2::UnitY)
    {
    }

    SpatialObject2D::~SpatialObject2D()
    {
    }

    void SpatialObject2D::SetPosition(Vector2 value)
    {
        position = value;
    }

    void SpatialObject2D::SetRotation(float value)
    {
        rotation = value;
    }

    void SpatialObject2D::SetScale(float value)
    {
        scale = value;
    }

    void SpatialObject2D::SetDirection(Vector2 value)
    {
        direction = value;

        const float lengthSquared = direction.GetLengthSquared();
        if (lengthSquared == 0.0f)
            direction = Vector2::UnitY;
        else if (lengthSquared != 1.0f)
            direction.Normalize();
    }

    void SpatialObject2D::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        position = reader.ReadVector2();
        rotation = reader.ReadFloat();
        scale = reader.ReadFloat();
        direction = reader.ReadVector2();
    }

    void SpatialObject2D::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        position = o->position;
        rotation = o->rotation;
        scale = o->scale;
        direction = o->direction;
    }
}