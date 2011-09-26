#pragma once
#ifndef __BIBIM_STREAMREADER_H__
#define __BIBIM_STREAMREADER_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Color.h>
#   include <Bibim/Vector2.h>
#   include <Bibim/Vector3.h>
#   include <Bibim/Vector4.h>

    namespace Bibim
    {
        class BinaryReader
        {
            public:
                explicit BinaryReader(Stream* sourceStream);
                BinaryReader(const BinaryReader& original);
                ~BinaryReader();

                void*  Read(void* buffer, int length);
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
                Color  ReadColor();
                Vector2 ReadVector2();
                Vector3 ReadVector3();
                Vector4 ReadVector4();

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