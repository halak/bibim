#pragma once
#ifndef __BIBIM_IMAGE_H__
#define __BIBIM_IMAGE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameAsset.h>
#   include <Bibim/Rect.h>
#   include <Bibim/RectF.h>

    namespace Bibim
    {
        class Image : public GameAsset
        {
            BBSerializableAssetClass(SourceTexture2D, Texture2D, 'G', 'I', 'M', 'G');
            public:
                Image(const URI& textureURI, const Rect& clippingRect);
                virtual ~Image();

                void SetRealTextureData(Texture2D* texture);
                void SetRealTextureData(Texture2D* texture, const Rect& clippingRect);

                inline const URI& GetTextureURI() const;
                inline const Rect& GetClippingRect() const;

                inline Texture2D* GetRealTexture() const;
                inline const Rect& GetRealClippingRect() const;
                inline const RectF& GetNormalizedRealClippingRect() const;

                inline uint GetRevision() const;

            private:
                Image();

            private:
                URI textureURI;
                Rect clippingRect;
                Texture2DPtr realTexture;
                Rect realClippingRect;
                RectF normalizedRealClippingRect;
                uint revision;
        };
    }

#   include <Bibim/Image.inl>

#endif