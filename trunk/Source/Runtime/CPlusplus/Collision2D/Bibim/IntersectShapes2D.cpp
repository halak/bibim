#include <Bibim/Config.h>
#include <Bibim/AxisAlignedBoxShape2D.h>
#include <Bibim/BoxShape2D.h>
#include <Bibim/Geom2D.h>
#include <Bibim/IntersectShapes2D.h>
#include <Bibim/Math.h>
#include <Bibim/PointShape2D.h>
#include <Bibim/SegmentShape2D.h>
#include <Bibim/Shape2D.h>
#include <Bibim/SphereShape2D.h>
#include <Bibim/UserShape2D.h>

namespace Bibim
{
    typedef bool (*F)(Shape2D*, Shape2D*);
    static const F IntersectFunctionTable[6][6] =
    {
        { (F)IntersectShapes2D::PointPoint, (F)IntersectShapes2D::PointSegment,   (F)IntersectShapes2D::PointSphere,   (F)IntersectShapes2D::PointAxisAlignedBox,          (F)IntersectShapes2D::PointBox,          (F)IntersectShapes2D::PointUserShape          },
        { nullptr,                          (F)IntersectShapes2D::SegmentSegment, (F)IntersectShapes2D::SegmentSphere, (F)IntersectShapes2D::SegmentAxisAlignedBox,        (F)IntersectShapes2D::SegmentBox,        (F)IntersectShapes2D::SegmentUserShape        },
        { nullptr,                          nullptr,                              (F)IntersectShapes2D::SphereSphere,  (F)IntersectShapes2D::SphereAxisAlignedBox,         (F)IntersectShapes2D::SphereBox,         (F)IntersectShapes2D::SphereUserShape         },
        { nullptr,                          nullptr,                              nullptr,                             (F)IntersectShapes2D::AxisAlignedBoxAxisAlignedBox, (F)IntersectShapes2D::AxisAlignedBoxBox, (F)IntersectShapes2D::AxisAlignedBoxUserShape },
        { nullptr,                          nullptr,                              nullptr,                             nullptr,                                            (F)IntersectShapes2D::BoxBox,            (F)IntersectShapes2D::BoxUserShape            },
        { nullptr,                          nullptr,                              nullptr,                             nullptr,                                            nullptr,                                 (F)IntersectShapes2D::UserShapeUserShape      },
    };

    bool IntersectShapes2D::Test(Shape2D* left, Shape2D* right)
    {
        if (left == nullptr || right == nullptr)
            return false;

        if (static_cast<int>(left->GetType()) < static_cast<int>(right->GetType()))
            return IntersectFunctionTable[left->GetType()][right->GetType()](left, right);
        else
            return IntersectFunctionTable[right->GetType()][left->GetType()](right, left);
    }

    bool IntersectShapes2D::PointPoint(PointShape2D* left, PointShape2D* right)
    {
        return Math::Equals(left->GetPosition(), right->GetPosition());
    }

    bool IntersectShapes2D::PointSegment(PointShape2D* left, SegmentShape2D* right)
    {
        return Geom2D::IntersectPointSegment(left->GetPosition(), right->GetStartPoint(), right->GetEndPoint());
    }

    bool IntersectShapes2D::PointSphere(PointShape2D* left, SphereShape2D* right)
    {
        return Vector2::GetDistanceSquared(left->GetPosition(), right->GetPosition()) <= right->GetScaledRadiusSquared();
    }

    bool IntersectShapes2D::PointAxisAlignedBox(PointShape2D* left, AxisAlignedBoxShape2D* right)
    {
        const Vector2 point = left->GetPosition();
        const Vector2 min = right->GetScaledMin();
        const Vector2 max = right->GetScaledMax(); 

        return min.X <= point.X && point.X <= max.X &&
               min.Y <= point.Y && point.Y <= max.Y;
    }

    bool IntersectShapes2D::PointBox(PointShape2D* left, BoxShape2D* right)
    {
        return Geom2D::IntersectPointBox(left->GetPosition(), right->GetCenter(), right->GetRotatedOrientation(), right->GetRotatedUp(), right->GetScaledExtension());
    }

    bool IntersectShapes2D::PointUserShape(PointShape2D* left, UserShape2D* right)
    {
        return right->IntersectPoint(left->GetPosition());
    }

    bool IntersectShapes2D::SegmentSegment(SegmentShape2D* left, SegmentShape2D* right)
    {
        return Geom2D::IntersectSegmentSegment(left->GetStartPoint(), left->GetEndPoint(), right->GetStartPoint(), right->GetEndPoint());
    }

    bool IntersectShapes2D::SegmentSphere(SegmentShape2D* left, SphereShape2D* right)
    {
        return Geom2D::GetPointSegmentDistanceSquared(right->GetPosition(), left->GetStartPoint(), left->GetEndPoint()) <= right->GetScaledRadiusSquared();
    }

    bool IntersectShapes2D::SegmentAxisAlignedBox(SegmentShape2D* left, AxisAlignedBoxShape2D* right)
    {
        return Geom2D::IntersectSegmentAxisAlignedBox(left->GetStartPoint(), left->GetEndPoint(), right->GetScaledMin(), right->GetScaledMax());
    }

    bool IntersectShapes2D::SegmentBox(SegmentShape2D* /*left*/, BoxShape2D* /*right*/)
    {
        return false;
    }

    bool IntersectShapes2D::SegmentUserShape(SegmentShape2D* left, UserShape2D* right)
    {
        return right->IntersectSegment(left->GetStartPoint(), left->GetEndPoint());
    }

    bool IntersectShapes2D::SphereSphere(SphereShape2D* left, SphereShape2D* right)
    {
        const float scaledRadiusSum = left->GetScaledRadius() + right->GetScaledRadius();
        return Vector2::GetDistanceSquared(left->GetPosition(), right->GetPosition()) <= (scaledRadiusSum * scaledRadiusSum);
    }

    bool IntersectShapes2D::SphereAxisAlignedBox(SphereShape2D* left, AxisAlignedBoxShape2D* right)
    {
        return Geom2D::GetPointAxisAlignedBoxDistanceSquared(left->GetPosition(), right->GetScaledMin(), right->GetScaledMax()) <= left->GetScaledRadiusSquared();
    }

    bool IntersectShapes2D::SphereBox(SphereShape2D* left, BoxShape2D* right)
    {
        const Vector2 closestPoint = Geom2D::GetPointBoxClosestPoint(left->GetPosition(), right->GetCenter(), right->GetRotatedOrientation(), right->GetRotatedUp(), right->GetScaledExtension());
        return Vector2::GetDistanceSquared(closestPoint, left->GetPosition()) <= left->GetScaledRadiusSquared();
    }

    bool IntersectShapes2D::SphereUserShape(SphereShape2D* left, UserShape2D* right)
    {
        return right->IntersectSphere(left->GetPosition(), left->GetScaledRadius());
    }

    bool IntersectShapes2D::AxisAlignedBoxAxisAlignedBox(AxisAlignedBoxShape2D* left, AxisAlignedBoxShape2D* right)
    {
        return Geom2D::IntersectAxisAlignedBoxAxisAlignedBox(left->GetScaledMin(), left->GetScaledMax(), right->GetScaledMax(), right->GetScaledMax());
    }

    bool IntersectShapes2D::AxisAlignedBoxBox(AxisAlignedBoxShape2D* /*left*/, BoxShape2D* /*right*/)
    {
        return false;
    }

    bool IntersectShapes2D::AxisAlignedBoxUserShape(AxisAlignedBoxShape2D* left, UserShape2D* right)
    {
        return right->IntersectAxisAlignedBox(left->GetScaledMin(), left->GetScaledMax());
    }

    bool IntersectShapes2D::BoxBox(BoxShape2D* left, BoxShape2D* right)
    {
        return Geom2D::IntersectBoxBox(left->GetCenter(), left->GetRotatedOrientation(), left->GetScaledExtension(), right->GetCenter(), right->GetRotatedOrientation(), right->GetScaledExtension());;
    }

    bool IntersectShapes2D::BoxUserShape(BoxShape2D* left, UserShape2D* right)
    {
        return right->IntersectBox(left->GetCenter(), left->GetRotatedOrientation(), left->GetRotatedUp(), left->GetExtension());
    }

    bool IntersectShapes2D::UserShapeUserShape(UserShape2D* left, UserShape2D* right)
    {
        return left->IntersectUserShape(right);
    }
}