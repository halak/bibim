#pragma once
#ifndef __BIBIM_UIIMAGE_H__
#define __BIBIM_UIIMAGE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/SharedObject.h>
#   include <Bibim/Rect.h>
#   include <Bibim/RectF.h>
#   include <Bibim/URI.h>

    namespace Bibim
    {
        class UIImage : public SharedObject
        {
            public:
                UIImage(const URI& textureURI, const Rect& clippingRect);
                virtual ~UIImage();

                void SetRealTextureData(Texture2D* texture);
                void SetRealTextureData(Texture2D* texture, const Rect& clippingRect);

                inline const URI& GetTextureURI() const;
                inline const Rect& GetClippingRect() const;

                inline Texture2D* GetRealTexture() const;
                inline const Rect& GetRealClippingRect() const;
                inline const RectF& GetNormalizedRealClippingRect() const;

                inline uint GetRevision() const;

            private:
                URI textureURI;
                Rect clippingRect;
                Texture2DPtr realTexture;
                Rect realClippingRect;
                RectF normalizedRealClippingRect;
                uint revision;
        };
    }

#   include <Bibim/UIImage.inl>

#endif