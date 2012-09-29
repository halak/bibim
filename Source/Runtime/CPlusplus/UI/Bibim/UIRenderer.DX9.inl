namespace Bibim
{
    GraphicsDevice* UIRenderer::GetGraphicsDevice() const
    {
        return graphicsDevice;
    }

    GameAssetStorage* UIRenderer::GetStorage() const
    {
        return storage;
    }

    const String& UIRenderer::GetShaderEffectDirectory() const
    {
        return shaderEffectDirectory;
    }

    float UIRenderer::GetFieldOfView() const
    {
        return fieldOfView;
    }

    const Matrix4& UIRenderer::GetViewTransform()
    {
        UpdateViewProjectionTransform();
        return viewTransform;
    }

    const Matrix4& UIRenderer::GetProjectionTransform()
    {
        UpdateViewProjectionTransform();
        return projectionTransform;
    }

    const Matrix4& UIRenderer::GetInversedViewTransform()
    {
        UpdateViewProjectionTransform();
        return viewTransformInv;
    }

    const Matrix4& UIRenderer::GetInversedProjectionTransform()
    {
        UpdateViewProjectionTransform();
        return projectionTransformInv;
    }

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