#pragma once
#ifndef __BIBIM_SOUNDFX_H__
#define __BIBIM_SOUNDFX_H__

#   include <Bibim/Foundation.h>

#   if (defined(BIBIM_PLATFORM_WINDOWS) && defined(BIBIM_PLATFORM_LINUX) && defined(BIBIM_PLATFORM_MACOS))
#       include <Bibim/SoundFX.Irrklang.h>
#   elif (defined(BIBIM_PLATFORM_ANDROID))
#       include <Bibim/SoundFX.Android.h>
#   elif (defined(BIBIM_PLATFORM_IOS))
#       include <Bibim/SoundFX.iOS.h>
#   endif

#endif