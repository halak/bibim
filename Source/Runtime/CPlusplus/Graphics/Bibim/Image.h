#pragma once
#ifndef __BIBIM_IMAGE_H__
#define __BIBIM_IMAGE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameAsset.h>
#   include <Bibim/Rect.h>
#   include <Bibim/RectF.h>
#   include <Bibim/String.h>

    namespace Bibim
    {
        class Image : public GameAsset
        {
            BBSerializableAssetClass(SourceTexture2D, Texture2D, 'G', 'I', 'M', 'G');
            public:
                Image(const String& textureURI, const Rect& clippingRect);
                Image(Texture2D* texture);
                Image(Texture2D* texture, const Rect& clippingRect);
                virtual ~Image();

                void Setup(Texture2D* texture);

                inline const String& GetTextureURI() const;
                inline const Rect& GetClippingRect() const;
                inline const RectF& GetNormalizedClippingRect() const;
                inline Texture2D* GetTexture() const;

            private:
                Image();
                Image(const String& textureURI, const Rect& clippingRect, Texture2D* texture);

            private:
                String textureURI;
                Rect clippingRect;
                RectF normalizedClippingRect;
                Texture2DPtr texture;
        };
    }

#   include <Bibim/Image.inl>

#endif