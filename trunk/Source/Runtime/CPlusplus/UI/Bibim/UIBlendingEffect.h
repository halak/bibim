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

            public:
                UIBlendingEffect();
                UIBlendingEffect(BlendMode mode);
                virtual ~UIBlendingEffect();

                virtual Effector* CreateEffector(UIRenderer::Effector* parent);
                
                inline BlendMode GetMode() const;
                inline void SetMode(BlendMode value);

            private:
                BlendMode mode;
        };
    }

#   include <Bibim/UIBlendingEffect.inl>

#endif