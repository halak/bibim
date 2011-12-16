#pragma once
#ifndef __BIBIM_UIWINDOW3D_H__
#define __BIBIM_UIWINDOW3D_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIWindow.h>
#   include <Bibim/Matrix4.h>
#   include <Bibim/RectF.h>
#   include <Bibim/Vector2.h>
#   include <Bibim/Vector3.h>

    namespace Bibim
    {
        class UIWindow3D : public UIWindow
        {
            BBComponentClass(UIWindow3D, UIWindow, 'U', 'W', 'N', '3');
            public:
                UIWindow3D();
                explicit UIWindow3D(int childrenCapacity);
                virtual ~UIWindow3D();

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
                inline void SetScale(float value);

            private:
                void UpdateMatrix(RectF bounds);

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

#   include <Bibim/UIWindow3D.inl>

#endif