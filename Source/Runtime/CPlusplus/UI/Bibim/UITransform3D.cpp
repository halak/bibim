#include <Bibim/Config.h>
#include <Bibim/UITransform3D.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/Math.h>
#include <Bibim/Matrix4.h>
#include <Bibim/UIVisualVisitor.h>

namespace Bibim
{
    BBImplementsComponent(UITransform3D);

    UITransform3D::UITransform3D()
        : localOffset(Vector3::Zero),
          globalOffset(Vector3::Zero),
          rotationCenter(Vector2(0.49f, 0.49f)),
          rotation(Vector3::Zero),
          scaleCenter(Vector2(0.49f, 0.49f)),
          scale(Vector2::One),
          matrix(),
          lastBounds(RectF::Empty),
          matrixChanged(true)
    {
    }

    UITransform3D::~UITransform3D()
    {
    }

    Matrix4 RotationPitchYawRoll(Vector3 value)
    {
        const float yaw   = value.Y * 0.5f;
        const float pitch = value.X * 0.5f;
        const float roll  = value.Z * 0.5f;
        const Vector4 rotationQuaternion = Vector4(Math::Sin(yaw) * Math::Cos(pitch) * Math::Sin(roll) + Math::Cos(yaw) * Math::Sin(pitch) * Math::Cos(roll),
                                                   Math::Sin(yaw) * Math::Cos(pitch) * Math::Cos(roll) - Math::Cos(yaw) * Math::Sin(pitch) * Math::Sin(roll),
                                                   Math::Cos(yaw) * Math::Cos(pitch) * Math::Sin(roll) - Math::Sin(yaw) * Math::Sin(pitch) * Math::Cos(roll),
                                                   Math::Cos(yaw) * Math::Cos(pitch) * Math::Cos(roll) + Math::Sin(yaw) * Math::Sin(pitch) * Math::Sin(roll));

        const float x = rotationQuaternion.X;
        const float y = rotationQuaternion.Y;
        const float z = rotationQuaternion.Z;
        const float w = rotationQuaternion.W;
        return Matrix4(1.0f - 2.0f * (y * y + z * z),
                       2.0f * (x * y + z * w),
                       2.0f * (x * z - y * w),
                       0.0f,
                       2.0f * (x * y - z * w),
                       1.0f - 2.0f * (x * x + z * z),
                       2.0f * (y * z + x * w),
                       0.0f,
                       2.0f * (x * z + y * w),
                       2.0f * (y * z - x * w),
                       1.0f - 2.0f * (x * x + y * y),
                       0.0f,
                       0.0f, 0.0f, 0.0f, 1.0f);
    }

    Matrix4 Transformation(Vector3 scaleCenter, Vector3 scale, Vector3 rotationCenter, Vector3 rotation, Vector3 translation)
    {
        Matrix4 m = Matrix4::Translation(-scaleCenter);
        m *= Matrix4::Scaling(scale);
        m *= Matrix4::Translation(scaleCenter - rotationCenter);
        m *= RotationPitchYawRoll(rotation);
        m *= Matrix4::Translation(rotationCenter + translation);
        return m;
    }

    const Matrix4& UITransform3D::ComputeMatrix(UIVisualVisitor& context)
    {
        const RectF bounds = context.GetCurrentBounds();
        if (matrixChanged || lastBounds != bounds)
        {
            matrix = Transformation(Vector3(localOffset.X + bounds.X + (bounds.Width * scaleCenter.X),
                                            localOffset.Y + bounds.Y + (bounds.Height * scaleCenter.Y),
                                            localOffset.Z),
                                    Vector3(scale.X, scale.Y, 1.0f),
                                    Vector3(localOffset.X + bounds.X + (bounds.Width * rotationCenter.X),
                                            localOffset.Y + bounds.Y + (bounds.Height * rotationCenter.Y),
                                            localOffset.Z),
                                    rotation,
                                    globalOffset);
            matrixChanged = false;
            lastBounds = bounds;
        }

        return matrix;
    }

    void UITransform3D::Reset()
    {
        localOffset = Vector3::Zero;
        globalOffset = Vector3::Zero;
        rotationCenter = Vector2(0.49f, 0.49f);
        rotation = Vector3::Zero;
        scaleCenter = Vector2(0.49f, 0.49f);
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