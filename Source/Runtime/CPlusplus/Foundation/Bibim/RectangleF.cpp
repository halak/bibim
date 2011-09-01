#include <Bibim/PCH.h>
#include <Bibim/RectangleF.h>
#include <Bibim/Math.h>

namespace Bibim
{
    bool RectangleF::Intersects(const RectangleF& other) const
    {
        return GetRight() >= other.GetLeft() && GetLeft() <= GetRight() && GetBottom() >= other.GetTop() && GetTop() <= GetBottom();
    }

    RectangleF RectangleF::Intersect(const RectangleF& a, const RectangleF& b)
    {
        const float maximumLeft   = Math::Max(a.GetLeft(),   b.GetLeft());
        const float maximumTop    = Math::Max(a.GetTop(),    b.GetTop());
        const float minimumRight  = Math::Min(a.GetRight(),  b.GetRight());
        const float minimumBottom = Math::Min(a.GetBottom(), b.GetBottom());
        return RectangleF(Vector2(maximumLeft, maximumTop), 
                          Vector2(minimumRight, minimumBottom));

    }

    RectangleF RectangleF::Union(const RectangleF& a, const RectangleF& b)
    {
        const float minimumLeft   = Math::Min(a.GetLeft(),   b.GetLeft());
        const float minimumTop    = Math::Min(a.GetTop(),    b.GetTop());
        const float maximumRight  = Math::Max(a.GetRight(),  b.GetRight());
        const float maximumBottom = Math::Max(a.GetBottom(), b.GetBottom());
        return RectangleF(Vector2(minimumLeft, minimumTop), 
                          Vector2(maximumRight, maximumBottom));
    }

    const RectangleF RectangleF::Empty = RectangleF(0.0f, 0.0f, 0.0f, 0.0f);
}