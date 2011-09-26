#include <Bibim/PCH.h>
#include <Bibim/UIButton.h>
#include <Bibim/UIFittedFrame.h>
#include <Bibim/UIMouseButtonEventArgs.h>
#include <Bibim/UIWindow.h>

namespace Bibim
{
    UIButton::UIButton()
        : currentState(NormalState),
          normalWindow(new UIWindow()),
          pushedWindow(new UIWindow()),
          hoveringWindow(new UIWindow()),
          currentWindow(normalWindow),
          hideInactives(true),
          stateSizeReferenced(true)
    {
        normalWindow->SetFrame(UIFittedFrame::Instance);
        normalWindow->Show();
        pushedWindow->SetFrame(UIFittedFrame::Instance);
        pushedWindow->Hide();
        hoveringWindow->SetFrame(UIFittedFrame::Instance);
        hoveringWindow->Hide();
        Add(hoveringWindow);
        Add(pushedWindow);
        Add(normalWindow);
    }

    UIButton::~UIButton()
    {
    }

    Vector2 UIButton::GetDesiredSize()
    {
        if (GetStateSizeReferenced())
        {
            // 활성화된 상태의 첫번째 자식 객체는 배경일 확률이 높으므로 그 객체의 크기를 사용한다.
            if (currentWindow && currentWindow->GetChildren().empty() == false)
                return currentWindow->GetChildren().front()->GetDesiredSize();
        }

        return UIVisual::GetDesiredSize();
    }

    void UIButton::SetCurrentState(State value)
    {
        if (currentState != value)
        {
            currentState = value;
            UpdateLayout();
        }
    }

    void UIButton::SetHideInactives(bool value)
    {
        if (hideInactives != value)
        {
            hideInactives = value;
            UpdateLayout();
        }
    }

    void UIButton::UpdateLayout()
    {
        currentWindow = OnUpdateLayout();
    }

    UIWindow* UIButton::OnUpdateLayout()
    {
        UIWindow* activeWindow = nullptr;
        switch (currentState)
        {
            case NormalState:
                activeWindow = normalWindow;
                break;
            case PushedState:
                activeWindow = pushedWindow;
                break;
            case HoveringState:
                activeWindow = hoveringWindow;
                break;
        }

        activeWindow->BringToFront();
        activeWindow->Show();

        if (GetHideInactives())
        {
            switch (currentState)
            {
                case NormalState:
                    pushedWindow->Hide();
                    hoveringWindow->Hide();
                    break;
                case PushedState:
                    normalWindow->Hide();
                    hoveringWindow->Hide();
                    break;
                case HoveringState:
                    normalWindow->Hide();
                    pushedWindow->Hide();
                    break;
            }
        }

        return activeWindow;
    }
    
    void UIButton::OnMouseEnter(const UIMouseEventArgs& /*args*/)
    {
        SetCurrentState(HoveringState);
    }

    void UIButton::OnMouseLeave(const UIMouseEventArgs& /*args*/)
    {
        SetCurrentState(NormalState);
    }

    bool UIButton::OnMouseButtonDown(const UIMouseButtonEventArgs& args)
    {
        if (args.GetButtonCode() == Key::MouseLeftButton)
            SetCurrentState(PushedState);

        return false;
    }

    bool UIButton::OnMouseButtonUp(const UIMouseButtonEventArgs& args)
    {
        if (args.GetButtonCode() == Key::MouseLeftButton)
            SetCurrentState(HoveringState);

        return false;
    }

    UIElement* UIButton::Read(AssetStreamReader& /*reader*/, UIElement* /*existingInstance*/)
    {
        return nullptr;
    }
}