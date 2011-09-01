#pragma once
#ifndef __BIBIM_UILISTBOX_H__
#define __BIBIM_UILISTBOX_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIFlowPanel.h>

    namespace Bibim
    {
        class UIListBox : public UIFlowPanel
        {
            public:
                UIListBox();
                virtual ~UIListBox();

            private:
        };
    }

#   include <Bibim/UIListBox.inl>

#endif