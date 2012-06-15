#pragma once
#ifndef __BIBIM_RENDERTARGETTEXTURE2D_DX9_H__
#define __BIBIM_RENDERTARGETTEXTURE2D_DX9_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Texture2D.h>
#   include <Bibim/Rect.h>

    namespace Bibim
    {
        class RenderTargetTexture2D : public Texture2D
        {
            BBAssetClass(RenderTargetTexture2D, Texture2D, 'R', 'T', 'X', '2');
            public:
                RenderTargetTexture2D(GraphicsDevice* graphicsDevice, int width, int height);
                virtual ~RenderTargetTexture2D();

                inline IDirect3DSurface9* GetD3DSurface() const;

            private:
                IDirect3DSurface9* d3dSurface;
        };
    }

#   include <Bibim/RenderTargetTexture2D.DX9.inl>

#endif