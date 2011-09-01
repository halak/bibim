#include <Bibim/PCH.h>
#include <Bibim/Keyboard.h>
#include <Bibim/KeyboardState.h>

namespace Bibim
{
    Keyboard::Keyboard()
        : state(new KeyboardState()),
          window(nullptr)
    {
        AllowDefaultKeys();
    }

    Keyboard::Keyboard(Window* window)
        : state(new KeyboardState()),
          window(nullptr)
    {
        AllowDefaultKeys();
        SetWindow(window);
    }

    Keyboard::~Keyboard()
    {
        delete state;
    }

    Window* Keyboard::GetWindow() const
    {
        return window;
    }

    void Keyboard::SetWindow(Window* value)
    {
        window = value;
    }

    void Keyboard::AllowDefaultKeys()
    {
        for (int i = 0; i < sizeof(allowedKeys) / sizeof(allowedKeys[0]); i++)
            allowedKeys[i] = 0x00000000;
        for (int i = 0; i < sizeof(Key::Codes) / sizeof(Key::Codes[0]) && Key::Codes[i] != Key::None; i++)
            SetAllowKey(Key::Codes[i], true);
    }
}