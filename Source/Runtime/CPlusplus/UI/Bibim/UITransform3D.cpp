#include <Bibim/PCH.h>
#include <Bibim/UITransform3D.h>
#include <Bibim/UIVisualVisitor.h>

namespace Bibim
{
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
}