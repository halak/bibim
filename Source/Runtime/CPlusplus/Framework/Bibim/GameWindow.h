#pragma once
#ifndef __BIBIM_GAMEWINDOW_H__
#define __BIBIM_GAMEWINDOW_H__

#   include <Bibim/Foundation.h>

#   if (defined(BIBIM_PLATFORM_WINDOWS))
#       include <Bibim/GameWindow.Windows.h>
#   elif (defined(BIBIM_PLATFORM_ANDROID))
#       include <Bibim/GameWindow.Android.h>
#   endif

#endif