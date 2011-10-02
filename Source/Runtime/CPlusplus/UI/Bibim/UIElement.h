#pragma once
#ifndef __BIBIM_UIELEMENT_H__
#define __BIBIM_UIELEMENT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/SharedObject.h>
#   include <Bibim/Property.h>
#   include <Bibim/String.h>

    namespace Bibim
    {
        class UIElement : public SharedObject
        {
            BBAbstractObjectClass(UIElement, SharedObject);
            BBThisIsNoncopyableClass(UIElement);
            public:
                typedef AssetStreamReader StreamReaderType;

            public:
                UIElement();
                virtual ~UIElement();

                inline const String& GetName() const;
                inline void SetName(const String& value);

            private:
                String name;
        };
    }

#   include <Bibim/UIElement.inl>

#endif