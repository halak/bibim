#include <Bibim/Config.h>
#include <Bibim/UIMouseWheelEventArgs.h>

namespace Bibim
{
    UIMouseWheelEventArgs::UIMouseWheelEventArgs()
        : UIMouseEventArgs(),
          wheelDelta(0)
    {
    }

    UIMouseWheelEventArgs::UIMouseWheelEventArgs(UIMouseEventDispatcher* dispatcher, UIVisual* target, Point2 position, int wheelDelta)
        : UIMouseEventArgs(dispatcher, target, position, Point2::Zero),
          wheelDelta(wheelDelta)
    {
    }

    UIMouseWheelEventArgs::UIMouseWheelEventArgs(UIMouseEventDispatcher* dispatcher, UIVisual* target, Point2 position, bool isLeftButtonPressed, bool isRightButtonPressed, bool isMiddleButtonPressed, int wheelDelta)
        : UIMouseEventArgs(dispatcher, target, position, Point2::Zero, isLeftButtonPressed, isRightButtonPressed, isMiddleButtonPressed),
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

    void UIMouseWheelEventArgs::Serialize(Serializer& context) const
    {
        UIMouseEventArgs::Serialize(context);
        context.Push(wheelDelta);
    }
}