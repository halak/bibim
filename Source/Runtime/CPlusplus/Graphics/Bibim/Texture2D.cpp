#include <Bibim/PCH.h>
#include <Bibim/Texture2D.h>
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
          d3dTexture(nullptr)
    {
    }

    Texture2D::Texture2D(GraphicsDevice* graphicsDevice, int width, int height, int surfaceWidth, int surfaceHeight)
        : graphicsDevice(graphicsDevice),
          width(width),
          height(height),
          surfaceWidth(surfaceWidth),
          surfaceHeight(surfaceHeight),
          d3dTexture(nullptr)
    {
    }

    Texture2D::~Texture2D()
    {
        CheckedRelease(d3dTexture);
    }

    void Texture2D::Setup(IDirect3DTexture9* d3dTexture, int width, int height, int surfaceWidth, int surfaceHeight)
    {
        CheckedRelease(this->d3dTexture);
        this->d3dTexture = d3dTexture;
        this->width = width;
        this->height = height;
        this->surfaceWidth = surfaceWidth;
        this->surfaceHeight = surfaceHeight;
    }
}