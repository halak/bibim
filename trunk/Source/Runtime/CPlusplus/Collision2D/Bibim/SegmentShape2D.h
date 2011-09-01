#pragma once
#ifndef __BIBIM_SEGMENTSHAPE2D_H__
#define __BIBIM_SEGMENTSHAPE2D_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Shape2D.h>

    namespace Bibim
    {
        class SegmentShape2D : public Shape2D
        {
            public:
                SegmentShape2D();
                virtual ~SegmentShape2D();

                Vector2 GetDirection() const;
                void SetDirection(Vector2 value);

                float GetFrontLength() const;
                void SetFrontLength(float value);

                float GetBackLength() const;
                void SetBackLength(float value);

                float GetLength() const;

                Vector2 GetStartPoint();
                Vector2 GetEndPoint();
                Vector2 GetRotatedDirection();

                virtual bool Raycast(const Ray2D& ray, RaycastReport2D& outReport, IRaycastCallback2D* callback);
                virtual void AppendTo(std::list<Vector2>& vertices);

            private:
                void UpdateParameters();

            private:
                Vector2 direction;
                float frontLength;
                float backLength;

                Vector2 startPoint;
                Vector2 endPoint;
                Vector2 rotatedDirection;
                unsigned int revision;
        };
    }

#endif