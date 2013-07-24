#pragma once
#ifndef __BIBIM_UIELEMENT_H__
#define __BIBIM_UIELEMENT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameComponent.h>
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
                inline void SetName(const String& value);
                inline int GetTag() const;
                inline void SetTag(int value);

            private:
                int id;
                String name;
                int tag;
        };
    }

#endif