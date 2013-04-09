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
    }

#   include <Bibim/RectF.inl>

#endif