#pragma once
#ifndef __BIBIM_TEXTURE2D_DX9_H__
#define __BIBIM_TEXTURE2D_DX9_H__

#include <Bibim/FWD.h>
#if (defined(BIBIM_USE_DIRECTX9))

#include <Bibim/GameAsset.h>
#include <Bibim/GraphicsDevice.h>
#include <d3dx9.h>

namespace Bibim
{
    class Texture2D : public GameAsset, public GraphicsDevice::LostEventListener
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

            inline IDirect3DTexture9* GetHandle() const;

        protected:
            Texture2D(GraphicsDevice* graphicsDevice);
            Texture2D(GraphicsDevice* graphicsDevice, int width, int height, int surfaceWidth, int surfaceHeight, PixelFormat pixelFormat);

            void Setup(IDirect3DTexture9* handle, int width, int height, int surfaceWidth, int surfaceHeight, PixelFormat pixelFormat);

            virtual void OnGraphicsDeviceLost(GraphicsDeviceBase* g);

        private:
            GraphicsDevice* graphicsDevice;
            int width;
            int height;
            int surfaceWidth;
            int surfaceHeight;
            PixelFormat pixelFormat;
            IDirect3DTexture9* handle;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    GraphicsDevice* Texture2D::GetGraphicsDevice() const
    {
        return graphicsDevice;
    }
    
    int Texture2D::GetWidth() const
    {
        return width;
    }

    int Texture2D::GetHeight() const
    {
        return height;
    }

    int Texture2D::GetSurfaceWidth() const
    {
        return surfaceWidth;
    }

    int Texture2D::GetSurfaceHeight() const
    {
        return surfaceHeight;
    }

    Texture2D::PixelFormat Texture2D::GetPixelFormat() const
    {
        return pixelFormat;
    }

    IDirect3DTexture9* Texture2D::GetHandle() const
    {
        return handle;
    }
}

#endif
#endif