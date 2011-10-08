#pragma once
#ifndef __BIBIM_SCRIPT_H__
#define __BIBIM_SCRIPT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameAsset.h>
#   include <Bibim/String.h>
#   include <vector>

    namespace Bibim
    {
        class Script : public GameAsset
        {
            BBReadableObjectClass(Script, GameAsset, GameAsset, 'S', 'C', 'R', 'T');
            public:
                typedef std::vector<byte> Buffer;
                typedef std::vector<String> StringCollection;

            public:
                Script();
                Script(const Buffer& buffer, uint entryPoint);
                virtual ~Script();

                inline const Buffer& GetBuffer() const;
                inline uint GetEntryPoint() const;
                inline const StringCollection& GetStringTable() const;

            private:
                struct MoveTag {};
                Script(Buffer& buffer, uint entryPoint, StringCollection& stringTable, MoveTag);

            private:
                Buffer buffer;
                uint entryPoint;
                StringCollection stringTable;
        };
    }

#   include <Bibim/Script.inl>

#endif