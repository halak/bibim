#include <Bibim/Config.h>
#if (defined(BIBIM_USE_DIRECTX9))

#include <Bibim/ShaderEffect.DX9.h>
#include <Bibim/AssetStreamReader.h>
#include <Bibim/CheckedRelease.h>
#include <Bibim/GraphicsDevice.DX9.h>
#include <Bibim/Log.h>
#include <Bibim/Matrix4.h>
#include <Bibim/Numerics.h>
#include <Bibim/String.h>
#include <Bibim/Texture2D.DX9.h>

namespace Bibim
{
    ShaderEffect::Parameter::Parameter(ShaderEffect* effect, D3DXHANDLE handle, const D3DXPARAMETER_DESC& desc)
        : effect(effect),
          handle(handle),
          desc(desc)
    {
    }

    ShaderEffect::Parameter::~Parameter()
    {
    }

    void ShaderEffect::Parameter::SetValue(bool value)
    {
        BBAssert(desc.Class == D3DXPC_SCALAR && desc.Type == D3DXPT_BOOL);
        effect->GetHandle()->SetBool(handle, value);
    }

    void ShaderEffect::Parameter::SetValue(int value)
    {
        BBAssert(desc.Class == D3DXPC_SCALAR && desc.Type == D3DXPT_INT);
        effect->GetHandle()->SetInt(handle, value);
    }

    void ShaderEffect::Parameter::SetValue(float value)
    {
        BBAssert(desc.Class == D3DXPC_SCALAR && desc.Type == D3DXPT_FLOAT);
        effect->GetHandle()->SetFloat(handle, value);
    }

    void ShaderEffect::Parameter::SetValue(Vector2 value)
    {
        BBAssert(desc.Class == D3DXPC_VECTOR && desc.Type == D3DXPT_FLOAT);
        const float values[] = { value.X, value.Y };
        effect->GetHandle()->SetFloatArray(handle, values, sizeof(values) / sizeof(values[0]));
    }

    void ShaderEffect::Parameter::SetValue(Vector3 value)
    {
        BBAssert(desc.Class == D3DXPC_VECTOR && desc.Type == D3DXPT_FLOAT);
        const float values[] = { value.X, value.Y, value.Z };
        effect->GetHandle()->SetFloatArray(handle, values, sizeof(values) / sizeof(values[0]));
    }

    void ShaderEffect::Parameter::SetValue(Vector4 value)
    {
        BBAssert(desc.Class == D3DXPC_VECTOR && desc.Type == D3DXPT_FLOAT);
        const float values[] = { value.X, value.Y, value.Z, value.W };
        effect->GetHandle()->SetFloatArray(handle, values, sizeof(values) / sizeof(values[0]));
    }

    void ShaderEffect::Parameter::SetValue(const Matrix4& value)
    {
        BBAssert(desc.Class == D3DXPC_MATRIX_ROWS && desc.Type == D3DXPT_FLOAT);
        const D3DXMATRIX matrix(value);
        effect->GetHandle()->SetMatrix(handle, &matrix);
    }

    void ShaderEffect::Parameter::SetValue(Texture2D* value)
    {
        BBAssert(desc.Class == D3DXPC_OBJECT && desc.Type == D3DXPT_TEXTURE);
        effect->GetHandle()->SetTexture(handle, value->GetHandle());
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    ShaderEffect::ShaderEffect(GraphicsDevice* graphicsDevice)
        : graphicsDevice(graphicsDevice),
          handle(nullptr)
    {
        if (graphicsDevice)
            graphicsDevice->AddLostEventListener(this);
    }

    ShaderEffect::~ShaderEffect()
    {
        CheckedRelease(handle);

        if (graphicsDevice)
            graphicsDevice->RemoveLostEventListener(this);
    }

    void ShaderEffect::Setup(ID3DXEffect* handle)
    {
        this->handle = handle;
    }

    ShaderEffect::Parameter* ShaderEffect::FindParameter(const char* name)
    {
        if (D3DXHANDLE parameterHandle = handle->GetParameterByName(nullptr, name))
        {
            D3DXPARAMETER_DESC desc = { 0, };
            handle->GetParameterDesc(parameterHandle, &desc);
            return new Parameter(this, parameterHandle, desc);
        }
        else
            return nullptr;
    }

    ShaderEffect::Parameter* ShaderEffect::FindParameter(const String& name)
    {
        return FindParameter(name.CStr());
    }

    GameAsset* ShaderEffect::Create(StreamReader& reader, GameAsset* existingInstance)
    {
        GraphicsDevice* graphicsDevice = static_cast<GraphicsDevice*>(reader.ReadModule(GraphicsDevice::ClassID));
        
        reader.ReadInt(); // NOT USED

        const int codeLength = reader.ReadInt();
        byte* code = BBStackAlloc(byte, codeLength);
        reader.Read(code, codeLength);

        ID3DXEffect* handle = nullptr;
        ID3DXBuffer* errorBuffer = nullptr;
        HRESULT result = D3DXCreateEffect(graphicsDevice->GetD3DDevice(),
                                          code, codeLength,
                                          NULL, NULL, D3DXSHADER_OPTIMIZATION_LEVEL3, 0, &handle, &errorBuffer);
        if (result != D3D_OK)
        {
            Log::Error("ShaderEffect", Int::ToString(result).CStr());

            if (errorBuffer)
                Log::Error("ShaderEffect", reinterpret_cast<const char*>(errorBuffer->GetBufferPointer()));
        }

        if (existingInstance == nullptr)
            existingInstance = new ShaderEffect(graphicsDevice);

        static_cast<ShaderEffect*>(existingInstance)->Setup(handle);

        BBStackFree(code);

        return existingInstance;
    }

    void ShaderEffect::OnGraphicsDeviceLost(GraphicsDeviceBase* g)
    {
        BBAssert(graphicsDevice == g);
        CheckedRelease(handle);
        SetStatus(DirtyStatus);
    }
}

#endif