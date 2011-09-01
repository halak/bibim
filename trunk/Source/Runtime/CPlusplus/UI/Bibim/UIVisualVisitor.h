#pragma once
#ifndef __BIBIM_UIVISUALVISITOR_H__
#define __BIBIM_UIVISUALVISITOR_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Matrix4.h>
#   include <Bibim/Rectangle.h>
#   include <Bibim/RectangleF.h>

    namespace Bibim
    {
        class UIVisualVisitor
        {
            BBThisIsNoncopyableClass(UIVisualVisitor);
            public:
                UIVisualVisitor(const Matrix4& viewTransform, const Matrix4& projectionTransform, bool visibleOnly);
                UIVisualVisitor(const Matrix4& viewTransform, const Matrix4& viewTransformInv, const Matrix4& projectionTransform, bool visibleOnly);
                virtual ~UIVisualVisitor();

                Vector2 Project(Vector2 point) const;
                Vector2 Unproject(Vector2 point) const;
                Vector2 UnprojectByParent(Vector2 point) const;

                void Project(Vector2& inOutPoint0, Vector2& inOutPoint1, Vector2& inOutPoint2, Vector2& inOutPoint3) const;
                void Project(Vector2* inOutPoints, int count) const;

                inline const RectangleF& GetViewport() const;
                inline float GetFieldOfView() const;
                inline bool GetVisibleOnly() const;

                inline UIVisual* GetCurrentVisual() const;
                inline float GetCurrentOpacity() const; 
                inline const RectangleF& GetCurrentBounds() const;
                inline const RectangleF& GetCurrentClippedBounds() const;
                inline const Matrix4& GetCurrentTransform() const;

                inline const Matrix4& GetViewTransform() const;
                inline const Matrix4& GetProjectionTransform() const;

            protected:
                void Visit(UIVisual* target);

                virtual void OnVisit() = 0;

            private:
                Vector2 UnprojectPoint(Vector2 point, const Matrix4& inversedTransform) const;

            private:
                 bool visibleOnly;

                UIVisualPtr currentVisual;
                float currentOpacity;
                RectangleF currentBounds;
                RectangleF currentClippedBounds;
                Matrix4 currentTransform;
                Matrix4 currentTransformInv;
                Matrix4 parentTransform;
                Matrix4 parentTransformInv;
                Matrix4 viewTransform;
                Matrix4 viewTransformInv;
                Matrix4 projectionTransform;
        };
    }

#   include <Bibim/UIVisualVisitor.inl>

#endif