#pragma once
#ifndef __BIBIM_SPHERESHAPE2D_H__
#define __BIBIM_SPHERESHAPE2D_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Shape2D.h>

    namespace Bibim
    {
        class SphereShape2D : public Shape2D
        {
            public:
                SphereShape2D();
                virtual ~SphereShape2D();

                float GetRadius() const;
                void  SetRadius(float value);

                float GetScaledRadius();
                float GetScaledRadiusSquared();

                virtual bool Raycast(const Ray2D& ray, RaycastReport2D& outReport, IRaycastCallback2D* callback);
                virtual void AppendTo(std::list<Vector2>& vertices);

            private:
                void UpdateParameters();

            private:
                float radius;
                float radiusSquared;
                float scaledRadius;
                float scaledRadiusSquared;
                unsigned int revision;
        };
    }

#endif