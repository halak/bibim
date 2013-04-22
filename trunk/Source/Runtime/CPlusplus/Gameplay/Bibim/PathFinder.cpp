#include <Bibim/Config.h>
#include <Bibim/PathFinder.h>

namespace Bibim
{
    PathFinder::PathFinder()
    {
    }

    PathFinder::~PathFinder()
    {
    }

    PathFinder::Point2Collection PathFinder::Find(Grid* grid, Point2 start, Point2 end)
    {
        Point2Collection result;
        Find(grid, start, end, result);
        return result;
    }
}