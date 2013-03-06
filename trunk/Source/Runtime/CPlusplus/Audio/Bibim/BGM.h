#pragma once
#ifndef __BIBIM_BGM_H__
#define __BIBIM_BGM_H__

#   include <Bibim/Foundation.h>

#   if (defined(BIBIM_PLATFORM_WINDOWS) && defined(BIBIM_PLATFORM_LINUX) && defined(BIBIM_PLATFORM_MACOS))
#       include <Bibim/BGM.Irrklang.h>
#   elif (defined(BIBIM_PLATFORM_ANDROID))
#       include <Bibim/BGM.Android.h>
#   elif (defined(BIBIM_PLATFORM_IOS))
#       include <Bibim/BGM.iOS.h>
#   endif

#endif