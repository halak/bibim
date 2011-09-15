#include <Bibim/PCH.h>
#include <Bibim/Texture2D.h>
#include <Bibim/GraphicsDevice.h>
#include <Bibim/CheckedRelease.h>

namespace Bibim
{
    Texture2D::Texture2D(GraphicsDevice* graphicsDevice)
        : graphicsDevice(graphicsDevice)
    {
        d3dTexture = NULL;
        width  = 0;
        height = 0;
        textureChanged = true;
    }

    Texture2D::~Texture2D()
    {
        CheckedRelease(d3dTexture);
    }

    int Texture2D::GetWidth()
    {
        if (GetTextureChanged())
        {
            SetTextureChanged(false);
            UpdateTexture();
        }

        return width;
    }

    int Texture2D::GetHeight()
    {
        if (GetTextureChanged())
        {
            SetTextureChanged(false);
            UpdateTexture();
        }

        return height;
    }

    int Texture2D::GetSurfaceWidth()
    {
        if (GetTextureChanged())
        {
            SetTextureChanged(false);
            UpdateTexture();
        }

        return surfaceWidth;
    }

    int Texture2D::GetSurfaceHeight()
    {
        if (GetTextureChanged())
        {
            SetTextureChanged(false);
            UpdateTexture();
        }

        return surfaceHeight;
    }

    IDirect3DTexture9* Texture2D::GetD3DTexture()
    {
        if (GetTextureChanged())
        {
            SetTextureChanged(false);
            UpdateTexture();
        }

        return d3dTexture;
    }

    void Texture2D::UpdateTexture()
    {
        CheckedRelease(d3dTexture);

        D3DTextureInfo newD3DTexture = CreateD3DTexture();
        d3dTexture    = newD3DTexture.Texture;
        width         = newD3DTexture.Width;
        height        = newD3DTexture.Height;
        surfaceWidth  = newD3DTexture.SurfaceWidth;
        surfaceHeight = newD3DTexture.SurfaceHeight;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    Texture2D::D3DTextureInfo::D3DTextureInfo()
        : Texture(nullptr),
          Width(0),
          Height(0),
          SurfaceWidth(0),
          SurfaceHeight(0)
    {
    }

    Texture2D::D3DTextureInfo::D3DTextureInfo(IDirect3DTexture9* texture, int width, int height)
        : Texture(texture),
          Width(width),
          Height(height),
          SurfaceWidth(width),
          SurfaceHeight(height)
    {
    }

    Texture2D::D3DTextureInfo::D3DTextureInfo(IDirect3DTexture9* texture, int width, int height, int surfaceWidth, int surfaceHeight)
        : Texture(texture),
          Width(width),
          Height(height),
          SurfaceWidth(surfaceWidth),
          SurfaceHeight(surfaceHeight)
    {
    }
}