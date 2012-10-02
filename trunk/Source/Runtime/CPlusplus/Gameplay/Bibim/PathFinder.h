#pragma once
#ifndef __BIBIM_PATHFINDER_H__
#define __BIBIM_PATHFINDER_H__

#   include <Bibim/FWD.h>
#   include <Bibim/SharedObject.h>
#   include <Bibim/Point2.h>
#   include <vector>

    namespace Bibim
    {
        class PathFinder : public SharedObject
        {
            public:
                struct Node
                {
                    int X;
                    int Y;
                    int G;
                    int H;
                    bool IsOpened;
                    bool IsClosed;
                    Node* Parent;

                    Node(int x, int y)
                    {
                        X = x;
                        Y = y;
                        G = 0;
                        H = -1;
                        IsOpened = false;
                        IsClosed = false;
                        Parent = nullptr;
                    }

                    inline int GetF() const { return H >= 0 ? G + H : G; }
                };

                class IGrid
                {
                    public:
                        virtual ~IGrid() { }

                        virtual Node* GetNodeAt(int x, int y) = 0;
                        virtual bool IsWalkableAt(int x, int y) = 0;
                };

                BBForwardDeclareSmartPointerClass(Grid);

                typedef std::vector<Point2> Point2Collection;

            public:
                PathFinder();
                virtual ~PathFinder();

                virtual void Find(IGrid* grid, Point2 start, Point2 end, Point2Collection& outPath) = 0;
                Point2Collection Find(IGrid* grid, Point2 start, Point2 end);
        };
    }

#   include <Bibim/PathFinder.inl>

#endif