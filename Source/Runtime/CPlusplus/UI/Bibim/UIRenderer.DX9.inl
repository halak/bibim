namespace Bibim
{
    void UIRenderer::DrawPrimitives(D3DPRIMITIVETYPE primitiveType, int numberOfPrimitives)
    {
        DrawPrimitivesActually(primitiveType, ColorOnlyMode, numberOfPrimitives, nullptr, nullptr);
    }

    void UIRenderer::DrawPrimitives(D3DPRIMITIVETYPE primitiveType, int numberOfPrimitives, Texture2D* texture)
    {
        DrawPrimitivesActually(primitiveType, ColorTextureOnlyMode, numberOfPrimitives, texture, nullptr);
    }

    void UIRenderer::DrawPrimitives(D3DPRIMITIVETYPE primitiveType, int numberOfPrimitives, Texture2D* texture, Texture2D* mask)
    {
        DrawPrimitivesActually(primitiveType, MaskedColorTextureMode, numberOfPrimitives, texture, mask);
    }
}