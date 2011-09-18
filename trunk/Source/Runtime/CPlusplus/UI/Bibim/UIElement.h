#pragma once
#ifndef __BIBIM_UIELEMENT_H__
#define __BIBIM_UIELEMENT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/SharedObject.h>
#   include <Bibim/Property.h>
#   include <Bibim/String.h>

    namespace Bibim
    {
#       define BBUIElementClass(a, b, c, d) public: \
                                                static const uint32 ClassID = BBMakeFOURCC(a, b, c, d); \
                                                virtual uint32 GetClassID() const { return ClassID; } \
                                            private:

        class UIElement : public SharedObject
        {
            BBThisIsNoncopyableClass(UIElement);
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