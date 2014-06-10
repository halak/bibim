#pragma once
#ifndef __BIBIM_UIFORCEGRIDEFFECT_H__
#define __BIBIM_UIFORCEGRIDEFFECT_H__

#include <Bibim/FWD.h>
#include <Bibim/UIGeometryEffect.h>
#include <Bibim/IUpdateable.h>
#include <Bibim/Timeline.h>
#include <vector>

namespace Bibim
{
    class UIForceGridEffect : public UIGeometryEffect
    {
        BBComponentClass(UIForceGridEffect, UIGeometryEffect, 'U', 'F', 'G', 'E');

        static const float DefaultDampingValue;
        static const float DefaultTargetLengthFactor;
        static const float DefaultPerspectiveProjectionFactor;
        static const float HighSpeedFixedFrameTime;
        static const float LowSpeedFixedFrameTime;

        public:
            enum FrameSpeed
            {
                High,
                Low,
            };

        public:
            UIForceGridEffect();
            UIForceGridEffect(Rect size, Vector2 spacing);
            virtual ~UIForceGridEffect();

            void InitializeXY(int width, int height, float spacingX, float spacingY);
            void Initialize(Rect size, Vector2 spacing);
                        
            inline Timeline* GetTimeline() const;
            void SetTimeline(Timeline* value);

            inline FrameSpeed GetFrameSpeed() const;
            void SetFrameSpeed(FrameSpeed value);

            void ApplyDirectedForce2D(float forceX, float forceY, float positionX, float positionY, float radius);
            //void ApplyDirectedForce3D(float forceX, float forceY, float forceZ, float positionX, float positionY, float positionZ, float radius);
            void ApplyImplosiveForce2D(float force, float positionX, float positionY, float radius);
            void ApplyImplosiveForce3D(float force, float positionX, float positionY, float positionZ, float radius);
            void ApplyExplosiveForce2D(float force, float positionX, float positionY, float radius);
            void ApplyExplosiveForce3D(float force, float positionX, float positionY, float positionZ, float radius);

            void ApplyDirectedForce(Vector2 force, Vector2 position, float radius);
            void ApplyDirectedForce(Vector3 force, Vector3 position, float radius);
            void ApplyImplosiveForce(float force, Vector2 position, float radius);
            void ApplyImplosiveForce(float force, Vector3 position, float radius);
            void ApplyExplosiveForce(float force, Vector2 position, float radius);
            void ApplyExplosiveForce(float force, Vector3 position, float radius);

            virtual void DrawQuad(UIRenderer* renderer, Vector2* p, Color color);
            virtual void DrawQuad(UIRenderer* renderer, Vector2* p, Color color, Vector2* uv,  Texture2D* texture);
            virtual void DrawQuad(UIRenderer* renderer, Vector2* p, Color color, Vector2* uv1, Texture2D* texture1, Vector2* uv2, Texture2D* texture2);

            virtual void DrawQuad(UIRenderer* renderer, Vector2* p, Color color, RectF clippingRect, Texture2D* texture);
            virtual void DrawQuad(UIRenderer* renderer, Vector2* p, Color color, RectF clippingRect, Texture2D* texture1, Vector2* uv2, Texture2D* texture2);

        public:
            static FrameSpeed ConvertFromStringToFrameSpeed(const char* value);
            static const char* ConvertFromFrameSpeedToString(FrameSpeed value);                

        protected:
            void OnStep(float dt, int timestamp);

        private:
            class PointMass
            {
                public:
                    PointMass();
                    PointMass(Vector3 position, float invMass);
                    ~PointMass();

                    inline void Update();

                    inline void ApplyForce(Vector3 force);
                    inline void IncreaseDamping(float factor);

                public:
                    Vector3 position;
                    Vector3 velocity;
                    float inverseMass;

                private:
                    Vector3 acceleration;
                    float damping;
            };

            struct Spring
            {
                public:
                    Spring(PointMass* end1, PointMass* end2, float stiffness, float damping);
                    ~Spring();

                    inline void Update();

                public:
                    PointMass* end1;
                    PointMass* end2;
                    float targetLength;
                    float stiffness;
                    float damping;
            };

            class Updater : public IUpdateable
            {
                public:
                    Updater();
                    virtual ~Updater();

                    virtual void Update(float dt, int timestamp);

                public:
                    UIForceGridEffect* o;
            };

        private:
            typedef std::vector<Spring> SpringCollection;
            typedef std::vector<PointMass> PointMassGridCollection;

            //Vector2 TranslateCoordinate(Vector3 pos, Point2 screenSize, Vector2* p);
            Vector2 TranslateCoordinate(Vector3 pos, Vector2* p);
            //static Vector2 PerspectiveVector(Vector3 v, Point2 screenSize);

            inline int GetPointIndex(int x, int y) const;

        private:
            Timeline* timeline;
            Updater updater;
            Rect size;
            Vector2 spacing;
            SpringCollection springs;
            PointMassGridCollection points;
            PointMassGridCollection fixedPoints;
            int cols;
            int rows;
            float frameTime;
            FrameSpeed frameSpeed;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    Timeline* UIForceGridEffect::GetTimeline() const
    {
        return timeline;
    }

    UIForceGridEffect::FrameSpeed UIForceGridEffect::GetFrameSpeed() const
    {
        return frameSpeed;
    }

    int UIForceGridEffect::GetPointIndex(int x, int y) const
    {
        return x + (y * cols);
    }
}

BBBindLuaEnum(Bibim::UIForceGridEffect::FrameSpeed,
              Bibim::UIForceGridEffect::ConvertFromStringToFrameSpeed,
              Bibim::UIForceGridEffect::ConvertFromFrameSpeedToString);

#endif