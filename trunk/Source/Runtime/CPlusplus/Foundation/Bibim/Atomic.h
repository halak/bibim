#pragma once
#ifndef __BIBIM_ATOMIC_H__
#define __BIBIM_ATOMIC_H__

#   include <Bibim/Foundation.h>

#   if (defined(BIBIM_PLATFORM_WINDOWS))
#       include <Bibim/Atomic.Windows.h>
#   endif

#endif