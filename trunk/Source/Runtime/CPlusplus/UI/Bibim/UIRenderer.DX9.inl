namespace Bibim
{
    UIRenderer::Effector::Effector(uint32 effectName, bool setupEnabled, bool beginEndEnabled)
        : effectName(effectName),
          setupEnabled(setupEnabled),
          beginEndEnabled(beginEndEnabled)
    {
    }

    uint32 UIRenderer::Effector::GetEffectName() const
    {
        return effectName;
    }

    bool UIRenderer::Effector::IsSetupEnabled() const
    {
        return setupEnabled;
    }

    bool UIRenderer::Effector::IsBeginEndEnabled() const
    {
        return beginEndEnabled;
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