#pragma once
#ifndef __BIBIM_RECTANGLEF_H__
#define __BIBIM_RECTANGLEF_H__

#   include <Bibim/Foundation.h>
#   include <Bibim/Vector2.h>

    namespace Bibim
    {
        struct RectangleF
        {
            float X;
            float Y;
            float Width;
            float Height;

            inline RectangleF();
            inline RectangleF(float x, float y, float width, float height);
            inline RectangleF(int x, int y, int width, int height);
            inline RectangleF(Vector2 leftTop, Vector2 rightBottom);
            inline RectangleF(const RectangleF& original);

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

            inline bool Contains(Vector2 p) const;
            bool Intersects(const RectangleF& other) const;

            inline bool IsEmpty() const;

            inline RectangleF& operator = (const RectangleF& original);
            
            inline bool operator == (const RectangleF& right) const;
            inline bool operator != (const RectangleF& right) const;

            static RectangleF Intersect(const RectangleF& a, const RectangleF& b);
            static RectangleF Union(const RectangleF& a, const RectangleF& b);

            static const RectangleF Empty;
        };
    }

#   include <Bibim/RectangleF.inl>

#endif