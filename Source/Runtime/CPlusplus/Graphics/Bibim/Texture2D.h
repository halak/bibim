#pragma once
#ifndef __BIBIM_TEXTURE2D_H__
#define __BIBIM_TEXTURE2D_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Asset.h>
#   include <d3dx9.h>

    namespace Bibim
    {
        class Texture2D : public Asset
        {
            public:
                enum PixelFormat
                {
                    ARGB32Pixels,
                    A8Pixels,
                };

            public:
                Texture2D(GraphicsDevice* graphicsDevice);
                virtual ~Texture2D();

                int GetWidth();
                int GetHeight();
                int GetSurfaceWidth();
                int GetSurfaceHeight();

                GraphicsDevice* GetGraphicsDevice();
                IDirect3DTexture9* GetD3DTexture();

            protected:
                bool GetTextureChanged() const;
                void SetTextureChanged(bool value = true);

                struct D3DTextureInfo
                {
                    IDirect3DTexture9* Texture;
                    int Width;
                    int Height;
                    int SurfaceWidth;
                    int SurfaceHeight;

                    D3DTextureInfo();
                    D3DTextureInfo(IDirect3DTexture9* texture, int width, int height);
                    D3DTextureInfo(IDirect3DTexture9* texture, int width, int height, int surfaceWidth, int surfaceHeight);
                };
                virtual D3DTextureInfo CreateD3DTexture() = 0;

            private:
                void UpdateTexture();

            private:
                GraphicsDevice* graphicsDevice;

                IDirect3DTexture9* d3dTexture;
                int width;
                int height;
                int surfaceWidth;
                int surfaceHeight;
                bool textureChanged;
        };
    }

#endif