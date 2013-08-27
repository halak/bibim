#include <Bibim/Config.h>
#include <Bibim/UIMouseEventArgs.h>

namespace Bibim
{
    UIMouseEventArgs::UIMouseEventArgs()
        : UIEventArgs(),
          dispatcher(nullptr),
          position(Point2::Zero),
          movement(Point2::Zero),
          isLeftButtonPressed(false),
          isRightButtonPressed(false),
          isMiddleButtonPressed(false)
    {
    }

    UIMouseEventArgs::UIMouseEventArgs(UIMouseEventDispatcher* dispatcher, UIVisual* target)
        : UIEventArgs(target),
          dispatcher(dispatcher),
          position(Point2::Zero),
          movement(Point2::Zero),
          isLeftButtonPressed(false),
          isRightButtonPressed(false),
          isMiddleButtonPressed(false)
    {
    }

    UIMouseEventArgs::UIMouseEventArgs(UIMouseEventDispatcher* dispatcher, UIVisual* target, Point2 position, Point2 movement)
        : UIEventArgs(target),
          dispatcher(dispatcher),
          position(position),
          movement(movement),
          isLeftButtonPressed(false),
          isRightButtonPressed(false),
          isMiddleButtonPressed(false)
    {
    }

    UIMouseEventArgs::UIMouseEventArgs(UIMouseEventDispatcher* dispatcher, UIVisual* target, Point2 position, Point2 movement, bool isLeftButtonPressed, bool isRightButtonPressed, bool isMiddleButtonPressed)
        : UIEventArgs(target),
          dispatcher(dispatcher),
          position(position),
          movement(movement),
          isLeftButtonPressed(isLeftButtonPressed),
          isRightButtonPressed(isRightButtonPressed),
          isMiddleButtonPressed(isMiddleButtonPressed)
    {
    }

    UIMouseEventArgs::UIMouseEventArgs(const UIMouseEventArgs& original)
        : UIEventArgs(original),
          dispatcher(original.dispatcher),
          position(original.position),
          movement(original.movement),
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