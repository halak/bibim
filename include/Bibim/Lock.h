#pragma once
#ifndef __BIBIM_LOCK_H__
#define __BIBIM_LOCK_H__

#   include <Bibim/Config.h>

#   if (defined(BIBIM_PLATFORM_WINDOWS))
#       include <Bibim/Lock.Windows.h>
#   elif (defined(BIBIM_PLATFORM_UNIX))
#       include <Bibim/Lock.Unix.h>
#   endif

#endif