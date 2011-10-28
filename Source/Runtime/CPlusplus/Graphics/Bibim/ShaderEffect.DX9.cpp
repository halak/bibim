#include <Bibim/PCH.h>
#include <Bibim/ShaderEffect.DX9.h>
#include <Bibim/AssetStreamReader.h>
#include <Bibim/GraphicsDevice.h>

namespace Bibim
{
    ShaderEffect::ShaderEffect(GraphicsDevice* graphicsDevice)
        : graphicsDevice(graphicsDevice),
          d3dEffect(nullptr)
    {
        IDirect3DDevice9* d3dDevice = graphicsDevice->GetD3DDevice();
        // D3DXCreateEffect(d3dDevice, 
    }

    ShaderEffect::~ShaderEffect()
    {
    }

    GameAsset* ShaderEffect::Create(StreamReader& reader, GameAsset* /*existingInstance*/)
    {
        GraphicsDevice* graphicsDevice = static_cast<GraphicsDevice*>(reader.ReadModule(GraphicsDevice::ClassID));
        return new ShaderEffect(graphicsDevice);
        //const int width = static_cast<int>(reader.ReadInt16());
        //const int height = static_cast<int>(reader.ReadInt16());
        //const int surfaceWidth = static_cast<int>(reader.ReadInt16());
        //const int surfaceHeight = static_cast<int>(reader.ReadInt16());
        //const PixelFormat pixelFormat = static_cast<PixelFormat>(reader.ReadInt8());
        //if (width == 0 || height == 0 || surfaceWidth == 0 || surfaceHeight == 0)
        //    return nullptr;

        //SourceTexture2D* texture = new SourceTexture2D(graphicsDevice, width, height, surfaceWidth, surfaceHeight, pixelFormat);
        //reader.ReadAsync(new LoadingTask(reader, texture, surfaceHeight));

        //return texture;
    }
}