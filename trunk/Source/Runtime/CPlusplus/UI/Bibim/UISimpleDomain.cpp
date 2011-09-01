#include <Bibim/PCH.h>
#include <Bibim/UISimpleDomain.h>
#include <Bibim/UIWindow.h>

namespace Bibim
{
    UISimpleDomain::UISimpleDomain()
    {
    }

    UISimpleDomain::UISimpleDomain(UIWindow* root)
        : UIDomain(root)
    {
    }

    UISimpleDomain::UISimpleDomain(UIWindow* root, UIVisual* focus)
        : UIDomain(root),
          focus(focus)
    {
    }

    UISimpleDomain::~UISimpleDomain()
    {
    }

    UIVisual* UISimpleDomain::GetFocus() const
    {
        return focus;
    }

    void UISimpleDomain::SetFocus(UIVisual* value)
    {
        focus = value;
    }
}