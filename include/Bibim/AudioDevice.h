#pragma once
#ifndef __BIBIM_AUDIODEVICE_H__
#define __BIBIM_AUDIODEVICE_H__

#   include <Bibim/Foundation.h>

#   if (defined(BIBIM_PLATFORM_WINDOWS) || defined(BIBIM_PLATFORM_LINUX) || defined(BIBIM_PLATFORM_MACOS))
#       include <Bibim/AudioDevice.AL.h>
#   else
#       include <Bibim/AudioDevice.AL.h>
#   endif

#endif