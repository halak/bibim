#include <Bibim/PCH.h>
#include <Bibim/Point2.h>
#include <Bibim/Math.h>

namespace Bibim
{
    const Point2 Point2::Zero = Point2(0, 0);

    float Point2::GetDistance(Point2 a, Point2 b)
    {
        return Math::Sqrt(static_cast<float>(GetDistanceSquared(a, b)));
    }

    int Point2::GetDistanceSquared(Point2 a, Point2 b)
    {
        return (b.X - a.X) * (b.X - a.X) + (b.Y - a.Y) * (b.Y - a.Y);
    }
}