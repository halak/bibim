#pragma once
#ifndef __BIBIM_SOURCETEXTURE2D_H__
#define __BIBIM_SOURCETEXTURE2D_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Texture2D.h>
#   include <Bibim/GameAssetLoadingTask.h>

    namespace Bibim
    {
        class SourceTexture2D : public Texture2D
        {
            BBReadableGameAssetClass('S', 'T', 'X', '2');
            public:
                SourceTexture2D();
                SourceTexture2D(GraphicsDevice* graphicsDevice, const URI& uri);
                virtual ~SourceTexture2D();

                virtual const URI& GetURI() const;

            protected:
                virtual Texture2D::D3DTextureInfo CreateD3DTexture();

            private:
                URI uri;

            private:
                class LoadingTask : public GameAssetLoadingTask
                {
                    public:
                        LoadingTask(SourceTexture2D* texture, const AssetReader& reader);
                        virtual ~LoadingTask();

                        virtual void Execute();

                    private:
                        SourceTexture2DPtr texture;
                        AssetReader reader;
                };
        };
    }

#endif