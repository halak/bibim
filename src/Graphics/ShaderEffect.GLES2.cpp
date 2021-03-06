﻿#include <Bibim/Config.h>
#if (defined(BIBIM_USE_OPENGLES2))

#include <Bibim/ShaderEffect.GLES2.h>
#include <Bibim/AssetStreamReader.h>
#include <Bibim/CheckedRelease.h>
#include <Bibim/GraphicsDevice.GLES2.h>
#include <Bibim/GLES2.h>
#include <Bibim/Log.h>
#include <Bibim/Matrix4.h>
#include <Bibim/Numerics.h>
#include <Bibim/String.h>
#include <Bibim/Texture2D.GLES2.h>
#include <Bibim/Log.h>

namespace Bibim
{
    ShaderEffect::Parameter::Parameter(ShaderEffect* effect, int location)
        : effect(effect),
          location(location)
    {
    }

    ShaderEffect::Parameter::~Parameter()
    {
    }

    void ShaderEffect::Parameter::SetValue(bool value)
    {
        glUseProgram(effect->GetHandle());
        glUniform1i(location, value ? 1 : 0);
    }

    void ShaderEffect::Parameter::SetValue(int value)
    {
        glUseProgram(effect->GetHandle());
        glUniform1i(location, value);
    }

    void ShaderEffect::Parameter::SetValue(float value)
    {
        glUseProgram(effect->GetHandle());
        glUniform1f(location, value);
    }

    void ShaderEffect::Parameter::SetValue(Vector2 value)
    {
        glUseProgram(effect->GetHandle());
        glUniform2f(location, value.X, value.Y);
    }

    void ShaderEffect::Parameter::SetValue(Vector3 value)
    {
        glUseProgram(effect->GetHandle());
        glUniform3f(location, value.X, value.Y, value.Z);
    }

    void ShaderEffect::Parameter::SetValue(Vector4 value)
    {
        glUseProgram(effect->GetHandle());
        glUniform4f(location, value.X, value.Y, value.Z, value.W);
    }

    void ShaderEffect::Parameter::SetValue(const Matrix4& value)
    {
        glUseProgram(effect->GetHandle());
        glUniformMatrix4fv(location, 1, GL_FALSE, value);
    }

    void ShaderEffect::Parameter::SetValue(Texture2D* /*value*/)
    {
        glUseProgram(effect->GetHandle());
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    ShaderEffect::ShaderEffect(GraphicsDevice* graphicsDevice)
        : graphicsDevice(graphicsDevice),
          handle(0)
    {
        if (graphicsDevice)
            graphicsDevice->AddLostEventListener(this);
    }

    ShaderEffect::~ShaderEffect()
    {
        if (handle)
            glDeleteProgram(handle);

        if (graphicsDevice)
            graphicsDevice->RemoveLostEventListener(this);
    }

    void ShaderEffect::Setup(GLuint handle)
    {
        this->handle = handle;
        positionLocation = glGetAttribLocation(handle, "Position");
        colorLocation = glGetAttribLocation(handle, "Color");
        texCoord1Location = glGetAttribLocation(handle, "TexCoord1");
        texCoord2Location = glGetAttribLocation(handle, "TexCoord2");
        mainSamplerLocation = glGetUniformLocation(handle, "MainSampler");
        maskSamplerLocation = glGetUniformLocation(handle, "MaskSampler");
        mvpTransformLocation = glGetUniformLocation(handle, "MVP");
    }

    ShaderEffect::Parameter* ShaderEffect::FindParameter(const char* name)
    {
        const int location = glGetUniformLocation(handle, name);
        if (location >= 0)
            return new Parameter(this, location);
        else
            return nullptr;
    }

    ShaderEffect::Parameter* ShaderEffect::FindParameter(const String& name)
    {
        return FindParameter(name.CStr());
    }

    static GLuint CompileShader(GLenum type, const char* sourceCode, int length)
    {
        BBAssertDebug(type == GL_VERTEX_SHADER || type == GL_FRAGMENT_SHADER);
        
        GLuint handle = glCreateShader(type);
        glShaderSource(handle, 1, &sourceCode, &length);
        glCompileShader(handle);

        int status = 0;
        glGetShaderiv(handle, GL_COMPILE_STATUS, &status);
        if (status == GL_FALSE)
        {
            GLchar messages[256];
            glGetShaderInfoLog(handle, sizeof(messages), 0, &messages[0]);

            Log::Warning("ShaderEffect", messages);

            // "Failed to create a vertex shader.";
            glDeleteShader(handle);
            return 0;
        }

        return handle;
    }

    GameAsset* ShaderEffect::Create(StreamReader& reader, GameAsset* existingInstance)
    {
        GraphicsDevice* graphicsDevice = static_cast<GraphicsDevice*>(reader.ReadModule(GraphicsDevice::ClassID));
        const int hint = reader.ReadInt();
        const int codeLength = reader.ReadInt();
        char* code = BBStackAlloc(char, codeLength);
        reader.Read(code, codeLength);

        const int vsCodeIndex = 0;
        const int vsCodeLength = hint;
        const int fsCodeIndex = hint + 1;
        const int fsCodeLength = codeLength - fsCodeIndex;

        GLuint vs = CompileShader(GL_VERTEX_SHADER,   &code[vsCodeIndex], vsCodeLength);
        GLuint fs = CompileShader(GL_FRAGMENT_SHADER, &code[fsCodeIndex], fsCodeLength);

        BBStackFree(code);

        if (vs == 0 || fs == 0)
        {
            if (vs)
                glDeleteShader(vs);
            if (fs)
                glDeleteShader(fs);

            return nullptr;
        }

        GLuint programHandle = glCreateProgram();
        if (programHandle == 0)
        {
            glDeleteShader(vs);
            glDeleteShader(fs);
            return nullptr;
        }

        glAttachShader(programHandle, vs);
        glAttachShader(programHandle, fs);

        glLinkProgram(programHandle);

        int status = 0;
        glGetProgramiv(programHandle, GL_LINK_STATUS, &status);
        if (status == GL_FALSE) 
        {
            GLchar messages[256];
            glGetProgramInfoLog(programHandle, sizeof(messages), 0, &messages[0]);

            Log::Warning("ShaderEffect", messages);

            // "Failed to link program."
            glDeleteProgram(programHandle);
            glDeleteShader(vs);
            glDeleteShader(fs);
            return nullptr;
        }

        // 이미 Program에 연결되었고 더 이상 쓰이지 않기 때문에 제거합니다.
        glDeleteShader(vs);
        glDeleteShader(fs);

        if (existingInstance == nullptr)
            existingInstance = new ShaderEffect(graphicsDevice);

        static_cast<ShaderEffect*>(existingInstance)->Setup(programHandle);

        return existingInstance;
    }

    void ShaderEffect::OnGraphicsDeviceLost(GraphicsDeviceBase* /*g*/)
    {
        if (handle)
        {
            glDeleteProgram(handle);
            handle = 0;
        }

        SetStatus(DirtyStatus);
    }
}

#endif