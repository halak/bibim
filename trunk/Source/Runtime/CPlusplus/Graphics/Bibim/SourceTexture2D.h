#pragma once
#ifndef __BIBIM_SOURCETEXTURE2D_H__
#define __BIBIM_SOURCETEXTURE2D_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Texture2D.h>

    namespace Bibim
    {
        class SourceTexture2D : public Texture2D
        {
            public:
                SourceTexture2D(GraphicsDevice* graphicsDevice, const URI& uri);
                virtual ~SourceTexture2D();

                virtual const URI& GetURI() const;

            protected:
                virtual Texture2D::D3DTextureInfo CreateD3DTexture();

            private:
                URI uri;
        };
    }

#endif