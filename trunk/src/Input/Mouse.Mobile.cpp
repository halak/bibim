#include <Bibim/Config.h>
#if (defined(BIBIM_PLATFORM_ANDROID) || defined(BIBIM_PLATFORM_IOS))

#include <Bibim/Mouse.h>

namespace Bibim
{
    void Mouse::SetPosition(Point2 /*value*/)
    {
    }

    void Mouse::SetVisible(bool /*value*/)
    {
    }
}

#endif