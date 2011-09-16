#include <Bibim/PCH.h>
#include <Bibim/SourceTexture2D.h>
#include <Bibim/AssetReader.h>
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

    GameAsset* SourceTexture2D::Read(AssetReader& reader, GameAsset* /*existingInstance*/)
    {
        GraphicsDevice* graphicsDevice = static_cast<GraphicsDevice*>(reader.ReadModule(GraphicsDevice::ClassID));
        const int width = static_cast<int>(reader.ReadInt16());
        const int height = static_cast<int>(reader.ReadInt16());
        const int pitch = reader.ReadInt32();

        IDirect3DDevice9* d3dDevice = graphicsDevice->GetD3DDevice();
        IDirect3DTexture9* d3dTexture = NULL;
        IDirect3DTexture9* d3dSysMemTexture = NULL;
        HRESULT result = D3D_OK;
        result = d3dDevice->CreateTexture(width, height, 1,
                                          0, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &d3dTexture, NULL);
        result = d3dDevice->CreateTexture(width, height, 1,
                                          0, D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM, &d3dSysMemTexture, NULL);

        D3DLOCKED_RECT d3dLockedRect;
        d3dSysMemTexture->LockRect(0, &d3dLockedRect, NULL, 0);
        byte* destination = static_cast<byte*>(d3dLockedRect.pBits);
        const int destinationPitch = static_cast<int>(d3dLockedRect.Pitch);
        /*const int sourcePitch = pitch;*/
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < pitch; x++)
                destination[x] = reader.ReadUInt8();

            destination += destinationPitch;
        }
        d3dSysMemTexture->UnlockRect(0);

        d3dDevice->UpdateTexture(d3dSysMemTexture, d3dTexture);
        d3dSysMemTexture->Release();

        return nullptr;
    }
}