#pragma once
#ifndef __BIBIM_POINTSHAPE2D__
#define __BIBIM_POINTSHAPE2D__

#   include <Bibim/FWD.h>
#   include <Bibim/Shape2D.h>

    namespace Bibim
    {
        class PointShape2D : public Shape2D
        {
            BBComponentClass(PointShape2D, Shape2D, 'P', 'T', 'S', '2');
            public:
                PointShape2D();
                virtual ~PointShape2D();

                virtual bool Raycast(Vector2 origin, Vector2 direction, float length, RaycastReport2D& outReport, IRaycastCallback2D* callback);
                virtual void Build(Vertices& vertices);
        };
    }

#endif