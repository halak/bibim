#include <Bibim/PCH.h>
#include <Bibim/UISimpleDomain.h>
#include <Bibim/Assert.h>
#include <Bibim/UIWindow.h>

namespace Bibim
{
    UISimpleDomain::UISimpleDomain()
        : focus(nullptr)
    {
    }

    UISimpleDomain::UISimpleDomain(UIWindow* root)
        : UIDomain(root),
          focus(nullptr)
    {
    }

    UISimpleDomain::UISimpleDomain(UIWindow* root, UIVisual* focus)
        : UIDomain(root),
          focus(nullptr)
    {
        SetFocus(focus);
    }

    UISimpleDomain::~UISimpleDomain()
    {
        if (focus)
            Blur(focus);
    }

    UIVisual* UISimpleDomain::GetFocus() const
    {
        return focus;
    }

    void UISimpleDomain::SetFocus(UIVisual* value)
    {
        if (value && value->GetFocusable() == false)
            return;

        if (focus != value)
        {
            if (focus)
                Blur(focus);

            focus = value;

            if (focus)
                Focus(focus);
        }
    }

    void UISimpleDomain::OnDestructed(UIVisual* visual)
    {
        BBAssert(focus == visual);
        focus = nullptr;
    }
}