#include <Bibim/PCH.h>
#include <Bibim/Texture2D.DX9.h>
#include <Bibim/GraphicsDevice.DX9.h>
#include <Bibim/CheckedRelease.h>

namespace Bibim
{
    Texture2D::Texture2D(GraphicsDevice* graphicsDevice)
        : graphicsDevice(graphicsDevice),
          width(0),
          height(0),
          surfaceWidth(0),
          surfaceHeight(0),
          pixelFormat(UnknownPixels),
          handle(nullptr)
    {
    }

    Texture2D::Texture2D(GraphicsDevice* graphicsDevice, int width, int height, int surfaceWidth, int surfaceHeight, PixelFormat pixelFormat)
        : graphicsDevice(graphicsDevice),
          width(width),
          height(height),
          surfaceWidth(surfaceWidth),
          surfaceHeight(surfaceHeight),
          pixelFormat(pixelFormat),
          handle(nullptr)
    {
    }

    Texture2D::~Texture2D()
    {
        CheckedRelease(handle);
    }

    void Texture2D::Setup(IDirect3DTexture9* handle, int width, int height, int surfaceWidth, int surfaceHeight, PixelFormat pixelFormat)
    {
        CheckedRelease(this->handle);
        this->handle = handle;
        this->width = width;
        this->height = height;
        this->surfaceWidth = surfaceWidth;
        this->surfaceHeight = surfaceHeight;
        this->pixelFormat = pixelFormat;
    }
}