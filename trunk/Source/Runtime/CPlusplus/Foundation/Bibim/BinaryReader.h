#pragma once
#ifndef __BIBIM_STREAMREADER_H__
#define __BIBIM_STREAMREADER_H__

#   include <Bibim/FWD.h>

    namespace Bibim
    {
        class BinaryReader
        {
            public:
                explicit BinaryReader(Stream* sourceStream);
                BinaryReader(const BinaryReader& original);
                ~BinaryReader();

                bool   ReadBool();
                int8   ReadInt8();
                uint8  ReadUInt8();
                int16  ReadInt16();
                uint16 ReadUInt16();
                int32  ReadInt32();
                uint32 ReadUInt32();
                int64  ReadInt64();
                uint64 ReadUInt64();
                float  ReadFloat();
                String ReadString();

                inline Stream* GetSource() const;

                BinaryReader& operator = (const BinaryReader& right);
                inline bool operator == (const BinaryReader& right) const;
                inline bool operator != (const BinaryReader& right) const;

            private:
                template <typename T> inline T ReadTemplate();

            private:
                StreamPtr sourceStream;
        };
    }

#   include <Bibim/BinaryReader.inl>

#endif