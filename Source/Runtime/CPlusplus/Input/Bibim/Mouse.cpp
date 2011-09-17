#include <Bibim/PCH.h>
#include <Bibim/Mouse.h>
#include <Bibim/Window.h>

namespace Bibim
{
    Mouse::Mouse()
        : window(nullptr)
    {
    }

    Mouse::Mouse(Window* window)
        : window(window)
    {
    }

    Mouse::~Mouse()
    {
    }
}