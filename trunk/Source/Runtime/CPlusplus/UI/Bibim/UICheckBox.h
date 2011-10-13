#pragma once
#ifndef __BIBIM_UICHECKBOX_H__
#define __BIBIM_UICHECKBOX_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIButton.h>

    namespace Bibim
    {
        class UICheckBox : public UIButton
        {
            BBComponentClass(UICheckBox, UIButton, 'U', 'C', 'B', 'X');
            public:
                UICheckBox();
                virtual ~UICheckBox();

                inline UIWindow* GetCheckedNormalWindow() const;
                inline UIWindow* GetCheckedPushedWindow() const;
                inline UIWindow* GetCheckedHoveringWindow() const;

                inline bool GetChecked() const;
                void SetChecked(bool value);

            protected:
                virtual UIWindow* OnUpdateLayout();

                virtual bool OnMouseClick(const UIMouseEventArgs& args);

            private:
                UIWindowPtr checkedNormalWindow;
                UIWindowPtr checkedPushedWindow;
                UIWindowPtr checkedHoveringWindow;
                bool checked;
        };
    }

#   include <Bibim/UICheckBox.inl>

#endif