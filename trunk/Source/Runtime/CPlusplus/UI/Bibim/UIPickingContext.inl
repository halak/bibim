namespace Bibim
{
    bool UIPickingContext::Contains(const RectF& bounds)
    {
        return bounds.Contains(currentPoint);
    }

    Vector2 UIPickingContext::GetPoint() const
    {
        return point;
    }

    Vector2 UIPickingContext::GetCurrentPoint() const
    {
        return currentPoint;
    }

    UIVisual* UIPickingContext::GetResult() const
    {
        return result;
    }
}