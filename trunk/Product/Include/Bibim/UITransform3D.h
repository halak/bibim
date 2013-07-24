#pragma once
#ifndef __BIBIM_UITransform3D_H__
#define __BIBIM_UITransform3D_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UITransform.h>
#   include <Bibim/Matrix4.h>
#   include <Bibim/RectF.h>
#   include <Bibim/Vector2.h>
#   include <Bibim/Vector3.h>

    namespace Bibim
    {
        class UITransform3D : public UITransform
        {
            BBComponentClass(UITransform3D, UITransform, 'U', 'T', 'M', '3');
            public:
                UITransform3D();
                virtual ~UITransform3D();

                virtual const Matrix4& ComputeMatrix(UIVisualVisitor& context);

                void Reset();

                void Rotate(Vector3 value);

                inline Vector3 GetLocalOffset() const;
                void SetLocalOffset(Vector3 value);
                
                inline Vector3 GetGlobalOffset() const;
                void SetGlobalOffset(Vector3 value);
                
                inline Vector2 GetRotationCenter() const;
                void SetRotationCenter(Vector2 value);
                
                inline Vector3 GetRotation() const;
                void SetRotation(Vector3 value);
                
                inline Vector2 GetScaleCenter() const;
                void SetScaleCenter(Vector2 value);
                
                inline Vector2 GetScale() const;
                void SetScale(Vector2 value);
                inline void SetScale(float value);

                Vector3 TransformOrientation(Vector3 value);

                inline void RotateXYZ(float x, float y, float z);

                inline Vector3 TransformOrientationXYZ(float x, float y, float z);
                inline void SetLocalOffsetXYZ(float x, float y, float z);
                inline void SetGlobalOffsetXYZ(float x, float y, float z);
                inline void SetRotationXYZ(float x, float y, float z);
                inline void SetRotationCenterXY(float x, float y);
                inline void SetScaleXY(float x, float y);
                inline void SetScaleCenterXY(float x, float y);

            private:
                Vector3 localOffset;
                Vector3 globalOffset;
                Vector2 rotationCenter;
                Vector3 rotation;
                Vector2 scaleCenter;
                Vector2 scale;
                Matrix4 matrix;
                RectF lastBounds;
                bool matrixChanged;
        };

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        Vector3 UITransform3D::GetLocalOffset() const
        {
            return localOffset;
        }

        Vector3 UITransform3D::GetGlobalOffset() const
        {
            return globalOffset;
        }

        Vector2 UITransform3D::GetRotationCenter() const
        {
            return rotationCenter;
        }

        Vector3 UITransform3D::GetRotation() const
        {
            return rotation;
        }

        Vector2 UITransform3D::GetScaleCenter() const
        {
            return scaleCenter;
        }

        Vector2 UITransform3D::GetScale() const
        {
            return scale;
        }

        void UITransform3D::SetScale(float value)
        {
            SetScale(Vector2(value, value));
        }

        Vector3 UITransform3D::TransformOrientationXYZ(float x, float y, float z)
        {
            return TransformOrientation(Vector3(x, y, z));
        }

        void UITransform3D::RotateXYZ(float x, float y, float z)
        {
            Rotate(Vector3(x, y, z));
        }

        void UITransform3D::SetLocalOffsetXYZ(float x, float y, float z)
        {
            SetLocalOffset(Vector3(x, y, z));
        }

        void UITransform3D::SetGlobalOffsetXYZ(float x, float y, float z)
        {
            SetGlobalOffset(Vector3(x, y, z));
        }

        void UITransform3D::SetRotationXYZ(float x, float y, float z)
        {
            SetRotation(Vector3(x, y, z));
        }

        void UITransform3D::SetRotationCenterXY(float x, float y)
        {
            SetRotationCenter(Vector2(x, y));
        }

        void UITransform3D::SetScaleXY(float x, float y)
        {
            SetScale(Vector2(x, y));
        }

        void UITransform3D::SetScaleCenterXY(float x, float y)
        {
            SetScaleCenter(Vector2(x, y));
        }
    }

#endif