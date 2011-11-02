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
                virtual ~UIEffectStack();

                bool Push(UIEffectMap* item);
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
        };
    }

#   include <Bibim/UIEffectStack.inl>

#endif