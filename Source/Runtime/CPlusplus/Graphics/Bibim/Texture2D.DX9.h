﻿#pragma once
#ifndef __BIBIM_TEXTURE2D_DX9_H__
#define __BIBIM_TEXTURE2D_DX9_H__

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
                    UnknownPixels,
                    A8R8G8B8Pixels,
                    A8Pixels,
                };

            public:
                virtual ~Texture2D();

                inline GraphicsDevice* GetGraphicsDevice() const;

                inline int GetWidth() const;
                inline int GetHeight() const;
                inline int GetSurfaceWidth() const;
                inline int GetSurfaceHeight() const;
                inline PixelFormat GetPixelFormat() const;

                inline IDirect3DTexture9* GetD3DTexture() const;

            protected:
                Texture2D(GraphicsDevice* graphicsDevice);
                Texture2D(GraphicsDevice* graphicsDevice, int width, int height, int surfaceWidth, int surfaceHeight, PixelFormat pixelFormat);

                void Setup(IDirect3DTexture9* d3dTexture, int width, int height, int surfaceWidth, int surfaceHeight, PixelFormat pixelFormat);

            private:
                GraphicsDevice* graphicsDevice;
                int width;
                int height;
                int surfaceWidth;
                int surfaceHeight;
                PixelFormat pixelFormat;
                IDirect3DTexture9* d3dTexture;
        };
    }

#   include <Bibim/Texture2D.DX9.inl>

#endif