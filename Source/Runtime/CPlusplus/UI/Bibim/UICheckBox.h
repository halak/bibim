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

                inline UIVisual* GetCheckedNormal() const;
                void SetCheckedNormal(UIVisual* value);
                inline UIVisual* GetCheckedPushed() const;
                void SetCheckedPushed(UIVisual* value);
                inline UIVisual* GetCheckedHovering() const;
                void SetCheckedHovering(UIVisual* value);

                inline bool GetChecked() const;
                void SetChecked(bool value);

            protected:
                virtual UIVisual* OnUpdateLayout();

                virtual bool OnMouseClick(const UIMouseEventArgs& args);

            private:
                UIVisualPtr checkedNormalVisual;
                UIVisualPtr checkedPushedVisual;
                UIVisualPtr checkedHoveringVisual;
                bool checked;
        };
    }

#   include <Bibim/UICheckBox.inl>

#endif