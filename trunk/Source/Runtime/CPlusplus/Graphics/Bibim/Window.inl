#pragma once
#ifndef __BIBIM_WINDOW_INL__
#define __BIBIM_WINDOW_INL__

namespace Bibim
{
    Window::Window()
        : wheelValue(0)
    {
    }

    int Window::GetWheel() const
    {
        return wheelValue;
    }

    void Window::SetWheel(int value)
    {
        wheelValue = value;
    }
}

#endif