#include <Bibim/PCH.h>
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
        if (checkedNormalVisual != value)
        {
            if (checkedNormalVisual)
                Remove(checkedNormalVisual);

            checkedNormalVisual = value;

            if (checkedNormalVisual)
                Add(checkedNormalVisual);
        }
    }

    void UICheckBox::SetCheckedPushed(UIVisual* value)
    {
        if (checkedPushedVisual != value)
        {
            if (checkedPushedVisual)
                Remove(checkedPushedVisual);

            checkedPushedVisual = value;

            if (checkedPushedVisual)
                Add(checkedPushedVisual);
        }
    }

    void UICheckBox::SetCheckedHovering(UIVisual* value)
    {
        if (checkedHoveringVisual != value)
        {
            if (checkedHoveringVisual)
                Remove(checkedHoveringVisual);

            checkedHoveringVisual = value;

            if (checkedHoveringVisual)
                Add(checkedHoveringVisual);
        }
    }

    void UICheckBox::SetChecked(bool value)
    {
        if (checked != value)
        {
            checked = value;
            UpdateLayout();
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

        const int activeVisualIndex = static_cast<int>(GetCurrentState()) + ((checked) ? 3 : 0);
        BBAssertDebug(0 <= activeVisualIndex && activeVisualIndex < sizeof(visuals) / sizeof(visuals[0]));
        UIVisual* activeVisual = visuals[activeVisualIndex];

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

    bool UICheckBox::OnMouseClick(const UIMouseEventArgs& /*args*/)
    {
        checked = !checked;
        UpdateLayout();
        return false;
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