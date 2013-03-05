#pragma once
#ifndef __BIBIM_SHADEREFFECT_GLES2_H__
#define __BIBIM_SHADEREFFECT_GLES2_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameAsset.h>
#   include <Bibim/GLES2.h>

    namespace Bibim
    {
        class ShaderEffect : public GameAsset
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
                        Parameter(ShaderEffect* effect, GLint location);

                    private:
                        ShaderEffect* effect;
                        GLint location;

                        friend class ShaderEffect;
                };
                typedef SharedPointer<Parameter> ParameterPtr;

            public:
                virtual ~ShaderEffect();

                       Parameter* FindParameter(const char* name);
                inline Parameter* FindParameter(const String& name);

                inline GLuint GetHandle() const;

            private:
                ShaderEffect(GraphicsDevice* graphicsDevice, GLuint handle);

            private:
                GraphicsDevice* graphicsDevice;
                GLuint handle;
        };

        typedef ShaderEffect::Parameter ShaderEffectParameter;
        typedef SharedPointer<ShaderEffectParameter> ShaderEffectParameterPtr;
    }

#   include <Bibim/ShaderEffect.GLES2.inl>

#endif