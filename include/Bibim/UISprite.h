#pragma once
#ifndef __BIBIM_UISPRITE_H__
#define __BIBIM_UISPRITE_H__

#include <Bibim/FWD.h>
#include <Bibim/UIVisual.h>
#include <Bibim/IUpdateable.h>
#include <Bibim/Sprite.h>

namespace Bibim
{
    class UISprite : public UIVisual
    {
        BBComponentClass(UISprite, UIVisual, 'U', 'S', 'P', 'R');
        public:
            UISprite();
            virtual ~UISprite();

            const Sprite::Keyframe* GetCurrentFrame() const;

            inline Sprite* GetSource() const;
            void SetSource(Sprite* value);

            inline float GetSpeed() const;
            void SetSpeed(float value);

            inline float GetTime() const;
            void SetTime(float value);

            inline int GetFrameIndex() const;
            void SetFrameIndex(int value);

            inline bool GetHorizontalFlip() const;
            inline void SetHorizontalFlip(bool value);

            inline bool GetVerticalFlip() const;
            inline void SetVerticalFlip(bool value);

            inline Timeline* GetTimeline() const;
            void SetTimeline(Timeline* value);

            virtual Vector2 GetContentSize();

        protected:
                    void OnStep(float dt, int timestamp);
            virtual void OnDraw(UIDrawingContext& context);

        private:
            void UpdateOrigin();

            class Updater : public IUpdateable
            {
                public:
                    UISprite* Owner;

                    virtual ~Updater();

                    virtual void Update(float dt, int timestamp);
            };

        private:
            SpritePtr source;
            float speed;
            float time;
            int frameIndex;
            bool horizontalFlip;
            bool verticalFlip;
            Timeline* timeline;
            Updater updater;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    Sprite* UISprite::GetSource() const
    {
        return source;
    }

    float UISprite::GetSpeed() const
    {
        return speed;
    }

    float UISprite::GetTime() const
    {
        return time;
    }

    int UISprite::GetFrameIndex() const
    {
        return frameIndex;
    }

    bool UISprite::GetHorizontalFlip() const
    {
        return horizontalFlip;
    }

    void UISprite::SetHorizontalFlip(bool value)
    {
        horizontalFlip = value;
    }

    bool UISprite::GetVerticalFlip() const
    {
        return verticalFlip;
    }

    void UISprite::SetVerticalFlip(bool value)
    {
        verticalFlip = value;
    }

    Timeline* UISprite::GetTimeline() const
    {
        return timeline;
    }
}

#endif