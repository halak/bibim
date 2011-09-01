#include <Bibim/PCH.h>
#include <Bibim/UIKeyboardEventArgs.h>

namespace Bibim
{
    UIKeyboardEventArgs::UIKeyboardEventArgs()
        : UIEventArgs(nullptr),
          keyCode0(Key::None),
          keyCode1(Key::None),
          keyCode2(Key::None),
          keyCode3(Key::None)
    {
    }

    UIKeyboardEventArgs::UIKeyboardEventArgs(UIVisual* target, Key::Code keyCode)
        : UIEventArgs(target),
          keyCode0(keyCode),
          keyCode1(Key::None),
          keyCode2(Key::None),
          keyCode3(Key::None)
    {
    }

    UIKeyboardEventArgs::UIKeyboardEventArgs(UIVisual* target, Key::Code keyCode0, Key::Code keyCode1, Key::Code keyCode2, Key::Code keyCode3)
        : UIEventArgs(target),
          keyCode0(keyCode0),
          keyCode1(keyCode1),
          keyCode2(keyCode2),
          keyCode3(keyCode3)
    {
    }

    UIKeyboardEventArgs::UIKeyboardEventArgs(const UIKeyboardEventArgs& original)
        : UIEventArgs(original),
          keyCode0(original.keyCode0),
          keyCode1(original.keyCode1),
          keyCode2(original.keyCode2),
          keyCode3(original.keyCode3)
    {
    }

    UIKeyboardEventArgs::~UIKeyboardEventArgs()
    {
    }

    UIKeyboardEventArgs* UIKeyboardEventArgs::Clone() const
    {
        return new UIKeyboardEventArgs(*this);
    }
}