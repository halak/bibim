#pragma once
#ifndef __BIBIM_UIRADIOBUTTON_H__
#define __BIBIM_UIRADIOBUTTON_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UICheckBox.h>

    namespace Bibim
    {
        class UIRadioButton : public UICheckBox
        {
            BBComponentClass(UIRadioButton, UICheckBox, 'U', 'R', 'D', 'B');
            public:
                UIRadioButton();
                virtual ~UIRadioButton();

            protected:
                virtual bool OnMouseClick(const UIMouseEventArgs& args);
                virtual void OnChecked();
                virtual void OnUnchecked();
        };
    }

#endif