namespace Bibim
{
    UIRenderer::Effector::Effector(uint32 effectName)
        : effectName(effectName)
    {
    }

    uint32 UIRenderer::Effector::GetEffectName() const
    {
        return effectName;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

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
}