#include <Bibim/PCH.h>
#include <Bibim/SourceTexture2D.h>
#include <Bibim/AssetReader.h>
#include <Bibim/GameAssetStorage.h>
#include <Bibim/GraphicsDevice.h>

namespace Bibim
{
    SourceTexture2D::SourceTexture2D(GraphicsDevice* graphicsDevice)
        : Texture2D(graphicsDevice)
    {
    }

    SourceTexture2D::SourceTexture2D(GraphicsDevice* graphicsDevice, int width, int height)
        : Texture2D(graphicsDevice, width, height, width, height)
    {
        SetStatus(LoadingStatus);
    }

    SourceTexture2D::~SourceTexture2D()
    {
    }

    GameAsset* SourceTexture2D::Read(AssetReader& reader, GameAsset* /*existingInstance*/)
    {
        GraphicsDevice* graphicsDevice = static_cast<GraphicsDevice*>(reader.ReadModule(GraphicsDevice::ClassID));
        const int width = static_cast<int>(reader.ReadInt16());
        const int height = static_cast<int>(reader.ReadInt16());

        SourceTexture2D* texture = new SourceTexture2D(graphicsDevice, width, height);
        reader.ReadAsync(new LoadingTask(texture, reader));

        return texture;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    SourceTexture2D::LoadingTask::LoadingTask(SourceTexture2D* texture, const AssetReader& reader)
        : texture(texture),
          reader(reader)
    {
    }

    SourceTexture2D::LoadingTask::~LoadingTask()
    {
    }

    void SourceTexture2D::LoadingTask::Execute()
    {
        const int pitch = reader.ReadInt32();

        IDirect3DDevice9* d3dDevice = texture->GetGraphicsDevice()->GetD3DDevice();
        const int width  = texture->GetWidth();
        const int height = texture->GetHeight();

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
        for (int y = 0; y < height; y++)
        {
            reader.Read(destination, pitch);
            destination += destinationPitch;
        }
        d3dSysMemTexture->UnlockRect(0);

        d3dDevice->UpdateTexture(d3dSysMemTexture, d3dTexture);
        d3dSysMemTexture->Release();

        texture->Setup(d3dTexture, width, height, width, height);
        texture->IncreaseRevision();
        texture->SetStatus(CompletedStatus);
    }
}