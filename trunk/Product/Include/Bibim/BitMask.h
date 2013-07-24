#pragma once
#ifndef __BIBIM_BItMASK_H__
#define __BIBIM_BItMASK_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameAsset.h>
#   include <vector>

    namespace Bibim
    {
        class BitMask : public GameAsset
        {
            BBSerializableAssetClass(BitMask, GameAsset, 'B', 'I', 'T', 'M');
            public:
                BitMask(int width, int height, int pitch, std::vector<byte>& buffer);
                virtual ~BitMask();

                bool GetPixel(int x, int y) const;
                void SetPixel(int x, int y, bool value);

                inline int GetWidth() const;
                inline int GetHeight() const;
                inline int GetPitch() const;

            private:
                int width;
                int height;
                int pitch;
                std::vector<byte> buffer;

                static const int BitsPerByte = 8;
        };

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        int BitMask::GetWidth() const
        {
            return width;
        }

        int BitMask::GetHeight() const
        {
            return height;
        }

        int BitMask::GetPitch() const
        {
            return pitch;
        }
    }

#endif