#include <Bibim/PCH.h>
#include <Bibim/Rect.h>
#include <Bibim/Math.h>

namespace Bibim
{
    Rect Rect::Intersect(const Rect& a, const Rect& b)
    {
        const int maximumLeft   = Math::Max(a.GetLeft(),   b.GetLeft());
        const int maximumTop    = Math::Max(a.GetTop(),    b.GetTop());
        const int minimumRight  = Math::Min(a.GetRight(),  b.GetRight());
        const int minimumBottom = Math::Min(a.GetBottom(), b.GetBottom());
        return Rect(Point(maximumLeft, maximumTop), 
                         Point(minimumRight, minimumBottom));

    }

    Rect Rect::Union(const Rect& a, const Rect& b)
    {
        const int minimumLeft   = Math::Min(a.GetLeft(),   b.GetLeft());
        const int minimumTop    = Math::Min(a.GetTop(),    b.GetTop());
        const int maximumRight  = Math::Max(a.GetRight(),  b.GetRight());
        const int maximumBottom = Math::Max(a.GetBottom(), b.GetBottom());
        return Rect(Point(minimumLeft, minimumTop), 
                         Point(maximumRight, maximumBottom));
    }

    const Rect Rect::Empty = Rect(0, 0, 0, 0);
}