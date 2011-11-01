#pragma once
#ifndef __BIBIM_TEXTURE2D_H__
#define __BIBIM_TEXTURE2D_H__

#   include <Bibim/Foundation.h>

#   if (defined(BIBIM_USE_DIRECTX9))
#       include <Bibim/Texture2D.DX9.h>
#   elif (defined(BIBIM_USE_OPENGLES2))
#       include <Bibim/Texture2D.GLES2.h>
#   endif

#endif