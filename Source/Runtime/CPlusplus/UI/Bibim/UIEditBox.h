#pragma once
#ifndef __BIBIM_UIEDITBOX_H__
#define __BIBIM_UIEDITBOX_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIWindow.h>

    namespace Bibim
    {
        class UIEditBox : public UIWindow
        {
            public:
                UIEditBox();
                virtual ~UIEditBox();

            private:
        };
    }

#   include <Bibim/UIEditBox.inl>

#endif