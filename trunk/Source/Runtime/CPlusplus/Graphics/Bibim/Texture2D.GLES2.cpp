#include <Bibim/PCH.h>
#include <Bibim/Texture2D.GLES2.h>
#include <Bibim/GraphicsDevice.GLES2.h>
#include <Bibim/CheckedRelease.h>

namespace Bibim
{
    Texture2D::Texture2D(GraphicsDevice* graphicsDevice)
        : graphicsDevice(graphicsDevice),
          width(0),
          height(0),
          surfaceWidth(0),
          surfaceHeight(0),
          pixelFormat(UnknownPixels)
    {
    }

    Texture2D::Texture2D(GraphicsDevice* graphicsDevice, int width, int height, int surfaceWidth, int surfaceHeight, PixelFormat pixelFormat)
        : graphicsDevice(graphicsDevice),
          width(width),
          height(height),
          surfaceWidth(surfaceWidth),
          surfaceHeight(surfaceHeight),
          pixelFormat(pixelFormat)
    {
    }

    Texture2D::~Texture2D()
    {
    }

    void Texture2D::Setup(IDirect3DTexture9* d3dTexture, int width, int height, int surfaceWidth, int surfaceHeight, PixelFormat pixelFormat)
    {
        CheckedRelease(this->d3dTexture);
        this->d3dTexture = d3dTexture;
        this->width = width;
        this->height = height;
        this->surfaceWidth = surfaceWidth;
        this->surfaceHeight = surfaceHeight;
        this->pixelFormat = pixelFormat;
    }
}