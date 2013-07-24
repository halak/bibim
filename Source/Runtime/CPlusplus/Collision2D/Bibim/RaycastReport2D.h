#pragma once
#ifndef __BIBIM_RAYCASTREPORT2D_H__
#define __BIBIM_RAYCASTREPORT2D_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Vector2.h>

    namespace Bibim
    {
        struct RaycastReport2D
        {
            Shape2D* ImpactShape;
            Vector2  ImpactPoint;
            Vector2  ImpactNormal;
            float    ImpactDistance;

            inline RaycastReport2D();
            inline RaycastReport2D(Shape2D* shape, const Vector2& point, const Vector2& normal, float distance);
            inline RaycastReport2D(const RaycastReport2D& original);

            inline RaycastReport2D& operator = (const RaycastReport2D& original);
            
            inline bool operator == (const RaycastReport2D& right) const;
            inline bool operator != (const RaycastReport2D& right) const;
        };

        class IRaycastCallback2D
        {
            public:
                virtual ~IRaycastCallback2D() { }
                virtual bool OnHit(float distanceSquared) = 0;
        };
    }

#endif