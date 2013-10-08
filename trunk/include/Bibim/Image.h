#pragma once
#ifndef __BIBIM_IMAGE_H__
#define __BIBIM_IMAGE_H__

#include <Bibim/FWD.h>
#include <Bibim/GameAsset.h>
#include <Bibim/Rect.h>
#include <Bibim/RectF.h>
#include <Bibim/String.h>

namespace Bibim
{
    class Image : public GameAsset
    {
        BBSerializableAssetClass(Image, GameAsset, 'G', 'I', 'M', 'G');
        public:
            enum Transform
            {
                Identity,
                RotateCW90,
            };

        public:
            Image(const String& textureURI, const Rect& clippingRect);
            Image(Texture2D* texture);
            Image(Texture2D* texture, const Rect& clippingRect);
            // for drawing
            Image(Texture2D* texture, const RectF& normalizedClippingRect, Transform appliedTransform);
            virtual ~Image();

            void Setup(Texture2D* texture);

            inline const String& GetTextureURI() const;
            inline const Rect& GetClippingRect() const;
            inline const RectF& GetNormalizedClippingRect() const;
            inline Transform GetAppliedTransform() const;
            inline int GetWidth() const;
            inline int GetHeight() const;
            inline Texture2D* GetTexture() const;

        public:
            static Image* Create(ComponentStreamReader& reader);
            static RectF CalculateNormalizedRect(const Rect& clippingRect, Texture2D* texture);

        private:
            Image();
            Image(const String& textureURI, const Rect& clippingRect, Transform appliedTransform, Texture2D* texture);

        private:
            Texture2DPtr texture;
            Rect clippingRect;
            RectF normalizedClippingRect;
            Transform appliedTransform;
            String textureURI;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    const String& Image::GetTextureURI() const
    {
        return textureURI;
    }

    const Rect& Image::GetClippingRect() const
    {
        return clippingRect;
    }
    
    const RectF& Image::GetNormalizedClippingRect() const
    {
        return normalizedClippingRect;
    }

    Image::Transform Image::GetAppliedTransform() const
    {
        return appliedTransform;
    }

    int Image::GetWidth() const
    {
        return appliedTransform == Identity ? clippingRect.Width : clippingRect.Height;
    }

    int Image::GetHeight() const
    {
        return appliedTransform == Identity ? clippingRect.Height : clippingRect.Width;
    }

    Texture2D* Image::GetTexture() const
    {
        return texture;
    }
}

#endif