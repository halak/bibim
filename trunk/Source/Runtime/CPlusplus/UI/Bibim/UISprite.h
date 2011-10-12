#pragma once
#ifndef __BIBIM_UISPRITE_H__
#define __BIBIM_UISPRITE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIVisual.h>

    namespace Bibim
    {
        class UISprite : public UIVisual
        {
            BBCreatableObjectClass(UISprite, UIVisual, UIElement, 'U', 'S', 'P', 'R');
            public:
                UISprite();
                virtual ~UISprite();

                virtual Vector2 GetDesiredSize();

                inline UIImage* GetImage() const;
                void SetImage(UIImage* value);

                inline bool GetAutoResize() const;
                inline void SetAutoResize(bool value);

                inline bool GetHorizontalFlip() const;
                inline void SetHorizontalFlip(bool value);

                inline bool GetVerticalFlip() const;
                inline void SetVerticalFlip(bool value);

            protected:
                virtual void OnDraw(UIDrawingContext& context);

            private:
                UIImagePtr image;
                bool autoResize;
                bool horizontalFlip;
                bool verticalFlip;
        };
    }

#   include <Bibim/UISprite.inl>

#endif