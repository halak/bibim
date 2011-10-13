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