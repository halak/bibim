#pragma once
#ifndef __BIBIM_BLENDMODE_H__
#define __BIBIM_BLENDMODE_H__

#include <Bibim/FWD.h>

namespace Bibim
{
    enum BlendMode
    {
        NormalBlend,
        AdditiveBlend,
        LightenBlend,
        DarkenBlend,
        MultiplyBlend,
        ScreenBlend,
        LinearDodgeBlend = AdditiveBlend,
    };
}

#endif