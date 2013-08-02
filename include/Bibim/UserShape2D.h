#pragma once
#ifndef __BIBIM_USERSHAPE2D__
#define __BIBIM_USERSHAPE2D__

#include <Bibim/FWD.h>
#include <Bibim/Shape2D.h>

namespace Bibim
{
    class UserShape2D : public Shape2D
    {
        BBAbstractComponentClass(UserShape2D, Shape2D);
        public:
            virtual ~UserShape2D();

            virtual bool IntersectPoint(Vector2 point) = 0;
            virtual bool IntersectSegment(Vector2 start, Vector2 end) = 0;
            virtual bool IntersectSphere(Vector2 center, float radius) = 0;
            virtual bool IntersectAxisAlignedBox(Vector2 leftTop, Vector2 rightBottom) = 0;
            virtual bool IntersectBox(Vector2 center, Vector2 orientation, Vector2 up, Vector2 extension) = 0;
            virtual bool IntersectUserShape(UserShape2D* other) = 0;

        protected:
            UserShape2D();
    };
}

#endif