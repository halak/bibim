#pragma once
#ifndef __BIBIM_TEXTURE2D_GLES2_H__
#define __BIBIM_TEXTURE2D_GLES2_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameAsset.h>
#   include <Bibim/GLES2.h>
#   include <Bibim/GraphicsDevice.h>

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

                inline GLuint GetHandle() const;

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
    }

#   include <Bibim/Texture2D.GLES2.inl>

#endif