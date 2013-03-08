#include <Bibim/PCH.h>
#include <Bibim/Keyboard.h>

namespace Bibim
{
    Keyboard::Keyboard()
        : window(nullptr)
    {
        AllowDefaultKeys();
    }

    Keyboard::Keyboard(Window* window)
        : window(window)
    {
        AllowDefaultKeys();
    }

    Keyboard::~Keyboard()
    {
    }

    void Keyboard::keyDown(Key::Code code)//MOBILE
    {
        const int index = static_cast<int>(static_cast<int>(code) / (sizeof(int) * 8));
        const int bit   = static_cast<int>(static_cast<int>(code) % (sizeof(int) * 8));
        state.Keys[index] |= (0x80000000 >> bit);
    }
    
    void Keyboard::keyUp(Key::Code code)//MOBILE
    {
        const int index = static_cast<int>(static_cast<int>(code) / (sizeof(int) * 8));
        const int bit   = static_cast<int>(static_cast<int>(code) % (sizeof(int) * 8));
        state.Keys[index] &= ~(0x80000000 >> bit);
    }

    void Keyboard::AllowDefaultKeys()
    {
        for (int i = 0; i < sizeof(allowedKeys) / sizeof(allowedKeys[0]); i++)
            allowedKeys[i] = 0x00000000;
        for (int i = 0; i < sizeof(Key::Codes) / sizeof(Key::Codes[0]) && Key::Codes[i] != Key::None; i++)
            SetAllowKey(Key::Codes[i], true);
    }
}