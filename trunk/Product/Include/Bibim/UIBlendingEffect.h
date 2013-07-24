#pragma once
#ifndef __BIBIM_UIBLENDINGEFFECT_H__
#define __BIBIM_UIBLENDINGEFFECT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIPixelEffect.h>
#   include <Bibim/BlendMode.h>

    namespace Bibim
    {
        class UIBlendingEffect : public UIPixelEffect
        {
            BBComponentClass(UIBlendingEffect, UIPixelEffect, 'U', 'B', 'L', 'F');
            public:
                static const int ClassIndex = 1;

            public:
                UIBlendingEffect();
                UIBlendingEffect(BlendMode mode);
                UIBlendingEffect(const char* mode);
                virtual ~UIBlendingEffect();

                virtual UIRenderer::Effector* CreateEffector(UIRenderer::Effector* parent, bool isShaderFunctionRendering);
                
                inline BlendMode GetMode() const;
                inline void SetMode(BlendMode value);

            public:
                static BlendMode ConvertFromStringToBlendMode(const char* value);
                static const char* ConvertFromBlendModeToString(BlendMode value);

            private:
                class Effector : public UIRenderer::Effector
                {
                    public:
                        Effector(Effector* parent, UIBlendingEffect* effect);
                        virtual ~Effector();

                        virtual void Begin(UIRendererBase* renderer);
                        virtual void End(UIRendererBase* renderer);

                    private:
                        BlendMode mode;
                        BlendMode oldMode;
                };

            private:
                BlendMode mode;
        };

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        BlendMode UIBlendingEffect::GetMode() const
        {
            return mode;
        }

        void UIBlendingEffect::SetMode(BlendMode value)
        {
            mode = value;
        }
    }

    BBBindLuaEnum(Bibim::BlendMode,
                  Bibim::UIBlendingEffect::ConvertFromStringToBlendMode,
                  Bibim::UIBlendingEffect::ConvertFromBlendModeToString);

#endif