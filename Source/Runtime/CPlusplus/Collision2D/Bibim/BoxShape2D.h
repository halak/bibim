#pragma once
#ifndef __BIBIM_BOXSHAPE2D_H__
#define __BIBIM_BOXSHAPE2D_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Shape2D.h>

    namespace Bibim
    {
        class BoxShape2D : public Shape2D
        {
            BBComponentClass(BoxShape2D, Shape2D, 'O', 'B', 'S', '2');
            public:
                BoxShape2D();
                virtual ~BoxShape2D();

                inline Vector2 GetOrientation() const;
                void SetOrientation(Vector2 value);

                inline Vector2 GetExtension() const;
                void SetExtension(Vector2 value);

                Vector2 GetCenter();
                Vector2 GetRotatedOrientation();
                Vector2 GetRotatedUp();
                Vector2 GetScaledExtension();
                Vector2 GetP0();
                Vector2 GetP1();
                Vector2 GetP2();
                Vector2 GetP3();

                virtual bool Raycast(Vector2 origin, Vector2 direction, float length, RaycastReport2D& outReport, IRaycastCallback2D* callback);
                virtual void Build(Vertices& vertices);

                inline void SetOrientationXY(float x, float y);
                inline void SetExtensionXY(float x, float y);

            private:
                void UpdateParameters();

            private:
                Vector2 orientation;
                Vector2 extension;

                Vector2 center;
                Vector2 rotatedOrientation;
                Vector2 rotatedUp;
                Vector2 scaledExtension;
                Vector2 p0, p1, p2, p3;
                int revision;
        };   
    }

#endif