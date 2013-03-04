#include <Bibim/PCH.h>
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
        effect->GetD3DEffect()->SetBool(handle, value);
    }

    void ShaderEffect::Parameter::SetValue(int value)
    {
        BBAssert(desc.Class == D3DXPC_SCALAR && desc.Type == D3DXPT_INT);
        effect->GetD3DEffect()->SetInt(handle, value);
    }

    void ShaderEffect::Parameter::SetValue(float value)
    {
        BBAssert(desc.Class == D3DXPC_SCALAR && desc.Type == D3DXPT_FLOAT);
        effect->GetD3DEffect()->SetFloat(handle, value);
    }

    void ShaderEffect::Parameter::SetValue(Vector2 value)
    {
        BBAssert(desc.Class == D3DXPC_VECTOR && desc.Type == D3DXPT_FLOAT);
        const float values[] = { value.X, value.Y };
        effect->GetD3DEffect()->SetFloatArray(handle, values, sizeof(values) / sizeof(values[0]));
    }

    void ShaderEffect::Parameter::SetValue(Vector3 value)
    {
        BBAssert(desc.Class == D3DXPC_VECTOR && desc.Type == D3DXPT_FLOAT);
        const float values[] = { value.X, value.Y, value.Z };
        effect->GetD3DEffect()->SetFloatArray(handle, values, sizeof(values) / sizeof(values[0]));
    }

    void ShaderEffect::Parameter::SetValue(Vector4 value)
    {
        BBAssert(desc.Class == D3DXPC_VECTOR && desc.Type == D3DXPT_FLOAT);
        const float values[] = { value.X, value.Y, value.Z, value.W };
        effect->GetD3DEffect()->SetFloatArray(handle, values, sizeof(values) / sizeof(values[0]));
    }

    void ShaderEffect::Parameter::SetValue(const Matrix4& value)
    {
        BBAssert(desc.Class == D3DXPC_MATRIX_ROWS && desc.Type == D3DXPT_FLOAT);
        const D3DXMATRIX matrix(value);
        effect->GetD3DEffect()->SetMatrix(handle, &matrix);
    }

    void ShaderEffect::Parameter::SetValue(Texture2D* value)
    {
        BBAssert(desc.Class == D3DXPC_OBJECT && desc.Type == D3DXPT_TEXTURE);
        effect->GetD3DEffect()->SetTexture(handle, value->GetD3DTexture());
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    ShaderEffect::ShaderEffect(GraphicsDevice* graphicsDevice, ID3DXEffect* d3dEffect)
        : graphicsDevice(graphicsDevice),
          d3dEffect(d3dEffect)
    {
        /*IDirect3DDevice9* d3dDevice = graphicsDevice->GetD3DDevice();*/
    }

    ShaderEffect::~ShaderEffect()
    {
        CheckedRelease(d3dEffect);
    }

    ShaderEffect::Parameter* ShaderEffect::FindParameter(const char* name)
    {
        if (D3DXHANDLE handle = d3dEffect->GetParameterByName(nullptr, name))
        {
            D3DXPARAMETER_DESC desc = { 0, };
            d3dEffect->GetParameterDesc(handle, &desc);
            return new Parameter(this, handle, desc);
        }
        else
            return nullptr;
    }

    ShaderEffect::Parameter* ShaderEffect::FindParameter(const String& name)
    {
        return FindParameter(name.CStr());
    }

    GameAsset* ShaderEffect::Create(StreamReader& reader, GameAsset* /*existingInstance*/)
    {
        GraphicsDevice* graphicsDevice = static_cast<GraphicsDevice*>(reader.ReadModule(GraphicsDevice::ClassID));
        const String code = reader.ReadString();       

        ID3DXEffect* d3dEffect = nullptr;
        ID3DXBuffer* errorBuffer = nullptr;
        HRESULT result = D3DXCreateEffect(graphicsDevice->GetD3DDevice(),
                                          code.CStr(), code.GetLength(),
                                          NULL, NULL, D3DXSHADER_OPTIMIZATION_LEVEL3, 0, &d3dEffect, &errorBuffer);
        if (result != D3D_OK)
        {
            Log::Error("ShaderEffect", Int::ToString(result).CStr());

            if (errorBuffer)
                Log::Error("ShaderEffect", reinterpret_cast<const char*>(errorBuffer->GetBufferPointer()));

            Log::Error("ShaderEffect", code.CStr());
        }

        return new ShaderEffect(graphicsDevice, d3dEffect);
    }
}