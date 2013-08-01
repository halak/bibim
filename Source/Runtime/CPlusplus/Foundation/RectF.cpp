#include <Bibim/Config.h>
#include <Bibim/RectF.h>
#include <Bibim/Math.h>

namespace Bibim
{
    bool RectF::Intersects(const RectF& other) const
    {
        return GetRight() >= other.GetLeft() && GetLeft() <= GetRight() && GetBottom() >= other.GetTop() && GetTop() <= GetBottom();
    }

    RectF RectF::Intersect(const RectF& a, const RectF& b)
    {
        const float maximumLeft   = Math::Max(a.GetLeft(),   b.GetLeft());
        const float maximumTop    = Math::Max(a.GetTop(),    b.GetTop());
        const float minimumRight  = Math::Min(a.GetRight(),  b.GetRight());
        const float minimumBottom = Math::Min(a.GetBottom(), b.GetBottom());
        return RectF(Vector2(maximumLeft, maximumTop), 
                     Vector2(minimumRight, minimumBottom));

    }

    RectF RectF::Union(const RectF& a, const RectF& b)
    {
        const float minimumLeft   = Math::Min(a.GetLeft(),   b.GetLeft());
        const float minimumTop    = Math::Min(a.GetTop(),    b.GetTop());
        const float maximumRight  = Math::Max(a.GetRight(),  b.GetRight());
        const float maximumBottom = Math::Max(a.GetBottom(), b.GetBottom());
        return RectF(Vector2(minimumLeft, minimumTop), 
                     Vector2(maximumRight, maximumBottom));
    }

    const RectF RectF::Empty = RectF(0.0f, 0.0f, 0.0f, 0.0f);
}