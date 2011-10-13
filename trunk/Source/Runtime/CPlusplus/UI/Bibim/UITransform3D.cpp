#include <Bibim/PCH.h>
#include <Bibim/UITransform3D.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/UIVisualVisitor.h>

namespace Bibim
{
    BBImplementsComponent(UITransform3D);

    UITransform3D::UITransform3D()
        : localOffset(Vector3::Zero),
          globalOffset(Vector3::Zero),
          rotationCenter(Vector2(0.5f, 0.5f)),
          rotation(Vector3::Zero),
          scaleCenter(Vector2(0.5f, 0.5f)),
          scale(Vector2::One),
          matrix(),
          lastBounds(RectF::Empty),
          matrixChanged(true)
    {
    }

    UITransform3D::~UITransform3D()
    {
    }

    void UITransform3D::Reset()
    {
        localOffset = Vector3::Zero;
        globalOffset = Vector3::Zero;
        rotationCenter = Vector2(0.5f, 0.5f);
        rotation = Vector3::Zero;
        scaleCenter = Vector2(0.5f, 0.5f);
        scale = Vector2::One;
    }

    void UITransform3D::SetLocalOffset(Vector3 value)
    {
        if (localOffset != value)
        {
            localOffset = value;
            matrixChanged = true;
        }
    }

    void UITransform3D::SetGlobalOffset(Vector3 value)
    {
        if (globalOffset != value)
        {
            globalOffset = value;
            matrixChanged = true;
        }
    }

    void UITransform3D::SetRotationCenter(Vector2 value)
    {
        if (rotationCenter != value)
        {
            rotationCenter = value;
            matrixChanged = true;
        }
    }

    void UITransform3D::SetRotation(Vector3 value)
    {
        if (rotation != value)
        {
            rotation = value;
            matrixChanged = true;
        }
    }

    void UITransform3D::SetScaleCenter(Vector2 value)
    {
        if (scaleCenter != value)
        {
            scaleCenter = value;
            matrixChanged = true;
        }
    }

    void UITransform3D::SetScale(Vector2 value)
    {
        if (scale != value)
        {
            scale = value;
            matrixChanged = true;
        }
    }

    void UITransform3D::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        localOffset = reader.ReadVector3();
        globalOffset = reader.ReadVector3();
        rotationCenter = reader.ReadVector2();
        rotation = reader.ReadVector3();
        scaleCenter = reader.ReadVector2();
        scale = reader.ReadVector2();
        matrixChanged = true;
    }

    void UITransform3D::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const UITransform3D* o = static_cast<const UITransform3D*>(original);
        localOffset = o->localOffset;
        globalOffset = o->globalOffset;
        rotationCenter = o->rotationCenter;
        rotation = o->rotation;
        scaleCenter = o->scaleCenter;
        scale = o->scale;
        matrix = o->matrix;
        lastBounds = o->lastBounds;
        matrixChanged = o->matrixChanged;
    }
}