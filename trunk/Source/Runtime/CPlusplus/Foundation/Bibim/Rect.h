#pragma once
#ifndef __BIBIM_RECT_H__
#define __BIBIM_RECT_H__

#   include <Bibim/Foundation.h>
#   include <Bibim/Point.h>

    namespace Bibim
    {
        struct Rect
        {
            int X;
            int Y;
            int Width;
            int Height;

            inline Rect();
            inline Rect(int x, int y, int width, int height);
            inline Rect(Point leftTop, Point rightBottom);
            inline Rect(const Rect& original);

            inline int GetLeft() const;
            inline int GetTop() const;
            inline int GetRight() const;
            inline int GetBottom() const;
            inline int GetCenter() const;
            inline int GetMiddle() const;
            inline Point GetCenterPoint() const;

            inline void SetLeft(int value);
            inline void SetTop(int value);
            inline void SetRight(int value);
            inline void SetBottom(int value);

            inline bool Contains(Point p) const;

            inline bool IsEmpty() const;

            inline Rect& operator = (const Rect& right);
            
            inline bool operator == (const Rect& right) const;
            inline bool operator != (const Rect& right) const;

            static Rect Intersect(const Rect& a, const Rect& b);
            static Rect Union(const Rect& a, const Rect& b);

            static const Rect Empty;
        };
    }

#   include <Bibim/Rect.inl>

#endif