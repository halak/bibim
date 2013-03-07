#include <Bibim/PCH.h>
#include <Bibim/SourceTexture2D.GLES2.h>
#include <Bibim/AssetStreamReader.h>
#include <Bibim/GameAssetStorage.h>
#include <Bibim/GraphicsDevice.GLES2.h>
#include <Bibim/PNGReader.h>
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

        Read(texture, reader);

        return texture;
    }

    void SourceTexture2D::Read(SourceTexture2D* self, StreamReader& reader)
    {
        enum Compression
        {
            Raw,
            PNG,
        };

        const int pitch = reader.ReadInt();
        if (pitch == 0)
            self->SetStatus(FaultStatus);

        const Compression compression = static_cast<Compression>(reader.ReadByte());
        const int width  = self->GetSurfaceWidth();
        const int height = self->GetSurfaceHeight();
        const PixelFormat pixelFormat = self->GetPixelFormat();

        GLint glesFormat = GetGLESPixelFormat(pixelFormat);
        byte* destination = new byte [pitch * height];
        const int destinationPitch = pitch;
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
                {
                    if (PNGReader::Read(reader, destination, destinationPitch) == false)
                        self->SetStatus(FaultStatus);
                }
                break;
        }

        GLuint textureHandle = 0;

        glActiveTexture(GL_TEXTURE0);
        glGenTextures(1, &textureHandle);
        glBindTexture(GL_TEXTURE_2D, textureHandle);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, glesFormat, width, height, 0, glesFormat, GL_UNSIGNED_BYTE, destination);

        self->Setup(textureHandle, self->GetWidth(), self->GetHeight(), width, height, pixelFormat);
        self->IncreaseRevision();

        if (self->GetStatus() == LoadingStatus)
            self->SetStatus(CompletedStatus);

        delete [] destination;
    }
}