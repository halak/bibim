#pragma once
#ifndef __BIBIM_GAMEWINDOW_H__
#define __BIBIM_GAMEWINDOW_H__

#   include <Bibim/Config.h>

#   if (defined(BIBIM_PLATFORM_WINDOWS))
#       include <Bibim/GameWindow.Windows.h>
#   else
#       include <Bibim/GameWindow.Mobile.h>
#   endif

#endif