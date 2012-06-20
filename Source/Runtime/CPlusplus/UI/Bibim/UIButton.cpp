#include <Bibim/PCH.h>
#include <Bibim/UIButton.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/UIMouseButtonEventArgs.h>
#include <Bibim/UIVisual.h>

namespace Bibim
{
    BBImplementsComponent(UIButton);

    UIButton::UIButton()
        : currentState(NormalState),
          normalVisual(),
          pushedVisual(),
          hoveringVisual(),
          currentVisual(),
          hideInactives(true),
          frozen(false)
    {
    }

    UIButton::~UIButton()
    {
    }

    void UIButton::SetNormal(UIVisual* value)
    {
        if (normalVisual != value)
        {
            if (normalVisual)
                Remove(normalVisual);

            normalVisual = value;

            if (normalVisual)
                Add(normalVisual);
        }
    }

    void UIButton::SetPushed(UIVisual* value)
    {
        if (pushedVisual != value)
        {
            if (pushedVisual)
                Remove(pushedVisual);

            pushedVisual = value;

            if (pushedVisual)
                Add(pushedVisual);
        }
    }

    void UIButton::SetHovering(UIVisual* value)
    {
        if (hoveringVisual != value)
        {
            if (hoveringVisual)
                Remove(hoveringVisual);

            hoveringVisual = value;

            if (hoveringVisual)
                Add(hoveringVisual);
        }
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
            switch (currentState)
            {
                case NormalState:
                    if (pushedVisual)
                        pushedVisual->Hide();
                    if (hoveringVisual)
                        hoveringVisual->Hide();
                    break;
                case PushedState:
                    if (normalVisual)
                        normalVisual->Hide();
                    if (hoveringVisual)
                        hoveringVisual->Hide();
                    break;
                case HoveringState:
                    if (normalVisual)
                        normalVisual->Hide();
                    if (pushedVisual)
                        pushedVisual->Hide();
                    break;
            }
        }

        return activeVisual;
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
        frozen = o->frozen;
        SetCurrentState(NormalState);
    }
}