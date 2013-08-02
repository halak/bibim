#pragma once
#ifndef __BIBIM_COLLISION2D_H__
#define __BIBIM_COLLISION2D_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameModule.h>
#   include <Bibim/Listeners.h>
#   include <vector>

    namespace Bibim
    {
        class CollisionSpace2D : public GameModule
        {
            BBModuleClass(CollisionSpace2D, GameModule, 'C', 'O', 'S', '2');
            public:
                class IEventListener
                {
                    public:
                        virtual ~IEventListener() { }
                        virtual void OnIntersected(Shape2D* shapeA, Shape2D* shapeB, int groupA, int groupB) = 0;
                };

                typedef std::vector<Shape2DPtr> ShapeCollection;

            public:
                CollisionSpace2D();
                virtual ~CollisionSpace2D();

                int Detect();

                bool Raycast(Vector2 origin, Vector2 direction, float length, int group, RaycastReport2D& outReport);

                void Add(Shape2D* shape, int group);
                void Remove(Shape2D* shape);
                inline void Clear();
                inline void Clear(int group);
                bool Find(Shape2D* shape, int* outGroup, int* outIndex) const;

                void AddListener(IEventListener* item);
                void AddListener(IEventListener* item, SharedObject* object);
                bool RemoveListener(IEventListener* item);

                int  GetGroup(Shape2D* shape) const;
                void SetGroup(Shape2D* shape, int group);

                inline int GetNumberOfGroups() const;
                void SetNumberOfGroups(int numberOfGroups);

                inline bool GetCollisionRelationship(int groupA, int groupB) const;
                inline void SetCollisionRelationship(int groupA, int groupB, bool detectable);

                inline const ShapeCollection& GetShapes(int group) const;

            private:
                typedef std::vector<bool> BooleanCollection;

                inline Shape2D* GetShapeUnsafely(int group, int index) const;

                int  Detect(ShapeCollection& groupA, ShapeCollection& groupB, int groupANumber, int groupBNumber);
                void Detect(Shape2D* shapeA, Shape2D* shapeB, int groupA, int groupB);

            private:
                std::vector<ShapeCollection>   shapes;
                std::vector<BooleanCollection> collisionRelationships;
                Listeners<IEventListener> listeners;
        };

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        void CollisionSpace2D::Clear()
        {
            shapes.clear();
        }

        void CollisionSpace2D::Clear(int group)
        {
            shapes.at(group).clear();
        }

        int CollisionSpace2D::GetNumberOfGroups() const
        {
            return static_cast<int>(shapes.size());
        }

        bool CollisionSpace2D::GetCollisionRelationship(int groupA, int groupB) const
        {
            return collisionRelationships.at(groupA).at(groupB);
        }

        void CollisionSpace2D::SetCollisionRelationship(int groupA, int groupB, bool detectable)
        {
            collisionRelationships.at(groupA).at(groupB) = detectable;
            collisionRelationships.at(groupB).at(groupA) = detectable;
        }

        const CollisionSpace2D::ShapeCollection& CollisionSpace2D::GetShapes(int group) const
        {
            return shapes.at(group);
        }
    }

#endif