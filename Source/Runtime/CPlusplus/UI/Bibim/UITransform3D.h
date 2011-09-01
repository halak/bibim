#pragma once
#ifndef __BIBIM_UITRANSFORM3D_H__
#define __BIBIM_UITRANSFORM3D_H__

#   include <Bibim/UITransform.h>
#   include <Bibim/RectangleF.h>
#   include <Bibim/Vector2.h>
#   include <Bibim/Vector3.h>

    namespace Bibim
    {
        class UITransform3D : public UITransform
        {
            public:
                UITransform3D();
                virtual ~UITransform3D();

                virtual const Matrix4& ComputeMatrix(UIVisualVisitor& visitor);

                void Reset();

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

            private:
                Vector3 localOffset;
                Vector3 globalOffset;
                Vector2 rotationCenter;
                Vector3 rotation;
                Vector2 scaleCenter;
                Vector2 scale;
                Matrix4 matrix;
                RectangleF lastBounds;
                bool matrixChanged;
        };
    }

#   include <Bibim/UITransform3D.inl>

#endif