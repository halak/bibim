#pragma once
#ifndef __BIBIM_UICHECKBOX_H__
#define __BIBIM_UICHECKBOX_H__

#include <Bibim/FWD.h>
#include <Bibim/UIButton.h>

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
            virtual void OnChecked();
            virtual void OnUnchecked();

        private:
            UIVisualPtr checkedNormalVisual;
            UIVisualPtr checkedPushedVisual;
            UIVisualPtr checkedHoveringVisual;
            bool checked;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    UIVisual* UICheckBox::GetCheckedNormal() const
    {
        return checkedNormalVisual;
    }

    UIVisual* UICheckBox::GetCheckedPushed() const
    {
        return checkedPushedVisual;
    }

    UIVisual* UICheckBox::GetCheckedHovering() const
    {
        return checkedHoveringVisual;
    }

    bool UICheckBox::GetChecked() const
    {
        return checked;
    }
}

#endif