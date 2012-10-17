#pragma once
#ifndef __BIBIM_SHAPE2D_H__
#define __BIBIM_SHAPE2D_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameComponent.h>
#   include <Bibim/Vector2.h>
#   include <list>
#   include <vector>

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

                class Vertices
                {
                    public:
                        virtual ~Vertices() = 0 { };

                        virtual void Append(Vector2 p0) = 0;
                        virtual void Append(Vector2 p0, Vector2 p1) = 0;
                        virtual void Append(Vector2 p0, Vector2 p1, Vector2 p2) = 0;
                        virtual void Append(Vector2 p0, Vector2 p1, Vector2 p2, Vector2 p3) = 0;
                        virtual void Append(const std::vector<Vector2>& p) = 0;
                };

                class SimpleVertices : public Vertices
                {
                    public:
                        SimpleVertices();
                        virtual ~SimpleVertices();

                        void Clear();

                        virtual void Append(Vector2 p0);
                        virtual void Append(Vector2 p0, Vector2 p1);
                        virtual void Append(Vector2 p0, Vector2 p1, Vector2 p2);
                        virtual void Append(Vector2 p0, Vector2 p1, Vector2 p2, Vector2 p3);
                        virtual void Append(const std::vector<Vector2>& p);

                        inline const std::list<Vector2>& GetData() const;

                    private:
                        std::list<Vector2> v;
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
                virtual void Build(Vertices& vertices) = 0;

                static bool Intersect(Shape2D* left, Shape2D* right);

                inline float GetPositionX() const;
                inline float GetPositionY() const;
                inline void SetPositionXY(float x, float y);

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