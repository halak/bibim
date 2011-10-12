#pragma once
#ifndef __BIBIM_UIELEMENTFACTORY_H__
#define __BIBIM_UIELEMENTFACTORY_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIElement.h>

    namespace Bibim
    {
        class UIElementFactory
        {
            BBThisIsStaticClass(UIElementFactory);
            public:
                typedef UIElement::StreamReader StreamReader;
                typedef UIElement* (*CreateFunction)(StreamReader&, UIElement*);

            public:
                static inline UIElement* Create(StreamReader& reader);
                static UIElement* Create(StreamReader& reader, UIElement* existingInstance);

                template <typename T> static void AddEntry();
                static void AddEntry(uint32 id, CreateFunction function);
                static void SortEntries();
        };
    }

#    include <Bibim/UIElementFactory.inl>

#endif