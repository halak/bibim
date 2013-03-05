#include <Bibim/PCH.h>
#include <Bibim/SourceTexture2D.GLES2.h>
#include <Bibim/AssetStreamReader.h>
#include <Bibim/GameAssetStorage.h>
#include <Bibim/GraphicsDevice.GLES2.h>
#include <Bibim/PNGReader.h>
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
        AssetLoadingTask* task = new LoadingTask(reader, texture, surfaceHeight);
        task->Execute();
        delete task;
        // reader.ReadAsync(new LoadingTask(reader, texture, surfaceHeight));

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
        const int width  = texture->GetSurfaceWidth();
        const int height = texture->GetSurfaceHeight();
        const PixelFormat pixelFormat = texture->GetPixelFormat();

        GLint glesFormat = GetGLESPixelFormat(pixelFormat);
        byte* destination = new byte [pitch * height];
        const int destinationPitch = pitch;
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
                    if (PNGReader::Read(reader, destination, destinationPitch) == false)
                        texture->SetStatus(FaultStatus);
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

        texture->Setup(textureHandle, texture->GetWidth(), texture->GetHeight(), width, height, pixelFormat);
        texture->IncreaseRevision();

        if (texture->GetStatus() == LoadingStatus)
            texture->SetStatus(CompletedStatus);

        delete [] destination;
    }

    void SourceTexture2D::LoadingTask::Cancel()
    {
        cancelled = true;
    }
}