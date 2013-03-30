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

                inline void RotateXYZ(float x, float y, float z);

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
    }

#   include <Bibim/UITransform3D.inl>

#endif