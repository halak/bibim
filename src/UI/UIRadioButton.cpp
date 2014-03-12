#include <Bibim/Config.h>
#include <Bibim/UIRadioButton.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/UIMouseEventArgs.h>
#include <Bibim/UIWindow.h>

namespace Bibim
{
    BBImplementsComponent(UIRadioButton);

    UIRadioButton::UIRadioButton()
    {
    }

    UIRadioButton::~UIRadioButton()
    {
    }

    void UIRadioButton::OnChecked()
    {
        UIPanel* parent = GetParent();
        if (parent == nullptr)
            return;

        const UIPanel::VisualCollection& siblings = parent->GetChildren();
        for (UIPanel::VisualCollection::const_iterator it = siblings.begin(); it != siblings.end(); ++it)
        {
            UIVisual* item = (*it);
            if (item != this && item->GetClassID() == UIRadioButton::ClassID)
                static_cast<UIRadioButton*>(item)->SetChecked(false);
        }
    }
    
    void UIRadioButton::OnUnchecked()
    {
    }

    bool UIRadioButton::OnMouseClick(const UIMouseEventArgs& args)
    {
        if (GetChecked() == false)
            return Base::OnMouseClick(args);
        else
            return true;
    }

    void UIRadioButton::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
    }

    void UIRadioButton::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
    }
}