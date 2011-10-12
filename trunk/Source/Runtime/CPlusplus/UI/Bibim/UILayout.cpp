#include <Bibim/PCH.h>
#include <Bibim/UILayout.h>
#include <Bibim/AssetStreamReader.h>
#include <Bibim/UIStreamReader.h>

namespace Bibim
{
    UILayout::UILayout()
    {
    }

    UILayout::~UILayout()
    {
    }

    GameAsset* UILayout::Create(StreamReader& reader, GameAsset* /*existingInstance*/)
    {
        return nullptr;
        //GraphicsDevice* graphicsDevice = static_cast<GraphicsDevice*>(reader.ReadModule(GraphicsDevice::ClassID));
        //const int width = static_cast<int>(reader.ReadInt16());
        //const int height = static_cast<int>(reader.ReadInt16());
        //const int surfaceWidth = static_cast<int>(reader.ReadInt16());
        //const int surfaceHeight = static_cast<int>(reader.ReadInt16());
        //if (width == 0 || height == 0 || surfaceWidth == 0 || surfaceHeight == 0)
        //    return nullptr;

        //SourceTexture2D* texture = new SourceTexture2D(graphicsDevice, width, height, surfaceWidth, surfaceHeight);
        //reader.ReadAsync(new LoadingTask(reader, texture, surfaceHeight));

        //return texture;
    }
}