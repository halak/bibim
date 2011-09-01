#pragma once
#ifndef __BIBIM_RECTANGLE_H__
#define __BIBIM_RECTANGLE_H__

#   include <Bibim/Foundation.h>
#   include <Bibim/Point.h>

    namespace Bibim
    {
        struct Rectangle
        {
            int X;
            int Y;
            int Width;
            int Height;

            inline Rectangle();
            inline Rectangle(int x, int y, int width, int height);
            inline Rectangle(Point leftTop, Point rightBottom);
            inline Rectangle(const Rectangle& original);

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

            inline Rectangle& operator = (const Rectangle& original);
            
            inline bool operator == (const Rectangle& right) const;
            inline bool operator != (const Rectangle& right) const;

            static Rectangle Intersect(const Rectangle& a, const Rectangle& b);
            static Rectangle Union(const Rectangle& a, const Rectangle& b);

            static const Rectangle Empty;
        };
    }

#   include <Bibim/Rectangle.inl>

#endif