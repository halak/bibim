#pragma once
#ifndef __BIBIM_SOURCETEXTURE2D_H__
#define __BIBIM_SOURCETEXTURE2D_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Texture2D.h>
#   include <Bibim/AssetLoadingTask.h>
#   include <Bibim/AssetStreamReader.h>

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
                        LoadingTask(const AssetStreamReader& reader, SourceTexture2D* texture, uint totalBytes);
                        virtual ~LoadingTask();

                        virtual void Execute();
                        virtual void Cancel();

                    private:
                        SourceTexture2DPtr texture;
                        AssetStreamReader reader;
                        bool cancelled;
                };
        };
    }

#endif