#pragma once
#ifndef __BIBIM_TEXTURE2D_H__
#define __BIBIM_TEXTURE2D_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameAsset.h>
#   include <d3dx9.h>

    namespace Bibim
    {
        class Texture2D : public GameAsset
        {
            public:
                enum PixelFormat
                {
                    A8G8B8A8Pixels,
                    A8Pixels,
                };

            public:
                virtual ~Texture2D();

                inline GraphicsDevice* GetGraphicsDevice() const;

                inline int GetWidth() const;
                inline int GetHeight() const;
                inline int GetSurfaceWidth() const;
                inline int GetSurfaceHeight() const;

                inline IDirect3DTexture9* GetD3DTexture() const;

            protected:
                Texture2D(GraphicsDevice* graphicsDevice);
                Texture2D(GraphicsDevice* graphicsDevice, int width, int height, int surfaceWidth, int surfaceHeight);

                void Setup(IDirect3DTexture9* d3dTexture, int width, int height, int surfaceWidth, int surfaceHeight);

            private:
                GraphicsDevice* graphicsDevice;
                int width;
                int height;
                int surfaceWidth;
                int surfaceHeight;
                IDirect3DTexture9* d3dTexture;
        };
    }

#   include <Bibim/Texture2D.inl>

#endif