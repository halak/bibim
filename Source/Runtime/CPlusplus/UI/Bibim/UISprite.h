#pragma once
#ifndef __BIBIM_UISPRITE_H__
#define __BIBIM_UISPRITE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIVisual.h>

    namespace Bibim
    {
        class UISprite : public UIVisual
        {
            BBComponentClass(UISprite, UIVisual, 'U', 'S', 'P', 'R');
            public:
                UISprite();
                virtual ~UISprite();

                inline Image* GetImage() const;
                void SetImage(Image* value);

                inline bool GetAutoResize() const;
                inline void SetAutoResize(bool value);

                inline bool GetHorizontalFlip() const;
                inline void SetHorizontalFlip(bool value);

                inline bool GetVerticalFlip() const;
                inline void SetVerticalFlip(bool value);

                inline BitMask* GetMask() const;
                inline void SetMask(BitMask* value);

            protected:
                virtual void OnDraw(UIDrawingContext& context);
                virtual void OnPick(UIPickingContext& context);

            private:
                ImagePtr image;
                bool autoResize;
                bool horizontalFlip;
                bool verticalFlip;
                BitMaskPtr mask;
        };
    }

#   include <Bibim/UISprite.inl>

#endif