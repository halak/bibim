#pragma once
#ifndef __BIBIM_UIIMAGE_H__
#define __BIBIM_UIIMAGE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/SharedObject.h>
#   include <Bibim/Rectangle.h>
#   include <Bibim/RectangleF.h>
#   include <Bibim/URI.h>

    namespace Bibim
    {
        class UIImage : public SharedObject
        {
            public:
                UIImage(const URI& textureURI, const Rectangle& clippingRectangle);
                virtual ~UIImage();

                void SetRealTextureData(Texture2D* texture);
                void SetRealTextureData(Texture2D* texture, const Rectangle& clippingRectangle);

                inline const URI& GetTextureURI() const;
                inline const Rectangle& GetClippingRectangle() const;

                inline Texture2D* GetRealTexture() const;
                inline const Rectangle& GetRealClippingRectangle() const;
                inline const RectangleF& GetNormalizedRealClippingRectangle() const;

                inline uint GetRevision() const;

            private:
                URI textureURI;
                Rectangle clippingRectangle;
                Texture2DPtr realTexture;
                Rectangle realClippingRectangle;
                RectangleF normalizedRealClippingRectangle;
                uint revision;
        };
    }

#   include <Bibim/UIImage.inl>

#endif