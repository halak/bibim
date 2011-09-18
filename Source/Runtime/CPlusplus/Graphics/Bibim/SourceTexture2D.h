#pragma once
#ifndef __BIBIM_SOURCETEXTURE2D_H__
#define __BIBIM_SOURCETEXTURE2D_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Texture2D.h>
#   include <Bibim/AssetLoadingTask.h>
#   include <Bibim/AssetReader.h>

    namespace Bibim
    {
        class SourceTexture2D : public Texture2D
        {
            BBReadableGameAssetClass('S', 'T', 'X', '2');
            public:
                SourceTexture2D(GraphicsDevice* graphicsDevice);
                virtual ~SourceTexture2D();

            private:
                SourceTexture2D(GraphicsDevice* graphicsDevice, int width, int height);

            private:
                class LoadingTask : public AssetLoadingTask
                {
                    public:
                        LoadingTask(const String& name, uint totalBytes, SourceTexture2D* texture, const AssetReader& reader);
                        virtual ~LoadingTask();

                        virtual void Execute();

                    private:
                        SourceTexture2DPtr texture;
                        AssetReader reader;
                };
        };
    }

#endif