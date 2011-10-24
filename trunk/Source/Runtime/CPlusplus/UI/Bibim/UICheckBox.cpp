#include <Bibim/PCH.h>
#include <Bibim/UICheckBox.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/UIFittedFrame.h>
#include <Bibim/UIMouseEventArgs.h>
#include <Bibim/UIWindow.h>

namespace Bibim
{
    BBImplementsComponent(UICheckBox);

    UICheckBox::UICheckBox()
        : checkedNormalWindow(new UIWindow()),
          checkedPushedWindow(new UIWindow()),
          checkedHoveringWindow(new UIWindow()),
          checked(false)
    {
        checkedNormalWindow->SetFrame(UIFittedFrame::Instance);
        checkedNormalWindow->Hide();
        checkedPushedWindow->SetFrame(UIFittedFrame::Instance);
        checkedPushedWindow->Hide();
        checkedHoveringWindow->SetFrame(UIFittedFrame::Instance);
        checkedHoveringWindow->Hide();
        Add(checkedHoveringWindow);
        Add(checkedPushedWindow);
        Add(checkedNormalWindow);
    }

    UICheckBox::~UICheckBox()
    {
    }

    void UICheckBox::SetChecked(bool value)
    {
        if (checked != value)
        {
            checked = value;
            UpdateLayout();
        }
    }

    UIWindow* UICheckBox::OnUpdateLayout()
    {
        UIWindow* const windows[] = 
        {
            GetNormalWindow(), GetPushedWindow(), GetHoveringWindow(),
            checkedNormalWindow, checkedPushedWindow, checkedHoveringWindow,
        };
        BBStaticAssert(NormalState == 0 && PushedState == 1 && HoveringState == 2);

        const int activeWindowIndex = static_cast<int>(GetCurrentState()) + ((checked) ? 3 : 0);
        BBAssertDebug(0 <= activeWindowIndex && activeWindowIndex < sizeof(windows) / sizeof(windows[0]));
        UIWindow* activeWindow = windows[activeWindowIndex];

        activeWindow->BringToFront();
        activeWindow->Show();

        if (GetHideInactives())
        {
            for (int i = 0; i < sizeof(windows) / sizeof(windows[0]); i++)
            {
                if (i != activeWindowIndex)
                    windows[i]->Hide();
            }
        }

        return activeWindow;
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
        checkedNormalWindow = static_cast<UIWindow*>(reader.ReadComponent());
        checkedPushedWindow = static_cast<UIWindow*>(reader.ReadComponent());
        checkedHoveringWindow = static_cast<UIWindow*>(reader.ReadComponent());
        checked = reader.ReadBool();
    }

    void UICheckBox::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        checkedNormalWindow = context.Clone(o->checkedNormalWindow);
        checkedPushedWindow = context.Clone(o->checkedPushedWindow);
        checkedHoveringWindow = context.Clone(o->checkedHoveringWindow);
        checked = o->checked;
    }
}