#pragma once
#ifndef __BIBIM_UIEVENTHANDLER_H__
#define __BIBIM_UIEVENTHANDLER_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIElement.h>

    namespace Bibim
    {
        class UIEventHandler : public UIElement
        {
            BBAbstractComponentClass(UIEventHandler, UIElement);
            public:
                virtual ~UIEventHandler();

                virtual bool Invoke(const UIEventArgs& args) = 0;

                virtual bool IsSequence() const;

            protected:
                UIEventHandler();
        };
    }

#   include <Bibim/UIEventHandler.inl>

#endif