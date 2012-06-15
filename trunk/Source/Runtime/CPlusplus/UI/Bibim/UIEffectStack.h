#pragma once
#ifndef __BIBIM_UIEFFECTSTACK_H__
#define __BIBIM_UIEFFECTSTACK_H__

#   include <Bibim/FWD.h>
#   include <Bibim/SharedObject.h>
#   include <Bibim/UIRenderer.h>
#   include <vector>

    namespace Bibim
    {
        class UIEffectStack : public SharedObject
        {
            public:
                typedef std::vector<UIRenderer::EffectorPtr> EffectorCollection;
                typedef std::vector<UIRenderer::EffectorPtr> EffectorMap;

            public:
                UIEffectStack();
                UIEffectStack(bool isShaderFunctionRendering);
                virtual ~UIEffectStack();

                bool Push(UIEffectMap* item);
                bool Push(UIEffectMap* item, ImagePtr& outMask);
                bool Pop();
                void Clear();

                inline const EffectorCollection& GetTopEffectors() const;

            private:
                void ExpandClass(int newSize);
                void ExpandDepth(int newSize);

            private:
                EffectorCollection topEffectors;
                int depth;
                EffectorMap map;
                int numberOfClasses;
                int maxDepth;
                bool isShaderFunctionRendering;
        };
    }

#   include <Bibim/UIEffectStack.inl>

#endif