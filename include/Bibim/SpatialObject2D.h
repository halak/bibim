#pragma once
#ifndef __BIBIM_SPATIALOBJECT2D_H__
#define __BIBIM_SPATIALOBJECT2D_H__

#include <Bibim/FWD.h>
#include <Bibim/GameComponent.h>
#include <Bibim/Vector2.h>

namespace Bibim
{
    class SpatialObject2D : public Bibim::GameComponent
    {
        BBComponentClass(SpatialObject2D, GameComponent, 'S', 'P', '2', 'D');
        public:
            SpatialObject2D();
            virtual ~SpatialObject2D();

            inline Vector2 GetPosition() const;
            virtual void SetPosition(Vector2 value);
            inline float GetRotation() const;
            virtual void SetRotation(float value);
            inline float GetScale() const;
            virtual void SetScale(float value);

            inline Vector2 GetDirection() const;
            void SetDirection(Vector2 value);

            inline void SetPositionXY(float x, float y);

        private:
            Vector2 position;
            float rotation;
            float scale;
            Vector2 direction;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    Vector2 SpatialObject2D::GetPosition() const
    {
        return position;
    }

    float SpatialObject2D::GetRotation() const
    {
        return rotation;
    }

    float SpatialObject2D::GetScale() const
    {
        return scale;
    }

    Vector2 SpatialObject2D::GetDirection() const
    {
        return direction;
    }

    void SpatialObject2D::SetPositionXY(float x, float y)
    {
        SetPosition(Vector2(x, y));
    }
}

#endif