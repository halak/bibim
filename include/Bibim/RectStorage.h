#pragma once
#ifndef __BIBIM_RECTSTORAGE_H__
#define __BIBIM_RECTSTORAGE_H__

#include <Bibim/FWD.h>
#include <Bibim/Rect.h>
#include <list>

namespace Bibim
{
    class RectStorage
    {
        public:
            typedef std::list<Rect> RectCollection;

        public:
            RectStorage();
            RectStorage(int width, int height);
            RectStorage(const RectStorage& original);
            ~RectStorage();

            void Clear();
            void Clear(int width, int height);

            Rect Allocate(int width, int height);
            void Deallocate(const Rect& rect);

            int GetWidth() const;
            int GetHeight() const;

            const RectCollection& GetFreeRects() const;
            const RectCollection& GetAllocatedRects() const;

            RectStorage& operator = (const RectStorage& right);

            bool operator == (const RectStorage& right) const;
            bool operator != (const RectStorage& right) const;

        private:
            static void Merge(RectCollection& rects, RectCollection::iterator targetIterator);

        private:
            int width;
            int height;
            RectCollection freeRects;
            RectCollection allocatedRects;
    };
}

#endif