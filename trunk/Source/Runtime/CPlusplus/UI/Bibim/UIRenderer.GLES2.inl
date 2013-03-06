namespace Bibim
{
    void UIRenderer::DrawArrays(GLenum primitiveType, int numberOfVertices)
    {
        DrawArraysActually(primitiveType, ColorOnlyMode, numberOfVertices, nullptr, nullptr);
    }

    void UIRenderer::DrawArrays(GLenum primitiveType, int numberOfVertices, Texture2D* texture)
    {
        DrawArraysActually(primitiveType, ColorTextureOnlyMode, numberOfVertices, texture, nullptr);
    }

    void UIRenderer::DrawArrays(GLenum primitiveType, int numberOfVertices, Texture2D* texture, Texture2D* mask)
    {
        DrawArraysActually(primitiveType, MaskedColorTextureMode, numberOfVertices, texture, mask);
    }
}