#pragma once
#ifndef __BIBIM_UIEFFECTMAP_H__
#define __BIBIM_UIEFFECTMAP_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIElement.h>
#   include <vector>

    namespace Bibim
    {
        class UIEffectMap : public UIElement
        {
            BBComponentClass(UIEffectMap, UIElement, 'U', 'F', 'X', 'M');
            public:
                typedef std::vector<UIPixelEffectPtr> PixelEffectCollection;

            public:
                UIEffectMap();
                virtual ~UIEffectMap();

                void Insert(UIPixelEffect* item);
                bool Remove(UIPixelEffect* item);
                bool Remove(int index);
                void RemoveAll();
                UIPixelEffect* FindPixelEffect(const String& name);

                inline UIGeometryEffect* GetGeometryEffect() const;
                void SetGeometryEffect(UIGeometryEffect* value);
                inline const PixelEffectCollection& GetPixelEffects() const;

            private:
                UIGeometryEffectPtr geomEffect;
                PixelEffectCollection pixelEffects;
        };

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        UIGeometryEffect* UIEffectMap::GetGeometryEffect() const
        {
            return geomEffect;
        }

        const UIEffectMap::PixelEffectCollection& UIEffectMap::GetPixelEffects() const
        {
            return pixelEffects;
        }
    }

#endif