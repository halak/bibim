#pragma once
#ifndef __BIBIM_ENVIRONMENT_H__
#define __BIBIM_ENVIRONMENT_H__

#   include <Bibim/Foundation.h>

#   if (defined(BIBIM_PLATFORM_WINDOWS))
#       include <Bibim/Environment.Windows.h>
#   elif (defined(BIBIM_PLATFORM_ANDROID))
#       include <Bibim/Environment.Android.h>
#   elif (defined(BIBIM_PLATFORM_IOS))
#       include <Bibim/Environment.iOS.h>
#   endif

#endif