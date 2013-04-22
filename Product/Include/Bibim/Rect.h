#pragma once
#ifndef __BIBIM_RECT_H__
#define __BIBIM_RECT_H__

#   include <Bibim/Foundation.h>
#   include <Bibim/Point2.h>

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
            inline Rect(Point2 leftTop, Point2 rightBottom);
            inline Rect(const Rect& original);

            inline int GetLeft() const;
            inline int GetTop() const;
            inline int GetRight() const;
            inline int GetBottom() const;
            inline int GetCenter() const;
            inline int GetMiddle() const;
            inline Point2 GetCenterPoint() const;

            inline void SetLeft(int value);
            inline void SetTop(int value);
            inline void SetRight(int value);
            inline void SetBottom(int value);

            inline bool Contains(Point2 p) const;

            inline bool IsEmpty() const;

            inline Rect& operator = (const Rect& right);
            
            inline bool operator == (const Rect& right) const;
            inline bool operator != (const Rect& right) const;

            static Rect Intersect(const Rect& a, const Rect& b);
            static Rect Union(const Rect& a, const Rect& b);

            static const Rect Empty;
        };

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        Rect::Rect()
            : X(0), Y(0), Width(0), Height(0)
        {
        }

        Rect::Rect(int x, int y, int width, int height)
            : X(x), Y(y), Width(width), Height(height)
        {
        }

        Rect::Rect(Point2 leftTop, Point2 rightBottom)
            : X(leftTop.X),
              Y(leftTop.Y),
              Width(rightBottom.X - leftTop.X),
              Height(rightBottom.Y - leftTop.Y)
        {
        }

        Rect::Rect(const Rect& original)
            : X(original.X), Y(original.Y), Width(original.Width), Height(original.Height)
        {
        }

        int Rect::GetLeft() const
        {
            return X;
        }

        int Rect::GetTop() const
        {
            return Y;
        }

        int Rect::GetRight() const
        {
            return X + Width;
        }

        int Rect::GetBottom() const
        {
            return Y + Height;
        }

        int Rect::GetCenter() const
        {
            return X + Width / 2;
        }

        int Rect::GetMiddle() const
        {
            return Y + Height / 2;
        }

        Point2 Rect::GetCenterPoint() const
        {
            return Point2(GetCenter(), GetMiddle());
        }

        void Rect::SetLeft(int value)
        {
            const int right = GetRight();

            X = value;
            Width = right - X;
        }

        void Rect::SetTop(int value)
        {
            const int bottom = GetBottom();

            Y = value;
            Height = bottom - Y;
        }

        void Rect::SetRight(int value)
        {
            Width = value - X;
        }

        void Rect::SetBottom(int value)
        {
            Height = value - Y;
        }

        bool Rect::Contains(Point2 p) const
        {
            return GetLeft() <= p.X && p.X <= GetRight() &&
                   GetTop()  <= p.Y && p.Y <= GetBottom();
        }

        bool Rect::IsEmpty() const
        {
            return Width == 0 || Height == 0;
        }

        Rect& Rect::operator = (const Rect& right)
        {
            X      = right.X;
            Y      = right.Y;
            Width  = right.Width;
            Height = right.Height;
            return *this;
        }

        bool Rect::operator == (const Rect& right) const
        {
            return X == right.X && Y == right.Y && Width == right.Width && Height == right.Height;
        }

        bool Rect::operator != (const Rect& right) const
        {
            return !operator == (right);
        }
    }

#endif