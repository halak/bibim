#pragma once
#ifndef __BIBIM_INTERSECTSHAPES2D_H__
#define __BIBIM_INTERSECTSHAPES2D_H__

#   include <Bibim/FWD.h>

    namespace Bibim
    {
        class IntersectShapes2D
        {
            BBThisIsStaticClass(IntersectShapes2D);
            public:
                static bool Test(Shape2D* left, Shape2D* right);

                static bool PointPoint(PointShape2D* left, PointShape2D* right);
                static bool PointSegment(PointShape2D* left, SegmentShape2D* right);
                static bool PointSphere(PointShape2D* left, SphereShape2D* right);
                static bool PointAxisAlignedBox(PointShape2D* left, AxisAlignedBoxShape2D* right);
                static bool PointBox(PointShape2D* left, BoxShape2D* right);
                static bool PointUserShape(PointShape2D* left, UserShape2D* right);

                static bool SegmentSegment(SegmentShape2D* left, SegmentShape2D* right);
                static bool SegmentSphere(SegmentShape2D* left, SphereShape2D* right);
                static bool SegmentAxisAlignedBox(SegmentShape2D* left, AxisAlignedBoxShape2D* right);
                static bool SegmentBox(SegmentShape2D* left, BoxShape2D* right);
                static bool SegmentUserShape(SegmentShape2D* left, UserShape2D* right);

                static bool SphereSphere(SphereShape2D* left, SphereShape2D* right);
                static bool SphereAxisAlignedBox(SphereShape2D* left, AxisAlignedBoxShape2D* right);
                static bool SphereBox(SphereShape2D* left, BoxShape2D* right);
                static bool SphereUserShape(SphereShape2D* left, UserShape2D* right);

                static bool AxisAlignedBoxAxisAlignedBox(AxisAlignedBoxShape2D* left, AxisAlignedBoxShape2D* right);
                static bool AxisAlignedBoxBox(AxisAlignedBoxShape2D* left, BoxShape2D* right);
                static bool AxisAlignedBoxUserShape(AxisAlignedBoxShape2D* left, UserShape2D* right);

                static bool BoxBox(BoxShape2D* left, BoxShape2D* right);
                static bool BoxUserShape(BoxShape2D* left, UserShape2D* right);

                static bool UserShapeUserShape(UserShape2D* left, UserShape2D* right);
        };
    }

#endif