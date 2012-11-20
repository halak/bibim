#include <Bibim/PCH.h>
#include <Bibim/UIMouseEventArgs.h>

namespace Bibim
{
    UIMouseEventArgs::UIMouseEventArgs()
        : UIEventArgs(),
          position(Point2::Zero),
          isLeftButtonPressed(false),
          isRightButtonPressed(false),
          isMiddleButtonPressed(false)
    {
    }

    UIMouseEventArgs::UIMouseEventArgs(UIVisual* target)
        : UIEventArgs(target),
          position(Point2::Zero),
          isLeftButtonPressed(false),
          isRightButtonPressed(false),
          isMiddleButtonPressed(false)
    {
    }

    UIMouseEventArgs::UIMouseEventArgs(UIVisual* target, Point2 position)
        : UIEventArgs(target),
          position(position),
          isLeftButtonPressed(false),
          isRightButtonPressed(false),
          isMiddleButtonPressed(false)
    {
    }

    UIMouseEventArgs::UIMouseEventArgs(UIVisual* target, Point2 position, bool isLeftButtonPressed, bool isRightButtonPressed, bool isMiddleButtonPressed)
        : UIEventArgs(target),
          position(position),
          isLeftButtonPressed(isLeftButtonPressed),
          isRightButtonPressed(isRightButtonPressed),
          isMiddleButtonPressed(isMiddleButtonPressed)
    {
    }

    UIMouseEventArgs::UIMouseEventArgs(const UIMouseEventArgs& original)
        : UIEventArgs(original),
          position(original.position),
          isLeftButtonPressed(original.isLeftButtonPressed),
          isRightButtonPressed(original.isRightButtonPressed),
          isMiddleButtonPressed(original.isMiddleButtonPressed)
    {
    }

    UIMouseEventArgs::~UIMouseEventArgs()
    {
    }

    UIMouseEventArgs* UIMouseEventArgs::Clone() const
    {
        return new UIMouseEventArgs(*this);
    }

    void UIMouseEventArgs::Serialize(Serializer& context) const
    {
        UIEventArgs::Serialize(context);
        context.Push(position.X);
        context.Push(position.Y);
        context.Push(isLeftButtonPressed);
        context.Push(isRightButtonPressed);
        context.Push(isMiddleButtonPressed);
    }
}