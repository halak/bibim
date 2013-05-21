#pragma once
#ifndef __BIBIM_CLIPBOARD_H__
#define __BIBIM_CLIPBOARD_H__

#   include <Bibim/Foundation.h>

#   if (defined(BIBIM_PLATFORM_WINDOWS))
#       include <Bibim/Clipboard.Windows.h>
#   elif (defined(BIBIM_PLATFORM_ANDROID))
#       include <Bibim/Clipboard.Android.h>
#   elif (defined(BIBIM_PLATFORM_IOS))
#       include <Bibim/Clipboard.iOS.h>
#   endif

#endif