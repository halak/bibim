#include <Bibim/PCH.h>
#include <Bibim/RectangleStorage.h>
#include <Bibim/Assert.h>
#include <algorithm>

namespace Bibim
{
    RectangleStorage::RectangleStorage()
        : width(0),
          height(0)
    {
    }

    RectangleStorage::RectangleStorage(int width, int height)
        : width(width),
          height(height)
    {
        Clear(width, height);
    }

    RectangleStorage::RectangleStorage(const RectangleStorage& original)
        : width(original.width),
          height(original.height),
          freeRectangles(original.freeRectangles),
          allocatedRectangles(original.allocatedRectangles)
    {
    }

    RectangleStorage::~RectangleStorage()
    {
    }

    void RectangleStorage::Clear()
    {
        Clear(width, height);
    }

    void RectangleStorage::Clear(int width, int height)
    {
        BBAssert(width > 0 && height > 0);

        this->width  = width;
        this->height = height;
        freeRectangles.clear();
        freeRectangles.push_back(Rectangle(0, 0, width, height));
        allocatedRectangles.clear();
    }

    Rectangle RectangleStorage::Allocate(int width, int height)
    {
        if (GetWidth() == 0 || GetHeight() == 0)
            return Rectangle::Empty;

        // 1. 빈 영역중에 크기 같은 영역이 있으면 바로 할당한다.
        // 2. 빈 영역중에 가로크기나, 세로크기가 같은것이 있으면 분할해 할당한다.
        // 3. 빈 영역중 가장 가까운 영역을 찾아서 분할해 할당한다.

        Rectangle nearest = Rectangle::Empty;
        RectangleCollection::iterator nearestIterator = freeRectangles.end();

        for (RectangleCollection::iterator it = freeRectangles.begin(); it != freeRectangles.end(); ++it)
        {
            const Rectangle current = (*it);

            if (current.Width == width && current.Height == height)
            {
                freeRectangles.erase(it);
                allocatedRectangles.push_back(current);
                return current;
            }

            if (current.Width == width && current.Height >= height)
            {
                Rectangle result = current;
                result.Height = height;
                (*it).Y += height;
                (*it).Height -= height;
                allocatedRectangles.push_back(result);
                return result;
            }

            if (current.Width >= width && current.Height == height)
            {
                Rectangle result = current;
                result.Width = width;
                (*it).X += width;
                (*it).Width -= width;
                allocatedRectangles.push_back(result);
                return result;
            }

            if (current.Width >= width && current.Height >= height)
            {
                if (nearest == Rectangle::Empty || (current.Width <= nearest.Width && current.Height <= nearest.Height))
                {
                    nearest = current;
                    nearestIterator = it;
                }
            }
        }

        if (nearest != Rectangle::Empty)
        {
            const int xPoints[3] =
            {
                nearest.GetLeft(),
                nearest.GetLeft() + width,
                nearest.GetRight(),
            };
            const int yPoints[3] =
            {
                nearest.GetTop(),
                nearest.GetTop() + height,
                nearest.GetBottom(),
            };

            const Rectangle leftUp  = Rectangle(Point(xPoints[0], yPoints[0]), Point(xPoints[1], yPoints[1]));
            const Rectangle rightUp = Rectangle(Point(xPoints[1], yPoints[0]), Point(xPoints[2], yPoints[1]));
            const Rectangle down    = Rectangle(Point(xPoints[0], yPoints[1]), Point(xPoints[2], yPoints[2]));

            freeRectangles.erase(nearestIterator);
            freeRectangles.push_back(rightUp);
            freeRectangles.push_back(down);
            allocatedRectangles.push_back(leftUp);

            return leftUp;
        }
        else
            return Rectangle::Empty;
    }

    void RectangleStorage::Deallocate(const Rectangle& rectangle)
    {
        RectangleCollection::iterator it = std::find(allocatedRectangles.begin(), allocatedRectangles.end(), rectangle);
        if (it != allocatedRectangles.end())
        {
            freeRectangles.push_front(rectangle);
            Merge(freeRectangles, freeRectangles.begin());
            allocatedRectangles.erase(it);
        }
    }

    void RectangleStorage::Merge(RectangleCollection& rectangles, RectangleCollection::iterator targetIterator)
    {
        // targetIterator와 통합 가능한 영역을 찾아서 통합하고,
        // 그렇게 통합된 영역을 다른 영역과 통합해보기 위해 Merge를 재귀호출한다.

        const Rectangle target = (*targetIterator);
        for (RectangleCollection::iterator it = rectangles.begin(); it != rectangles.end(); ++it)
        {
            if (it == targetIterator)
                continue;

            Rectangle& current = *it;

            if (current.GetLeft() == target.GetLeft() && current.GetRight() == target.GetRight())
            {
                if (current.GetTop() == target.GetBottom())
                {
                    current.SetTop(target.GetTop());
                    rectangles.erase(targetIterator);
                    Merge(rectangles, it);
                    return;
                }

                if (current.GetBottom() == target.GetTop())
                {
                    current.SetBottom(target.GetBottom());
                    rectangles.erase(targetIterator);
                    Merge(rectangles, it);
                    return;
                }
            }

            if (current.GetTop() == target.GetTop() && current.GetBottom() == target.GetBottom())
            {
                if (current.GetLeft() == target.GetRight())
                {
                    current.SetLeft(target.GetLeft());
                    rectangles.erase(targetIterator);
                    Merge(rectangles, it);
                    return;
                }

                if (current.GetRight() == target.GetLeft())
                {
                    current.SetRight(target.GetRight());
                    rectangles.erase(targetIterator);
                    Merge(rectangles, it);
                    return;
                }
            }
        }
    }

    int RectangleStorage::GetWidth() const
    {
        return width;
    }

    int RectangleStorage::GetHeight() const
    {
        return height;
    }

    const RectangleStorage::RectangleCollection& RectangleStorage::GetFreeRectangles() const
    {
        return freeRectangles;
    }

    const RectangleStorage::RectangleCollection& RectangleStorage::GetAllocatedRectangles() const
    {
        return allocatedRectangles;
    }

    RectangleStorage& RectangleStorage::operator = (const RectangleStorage& right)
    {
        width = right.width;
        height = right.height;
        freeRectangles = right.freeRectangles;
        allocatedRectangles = right.allocatedRectangles;
        return *this;
    }

    bool RectangleStorage::operator == (const RectangleStorage& right) const
    {
        return freeRectangles == right.freeRectangles &&
               allocatedRectangles == right.allocatedRectangles;
    }

    bool RectangleStorage::operator != (const RectangleStorage& right) const
    {
        return !operator == (right);
    }
}