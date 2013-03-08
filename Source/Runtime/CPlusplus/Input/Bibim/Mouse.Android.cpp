#include <Bibim/PCH.h>
#include <Bibim/Mouse.h>
#include <Bibim/Window.h>

namespace Bibim
{
    const MouseState& Mouse::GetState()
    {
        return MouseState::Empty;
    }

    void Mouse::SetPosition(Point2 /*value*/)
    {
    }

    void Mouse::SetVisible(bool /*value*/)
    {
    }
}