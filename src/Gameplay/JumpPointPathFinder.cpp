#include <Bibim/Config.h>
#include <Bibim/JumpPointPathFinder.h>
#include <Bibim/Math.h>
#include <algorithm>

namespace Bibim
{
    struct OpenListPredicate
    {
        bool operator () (const PathFinder::Node* a, const PathFinder::Node* b) const
        {
            return a->GetF() > b->GetF();
        }
    };

    JumpPointPathFinder::JumpPointPathFinder()
    {
    }

    JumpPointPathFinder::~JumpPointPathFinder()
    {
    }
    
    void JumpPointPathFinder::Find(Grid* grid, Point2 start, Point2 end, Point2Collection& outPath)
    {
        if (grid == nullptr)
            return;

        this->grid = grid;
        this->start = start;
        this->end = end;

        Node* startNode = grid->GetNodeAt(start.X, start.Y);
        Node* endNode = grid->GetNodeAt(end.X, end.Y);
        openList.push_back(startNode);
        startNode->IsOpened = true;

        while (openList.empty() == false)
        {
            std::pop_heap(openList.begin(), openList.end(), OpenListPredicate());
            Node* node = openList.back();
            openList.pop_back();
            node->IsClosed = true;

            if (node == endNode)
            {
                outPath.clear();

                Node* currentNode = endNode;
                do
                {
                    outPath.push_back(Point2(currentNode->X, currentNode->Y));
                    currentNode = currentNode->Parent;
                } while (currentNode);

                std::reverse(outPath.begin(), outPath.end());
                return;
            }

            IdentifySuccessors(node);
        }

        outPath.clear();
    }

    void JumpPointPathFinder::IdentifySuccessors(Node* node)
    {
        const int x = node->X;
        const int y = node->Y;

        Point2Collection neighbors;
        FindNeighbors(node, neighbors);
        for (Point2Collection::const_iterator it = neighbors.begin(); it != neighbors.end(); ++it)
        {
            Point2 jumpPoint = Point2::Zero;
            if (Jump(Point2(x, y), *it, jumpPoint) == false)
                continue;

            Node* jumpNode = grid->GetNodeAt(jumpPoint.X, jumpPoint.Y);
            if (jumpNode->IsClosed)
                continue;

            const int distance = static_cast<int>(Point2::GetDistance(jumpPoint, Point2(x, y)));
            const int nextG = node->G + distance;

            if (jumpNode->IsOpened == false || nextG < jumpNode->G)
            {
                jumpNode->G = nextG;
                if (jumpNode->H < 0)
                    jumpNode->H = Math::Abs(jumpPoint.X - end.X) + Math::Abs(jumpPoint.Y - end.Y);
                jumpNode->Parent = node;

                if (jumpNode->IsOpened == false)
                {
                    openList.push_back(jumpNode);
                    std::push_heap(openList.begin(), openList.end(), OpenListPredicate());
                    jumpNode->IsOpened = true;
                }
                else
                    std::sort_heap(openList.begin(), openList.end(), OpenListPredicate());
            }
        }
    }

    bool JumpPointPathFinder::Jump(Point2 s, Point2 e, Point2& outResult) const
    {
        if (grid->IsWalkableAt(e.X, e.Y) == false)
            return false;
        else if (e == end)
        {
            outResult = e;
            return true;
        }

        const int dx = e.X - s.X;
        const int dy = e.Y - s.Y;
        if (dx != 0 && dy != 0)
        {
            if ((grid->IsWalkableAt(e.X - dx, e.Y + dy) && grid->IsWalkableAt(e.X - dx, e.Y) == false) ||
                (grid->IsWalkableAt(e.X + dx, e.Y - dy) && grid->IsWalkableAt(e.X, e.Y - dy) == false))
            {
                outResult = e;
                return true;
            }
        }
        else
        {
            if (dx != 0)
            {
                if ((grid->IsWalkableAt(e.X + dx, e.Y + 1) && grid->IsWalkableAt(e.X, e.Y + 1) == false) ||
                    (grid->IsWalkableAt(e.X + dx, e.Y - 1) && grid->IsWalkableAt(e.X, e.Y - 1) == false))
                {
                    outResult = e;
                    return true;
                }
            }
            else
            {
                if ((grid->IsWalkableAt(e.X + 1, e.Y + dy) && grid->IsWalkableAt(e.X + 1, e.Y) == false) ||
                    (grid->IsWalkableAt(e.X - 1, e.Y + dy) && grid->IsWalkableAt(e.X - 1, e.Y) == false))
                {
                    outResult = e;
                    return true;
                }
            }
        }

        if (dx != 0 && dy != 0)
        {
            Point2 t = Point2::Zero;
            if (Jump(e, Point2(e.X + dx, e.Y), t) ||
                Jump(e, Point2(e.X, e.Y + dy), t))
            {
                outResult = e;
                return true;
            }
        }

        if (grid->IsWalkableAt(e.X + dx, e.Y) || grid->IsWalkableAt(e.X, e.Y + dy))
            return Jump(e, Point2(e.X + dx, e.Y + dy), outResult);
        else
            return false;
    }

    void JumpPointPathFinder::FindNeighbors(Node* node, Point2Collection& outValues) const
    {
        const int x = node->X;
        const int y = node->Y;

        outValues.clear();

        if (node->Parent)
        {
            const int px = node->Parent->X;
            const int py = node->Parent->Y;
            const int dx = (x - px) / Math::Max(Math::Abs(x - px), 1);
            const int dy = (y - py) / Math::Max(Math::Abs(y - py), 1);

            if (dx != 0 && dy != 0)
            {
                const bool dxWalkable = grid->IsWalkableAt(x + dx, y);
                const bool dyWalkable = grid->IsWalkableAt(x, y + dy);

                if (dyWalkable)
                    outValues.push_back(Point2(x, y + dy));
                if (dxWalkable)
                    outValues.push_back(Point2(x + dx, y));
                if (dxWalkable || dyWalkable)
                    outValues.push_back(Point2(x + dx, y + dy));

                if (grid->IsWalkableAt(x - dx, y) == false && dyWalkable)
                    outValues.push_back(Point2(x - dx, y + dy));
                if (grid->IsWalkableAt(x, y - dy) == false && dxWalkable)
                    outValues.push_back(Point2(x + dx, y - dy));
            }
            else
            {
                if (dx == 0)
                {
                    if (grid->IsWalkableAt(x, y + dy))
                    {
                        outValues.push_back(Point2(x, y + dy));

                        if (grid->IsWalkableAt(x + 1, y) == false)
                            outValues.push_back(Point2(x + 1, y + dy));
                        if (grid->IsWalkableAt(x - 1, y) == false)
                            outValues.push_back(Point2(x - 1, y + dy));
                    }
                }
                else
                {
                    if (grid->IsWalkableAt(x + dx, y))
                    {
                        outValues.push_back(Point2(x + dx, y));

                        if (grid->IsWalkableAt(x, y + 1) == false)
                            outValues.push_back(Point2(x + dx, y + 1));
                        if (grid->IsWalkableAt(x, y - 1) == false)
                            outValues.push_back(Point2(x + dx, y - 1));
                    }
                }
            }
        }
        else
        {
            bool d0 = false;
            bool d1 = false;
            bool d2 = false;
            bool d3 = false;

            if (grid->IsWalkableAt(x, y - 1))
            {
                outValues.push_back(Point2(x, y - 1));
                d0 = true;
                d1 = true;
            }

            if (grid->IsWalkableAt(x + 1, y))
            {
                outValues.push_back(Point2(x + 1, y));
                d1 = true;
                d2 = true;
            }

            if (grid->IsWalkableAt(x, y + 1))
            {
                outValues.push_back(Point2(x, y + 1));
                d2 = true;
                d3 = true;
            }

            if (grid->IsWalkableAt(x - 1, y))
            {
                outValues.push_back(Point2(x - 1, y));
                d3 = true;
                d0 = true;
            }

            if (d0 && grid->IsWalkableAt(x - 1, y - 1))
                outValues.push_back(Point2(x - 1, y - 1));
            
            if (d1 && grid->IsWalkableAt(x + 1, y - 1))
                outValues.push_back(Point2(x + 1, y - 1));
            
            if (d2 && grid->IsWalkableAt(x + 1, y + 1))
                outValues.push_back(Point2(x + 1, y + 1));

            if (d3 && grid->IsWalkableAt(x - 1, y + 1))
                outValues.push_back(Point2(x - 1, y + 1));
        }
    }
}