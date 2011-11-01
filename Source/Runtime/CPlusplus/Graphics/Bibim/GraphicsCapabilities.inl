namespace Bibim
{
    const GraphicsCapabilities::DisplayModeCollection& GraphicsCapabilities::GetDisplayModes() const
    {
        return displayModes;
    }

    GraphicsCapabilities::VertexShader GraphicsCapabilities::GetVertexShaderVersion() const
    {
        return vertexShaderVersion;
    }

    GraphicsCapabilities::PixelShader GraphicsCapabilities::GetPixelShaderVersion() const
    {
        return pixelShaderVersion;
    }

    bool GraphicsCapabilities::IsShaderSupported() const
    {
        return vertexShaderVersion != VSNotSupported && pixelShaderVersion != PSNotSupported;
    }
}