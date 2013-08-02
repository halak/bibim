#pragma once
#ifndef __BIBIM_SHADEREFFECT_H__
#define __BIBIM_SHADEREFFECT_H__

#   include <Bibim/Config.h>

#   if (defined(BIBIM_USE_DIRECTX9))
#       include <Bibim/ShaderEffect.DX9.h>
#   elif (defined(BIBIM_USE_OPENGLES2))
#       include <Bibim/ShaderEffect.GLES2.h>
#   endif

#endif