#pragma once
#ifndef __BIBIM_UIVISUALVISITOR_H__
#define __BIBIM_UIVISUALVISITOR_H__

#include <Bibim/FWD.h>
#include <Bibim/Matrix4.h>
#include <Bibim/Rect.h>
#include <Bibim/RectF.h>

namespace Bibim
{
    class UIVisualVisitor
    {
        BBThisIsNoncopyableClass(UIVisualVisitor);
        public:
            explicit UIVisualVisitor(Point2 screenSize, bool visibleOnly);
            UIVisualVisitor(Point2 screenSize, const Matrix4& viewTransform, const Matrix4& projectionTransform, bool visibleOnly);
            UIVisualVisitor(Point2 screenSize, const Matrix4& viewTransform, const Matrix4& viewTransformInv, const Matrix4& projectionTransform, bool visibleOnly);
            virtual ~UIVisualVisitor();

            Vector2 Project(Vector2 point) const;
            Vector2 Unproject(Vector2 point) const;
            Vector2 UnprojectByParent(Vector2 point) const;

            void Project(Vector2& inOutPoint0, Vector2& inOutPoint1, Vector2& inOutPoint2, Vector2& inOutPoint3) const;
            void Project(Vector2* inOutPoints, int count) const;

            inline const RectF& GetViewport() const;
            inline float GetFieldOfView() const;
            inline bool GetVisibleOnly() const;

            inline UIVisual* GetCurrentVisual() const;
            inline float GetCurrentOpacity() const; 
            inline const RectF& GetCurrentBounds() const;
            inline const RectF& GetCurrentClippedBounds() const;
            inline const UIGeometryEffect* GetCurrentGeometryEffect() const;
            inline const Matrix4& GetCurrentTransform() const;

            inline const Matrix4& GetViewTransform() const;
            inline const Matrix4& GetProjectionTransform() const;

        protected:
            void Ready(UIVisual* target);
            void Visit(UIVisual* target);

            virtual void OnVisit() = 0;

        private:
            Vector2 UnprojectPoint(Vector2 point, const Matrix4& inversedTransform) const;

        private:
            Vector2 screenSize;
            float fieldOfView;
            bool visibleOnly;

            UIVisualPtr currentVisual;
            float currentOpacity;
            RectF currentBounds;
            RectF currentClippedBounds;
            UIGeometryEffectPtr currentGeometryEffect;
            Matrix4 currentTransform;
            Matrix4 currentTransformInv;
            Matrix4 parentTransform;
            Matrix4 parentTransformInv;
            Matrix4 viewTransform;
            Matrix4 viewTransformInv;
            Matrix4 projectionTransform;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    bool UIVisualVisitor::GetVisibleOnly() const
    {
        return visibleOnly;
    }

    UIVisual* UIVisualVisitor::GetCurrentVisual() const
    {
        return currentVisual;
    }

    float UIVisualVisitor::GetCurrentOpacity() const
    {
        return currentOpacity;
    }

    const RectF& UIVisualVisitor::GetCurrentBounds() const
    {
        return currentBounds;
    }

    const RectF& UIVisualVisitor::GetCurrentClippedBounds() const
    {
        return currentClippedBounds;
    }

    const UIGeometryEffect* UIVisualVisitor::GetCurrentGeometryEffect() const
    {
        return currentGeometryEffect;
    }

    const Matrix4& UIVisualVisitor::GetCurrentTransform() const
    {
        return currentTransform;
    }

    const Matrix4& UIVisualVisitor::GetViewTransform() const
    {
        return viewTransform;
    }

    const Matrix4& UIVisualVisitor::GetProjectionTransform() const
    {
        return projectionTransform;
    }
}

#endif