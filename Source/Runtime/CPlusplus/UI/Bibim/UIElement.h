#pragma once
#ifndef __BIBIM_UIELEMENT_H__
#define __BIBIM_UIELEMENT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameComponent.h>
#   include <Bibim/Property.h>
#   include <Bibim/String.h>
#   include <map>

    namespace Bibim
    {
        class UIElement : public GameComponent
        {
            BBAbstractComponentClass(UIElement, GameComponent);
            public:
                static const int UnspecifiedID;

            public:
                UIElement();
                virtual ~UIElement();

                inline int GetID() const;
                inline void SetID(int value);
                inline const String& GetName() const;
                inline const char* GetNameAsChars() const;
                inline void SetName(const String& value);
                inline void SetNameByChars(const char* value);

            private:
                int id;
                String name;
        };
    }

#   include <Bibim/UIElement.inl>

#endif