#pragma once
#ifndef __BIBIM_TEXTURE2D_GLES2_H__
#define __BIBIM_TEXTURE2D_GLES2_H__

#include <Bibim/FWD.h>
#if (defined(BIBIM_USE_OPENGLES2))

#include <Bibim/GameAsset.h>
#include <Bibim/GLES2.h>
#include <Bibim/GraphicsDevice.h>
#include <Bibim/Rect.h>

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

            virtual GLuint GetHandle();

        protected:
            Texture2D(GraphicsDevice* graphicsDevice);
            Texture2D(GraphicsDevice* graphicsDevice, int width, int height, int surfaceWidth, int surfaceHeight, PixelFormat pixelFormat);

            void Setup(GLuint handle, int width, int height, int surfaceWidth, int surfaceHeight, PixelFormat pixelFormat);

            virtual void OnGraphicsDeviceLost(GraphicsDeviceBase* g);

            static int GetBytesPerPixel(PixelFormat value);
            static GLint GetGLESPixelFormat(PixelFormat value);

        private:
            GraphicsDevice* graphicsDevice;
            int width;
            int height;
            int surfaceWidth;
            int surfaceHeight;
            PixelFormat pixelFormat;
            GLuint handle;
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
}

#endif
#endif