#include <Bibim/PCH.h>
#include <Bibim/UIMouseButtonEventArgs.h>

namespace Bibim
{
    UIMouseButtonEventArgs::UIMouseButtonEventArgs()
        : UIMouseEventArgs(),
          buttonCode(Key::None)
    {
    }

    UIMouseButtonEventArgs::UIMouseButtonEventArgs(UIVisual* target, Point2 position, Key::Code buttonCode)
        : UIMouseEventArgs(target, position),
          buttonCode(buttonCode)
    {
    }

    UIMouseButtonEventArgs::UIMouseButtonEventArgs(UIVisual* target, Point2 position, bool isLeftButtonPressed, bool isRightButtonPressed, bool isMiddleButtonPressed, Key::Code buttonCode)
        : UIMouseEventArgs(target, position, isLeftButtonPressed, isRightButtonPressed, isMiddleButtonPressed),
          buttonCode(buttonCode)
    {
    }

    UIMouseButtonEventArgs::UIMouseButtonEventArgs(const UIMouseEventArgs& base, Key::Code buttonCode)
        : UIMouseEventArgs(base),
          buttonCode(buttonCode)
    {
    }

    UIMouseButtonEventArgs::UIMouseButtonEventArgs(const UIMouseButtonEventArgs& original)
        : UIMouseEventArgs(original),
          buttonCode(original.buttonCode)
    {
    }

    UIMouseButtonEventArgs::~UIMouseButtonEventArgs()
    {
    }

    UIMouseButtonEventArgs* UIMouseButtonEventArgs::Clone() const
    {
        return new UIMouseButtonEventArgs(*this);
    }

    void UIMouseButtonEventArgs::Serialize(Serializer& context) const
    {
        UIMouseEventArgs::Serialize(context);
        if (buttonCode != Key::None)
            context.Push(Key::ToString(buttonCode));
    }
}