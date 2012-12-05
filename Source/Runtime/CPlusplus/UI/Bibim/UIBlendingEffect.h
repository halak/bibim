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

                        virtual void Begin(UIRenderer* renderer);
                        virtual void End(UIRenderer* renderer);

                    private:
                        BlendMode mode;
                        BlendMode oldMode;
                };

            private:
                BlendMode mode;
        };
    }

#   include <Bibim/UIBlendingEffect.inl>

    BBBindLuaEnum(Bibim::BlendMode,
                  Bibim::UIBlendingEffect::ConvertFromStringToBlendMode,
                  Bibim::UIBlendingEffect::ConvertFromBlendModeToString);

#endif