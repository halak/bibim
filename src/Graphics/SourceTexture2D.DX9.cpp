#include <Bibim/Config.h>
#if (defined(BIBIM_USE_DIRECTX9))

#include <Bibim/SourceTexture2D.DX9.h>
#include <Bibim/AssetStreamReader.h>
#include <Bibim/GameAssetStorage.h>
#include <Bibim/GraphicsDevice.DX9.h>
#include <Bibim/PNGReader.h>
#include <Bibim/JPEGReader.h>
#include <Bibim/Stream.h>

namespace Bibim
{
    SourceTexture2D::SourceTexture2D(GraphicsDevice* graphicsDevice)
        : Texture2D(graphicsDevice)
    {
    }

    SourceTexture2D::SourceTexture2D(GraphicsDevice* graphicsDevice, int width, int height, int surfaceWidth, int surfaceHeight, PixelFormat pixelFormat)
        : Texture2D(graphicsDevice, width, height, surfaceWidth, surfaceHeight, pixelFormat)
    {
        SetStatus(LoadingStatus);
    }

    SourceTexture2D::~SourceTexture2D()
    {
    }

    GameAsset* SourceTexture2D::Create(StreamReader& reader, GameAsset* existingInstance)
    {
        GraphicsDevice* graphicsDevice = static_cast<GraphicsDevice*>(reader.ReadModule(GraphicsDevice::ClassID));
        const int width = static_cast<int>(reader.ReadShortInt());
        const int height = static_cast<int>(reader.ReadShortInt());
        const int surfaceWidth = static_cast<int>(reader.ReadShortInt());
        const int surfaceHeight = static_cast<int>(reader.ReadShortInt());
        const PixelFormat pixelFormat = static_cast<PixelFormat>(reader.ReadByte());
        if (width == 0 || height == 0 || surfaceWidth == 0 || surfaceHeight == 0)
            return existingInstance;

        if (existingInstance == nullptr)
            existingInstance = new SourceTexture2D(graphicsDevice, width, height, surfaceWidth, surfaceHeight, pixelFormat);
        
        Read(static_cast<SourceTexture2D*>(existingInstance), reader);

        return existingInstance;
    }

    void SourceTexture2D::Read(SourceTexture2D* thiz, StreamReader& reader)
    {
        enum Compression
        {
            Raw,
            PNG,
            JPEG,
        };

        const int pitch = reader.ReadInt();
        if (pitch == 0)
        {
            thiz->SetStatus(FaultStatus);
            return;
        }

        const Compression compression = static_cast<Compression>(reader.ReadByte());

        IDirect3DDevice9* d3dDevice = thiz->GetGraphicsDevice()->GetD3DDevice();
        if (d3dDevice == nullptr)
        {
            thiz->SetStatus(FaultStatus);
            return;
        }

        const int width  = thiz->GetSurfaceWidth();
        const int height = thiz->GetSurfaceHeight();
        const PixelFormat pixelFormat = thiz->GetPixelFormat();

        D3DFORMAT d3dFormat = D3DFMT_UNKNOWN;
        switch (pixelFormat)
        {
            case A8R8G8B8Pixels:
                d3dFormat = D3DFMT_A8R8G8B8;
                break;
            case A8Pixels:
                d3dFormat = D3DFMT_A8;
                break;
        }

        IDirect3DTexture9* d3dTexture = nullptr;
        IDirect3DTexture9* d3dSysMemTexture = nullptr;
        HRESULT result = D3D_OK;
        result = d3dDevice->CreateTexture(width, height, 1,
                                          0, d3dFormat, D3DPOOL_DEFAULT, &d3dTexture, nullptr);
        if (result != D3D_OK)
        {
            thiz->SetStatus(FaultStatus);
            return;
        }

        result = d3dDevice->CreateTexture(width, height, 1,
                                          0, d3dFormat, D3DPOOL_SYSTEMMEM, &d3dSysMemTexture, nullptr);
        if (result != D3D_OK)
        {
            d3dTexture->Release();
            thiz->SetStatus(FaultStatus);
            return;
        }

        D3DLOCKED_RECT d3dLockedRect;
        d3dSysMemTexture->LockRect(0, &d3dLockedRect, nullptr, 0);
        byte* destination = static_cast<byte*>(d3dLockedRect.pBits);
        const int destinationPitch = static_cast<int>(d3dLockedRect.Pitch);
        switch (compression)
        {
            case Raw:
                for (int y = 0; y < height; y++)
                {
                    reader.Read(destination, pitch);
                    destination += destinationPitch;
                }
                break;
            case PNG:
                if (PNGReader::Read(reader, destination, destinationPitch, true) == false)
                    thiz->SetStatus(FaultStatus);
                break;
            case JPEG:
                if (JPEGReader::Read(reader, destination, destinationPitch, true) == false)
                    thiz->SetStatus(FaultStatus);
                break;
        }
        d3dSysMemTexture->UnlockRect(0);

        d3dDevice->UpdateTexture(d3dSysMemTexture, d3dTexture);
        d3dSysMemTexture->Release();

        thiz->Setup(d3dTexture, thiz->GetWidth(), thiz->GetHeight(), width, height, pixelFormat);
        thiz->IncreaseRevision();

        if (thiz->GetStatus() == LoadingStatus)
            thiz->SetStatus(CompletedStatus);
    }
}

#endif