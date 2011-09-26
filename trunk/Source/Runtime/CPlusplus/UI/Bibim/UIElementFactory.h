#pragma once
#ifndef __BIBIM_UIELEMENTFACTORY_H__
#define __BIBIM_UIELEMENTFACTORY_H__

#    include <Bibim/FWD.h>

    namespace Bibim
    {
        class UIElementFactory
        {
            BBThisIsStaticClass(UIElementFactory);
            public:
                typedef UIElement* (*CreateFunction)(AssetStreamReader&, UIElement*);

            public:
                static inline UIElement* Create(AssetStreamReader& reader);
                static UIElement* Create(AssetStreamReader& reader, UIElement* existingInstance);

                template <typename T> static void AddEntry();
                static void AddEntry(uint32 id, CreateFunction function);
                static void SortEntries();
        };
    }

#    include <Bibim/UIElementFactory.inl>

#endif