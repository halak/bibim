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
            BBReadableObjectClass(Script, GameAsset, GameAsset, 'S', 'C', 'R', 'T');
            public:
                typedef std::vector<byte> Buffer;

            public:
                Script();
                Script(const Buffer& buffer, uint entryPoint);
                virtual ~Script();

                inline const Buffer& GetBuffer() const;
                inline uint GetEntryPoint() const;

            private:
                struct MoveTag {};
                Script(Buffer& buffer, uint entryPoint, MoveTag);

            private:
                Buffer buffer;
                uint entryPoint;
        };
    }

#   include <Bibim/Script.inl>

#endif