#include <Bibim/Config.h>
#if (defined(BIBIM_USE_OPENGLES2))

#include <Bibim/Texture2D.GLES2.h>
#include <Bibim/GLES2.h>
#include <Bibim/GraphicsDevice.GLES2.h>

namespace Bibim
{
    Texture2D::Texture2D(GraphicsDevice* graphicsDevice)
        : graphicsDevice(graphicsDevice),
          width(0),
          height(0),
          surfaceWidth(0),
          surfaceHeight(0),
          pixelFormat(UnknownPixels),
          handle(0)
    {
        if (graphicsDevice)
            graphicsDevice->AddLostEventListener(this);
    }

    Texture2D::Texture2D(GraphicsDevice* graphicsDevice, int width, int height, int surfaceWidth, int surfaceHeight, PixelFormat pixelFormat)
        : graphicsDevice(graphicsDevice),
          width(width),
          height(height),
          surfaceWidth(surfaceWidth),
          surfaceHeight(surfaceHeight),
          pixelFormat(pixelFormat),
          handle(0)
    {
        if (graphicsDevice)
            graphicsDevice->AddLostEventListener(this);
    }

    Texture2D::~Texture2D()
    {
        if (handle)
            glDeleteTextures(1, &handle);
        if (graphicsDevice)
            graphicsDevice->RemoveLostEventListener(this);
    }

    void Texture2D::Setup(unsigned int handle, int width, int height, int surfaceWidth, int surfaceHeight, PixelFormat pixelFormat)
    {
        if (this->handle)
            glDeleteTextures(1, &this->handle);
        this->handle = handle;
        this->width = width;
        this->height = height;
        this->surfaceWidth = surfaceWidth;
        this->surfaceHeight = surfaceHeight;
        this->pixelFormat = pixelFormat;
    }

    unsigned int Texture2D::GetHandle()
    {
        return handle;
    }

    void Texture2D::OnGraphicsDeviceLost(GraphicsDeviceBase* /*g*/)
    {
        if (handle)
        {
            glDeleteTextures(1, &handle);
            handle = 0;
        }

        SetStatus(DirtyStatus);
    }

    int Texture2D::GetBytesPerPixel(PixelFormat value)
    {
        switch (value)
        {
            case A8R8G8B8Pixels:
                return 4;
            case A8Pixels:
                return 1;
            case A8A8A8A8Pixels:
                return 4;
            default:
                return 0;
        }
    }

    int Texture2D::GetGLESPixelFormat(PixelFormat value)
    {
        switch (value)
        {
            case A8R8G8B8Pixels:
                return GL_RGBA;
            case A8Pixels:
                return GL_ALPHA;
            case A8A8A8A8Pixels:
                return GL_RGBA;
            default:
                return GL_RGBA;
        }
    }
}

#endif