#pragma once
#ifndef __BIBIM_SHADEREFFECT_DX9_H__
#define __BIBIM_SHADEREFFECT_DX9_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameAsset.h>
#   include <Bibim/GraphicsDevice.h>
#   include <d3dx9.h>

    namespace Bibim
    {
        class ShaderEffect : public GameAsset, public GraphicsDevice::LostEventListener
        {
            BBSerializableAssetClass(ShaderEffect, GameAsset, 'S', 'H', 'E', 'F');
            public:
                class Parameter : public SharedObject
                {
                    public:
                        virtual ~Parameter();

                        void SetValue(bool value);
                        void SetValue(int value);
                        void SetValue(float value);
                        void SetValue(Vector2 value);
                        void SetValue(Vector3 value);
                        void SetValue(Vector4 value);
                        void SetValue(const Matrix4& value);
                        void SetValue(Texture2D* value);

                    private:
                        Parameter(ShaderEffect* effect, D3DXHANDLE handle, const D3DXPARAMETER_DESC& desc);

                    private:
                        ShaderEffect* effect;
                        D3DXHANDLE handle;
                        D3DXPARAMETER_DESC desc;

                        friend class ShaderEffect;
                };
                typedef SharedPointer<Parameter> ParameterPtr;

            public:
                virtual ~ShaderEffect();

                       Parameter* FindParameter(const char* name);
                inline Parameter* FindParameter(const String& name);

                inline ID3DXEffect* GetHandle() const;

            private:
                ShaderEffect(GraphicsDevice* graphicsDevice);

                void Setup(ID3DXEffect* handle);

                virtual void OnGraphicsDeviceLost(GraphicsDeviceBase* g);

            private:
                GraphicsDevice* graphicsDevice;
                ID3DXEffect* handle;
        };

        typedef ShaderEffect::Parameter ShaderEffectParameter;
        typedef SharedPointer<ShaderEffectParameter> ShaderEffectParameterPtr;
    }

#endif