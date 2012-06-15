#include <Bibim/PCH.h>
#include <Bibim/UIEventArgs.h>
#include <Bibim/UIWindow.h>

namespace Bibim
{
    UIEventArgs::UIEventArgs()
        : target(nullptr)
    {
    }

    UIEventArgs::UIEventArgs(UIVisual* target)
        : target(target)
    {
    }

    UIEventArgs::UIEventArgs(const UIEventArgs& original)
        : target(original.target)
    {
    }

    UIEventArgs::~UIEventArgs()
    {
    }

    UIEventArgs* UIEventArgs::Clone() const
    {
        return new UIEventArgs(*this);
    }
}