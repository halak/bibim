#include <Bibim/PCH.h>
#include <Bibim/Texture2D.DX9.h>
#include <Bibim/GraphicsDevice.h>
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
          d3dTexture(nullptr)
    {
    }

    Texture2D::Texture2D(GraphicsDevice* graphicsDevice, int width, int height, int surfaceWidth, int surfaceHeight, PixelFormat pixelFormat)
        : graphicsDevice(graphicsDevice),
          width(width),
          height(height),
          surfaceWidth(surfaceWidth),
          surfaceHeight(surfaceHeight),
          pixelFormat(pixelFormat),
          d3dTexture(nullptr)
    {
    }

    Texture2D::~Texture2D()
    {
        CheckedRelease(d3dTexture);
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