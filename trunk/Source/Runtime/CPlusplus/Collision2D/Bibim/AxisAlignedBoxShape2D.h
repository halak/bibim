#pragma once
#ifndef __BIBIM_AXISALIGNEDBOXSHAPE2D__
#define __BIBIM_AXISALIGNEDBOXSHAPE2D__

#   include <Bibim/Shape2D.h>

    namespace Bibim
    {
        class AxisAlignedBoxShape2D : public Shape2D
        {
            public:
                AxisAlignedBoxShape2D();
                virtual ~AxisAlignedBoxShape2D();

                Vector2 GetMin() const;
                void    SetMin(Vector2 value);

                Vector2 GetMax() const;
                void    SetMax(Vector2 value);

                Vector2 GetScaledMin();
                Vector2 GetScaledMax();

                virtual bool Raycast(Vector2 origin, Vector2 direction, RaycastReport2D& outReport, RaycastCallback2D* callback);
                virtual void AppendTo(std::list<Vector2>& vertices);

            private:
                void UpdateParameters();

            private:
                Vector2 min;
                Vector2 max;
                Vector2 scaledMin;
                Vector2 scaledMax;
                unsigned int revision;
        };
    }

#endif