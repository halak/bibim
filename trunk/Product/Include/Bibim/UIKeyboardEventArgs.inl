namespace Bibim
{
    UIKeyboardEventDispatcher* UIKeyboardEventArgs::GetDispatcher() const
    {
        return dispatcher;
    }

    bool UIKeyboardEventArgs::Contains(Key::Code keyCode) const
    {
        return keyCode0 == keyCode ||
               keyCode1 == keyCode ||
               keyCode2 == keyCode ||
               keyCode3 == keyCode;
    }

    Key::Code UIKeyboardEventArgs::GetKeyCode0() const
    {
        return keyCode0;
    }

    Key::Code UIKeyboardEventArgs::GetKeyCode1() const
    {
        return keyCode1;
    }

    Key::Code UIKeyboardEventArgs::GetKeyCode2() const
    {
        return keyCode2;
    }

    Key::Code UIKeyboardEventArgs::GetKeyCode3() const
    {
        return keyCode3;
    }

    Key::Code UIKeyboardEventArgs::GetKeyCodeAt(int index) const
    {
        switch (index)
        {
            case 0: return keyCode0;
            case 1: return keyCode1;
            case 2: return keyCode2;
            case 3: return keyCode3;
            default: return Key::None;
        }
    }
}