#pragma once
#ifndef __BIBIM_FILESTREAM_H__
#define __BIBIM_FILESTREAM_H__

#   include <Bibim/Foundation.h>

#   if (defined(BIBIM_PLATFORM_WINDOWS))
#       include <Bibim/FileStream.Windows.h>
#   elif (defined(BIBIM_PLATFORM_ANDROID))
#       include <Bibim/FileStream.Android.h>
#   elif (defined(BIBIM_PLATFORM_IOS))
#       include <Bibim/FileStream.iOS.h>
#   endif

#endif