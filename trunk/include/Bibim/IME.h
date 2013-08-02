#pragma once
#ifndef __BIBIM_IME_H__
#define __BIBIM_IME_H__

#   include <Bibim/Config.h>

#   if (defined(BIBIM_PLATFORM_WINDOWS))
#       include <Bibim/IME.Windows.h>
#   else
#       include <Bibim/IME.Mobile.h>
#   endif

#endif