#pragma once
#ifndef __BIBIM_UIOPACITYMASKEFFECT_H__
#define __BIBIM_UIOPACITYMASKEFFECT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIMaskEffect.h>
#   include <Bibim/Vector4.h>

    namespace Bibim
    {
        class UIOpacityMaskEffect : public UIMaskEffect
        {
            BBComponentClass(UIOpacityMaskEffect, UIMaskEffect, 'U', 'O', 'M', 'F');
            public:
                enum FillStyle
                {
                    FanStyle,
                    BarStyle,
                };

            public:
                UIOpacityMaskEffect();
                UIOpacityMaskEffect(Image* mask);
                UIOpacityMaskEffect(Image* mask, float startPoint, float length, FillStyle fill);
                virtual ~UIOpacityMaskEffect();

                virtual UIRenderer::Effector* CreateEffector(UIRenderer::Effector* parent, bool isShaderFunctionRendering);

                inline float GetStartPoint() const;
                void SetStartPoint(float value);

                inline float GetLength() const;
                void SetLength(float value);

                inline FillStyle GetFill() const;
                void SetFill(FillStyle value);

            public:
                static FillStyle ConvertFromStringToFillStyle(const char* value);
                static const char* ConvertFromFillStyleToString(FillStyle value);

            private:
                class EffectorForShaderFunction : public MaskEffector
                {
                    BBEffectorClass(EffectorForShaderFunction);
                    public:
                        EffectorForShaderFunction(UIOpacityMaskEffect* effect);
                        virtual ~EffectorForShaderFunction();
                };

                class FanEffectorForShaderFunction : public MaskEffector
                {
                    BBEffectorClass(FanEffectorForShaderFunction);
                    public:
                        FanEffectorForShaderFunction(UIOpacityMaskEffect* effect);
                        virtual ~FanEffectorForShaderFunction();

                        virtual void Setup(ShaderEffect* effect);

                    private:
                        Vector4 unifiedValue;
                };

                class BarEffectorForShaderFunction : public MaskEffector
                {
                    BBEffectorClass(BarEffectorForShaderFunction);
                    public:
                        BarEffectorForShaderFunction(UIOpacityMaskEffect* effect);
                        virtual ~BarEffectorForShaderFunction();

                        virtual void Setup(ShaderEffect* effect);

                    private:
                        Vector4 unifiedValue;
                };

                class EffectorForFixedFunction : public MaskEffector
                {
                    BBEffectorClass(EffectorForFixedFunction);
                    public:
                        EffectorForFixedFunction(UIOpacityMaskEffect* effect);
                        virtual ~EffectorForFixedFunction();

                        virtual void Begin(UIRendererBase* renderer);
                        virtual void End(UIRendererBase* renderer);
                };

            private:
                float startPoint;
                float length;
                FillStyle fill;
                float invLength;
        };
    }

    BBBindLuaEnum(Bibim::UIOpacityMaskEffect::FillStyle,
                  Bibim::UIOpacityMaskEffect::ConvertFromStringToFillStyle,
                  Bibim::UIOpacityMaskEffect::ConvertFromFillStyleToString);

#endif