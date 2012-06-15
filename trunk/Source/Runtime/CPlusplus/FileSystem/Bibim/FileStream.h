#pragma once
#ifndef __BIBIM_FILESTREAM_H__
#define __BIBIM_FILESTREAM_H__

#   include <Bibim/Foundation.h>

#   if (defined(BIBIM_PLATFORM_WINDOWS))
#       include <Bibim/FileStream.Windows.h>
#   else
#       include <Bibim/FileStream.CRT.h>
#   endif

#endif