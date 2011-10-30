#pragma once
#ifndef __BIBIM_UIPIXELEFFECT_H__
#define __BIBIM_UIPIXELEFFECT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIElement.h>

    namespace Bibim
    {
        class UIPixelEffect : public UIElement
        {
            BBAbstractComponentClass(UIPixelEffect, UIElement);
            public:
                class Effector : public SharedObject
                {
                    public:
                        virtual ~Effector() { }

                        virtual void Setup(ShaderEffect* effect) = 0;
                    protected:
                        Effector() { }
                };

            public:
                virtual ~UIPixelEffect();

                virtual Effector* CreateEffector(Effector* /*parent*/) { return 0; }

                inline int GetSlotIndex() const;
                inline bool IsFixedFunctionImplemented() const;
                inline bool IsShaderFunctionImplemented() const;

            protected:
                UIPixelEffect(int slotIndex, bool isFixedFunctionImplemented, bool isShaderFunctionImplemented);

            private:
                int slotIndex;
                bool isFixedFunctionImplemented;
                bool isShaderFunctionImplemented;
        };

        typedef UIPixelEffect::Effector UIPixelEffector;
        typedef SharedPointer<UIPixelEffector> UIPixelEffectorPtr;
    }

#   include <Bibim/UIPixelEffect.inl>

#endif