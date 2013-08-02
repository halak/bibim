﻿#pragma once
#ifndef __BIBIM_SOURCETEXTURE2D_GLES2_H__
#define __BIBIM_SOURCETEXTURE2D_GLES2_H__

#include <Bibim/FWD.h>
#if (defined(BIBIM_USE_OPENGLES2))

#include <Bibim/Texture2D.GLES2.h>
#include <Bibim/AssetLoadingTask.h>
#include <Bibim/AssetStreamReader.h>

namespace Bibim
{
    class SourceTexture2D : public Texture2D
    {
        BBSerializableAssetClass(SourceTexture2D, Texture2D, 'S', 'T', 'X', '2');
        public:
            SourceTexture2D(GraphicsDevice* graphicsDevice);
            virtual ~SourceTexture2D();

        private:
            SourceTexture2D(GraphicsDevice* graphicsDevice, int width, int height, int surfaceWidth, int surfaceHeight, PixelFormat pixelFormat);

            static void Read(SourceTexture2D* thiz, StreamReader& reader);
    };
}

#endif
#endif