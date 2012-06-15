#include <Bibim/PCH.h>
#include <Bibim/UIWindow3D.h>
#include <Bibim/ComponentStreamReader.h>

namespace Bibim
{
    BBImplementsComponent(UIWindow3D);
    
    UIWindow3D::UIWindow3D()
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

    UIWindow3D::UIWindow3D(int childrenCapacity)
        : Base(childrenCapacity),
          localOffset(Vector3::Zero),
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

    UIWindow3D::~UIWindow3D()
    {
    }

    void UIWindow3D::Reset()
    {
        localOffset = Vector3::Zero;
        globalOffset = Vector3::Zero;
        rotationCenter = Vector2(0.5f, 0.5f);
        rotation = Vector3::Zero;
        scaleCenter = Vector2(0.5f, 0.5f);
        scale = Vector2::One;
    }

    void UIWindow3D::SetLocalOffset(Vector3 value)
    {
        if (localOffset != value)
        {
            localOffset = value;
            matrixChanged = true;
        }
    }

    void UIWindow3D::SetGlobalOffset(Vector3 value)
    {
        if (globalOffset != value)
        {
            globalOffset = value;
            matrixChanged = true;
        }
    }

    void UIWindow3D::SetRotationCenter(Vector2 value)
    {
        if (rotationCenter != value)
        {
            rotationCenter = value;
            matrixChanged = true;
        }
    }

    void UIWindow3D::SetRotation(Vector3 value)
    {
        if (rotation != value)
        {
            rotation = value;
            matrixChanged = true;
        }
    }

    void UIWindow3D::SetScaleCenter(Vector2 value)
    {
        if (scaleCenter != value)
        {
            scaleCenter = value;
            matrixChanged = true;
        }
    }

    void UIWindow3D::SetScale(Vector2 value)
    {
        if (scale != value)
        {
            scale = value;
            matrixChanged = true;
        }
    }

    void UIWindow3D::OnRead(ComponentStreamReader& reader)
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

    void UIWindow3D::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const UIWindow3D* o = static_cast<const UIWindow3D*>(original);
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