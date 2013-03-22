#pragma once
#ifndef __BIBIM_PIPEDASSETPROVIDER_H__
#define __BIBIM_PIPEDASSETPROVIDER_H__

#   include <Bibim/Foundation.h>

#   if (defined(BIBIM_PLATFORM_WINDOWS))
#       include <Bibim/PipedAssetProvider.Default.h>
#   else
#       include <Bibim/PipedAssetProvider.Null.h>
#   endif

#endif