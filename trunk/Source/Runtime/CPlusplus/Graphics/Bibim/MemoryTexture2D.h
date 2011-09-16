#pragma once
#ifndef __BIBIM_MEMORYTEXTURE2D_H__
#define __BIBIM_MEMORYTEXTURE2D_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Texture2D.h>
#   include <vector>

    namespace Bibim
    {
        class MemoryTexture2D : public Texture2D
        {
            BBGameAssetClass('M', 'T', 'X', '2');
            public:
                MemoryTexture2D(GraphicsDevice* graphicsDevice, int width, int height, int pitch, const std::vector<byte>& red, const std::vector<byte>& green, const std::vector<byte>& blue);
                MemoryTexture2D(GraphicsDevice* graphicsDevice, int width, int height, int pitch, const std::vector<byte>& red, const std::vector<byte>& green, const std::vector<byte>& blue, const std::vector<byte>& alpha);
                virtual ~MemoryTexture2D();

            protected:
                virtual D3DTextureInfo CreateD3DTexture();

            private:
                void Construct(int width, int height, int pitch,
                               const byte* red, int redSize, const byte* green, int greenSize, const byte* blue, int blueSize, const byte* alpha, int alphaSize);

            private:
                int width;
                int height;
                int pitch;
                std::vector<byte> buffer;
                PixelFormat format;
        };
    }

#endif