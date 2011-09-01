#pragma once
#ifndef __BIBIM_POINTSHAPE2D__
#define __BIBIM_POINTSHAPE2D__

#   include <Bibim/FWD.h>
#   include <Bibim/Shape2D.h>

    namespace Bibim
    {
        class PointShape2D : public Shape2D
        {
            public:
                PointShape2D();
                virtual ~PointShape2D();

                virtual bool Raycast(const Ray2D& ray, RaycastReport2D& outReport, IRaycastCallback2D* callback);
                virtual void AppendTo(std::list<Vector2>& vertices);
        };
    }

#endif