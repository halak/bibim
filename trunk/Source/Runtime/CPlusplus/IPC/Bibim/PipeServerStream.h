#pragma once
#ifndef __BIBIM_PIPESERVERSTREAM_H__
#define __BIBIM_PIPESERVERSTREAM_H__

#   include <Bibim/Foundation.h>

#   if (defined(BIBIM_PLATFORM_WINDOWS))
#       include <Bibim/PipeServerStream.Windows.h>
#   else
#   endif

#endif