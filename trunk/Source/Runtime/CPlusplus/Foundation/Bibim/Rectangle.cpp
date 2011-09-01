#include <Bibim/PCH.h>
#include <Bibim/Rectangle.h>
#include <Bibim/Math.h>

namespace Bibim
{
    Rectangle Rectangle::Intersect(const Rectangle& a, const Rectangle& b)
    {
        const int maximumLeft   = Math::Max(a.GetLeft(),   b.GetLeft());
        const int maximumTop    = Math::Max(a.GetTop(),    b.GetTop());
        const int minimumRight  = Math::Min(a.GetRight(),  b.GetRight());
        const int minimumBottom = Math::Min(a.GetBottom(), b.GetBottom());
        return Rectangle(Point(maximumLeft, maximumTop), 
                         Point(minimumRight, minimumBottom));

    }

    Rectangle Rectangle::Union(const Rectangle& a, const Rectangle& b)
    {
        const int minimumLeft   = Math::Min(a.GetLeft(),   b.GetLeft());
        const int minimumTop    = Math::Min(a.GetTop(),    b.GetTop());
        const int maximumRight  = Math::Max(a.GetRight(),  b.GetRight());
        const int maximumBottom = Math::Max(a.GetBottom(), b.GetBottom());
        return Rectangle(Point(minimumLeft, minimumTop), 
                         Point(maximumRight, maximumBottom));
    }

    const Rectangle Rectangle::Empty = Rectangle(0, 0, 0, 0);
}