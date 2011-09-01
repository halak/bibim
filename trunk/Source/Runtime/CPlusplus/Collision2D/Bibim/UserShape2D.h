#pragma once
#ifndef __BIBIM_USERSHAPE2D__
#define __BIBIM_USERSHAPE2D__

#   include <Bibim/FWD.h>
#   include <Bibim/Shape2D.h>

    namespace Bibim
    {
        class IUserShape2D
        {
            public:
                virtual ~IUserShape2D() { }

                virtual bool IntersectPoint(UserShape2D* userShape, Vector2 point) = 0;
                virtual bool IntersectSegment(UserShape2D* userShape, Vector2 start, Vector2 end) = 0;
                virtual bool IntersectSphere(UserShape2D* userShape, Vector2 center, float radius) = 0;
                virtual bool IntersectAxisAlignedBox(UserShape2D* userShape, Vector2 leftTop, Vector2 rightBottom) = 0;
                virtual bool IntersectBox(UserShape2D* userShape, Vector2 center, Vector2 orientation, Vector2 up, Vector2 extension) = 0;
                virtual bool IntersectUserShape(UserShape2D* userShape, IUserShape2D* other) = 0;
                virtual bool Raycast(UserShape2D* userShape, const Ray2D& ray, RaycastReport2D& outReport, IRaycastCallback2D* callback) = 0;
                virtual void AppendTo(UserShape2D* userShape, std::list<Vector2> points) = 0;
        };

        class UserShape2D : public Shape2D
        {
            public:
                UserShape2D();
                UserShape2D(IUserShape2DPtr userShape);
                virtual ~UserShape2D();

                IUserShape2DPtr GetUserShape();
                void SerUserShape(IUserShape2DPtr value);

                virtual bool Raycast(const Ray2D& ray, RaycastReport2D& outReport, IRaycastCallback2D* callback);
                virtual void AppendTo(std::list<Vector2>& vertices);

            private:
                IUserShape2DPtr userShape;
        };
    }

#endif