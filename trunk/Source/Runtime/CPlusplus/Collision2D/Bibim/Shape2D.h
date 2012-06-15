#pragma once
#ifndef __BIBIM_SHAPE2D_H__
#define __BIBIM_SHAPE2D_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameComponent.h>
#   include <Bibim/Vector2.h>
#   include <list>

    namespace Bibim
    {
        class Shape2D : public GameComponent
        {
            BBAbstractComponentClass(Shape2D, GameComponent);
            public:
                enum Type
                {
                    PointType,
                    SegmentType,
                    SphereType,
                    AxisAlignedBoxType,
                    BoxType,
                    UserType,
                };

            public:
                virtual ~Shape2D();

                inline Type GetType() const;

                inline Vector2 GetPosition() const;
                       void    SetPosition(Vector2 value);

                inline float GetRotation() const;
                       void  SetRotation(float value);

                inline float GetScale() const;
                       void  SetScale(float value);

                virtual bool Raycast(Vector2 origin, Vector2 dir, float length, RaycastReport2D& outReport, IRaycastCallback2D* callback) = 0;
                virtual void AppendTo(std::list<Vector2>& vertices) = 0;

                static bool Intersect(Shape2D* left, Shape2D* right);

            protected:
                Shape2D(Type type);

                inline int GetSpatialRevision() const;

            private:
                const Type type;

                Vector2 position;
                float   rotation;
                float   scale;
                int revision;

            private:
                Shape2D& operator = (const Shape2D&);
        };
    }

#   include <Bibim/Shape2D.inl>

#endif