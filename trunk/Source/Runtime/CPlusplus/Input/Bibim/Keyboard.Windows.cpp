#include <Bibim/PCH.h>
#include <Bibim/Keyboard.h>
#include <Bibim/Assert.h>
#include <Bibim/Window.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

namespace Bibim
{
    const KeyboardState& Keyboard::GetState()
    {
        BBStaticAssert(sizeof(allowedKeys) == sizeof(state.Keys));

        if (window && window->GetHandle() == ::GetActiveWindow())
        {
            int code = 0;
            for (int i = 0; i < sizeof(allowedKeys) / sizeof(allowedKeys[0]); i++)
            {
                int& keyStateField = state.Keys[i];
                const int allowField = allowedKeys[i];
                for (unsigned int k = 0x80000000; k != 0x00000000; k >>= 1, code++)
                {
                    if ((allowField & k) != 0x00000000)
                    {
                        const int vkCode = static_cast<int>(code); // 일단 그대로 Mapping 했으므로 문제 없습니다.

                        if (GetAsyncKeyState(vkCode))
                            keyStateField |= k;
                        else
                            keyStateField &= ~k;
                    }
                    else
                        keyStateField &= ~k;
                }
            }

            return state;
        }
        else
            return KeyboardState::Empty;
    }
}