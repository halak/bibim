#include <Bibim/PCH.h>
#include <Bibim/SourceTexture2D.DX9.h>
#include <Bibim/AssetStreamReader.h>
#include <Bibim/GameAssetStorage.h>
#include <Bibim/GraphicsDevice.h>
#include <png.h>
#include <pngstruct.h>
#include <zlib.h>

#include <Bibim/Stream.h>

namespace Bibim
{
    static void ReadPNGData(png_structp pngReader, png_bytep data, png_size_t length)
    {
        AssetStreamReader* reader = ((AssetStreamReader*)pngReader->io_ptr);
        if (reader->Read(data, length) == nullptr)
            png_error(pngReader, "Read Error");
    }

    static bool ReadPNG(AssetStreamReader& reader, byte* destination, int destinationPitch)
    {
        byte signature[8];
        reader.Read(signature, sizeof(signature) / sizeof(signature[0]));
        if (png_sig_cmp(signature, 0, sizeof(signature) / sizeof(signature[0])))
            return false;

        png_structp pngReader = png_create_read_struct(PNG_LIBPNG_VER_STRING,
                                                       nullptr,
                                                       nullptr,
                                                       nullptr);
        if (pngReader == nullptr)
            return false;

        png_infop pngInfo = png_create_info_struct(pngReader);
        if (pngInfo == nullptr)
        {
            png_destroy_read_struct(&pngReader, nullptr, nullptr);
            return false;
        }

        png_set_read_fn(pngReader, (png_voidp)&reader, ReadPNGData);

        png_set_sig_bytes(pngReader, 8);

        png_read_info(pngReader, pngInfo);

        png_uint_32 width = 0;
        png_uint_32 height = 0;
        int bitDepth = 0;
        int colorType = 0;
        png_get_IHDR(pngReader, pngInfo, &width, &height, &bitDepth, &colorType, NULL, NULL, NULL);

        png_size_t pitch = png_get_rowbytes(pngReader, pngInfo);
        // png_size_t channels = png_get_channels(pngReader, pngInfo);

        BBAssert(static_cast<int>(pitch) == destinationPitch);

        png_bytep* rows = BBStackAlloc(png_bytep, height);
        for (png_uint_32 i = 0; i < height; i++)
            rows[i] = &destination[destinationPitch * i];

        png_read_image(pngReader, rows);

        png_read_end(pngReader, nullptr);

        png_destroy_read_struct(&pngReader, &pngInfo, nullptr);

        BBStackFree(rows);

        return true;
    }

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

    GameAsset* SourceTexture2D::Create(StreamReader& reader, GameAsset* /*existingInstance*/)
    {
        GraphicsDevice* graphicsDevice = static_cast<GraphicsDevice*>(reader.ReadModule(GraphicsDevice::ClassID));
        const int width = static_cast<int>(reader.ReadShortInt());
        const int height = static_cast<int>(reader.ReadShortInt());
        const int surfaceWidth = static_cast<int>(reader.ReadShortInt());
        const int surfaceHeight = static_cast<int>(reader.ReadShortInt());
        const PixelFormat pixelFormat = static_cast<PixelFormat>(reader.ReadByte());
        if (width == 0 || height == 0 || surfaceWidth == 0 || surfaceHeight == 0)
            return nullptr;

        SourceTexture2D* texture = new SourceTexture2D(graphicsDevice, width, height, surfaceWidth, surfaceHeight, pixelFormat);
        reader.ReadAsync(new LoadingTask(reader, texture, surfaceHeight));

        return texture;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    SourceTexture2D::LoadingTask::LoadingTask(const AssetStreamReader& reader, SourceTexture2D* texture, int totalBytes)
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
        enum Compression
        {
            Raw,
            PNG,
        };

        const int pitch = reader.ReadInt();
        if (pitch == 0)
            texture->SetStatus(FaultStatus);

        const Compression compression = static_cast<Compression>(reader.ReadByte());

        IDirect3DDevice9* d3dDevice = texture->GetGraphicsDevice()->GetD3DDevice();
        const int width  = texture->GetSurfaceWidth();
        const int height = texture->GetSurfaceHeight();
        const PixelFormat pixelFormat = texture->GetPixelFormat();

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
        result = d3dDevice->CreateTexture(width, height, 1,
                                          0, d3dFormat, D3DPOOL_SYSTEMMEM, &d3dSysMemTexture, nullptr);

        D3DLOCKED_RECT d3dLockedRect;
        d3dSysMemTexture->LockRect(0, &d3dLockedRect, nullptr, 0);
        byte* destination = static_cast<byte*>(d3dLockedRect.pBits);
        const int destinationPitch = static_cast<int>(d3dLockedRect.Pitch);
        switch (compression)
        {
            case Raw:
                for (int y = 0; y < height && cancelled == false; y++)
                {
                    reader.Read(destination, pitch);
                    destination += destinationPitch;
                    AddLoadedBytes(1);
                }
                break;
            case PNG:
                {
                    if (ReadPNG(reader, destination, destinationPitch) == false)
                        texture->SetStatus(FaultStatus);
                }
                break;
        }
        d3dSysMemTexture->UnlockRect(0);

        d3dDevice->UpdateTexture(d3dSysMemTexture, d3dTexture);
        d3dSysMemTexture->Release();

        texture->Setup(d3dTexture, texture->GetWidth(), texture->GetHeight(), width, height, pixelFormat);
        texture->IncreaseRevision();

        if (texture->GetStatus() == LoadingStatus)
            texture->SetStatus(CompletedStatus);
    }

    void SourceTexture2D::LoadingTask::Cancel()
    {
        cancelled = true;
    }
}