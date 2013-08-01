#include <Bibim/Config.h>
#include <Bibim/UICheckBox.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/UIMouseEventArgs.h>
#include <Bibim/UIWindow.h>

namespace Bibim
{
    BBImplementsComponent(UICheckBox);

    UICheckBox::UICheckBox()
        : checkedNormalVisual(),
          checkedPushedVisual(),
          checkedHoveringVisual(),
          checked(false)
    {
    }

    UICheckBox::~UICheckBox()
    {
    }

    void UICheckBox::SetCheckedNormal(UIVisual* value)
    {
        SetStateTemplate(checkedNormalVisual, value);
    }

    void UICheckBox::SetCheckedPushed(UIVisual* value)
    {
        SetStateTemplate(checkedPushedVisual, value);
    }

    void UICheckBox::SetCheckedHovering(UIVisual* value)
    {
        SetStateTemplate(checkedHoveringVisual, value);
    }

    void UICheckBox::SetChecked(bool value)
    {
        if (checked != value)
        {
            checked = value;
            UpdateLayout();

            if (checked)
                OnChecked();
            else
                OnUnchecked();
        }
    }

    UIVisual* UICheckBox::OnUpdateLayout()
    {
        UIVisual* const visuals[] = 
        {
            GetNormal(), GetPushed(), GetHovering(),
            checkedNormalVisual, checkedPushedVisual, checkedHoveringVisual,
        };
        BBStaticAssert(NormalState == 0 && PushedState == 1 && HoveringState == 2);

        State state = GetCurrentState();
        if (state == NormalState &&
            IsFocused() && GetFocusVisible())
            state = HoveringState;

        const int activeVisualIndex = static_cast<int>(state) + ((checked) ? 3 : 0);
        BBAssertDebug(0 <= activeVisualIndex && activeVisualIndex < sizeof(visuals) / sizeof(visuals[0]));
        UIVisual* activeVisual = visuals[activeVisualIndex];

        if (GetFrozen())
            activeVisual = checked ? static_cast<UIVisual*>(checkedNormalVisual) : GetNormal();

        if (activeVisual)
        {
            activeVisual->BringToFront();
            activeVisual->Show();
        }

        if (GetHideInactives())
        {
            for (int i = 0; i < sizeof(visuals) / sizeof(visuals[0]); i++)
            {
                if (visuals[i] && i != activeVisualIndex)
                    visuals[i]->Hide();
            }
        }

        return activeVisual;
    }

    bool UICheckBox::OnMouseClick(const UIMouseEventArgs& args)
    {
        if (GetFrozen() == false)
        {
            checked = !checked;
            UpdateLayout();

            if (checked)
                OnChecked();
            else
                OnUnchecked();
        }

        return Base::OnMouseClick(args);
    }

    void UICheckBox::OnChecked()
    {
    }

    void UICheckBox::OnUnchecked()
    {
    }

    void UICheckBox::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        checkedNormalVisual = static_cast<UIVisual*>(reader.ReadComponent());
        checkedPushedVisual = static_cast<UIVisual*>(reader.ReadComponent());
        checkedHoveringVisual = static_cast<UIVisual*>(reader.ReadComponent());
        checked = reader.ReadBool();
    }

    void UICheckBox::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        checkedNormalVisual = context.Clone(o->checkedNormalVisual);
        checkedPushedVisual = context.Clone(o->checkedPushedVisual);
        checkedHoveringVisual = context.Clone(o->checkedHoveringVisual);
        checked = o->checked;
    }
}