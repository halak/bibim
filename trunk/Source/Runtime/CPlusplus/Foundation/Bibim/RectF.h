#pragma once
#ifndef __BIBIM_RECTF_H__
#define __BIBIM_RECTF_H__

#   include <Bibim/Foundation.h>
#   include <Bibim/Vector2.h>

    namespace Bibim
    {
        struct RectF
        {
            float X;
            float Y;
            float Width;
            float Height;

            inline RectF();
            inline RectF(float x, float y, float width, float height);
            inline RectF(int x, int y, int width, int height);
            inline RectF(Vector2 leftTop, Vector2 rightBottom);
            inline RectF(const RectF& original);

            inline float GetLeft() const;
            inline float GetTop() const;
            inline float GetRight() const;
            inline float GetBottom() const;
            inline float GetCenter() const;
            inline float GetMiddle() const;
            inline Vector2 GetCenterPoint() const;

            inline void SetLeft(float value);
            inline void SetTop(float value);
            inline void SetRight(float value);
            inline void SetBottom(float value);

            inline void Inflate(float all);
            inline void Inflate(float horizontal, float vertical);
            inline void Inflate(float left, float top, float right, float bottom);

            inline bool Contains(Vector2 p) const;
            bool Intersects(const RectF& other) const;

            inline bool IsEmpty() const;

            inline RectF& operator = (const RectF& right);
            
            inline bool operator == (const RectF& right) const;
            inline bool operator != (const RectF& right) const;

            static RectF Intersect(const RectF& a, const RectF& b);
            static RectF Union(const RectF& a, const RectF& b);

            static const RectF Empty;
        };

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        RectF::RectF()
            : X(0.0f), Y(0.0f), Width(0.0f), Height(0.0f)
        {
        }

        RectF::RectF(float x, float y, float width, float height)
            : X(x), Y(y), Width(width), Height(height)
        {
        }

        RectF::RectF(int x, int y, int width, int height)
            : X(static_cast<float>(x)), Y(static_cast<float>(y)), Width(static_cast<float>(width)), Height(static_cast<float>(height))
        {
        }

        RectF::RectF(Vector2 leftTop, Vector2 rightBottom)
            : X(leftTop.X),
              Y(leftTop.Y),
              Width(rightBottom.X - leftTop.X),
              Height(rightBottom.Y - leftTop.Y)
        {
        }

        RectF::RectF(const RectF& original)
            : X(original.X), Y(original.Y), Width(original.Width), Height(original.Height)
        {
        }

        float RectF::GetLeft() const
        {
            return X;
        }

        float RectF::GetTop() const
        {
            return Y;
        }

        float RectF::GetRight() const
        {
            return X + Width;
        }

        float RectF::GetBottom() const
        {
            return Y + Height;
        }

        float RectF::GetCenter() const
        {
            return X + Width * 0.5f;
        }

        float RectF::GetMiddle() const
        {
            return Y + Height * 0.5f;
        }

        Vector2 RectF::GetCenterPoint() const
        {
            return Vector2(GetCenter(), GetMiddle());
        }

        void RectF::SetLeft(float value)
        {
            const float right = GetRight();

            X = value;
            Width = right - X;
        }

        void RectF::SetTop(float value)
        {
            const float bottom = GetBottom();

            Y = value;
            Height = bottom - Y;
        }

        void RectF::SetRight(float value)
        {
            Width = value - X;
        }

        void RectF::SetBottom(float value)
        {
            Height = value - Y;
        }

        void RectF::Inflate(float all)
        {
            Inflate(all, all, all, all);
        }

        void RectF::Inflate(float horizontal, float vertical)
        {
            Inflate(horizontal, vertical, horizontal, vertical);
        }

        void RectF::Inflate(float left, float top, float right, float bottom)
        {
            X -= left;
            Y -= top;
            Width += left + right;
            Height += top + bottom;
        }

        bool RectF::Contains(Vector2 p) const
        {
            return GetLeft() <= p.X && p.X <= GetRight() &&
                   GetTop()  <= p.Y && p.Y <= GetBottom();
        }

        bool RectF::IsEmpty() const
        {
            return Width == 0.0f || Height == 0.0f;
        }

        RectF& RectF::operator = (const RectF& right)
        {
            X      = right.X;
            Y      = right.Y;
            Width  = right.Width;
            Height = right.Height;
            return *this;
        }

        bool RectF::operator == (const RectF& right) const
        {
            return X == right.X && Y == right.Y && Width == right.Width && Height == right.Height;
        }

        bool RectF::operator != (const RectF& right) const
        {
            return !operator == (right);
        }
    }

#endif