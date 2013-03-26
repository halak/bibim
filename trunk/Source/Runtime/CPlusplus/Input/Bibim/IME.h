#pragma once
#ifndef __BIBIM_IME_H__
#define __BIBIM_IME_H__

#   include <Bibim/Foundation.h>

#   if (defined(BIBIM_PLATFORM_WINDOWS))
#       include <Bibim/IME.Windows.h>
#   elif (defined(BIBIM_PLATFORM_ANDROID))
#       include <Bibim/IME.Android.h>
#   elif (defined(BIBIM_PLATFORM_IOS))
#       include <Bibim/IME.iOS.h>
#   endif

#endif