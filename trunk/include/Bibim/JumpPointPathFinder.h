#pragma once
#ifndef __BIBIM_JUMPPOINTPATHFINDER_H__
#define __BIBIM_JUMPPOINTPATHFINDER_H__

#include <Bibim/FWD.h>
#include <Bibim/PathFinder.h>

namespace Bibim
{
    class JumpPointPathFinder : public PathFinder
    {
        public:
            JumpPointPathFinder();
            virtual ~JumpPointPathFinder();

            virtual void Find(Grid* grid, Point2 start, Point2 end, Point2Collection& outPath);

        private:
            void IdentifySuccessors(Node* node);
            bool Jump(Point2 s, Point2 e, Point2& outResult) const;
            void FindNeighbors(Node* node, Point2Collection& outValues) const;

        private:
            Grid* grid;
            Point2 start;
            Point2 end;
            std::vector<Node*> openList;
    };
}

#endif