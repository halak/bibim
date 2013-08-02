#pragma once
#ifndef __BIBIM_AXISALIGNEDBOXSHAPE2D__
#define __BIBIM_AXISALIGNEDBOXSHAPE2D__

#include <Bibim/Shape2D.h>

namespace Bibim
{
    class AxisAlignedBoxShape2D : public Shape2D
    {
        BBComponentClass(AxisAlignedBoxShape2D, Shape2D, 'A', 'B', 'S', '2');
        public:
            AxisAlignedBoxShape2D();
            virtual ~AxisAlignedBoxShape2D();

            inline Vector2 GetMin() const;
            void SetMin(Vector2 value);

            inline Vector2 GetMax() const;
            void SetMax(Vector2 value);

            Vector2 GetScaledMin();
            Vector2 GetScaledMax();

            virtual bool Raycast(Vector2 origin, Vector2 direction, float length, RaycastReport2D& outReport, IRaycastCallback2D* callback);
            virtual void Build(Vertices& vertices);

            inline void SetMinXY(float x, float y);
            inline void SetMaxXY(float x, float y);

        private:
            void UpdateParameters();

        private:
            Vector2 min;
            Vector2 max;
            Vector2 scaledMin;
            Vector2 scaledMax;
            int revision;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    Vector2 AxisAlignedBoxShape2D::GetMin() const
    {
        return min;
    }

    Vector2 AxisAlignedBoxShape2D::GetMax() const
    {
        return max;
    }

    void AxisAlignedBoxShape2D::SetMinXY(float x, float y)
    {
        SetMin(Vector2(x, y));
    }

    void AxisAlignedBoxShape2D::SetMaxXY(float x, float y)
    {
        SetMax(Vector2(x, y));
    }
}

#endif