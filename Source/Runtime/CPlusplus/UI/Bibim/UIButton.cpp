#include <Bibim/Config.h>
#include <Bibim/UIButton.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/UIMouseButtonEventArgs.h>
#include <Bibim/UIPickingContext.h>
#include <Bibim/UIVisual.h>

namespace Bibim
{
    BBImplementsComponent(UIButton);

    UIButton::UIButton()
        : currentState(NormalState),
          pushedVisual(),
          hoveringVisual(),
          currentVisual(),
          hideInactives(true),
          focusVisible(false),
          frozen(false)
    {
        SetFocusable(true);
    }

    UIButton::~UIButton()
    {
    }

    void UIButton::SetStateTemplate(UIVisualPtr& field, UIVisual* value)
    {
        if (field != value)
        {
            if (field)
                Remove(field);

            field = value;

            if (field)
                Add(field);
        }
    }

    void UIButton::SetNormal(UIVisual* value)
    {
        SetStateTemplate(normalVisual, value);
    }

    void UIButton::SetPushed(UIVisual* value)
    {
        SetStateTemplate(pushedVisual, value);
    }

    void UIButton::SetHovering(UIVisual* value)
    {
        SetStateTemplate(hoveringVisual, value);
    }

    void UIButton::SetCurrentState(State value)
    {
        currentState = value;
        UpdateLayout();
    }

    void UIButton::SetHideInactives(bool value)
    {
        if (hideInactives != value)
        {
            hideInactives = value;
            UpdateLayout();
        }
    }

    void UIButton::SetFocusVisible(bool value)
    {
        if (focusVisible != value)
        {
            focusVisible = value;
            UpdateLayout();
        }
    }

    void UIButton::SetFrozen(bool value)
    {
        if (frozen != value)
        {
            frozen = value;
            UpdateLayout();
        }
    }

    void UIButton::UpdateLayout()
    {
        currentVisual = OnUpdateLayout();
    }

    UIVisual* UIButton::OnUpdateLayout()
    {
        UIVisual* activeVisual = nullptr;
        if (frozen == false)
        {
            switch (currentState)
            {
                case NormalState:
                    activeVisual = normalVisual;
                    break;
                case PushedState:
                    activeVisual = pushedVisual;
                    break;
                case HoveringState:
                    activeVisual = hoveringVisual;
                    break;
            }

            if (activeVisual == normalVisual &&
                IsFocused() && GetFocusVisible())
            {
                activeVisual = hoveringVisual;
            }
        }
        else
            activeVisual = normalVisual;

        if (activeVisual)
        {
            activeVisual->BringToFront();
            activeVisual->Show();
        }

        if (GetHideInactives())
        {
            if (activeVisual == normalVisual)
            {
                if (pushedVisual)
                    pushedVisual->Hide();
                if (hoveringVisual)
                    hoveringVisual->Hide();
            }
            else if (activeVisual == pushedVisual)
            {
                if (normalVisual)
                    normalVisual->Hide();
                if (hoveringVisual)
                    hoveringVisual->Hide();
            }
            else if (activeVisual == hoveringVisual)
            {
                if (normalVisual)
                    normalVisual->Hide();
                if (pushedVisual)
                    pushedVisual->Hide();
            }
        }

        return activeVisual;
    }

    void UIButton::OnPick(UIPickingContext& context)
    {
        Base::OnPick(context);
        if (UIVisual* result = context.GetResult())
        {
            if (result == normalVisual ||
                result == pushedVisual ||
                result == hoveringVisual)
                context.SetResult(this);
        }
    }

    void UIButton::OnFocused()
    {
        UpdateLayout();
    }

    void UIButton::OnBlured()
    {
        UpdateLayout();
    }

    void UIButton::OnMouseEnter(const UIMouseEventArgs& /*args*/)
    {
        if (frozen == false)
            SetCurrentState(HoveringState);
    }

    void UIButton::OnMouseLeave(const UIMouseEventArgs& /*args*/)
    {
        SetCurrentState(NormalState);
    }

    bool UIButton::OnMouseButtonDown(const UIMouseButtonEventArgs& args)
    {
        if (frozen == false && args.GetButtonCode() == Key::MouseLeftButton)
            SetCurrentState(PushedState);

        return false;
    }

    bool UIButton::OnMouseButtonUp(const UIMouseButtonEventArgs& args)
    {
        if (args.GetButtonCode() == Key::MouseLeftButton)
        {
            if (frozen == false)
                SetCurrentState(HoveringState);
            else
                SetCurrentState(NormalState);
        }

        return false;
    }

    bool UIButton::OnMouseClick(const UIMouseEventArgs& /*args*/)
    {
        return true;
    }

    void UIButton::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        normalVisual = static_cast<UIVisual*>(reader.ReadComponent());
        pushedVisual = static_cast<UIVisual*>(reader.ReadComponent());
        hoveringVisual = static_cast<UIVisual*>(reader.ReadComponent());
        hideInactives = reader.ReadBool();
        focusVisible = reader.ReadBool();
        frozen = reader.ReadBool();
        SetCurrentState(NormalState);
    }

    void UIButton::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        normalVisual = context.Clone(o->normalVisual);
        pushedVisual = context.Clone(o->pushedVisual);
        hoveringVisual = context.Clone(o->hoveringVisual);
        hideInactives = o->hideInactives;
        focusVisible = o->focusVisible;
        frozen = o->frozen;
        SetCurrentState(NormalState);
    }
}