#pragma once
#ifndef __BIBIM_UIIMAGE_H__
#define __BIBIM_UIIMAGE_H__

#include <Bibim/FWD.h>
#include <Bibim/UIVisual.h>

namespace Bibim
{
    class UIImage : public UIVisual
    {
        BBComponentClass(UIImage, UIVisual, 'U', 'I', 'M', 'G');
        public:
            UIImage();
            virtual ~UIImage();

            inline Image* GetSource() const;
            void SetSource(Image* value);

            Texture2D* GetTexture() const;
            void SetTexture(Texture2D* value);

            inline bool GetHorizontalFlip() const;
            inline void SetHorizontalFlip(bool value);

            inline bool GetVerticalFlip() const;
            inline void SetVerticalFlip(bool value);

            inline BitMask* GetMask() const;
            inline void SetMask(BitMask* value);

            virtual Vector2 GetContentSize();

        protected:
            virtual void OnDraw(UIDrawingContext& context);
            virtual void OnPick(UIPickingContext& context);

        private:
            ImagePtr source;
            bool horizontalFlip;
            bool verticalFlip;
            BitMaskPtr mask;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    Image* UIImage::GetSource() const
    {
        return source;
    }

    bool UIImage::GetHorizontalFlip() const
    {
        return horizontalFlip;
    }

    void UIImage::SetHorizontalFlip(bool value)
    {
        horizontalFlip = value;
    }

    bool UIImage::GetVerticalFlip() const
    {
        return verticalFlip;
    }

    void UIImage::SetVerticalFlip(bool value)
    {
        verticalFlip = value;
    }

    BitMask* UIImage::GetMask() const
    {
        return mask;
    }

    void UIImage::SetMask(BitMask* value)
    {
        mask = value;
    }
}

#endif