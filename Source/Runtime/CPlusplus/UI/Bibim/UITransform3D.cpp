#include <Bibim/PCH.h>
#include <Bibim/UITransform3D.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/Matrix4.h>
#include <Bibim/UIVisualVisitor.h>
#include <d3dx9math.h>

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

    const Matrix4& UITransform3D::ComputeMatrix(UIVisualVisitor& context)
    {
        const RectF bounds = context.GetCurrentBounds();
        if (matrixChanged || lastBounds != bounds)
        {
            D3DXQUATERNION d3dRotation;
            D3DXQuaternionRotationYawPitchRoll(&d3dRotation, rotation.Y, rotation.X, rotation.Z);
            
            const D3DXVECTOR3 d3dScaleCenter = D3DXVECTOR3(localOffset.X + bounds.X + (bounds.Width * scaleCenter.X),
                                                           localOffset.Y + bounds.Y + (bounds.Height * scaleCenter.Y),
                                                           localOffset.Z);
            const D3DXVECTOR3 d3dScale = D3DXVECTOR3(scale.X, scale.Y, 1.0f);
            const D3DXVECTOR3 d3dRotationCenter = D3DXVECTOR3(localOffset.X + bounds.X + (bounds.Width * rotationCenter.X),
                                                              localOffset.Y + bounds.Y + (bounds.Height * rotationCenter.Y),
                                                              localOffset.Z);
            const D3DXVECTOR3 d3dTranslation = D3DXVECTOR3(globalOffset.X, globalOffset.Y, globalOffset.Z);

            D3DXMATRIX d3dResultTransform;
            D3DXMatrixTransformation(&d3dResultTransform, &d3dScaleCenter, nullptr, &d3dScale, &d3dRotationCenter, &d3dRotation, &d3dTranslation);

            matrix = Matrix4(d3dResultTransform);
            matrixChanged = false;
            lastBounds = bounds;
        }

        return matrix;
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

    void UITransform3D::Rotate(Vector3 value)
    {
        if (value != Vector3::Zero)
        {
            rotation += value;
            matrixChanged = true;
        }
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
        const This* o = static_cast<const This*>(original);
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