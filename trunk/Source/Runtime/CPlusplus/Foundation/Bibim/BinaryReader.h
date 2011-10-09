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

                static inline bool   ToBool(const byte* buffer);
                static inline int8   ToInt8(const byte* buffer);
                static inline uint8  ToUInt8(const byte* buffer);
                static inline int16  ToInt16(const byte* buffer);
                static inline uint16 ToUInt16(const byte* buffer);
                static inline int32  ToInt32(const byte* buffer);
                static inline uint32 ToUInt32(const byte* buffer);
                static inline int64  ToInt64(const byte* buffer);
                static inline uint64 ToUInt64(const byte* buffer);
                static inline float  ToFloat(const byte* buffer);
                static inline Color  ToColor(const byte* buffer);

            private:
                template <typename T> inline T ReadTemplate();

            private:
                StreamPtr sourceStream;
        };
    }

#   include <Bibim/BinaryReader.inl>

#endif