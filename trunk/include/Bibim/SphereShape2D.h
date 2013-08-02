#pragma once
#ifndef __BIBIM_SPHERESHAPE2D_H__
#define __BIBIM_SPHERESHAPE2D_H__

#include <Bibim/FWD.h>
#include <Bibim/Shape2D.h>

namespace Bibim
{
    class SphereShape2D : public Shape2D
    {
        BBComponentClass(SphereShape2D, Shape2D, 'S', 'P', 'S', '2');
        public:
            SphereShape2D();
            virtual ~SphereShape2D();

            float GetRadius() const;
            void  SetRadius(float value);

            float GetScaledRadius();
            float GetScaledRadiusSquared();

            virtual bool Raycast(Vector2 origin, Vector2 direction, float length, RaycastReport2D& outReport, IRaycastCallback2D* callback);
            virtual void Build(Vertices& vertices);

        private:
            void UpdateParameters();

        private:
            float radius;
            float radiusSquared;
            float scaledRadius;
            float scaledRadiusSquared;
            int revision;
    };
}

#endif