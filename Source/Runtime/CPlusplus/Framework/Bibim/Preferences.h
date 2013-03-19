#pragma once
#ifndef __BIBIM_PREFERENCES_H__
#define __BIBIM_PREFERENCES_H__

#   include <Bibim/Foundation.h>

#   if (defined(BIBIM_PLATFORM_WINDOWS))
#       include <Bibim/Preferences.Windows.h>
#   elif (defined(BIBIM_PLATFORM_ANDROID))
#       include <Bibim/Preferences.Android.h>
#   elif (defined(BIBIM_PLATFORM_IOS))
#       include <Bibim/Preferences.iOS.h>
#   endif

#endif