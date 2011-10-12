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
                typedef UIStreamReader StreamReader;

            public:
                static const uint UnspecifiedID;

            public:
                UIElement();
                virtual ~UIElement();

                inline uint GetID() const;
                inline void SetID(uint value);

                inline const String& GetName() const;
                inline void SetName(const String& value);

            protected:
                static void Read(StreamReader& reader, UIElement* o);

            private:
                uint id;
                String name;
        };
    }

#   include <Bibim/UIElement.inl>

#endif