#include <Bibim/PCH.h>
#include <Bibim/Keyboard.h>
#include <Bibim/Assert.h>
#include <Bibim/Window.h>

namespace Bibim
{
    const KeyboardState& Keyboard::GetState()
    {
        return state;
    }
}