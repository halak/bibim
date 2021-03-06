﻿#pragma once
#ifndef __BIBIM_RENDERTARGETTEXTURE2D_GLES2_H__
#define __BIBIM_RENDERTARGETTEXTURE2D_GLES2_H__

#include <Bibim/FWD.h>
#if (defined(BIBIM_USE_OPENGLES2))

#include <Bibim/Texture2D.GLES2.h>
#include <Bibim/Rect.h>

namespace Bibim
{
    class RenderTargetTexture2D : public Texture2D
    {
        BBAssetClass(RenderTargetTexture2D, Texture2D, 'R', 'T', 'X', '2');
        public:
            RenderTargetTexture2D(GraphicsDevice* graphicsDevice, int width, int height);
            virtual ~RenderTargetTexture2D();
    };
}

#endif
#endif