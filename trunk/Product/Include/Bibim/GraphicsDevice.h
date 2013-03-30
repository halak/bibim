#pragma once
#ifndef __BIBIM_GRAPHICSDEVICE_H__
#define __BIBIM_GRAPHICSDEVICE_H__

#   include <Bibim/Foundation.h>

#   if (defined(BIBIM_USE_DIRECTX9))
#       include <Bibim/GraphicsDevice.DX9.h>
#   elif (defined(BIBIM_USE_OPENGLES2))
#       include <Bibim/GraphicsDevice.GLES2.h>
#   endif

#endif