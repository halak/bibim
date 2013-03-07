﻿#pragma once
#ifndef __BIBIM_GAMEFRAMEWORK_H__
#define __BIBIM_GAMEFRAMEWORK_H__

#   include <Bibim/Foundation.h>

#   if (defined(BIBIM_PLATFORM_WINDOWS))
#       include <Bibim/GameFramework.Windows.h>
#   elif (defined(BIBIM_PLATFORM_ANDROID))
#       include <Bibim/GameFramework.Android.h>
#   endif

#endif