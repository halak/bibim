namespace Bibim
{
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