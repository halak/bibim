#pragma once
#ifndef __BIBIM_WINDOW_INL__
#define __BIBIM_WINDOW_INL__

namespace Bibim
{
    Signal<int>& Window::MouseWheel()
    {
        return mouseWheel;
    }
}

#endif