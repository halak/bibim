#include <Bibim/PCH.h>
#include <Bibim/UIMouseWheelEventArgs.h>

namespace Bibim
{
    UIMouseWheelEventArgs::UIMouseWheelEventArgs()
        : UIMouseEventArgs(),
          wheelDelta(0)
    {
    }

    UIMouseWheelEventArgs::UIMouseWheelEventArgs(UIVisual* target, Point2 position, int wheelDelta)
        : UIMouseEventArgs(target, position),
          wheelDelta(wheelDelta)
    {
    }

    UIMouseWheelEventArgs::UIMouseWheelEventArgs(UIVisual* target, Point2 position, bool isLeftButtonPressed, bool isRightButtonPressed, bool isMiddleButtonPressed, int wheelDelta)
        : UIMouseEventArgs(target, position, isLeftButtonPressed, isRightButtonPressed, isMiddleButtonPressed),
          wheelDelta(wheelDelta)
    {
    }

    UIMouseWheelEventArgs::UIMouseWheelEventArgs(const UIMouseEventArgs& base, int wheelDelta)
        : UIMouseEventArgs(base),
          wheelDelta(wheelDelta)
    {
    }

    UIMouseWheelEventArgs::UIMouseWheelEventArgs(const UIMouseWheelEventArgs& original)
        : UIMouseEventArgs(original),
          wheelDelta(original.wheelDelta)
    {
    }

    UIMouseWheelEventArgs::~UIMouseWheelEventArgs()
    {
    }

    UIMouseWheelEventArgs* UIMouseWheelEventArgs::Clone() const
    {
        return new UIMouseWheelEventArgs(*this);
    }
}