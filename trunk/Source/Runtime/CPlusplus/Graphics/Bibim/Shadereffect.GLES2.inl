namespace Bibim
{
    GLuint ShaderEffect::GetHandle() const
    {
        return handle;
    }

    GLuint ShaderEffect::GetPositionLocation() const
    {
        return positionLocation;
    }

    GLuint ShaderEffect::GetColorLocation() const
    {
        return colorLocation;
    }

    GLuint ShaderEffect::GetTexCoord1Location() const
    {
        return texCoord1Location;
    }

    GLuint ShaderEffect::GetTexCoord2Location() const
    {
        return texCoord2Location;
    }

    GLuint ShaderEffect::GetMainSamplerLocation() const
    {
        return mainSamplerLocation;
    }

    GLuint ShaderEffect::GetMaskSamplerLocation() const
    {
        return maskSamplerLocation;
    }

    GLuint ShaderEffect::GetMVPTransformLocation() const
    {
        return mvpTransformLocation;
    }
}