#pragma once
#ifndef __BIBIM_LOCK_H__
#define __BIBIM_LOCK_H__

#   include <Bibim/Foundation.h>

#   if (defined(BIBIM_PLATFORM_WINDOWS))
#       include <Bibim/Lock.Windows.h>
#   endif

#endif