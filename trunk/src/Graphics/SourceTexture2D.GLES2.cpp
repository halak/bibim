#include <Bibim/Config.h>
#if (defined(BIBIM_USE_OPENGLES2))

#include <Bibim/SourceTexture2D.GLES2.h>
#include <Bibim/AssetStreamReader.h>
#include <Bibim/GameAssetStorage.h>
#include <Bibim/GLES2.h>
#include <Bibim/GraphicsDevice.GLES2.h>
#include <Bibim/PNG.h>
#include <Bibim/JPEG.h>
#include <Bibim/Stream.h>
#include <Bibim/Log.h>
#include <Bibim/Numerics.h>

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
            PNGCompression,
            JPEGCompression,
        };

        const int pitch = reader.ReadInt();
        if (pitch == 0)
            thiz->SetStatus(FaultStatus);

        const Compression compression = static_cast<Compression>(reader.ReadByte());
        const int width  = thiz->GetSurfaceWidth();
        const int height = thiz->GetSurfaceHeight();
        const PixelFormat pixelFormat = thiz->GetPixelFormat();

        GLint glesFormat = GetGLESPixelFormat(pixelFormat);
        byte* destination = new byte [pitch * height];
        const int destinationPitch = pitch;
        switch (compression)
        {
            case Raw:
                {
                    byte* current = destination;
                    for (int y = 0; y < height; y++)
                    {
                        reader.Read(current, pitch);
                        current += destinationPitch;
                    }
                }
                break;
            case PNGCompression:
                if (PNG::Read(reader, destination, destinationPitch, false) == false)
                    thiz->SetStatus(FaultStatus);
                break;
            case JPEGCompression:
                if (JPEG::Read(reader, destination, destinationPitch, false) == false)
                    thiz->SetStatus(FaultStatus);
                break;
        }

        GLuint textureHandle = 0;
        glGenTextures(1, &textureHandle);
        GLES2::CheckLastError("glGenTextures");
        glBindTexture(GL_TEXTURE_2D, textureHandle);
        GLES2::CheckLastError("glBindTexture");

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//GL_NEAREST);
        GLES2::CheckLastError("glTexParameteri");

        glTexImage2D(GL_TEXTURE_2D, 0, glesFormat, width, height, 0, glesFormat, GL_UNSIGNED_BYTE, destination);
        GLES2::CheckLastError("glTexImage2D");

        thiz->Setup(textureHandle, thiz->GetWidth(), thiz->GetHeight(), width, height, pixelFormat);
        thiz->IncreaseRevision();

        if (thiz->GetStatus() == LoadingStatus)
            thiz->SetStatus(CompletedStatus);

        delete [] destination;
    }
}

#endif