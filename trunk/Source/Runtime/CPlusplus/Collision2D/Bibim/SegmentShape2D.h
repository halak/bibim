#pragma once
#ifndef __BIBIM_SEGMENTSHAPE2D_H__
#define __BIBIM_SEGMENTSHAPE2D_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Shape2D.h>

    namespace Bibim
    {
        class SegmentShape2D : public Shape2D
        {
            BBComponentClass(SegmentShape2D, Shape2D, 'S', 'G', 'S', '2');
            public:
                SegmentShape2D();
                virtual ~SegmentShape2D();

                inline Vector2 GetDirection() const;
                void SetDirection(Vector2 value);

                inline float GetFrontLength() const;
                void SetFrontLength(float value);

                inline float GetBackLength() const;
                void SetBackLength(float value);

                inline float GetLength() const;

                Vector2 GetStartPoint();
                Vector2 GetEndPoint();
                Vector2 GetRotatedDirection();

                virtual bool Raycast(Vector2 origin, Vector2 direction, float length, RaycastReport2D& outReport, IRaycastCallback2D* callback);
                virtual void Build(Vertices& vertices);

            private:
                void UpdateParameters();

            private:
                Vector2 direction;
                float frontLength;
                float backLength;

                Vector2 startPoint;
                Vector2 endPoint;
                Vector2 rotatedDirection;
                int revision;
        };

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        Vector2 SegmentShape2D::GetDirection() const
        {
            return direction;
        }

        float SegmentShape2D::GetFrontLength() const
        {
            return frontLength;
        }

        float SegmentShape2D::GetBackLength() const
        {
            return backLength;
        }

        float SegmentShape2D::GetLength() const
        {
            return GetFrontLength() + GetBackLength();
        }
    }

#endif