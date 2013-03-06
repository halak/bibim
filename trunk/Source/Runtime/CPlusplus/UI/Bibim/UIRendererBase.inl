namespace Bibim
{
    UIRendererBase::Vertex::Vertex()
    {
    }

    UIRendererBase::Vertex::Vertex(const Vertex& original)
        : Position(original.Position),
          Color(original.Color),
          TexCoord1(original.TexCoord1),
          TexCoord2(original.TexCoord2)
    {
    }

    UIRendererBase::Vertex::Vertex(Vector2 position, unsigned long color)
        : Position(position, 0.0f),
          Color(color)
    {
    }

    UIRendererBase::Vertex::Vertex(Vector2 position, unsigned long color, Vector2 texCoord1)
        : Position(position, 0.0f),
          Color(color),
          TexCoord1(texCoord1)
    {
    }

    UIRendererBase::Vertex::Vertex(Vector2 position, unsigned long color, Vector2 texCoord1, Vector2 texCoord2)
        : Position(position.X, position.Y, 0.0f),
          Color(color),
          TexCoord1(texCoord1),
          TexCoord2(texCoord2)
    {
    }

    UIRendererBase::Vertex::Vertex(Vector3 position, unsigned long color)
        : Position(position),
          Color(color)
    {
    }

    UIRendererBase::Vertex::Vertex(Vector3 position, unsigned long color, Vector2 texCoord1)
        : Position(position),
          Color(color),
          TexCoord1(texCoord1)
    {
    }

    UIRendererBase::Vertex::Vertex(Vector3 position, unsigned long color, Vector2 texCoord1, Vector2 texCoord2)
        : Position(position),
          Color(color),
          TexCoord1(texCoord1),
          TexCoord2(texCoord2)
    {
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    UIRendererBase::QuadSet::QuadSet()
        : StartIndex(0),
          Count(0),
          Capacity(0)
    {
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    UIRendererBase::Effector::Effector()
        : shaderEffectNameHint(0x00000000),
          isMaskEffector(false)
    {
    }

    UIRendererBase::Effector::Effector(int shaderEffectNameHint)
        : shaderEffectNameHint(shaderEffectNameHint),
          isMaskEffector(false)
    {
    }

    UIRendererBase::Effector::Effector(bool isMaskEffector)
        : shaderEffectNameHint(0x00000000),
          isMaskEffector(isMaskEffector)
    {
    }

    UIRendererBase::Effector::Effector(int shaderEffectNameHint, bool isMaskEffector)
        : shaderEffectNameHint(shaderEffectNameHint),
          isMaskEffector(isMaskEffector)
    {
    }

    int UIRendererBase::Effector::GetShaderEffectNameHint() const
    {
        return shaderEffectNameHint;
    }

    bool UIRendererBase::Effector::IsMaskEffector() const
    {
        return isMaskEffector;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    GraphicsDevice* UIRendererBase::GetGraphicsDevice() const
    {
        return graphicsDevice;
    }

    GameAssetStorage* UIRendererBase::GetStorage() const
    {
        return storage;
    }

    const String& UIRendererBase::GetShaderEffectDirectory() const
    {
        return shaderEffectDirectory;
    }

    float UIRendererBase::GetFieldOfView() const
    {
        return fieldOfView;
    }

    const Matrix4& UIRendererBase::GetViewTransform()
    {
        UpdateViewProjectionTransform();
        return viewTransform;
    }

    const Matrix4& UIRendererBase::GetProjectionTransform()
    {
        UpdateViewProjectionTransform();
        return projectionTransform;
    }

    const Matrix4& UIRendererBase::GetInversedViewTransform()
    {
        UpdateViewProjectionTransform();
        return viewTransformInv;
    }

    const Matrix4& UIRendererBase::GetInversedProjectionTransform()
    {
        UpdateViewProjectionTransform();
        return projectionTransformInv;
    }
}