#include <Bibim/PCH.h>
#include <Bibim/Mouse.h>
#include <Bibim/Window.h>

namespace Bibim
{
    Mouse::Mouse()
        : window(nullptr),
          isVisible(true)
    {
    }

    Mouse::Mouse(Window* window)
        : window(window),
          isVisible(true)
    {
    }

    Mouse::~Mouse()
    {
    }
}