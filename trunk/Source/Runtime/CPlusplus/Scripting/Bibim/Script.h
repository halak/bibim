#pragma once
#ifndef __BIBIM_SCRIPT_H__
#define __BIBIM_SCRIPT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameAsset.h>
#   include <vector>

    namespace Bibim
    {
        class Script : public GameAsset
        {
            BBReadableGameAssetClass('S', 'C', 'R', 'T');
            public:
                typedef std::vector<byte> Buffer;

            public:
                Script();
                Script(const Buffer& buffer);
                virtual ~Script();

                inline const Buffer& GetBuffer() const;

            private:
                struct MoveTag {};
                Script(Buffer& buffer, MoveTag);

            private:
                Buffer buffer;
        };
    }

#   include <Bibim/Script.inl>

#endif