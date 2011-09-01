#include <Bibim/PCH.h>
#include <Bibim/SourceTexture2D.h>
#include <Bibim/GraphicsDevice.h>

namespace Bibim
{
    SourceTexture2D::SourceTexture2D(GraphicsDevice* graphicsDevice, const URI& uri)
        : Texture2D(graphicsDevice),
          uri(uri)
    {
    }

    SourceTexture2D::~SourceTexture2D()
    {
    }

    const URI& SourceTexture2D::GetURI() const
    {
        return uri;
    }

    Texture2D::D3DTextureInfo SourceTexture2D::CreateD3DTexture()
    {
        BBAssert(uri.GetSource() == URI::Anywhere || uri.GetSource() == URI::FileSystem);

        D3DXIMAGE_INFO imageInfo = { 0, };

        IDirect3DTexture9* newD3DTexture = NULL;
        HRESULT result = D3DXCreateTextureFromFileEx(GetGraphicsDevice()->GetD3DDevice(),
                                                     uri.GetAddress().CStr(), D3DX_DEFAULT, D3DX_DEFAULT, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT, D3DCOLOR_ARGB(0, 0, 0, 0), &imageInfo, nullptr, &newD3DTexture);

        if (result == D3D_OK)
        {
            D3DSURFACE_DESC surfaceDesc;
            if (newD3DTexture->GetLevelDesc(0, &surfaceDesc) == D3D_OK)
            {
                return D3DTextureInfo(newD3DTexture,
                                      static_cast<int>(imageInfo.Width), static_cast<int>(imageInfo.Height),
                                      static_cast<int>(surfaceDesc.Width), static_cast<int>(surfaceDesc.Height));
            }
            else
                return D3DTextureInfo(newD3DTexture, static_cast<int>(imageInfo.Width), static_cast<int>(imageInfo.Height));
        }
        else
            return D3DTextureInfo();
    }
}