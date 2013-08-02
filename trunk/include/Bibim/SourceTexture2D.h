#pragma once
#ifndef __BIBIM_SOURCETEXTURE2D_H__
#define __BIBIM_SOURCETEXTURE2D_H__

#   include <Bibim/Config.h>

#   if (defined(BIBIM_USE_DIRECTX9))
#       include <Bibim/SourceTexture2D.DX9.h>
#   elif (defined(BIBIM_USE_OPENGLES2))
#       include <Bibim/SourceTexture2D.GLES2.h>
#   endif

#endif