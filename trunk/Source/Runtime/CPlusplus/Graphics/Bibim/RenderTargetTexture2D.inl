namespace Bibim
{
    IDirect3DSurface9* RenderTargetTexture2D::GetD3DSurface() const
    {
        return d3dSurface;
    }
}