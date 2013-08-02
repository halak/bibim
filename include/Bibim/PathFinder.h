#pragma once
#ifndef __BIBIM_PATHFINDER_H__
#define __BIBIM_PATHFINDER_H__

#include <Bibim/FWD.h>
#include <Bibim/SharedObject.h>
#include <Bibim/Point2.h>
#include <vector>

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

            BBForwardDeclareSmartPointerClass(Grid);
            class Grid
            {
                public:
                    virtual ~Grid() { }

                    virtual Node* GetNodeAt(int x, int y) = 0;
                    virtual bool IsWalkableAt(int x, int y) = 0;
            };

            typedef std::vector<Point2> Point2Collection;

        public:
            PathFinder();
            virtual ~PathFinder();

            virtual void Find(Grid* grid, Point2 start, Point2 end, Point2Collection& outPath) = 0;
            Point2Collection Find(Grid* grid, Point2 start, Point2 end);
    };
}

#endif