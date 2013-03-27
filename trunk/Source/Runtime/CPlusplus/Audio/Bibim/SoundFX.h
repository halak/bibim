#pragma once
#ifndef __BIBIM_SOUNDFX_H__
#define __BIBIM_SOUNDFX_H__

#   include <Bibim/Foundation.h>

#   if (defined(BIBIM_PLATFORM_WINDOWS) || defined(BIBIM_PLATFORM_LINUX) || defined(BIBIM_PLATFORM_MACOS))
#       include <Bibim/SoundFX.Irrklang.h>
#   else
#       include <Bibim/SoundFX.AL.h>
#   endif

#endif