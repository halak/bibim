#pragma once
#ifndef __BIBIM_DYNAMICTEXTURE2D_H__
#define __BIBIM_DYNAMICTEXTURE2D_H__

#   include <Bibim/Foundation.h>

#   if (defined(BIBIM_USE_DIRECTX9))
#       include <Bibim/DynamicTexture2D.DX9.h>
#   elif (defined(BIBIM_USE_OPENGLES2))
#       include <Bibim/DynamicTexture2D.GLES2.h>
#   endif

#endif