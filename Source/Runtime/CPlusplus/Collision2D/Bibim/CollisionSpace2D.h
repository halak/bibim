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

            public:
                CollisionSpace2D();
                virtual ~CollisionSpace2D();

                int Detect();

                bool Raycast(Vector2 origin, Vector2 direction, float length, int group, RaycastReport2D& outReport);

                void Add(Shape2D* shape, int group);
                void Remove(Shape2D* shape);
                void Clear();
                void Clear(int group);
                bool Find(Shape2D* shape, int* outGroup, int* outIndex) const;

                void AddListener(IEventListener* item);
                void AddListener(IEventListener* item, SharedObject* object);
                bool RemoveListener(IEventListener* item);

                int  GetGroup(Shape2D* shape) const;
                void SetGroup(Shape2D* shape, int group);

                int  GetNumberOfGroups() const;
                void SetNumberOfGroups(int numberOfGroups);

                bool GetCollisionRelationship(int groupA, int groupB) const;
                void SetCollisionRelationship(int groupA, int groupB, bool detectable);

            private:
                typedef std::vector<Shape2DPtr> ShapeCollection;
                typedef std::vector<bool>       BooleanCollection;

                int  Detect(ShapeCollection& groupA, ShapeCollection& groupB, int groupANumber, int groupBNumber);
                void Detect(Shape2D* shapeA, Shape2D* shapeB, int groupA, int groupB);

            private:
                std::vector<ShapeCollection>   shapes;
                std::vector<BooleanCollection> collisionRelationships;
                Listeners<IEventListener> listeners;
        };
    }

#endif