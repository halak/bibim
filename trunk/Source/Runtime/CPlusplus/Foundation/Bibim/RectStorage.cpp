#include <Bibim/PCH.h>
#include <Bibim/RectStorage.h>
#include <Bibim/Assert.h>
#include <algorithm>

namespace Bibim
{
    RectStorage::RectStorage()
        : width(0),
          height(0)
    {
    }

    RectStorage::RectStorage(int width, int height)
        : width(width),
          height(height)
    {
        Clear(width, height);
    }

    RectStorage::RectStorage(const RectStorage& original)
        : width(original.width),
          height(original.height),
          freeRects(original.freeRects),
          allocatedRects(original.allocatedRects)
    {
    }

    RectStorage::~RectStorage()
    {
    }

    void RectStorage::Clear()
    {
        Clear(width, height);
    }

    void RectStorage::Clear(int width, int height)
    {
        BBAssert(width > 0 && height > 0);

        this->width  = width;
        this->height = height;
        freeRects.clear();
        freeRects.push_back(Rect(0, 0, width, height));
        allocatedRects.clear();
    }

    Rect RectStorage::Allocate(int width, int height)
    {
        if (GetWidth() == 0 || GetHeight() == 0)
            return Rect::Empty;

        // 1. �� �����߿� ũ�� ���� ������ ������ �ٷ� �Ҵ��Ѵ�.
        // 2. �� �����߿� ����ũ�⳪, ����ũ�Ⱑ �������� ������ ������ �Ҵ��Ѵ�.
        // 3. �� ������ ���� ����� ������ ã�Ƽ� ������ �Ҵ��Ѵ�.

        Rect nearest = Rect::Empty;
        RectCollection::iterator nearestIterator = freeRects.end();

        for (RectCollection::iterator it = freeRects.begin(); it != freeRects.end(); ++it)
        {
            const Rect current = (*it);

            if (current.Width == width && current.Height == height)
            {
                freeRects.erase(it);
                allocatedRects.push_back(current);
                return current;
            }

            if (current.Width == width && current.Height >= height)
            {
                Rect result = current;
                result.Height = height;
                (*it).Y += height;
                (*it).Height -= height;
                allocatedRects.push_back(result);
                return result;
            }

            if (current.Width >= width && current.Height == height)
            {
                Rect result = current;
                result.Width = width;
                (*it).X += width;
                (*it).Width -= width;
                allocatedRects.push_back(result);
                return result;
            }

            if (current.Width >= width && current.Height >= height)
            {
                if (nearest == Rect::Empty || (current.Width <= nearest.Width && current.Height <= nearest.Height))
                {
                    nearest = current;
                    nearestIterator = it;
                }
            }
        }

        if (nearest != Rect::Empty)
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

            const Rect leftUp  = Rect(Point2(xPoints[0], yPoints[0]), Point2(xPoints[1], yPoints[1]));
            const Rect rightUp = Rect(Point2(xPoints[1], yPoints[0]), Point2(xPoints[2], yPoints[1]));
            const Rect down    = Rect(Point2(xPoints[0], yPoints[1]), Point2(xPoints[2], yPoints[2]));

            freeRects.erase(nearestIterator);
            freeRects.push_back(rightUp);
            freeRects.push_back(down);
            allocatedRects.push_back(leftUp);

            return leftUp;
        }
        else
            return Rect::Empty;
    }

    void RectStorage::Deallocate(const Rect& Rect)
    {
        RectCollection::iterator it = std::find(allocatedRects.begin(), allocatedRects.end(), Rect);
        if (it != allocatedRects.end())
        {
            freeRects.push_front(Rect);
            Merge(freeRects, freeRects.begin());
            allocatedRects.erase(it);
        }
    }

    void RectStorage::Merge(RectCollection& Rects, RectCollection::iterator targetIterator)
    {
        // targetIterator�� ���� ������ ������ ã�Ƽ� �����ϰ�,
        // �׷��� ���յ� ������ �ٸ� ������ �����غ��� ���� Merge�� ���ȣ���Ѵ�.

        const Rect target = (*targetIterator);
        for (RectCollection::iterator it = Rects.begin(); it != Rects.end(); ++it)
        {
            if (it == targetIterator)
                continue;

            Rect& current = *it;

            if (current.GetLeft() == target.GetLeft() && current.GetRight() == target.GetRight())
            {
                if (current.GetTop() == target.GetBottom())
                {
                    current.SetTop(target.GetTop());
                    Rects.erase(targetIterator);
                    Merge(Rects, it);
                    return;
                }

                if (current.GetBottom() == target.GetTop())
                {
                    current.SetBottom(target.GetBottom());
                    Rects.erase(targetIterator);
                    Merge(Rects, it);
                    return;
                }
            }

            if (current.GetTop() == target.GetTop() && current.GetBottom() == target.GetBottom())
            {
                if (current.GetLeft() == target.GetRight())
                {
                    current.SetLeft(target.GetLeft());
                    Rects.erase(targetIterator);
                    Merge(Rects, it);
                    return;
                }

                if (current.GetRight() == target.GetLeft())
                {
                    current.SetRight(target.GetRight());
                    Rects.erase(targetIterator);
                    Merge(Rects, it);
                    return;
                }
            }
        }
    }

    int RectStorage::GetWidth() const
    {
        return width;
    }

    int RectStorage::GetHeight() const
    {
        return height;
    }

    const RectStorage::RectCollection& RectStorage::GetFreeRects() const
    {
        return freeRects;
    }

    const RectStorage::RectCollection& RectStorage::GetAllocatedRects() const
    {
        return allocatedRects;
    }

    RectStorage& RectStorage::operator = (const RectStorage& right)
    {
        width = right.width;
        height = right.height;
        freeRects = right.freeRects;
        allocatedRects = right.allocatedRects;
        return *this;
    }

    bool RectStorage::operator == (const RectStorage& right) const
    {
        return freeRects == right.freeRects &&
               allocatedRects == right.allocatedRects;
    }

    bool RectStorage::operator != (const RectStorage& right) const
    {
        return !operator == (right);
    }
}