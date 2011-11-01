#pragma once
#ifndef __BIBIM_UIRENDERER_H__
#define __BIBIM_UIRENDERER_H__

#   include <Bibim/Foundation.h>

#   if (defined(BIBIM_USE_DIRECTX9))
#       include <Bibim/UIRenderer.DX9.h>
#   elif (defined(BIBIM_USE_OPENGLES2))
#       include <Bibim/UIRenderer.GLES2.h>
#   endif

#endif