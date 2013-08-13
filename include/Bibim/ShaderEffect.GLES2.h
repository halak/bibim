#pragma once
#ifndef __BIBIM_SHADEREFFECT_GLES2_H__
#define __BIBIM_SHADEREFFECT_GLES2_H__

#include <Bibim/FWD.h>
#if (defined(BIBIM_USE_OPENGLES2))

#include <Bibim/GameAsset.h>
#include <Bibim/GraphicsDeviceBase.h>

namespace Bibim
{
    class ShaderEffect : public GameAsset, public GraphicsDeviceBase::LostEventListener
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
                    Parameter(ShaderEffect* effect, int location);

                private:
                    ShaderEffect* effect;
                    int location;

                    friend class ShaderEffect;
            };
            typedef SharedPointer<Parameter> ParameterPtr;

        public:
            virtual ~ShaderEffect();

                   Parameter* FindParameter(const char* name);
            inline Parameter* FindParameter(const String& name);

            inline unsigned int GetHandle() const;
            inline unsigned int GetPositionLocation() const;
            inline unsigned int GetColorLocation() const;
            inline unsigned int GetTexCoord1Location() const;
            inline unsigned int GetTexCoord2Location() const;
            inline unsigned int GetMainSamplerLocation() const;
            inline unsigned int GetMaskSamplerLocation() const;
            inline unsigned int GetMVPTransformLocation() const;

        private:
            ShaderEffect(GraphicsDevice* graphicsDevice);

            void Setup(unsigned int handle);

            virtual void OnGraphicsDeviceLost(GraphicsDeviceBase* g);

        private:
            GraphicsDevice* graphicsDevice;
            unsigned int handle;
            unsigned int positionLocation;
            unsigned int colorLocation;
            unsigned int texCoord1Location;
            unsigned int texCoord2Location;
            unsigned int mainSamplerLocation;
            unsigned int maskSamplerLocation;
            unsigned int mvpTransformLocation;
    };

    typedef ShaderEffect::Parameter ShaderEffectParameter;
    typedef SharedPointer<ShaderEffectParameter> ShaderEffectParameterPtr;

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    unsigned int ShaderEffect::GetHandle() const
    {
        return handle;
    }

    unsigned int ShaderEffect::GetPositionLocation() const
    {
        return positionLocation;
    }

    unsigned int ShaderEffect::GetColorLocation() const
    {
        return colorLocation;
    }

    unsigned int ShaderEffect::GetTexCoord1Location() const
    {
        return texCoord1Location;
    }

    unsigned int ShaderEffect::GetTexCoord2Location() const
    {
        return texCoord2Location;
    }

    unsigned int ShaderEffect::GetMainSamplerLocation() const
    {
        return mainSamplerLocation;
    }

    unsigned int ShaderEffect::GetMaskSamplerLocation() const
    {
        return maskSamplerLocation;
    }

    unsigned int ShaderEffect::GetMVPTransformLocation() const
    {
        return mvpTransformLocation;
    }
}

#endif
#endif