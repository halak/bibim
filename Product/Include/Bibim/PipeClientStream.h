#pragma once
#ifndef __BIBIM_PIPECLIENTSTREAM_H__
#define __BIBIM_PIPECLIENTSTREAM_H__

#   include <Bibim/Foundation.h>

#   if (defined(BIBIM_PLATFORM_WINDOWS))
#       include <Bibim/PipeClientStream.Windows.h>
#   else
#   endif

#endif