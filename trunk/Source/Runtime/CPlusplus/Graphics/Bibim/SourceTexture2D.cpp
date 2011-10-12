#include <Bibim/PCH.h>
#include <Bibim/SourceTexture2D.h>
#include <Bibim/AssetStreamReader.h>
#include <Bibim/GameAssetStorage.h>
#include <Bibim/GraphicsDevice.h>

namespace Bibim
{
    SourceTexture2D::SourceTexture2D(GraphicsDevice* graphicsDevice)
        : Texture2D(graphicsDevice)
    {
    }

    SourceTexture2D::SourceTexture2D(GraphicsDevice* graphicsDevice, int width, int height, int surfaceWidth, int surfaceHeight)
        : Texture2D(graphicsDevice, width, height, surfaceWidth, surfaceHeight)
    {
        SetStatus(LoadingStatus);
    }

    SourceTexture2D::~SourceTexture2D()
    {
    }

    GameAsset* SourceTexture2D::Create(StreamReader& reader, GameAsset* /*existingInstance*/)
    {
        GraphicsDevice* graphicsDevice = static_cast<GraphicsDevice*>(reader.ReadModule(GraphicsDevice::ClassID));
        const int width = static_cast<int>(reader.ReadInt16());
        const int height = static_cast<int>(reader.ReadInt16());
        const int surfaceWidth = static_cast<int>(reader.ReadInt16());
        const int surfaceHeight = static_cast<int>(reader.ReadInt16());
        if (width == 0 || height == 0 || surfaceWidth == 0 || surfaceHeight == 0)
            return nullptr;

        SourceTexture2D* texture = new SourceTexture2D(graphicsDevice, width, height, surfaceWidth, surfaceHeight);
        reader.ReadAsync(new LoadingTask(reader, texture, surfaceHeight));

        return texture;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    SourceTexture2D::LoadingTask::LoadingTask(const AssetStreamReader& reader, SourceTexture2D* texture, uint totalBytes)
        : AssetLoadingTask(reader.GetName(), totalBytes),
          texture(texture),
          reader(reader),
          cancelled(false)
    {
    }

    SourceTexture2D::LoadingTask::~LoadingTask()
    {
    }

    void SourceTexture2D::LoadingTask::Execute()
    {
        const int pitch = reader.ReadInt32();
        if (pitch == 0)
            texture->SetStatus(FaultStatus);

        IDirect3DDevice9* d3dDevice = texture->GetGraphicsDevice()->GetD3DDevice();
        const int width  = texture->GetSurfaceWidth();
        const int height = texture->GetSurfaceHeight();

        IDirect3DTexture9* d3dTexture = nullptr;
        IDirect3DTexture9* d3dSysMemTexture = nullptr;
        HRESULT result = D3D_OK;
        result = d3dDevice->CreateTexture(width, height, 1,
                                          0, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &d3dTexture, nullptr);
        result = d3dDevice->CreateTexture(width, height, 1,
                                          0, D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM, &d3dSysMemTexture, nullptr);

        D3DLOCKED_RECT d3dLockedRect;
        d3dSysMemTexture->LockRect(0, &d3dLockedRect, nullptr, 0);
        byte* destination = static_cast<byte*>(d3dLockedRect.pBits);
        const int destinationPitch = static_cast<int>(d3dLockedRect.Pitch);
        for (int y = 0; y < height && cancelled == false; y++)
        {
            reader.Read(destination, pitch);
            destination += destinationPitch;
            AddLoadedBytes(1);
        }
        d3dSysMemTexture->UnlockRect(0);

        d3dDevice->UpdateTexture(d3dSysMemTexture, d3dTexture);
        d3dSysMemTexture->Release();

        texture->Setup(d3dTexture, width, height, width, height);
        texture->IncreaseRevision();
        texture->SetStatus(CompletedStatus);
    }

    void SourceTexture2D::LoadingTask::Cancel()
    {
        cancelled = true;
    }
}