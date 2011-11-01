#pragma once
#ifndef __BIBIM_STREAMWRITER_H__
#define __BIBIM_STREAMWRITER_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Color.h>
#   include <Bibim/Vector2.h>
#   include <Bibim/Vector3.h>
#   include <Bibim/Vector4.h>

    namespace Bibim
    {
        class BinaryWriter
        {
            public:
                explicit BinaryWriter(Stream* sourceStream);
                BinaryWriter(const BinaryWriter& original);
                ~BinaryWriter();

                void Write(bool value);
                void Write(int8 value);
                void Write(uint8 value);
                void Write(int16 value);
                void Write(uint16 value);
                void Write(int32 value);
                void Write(uint32 value);
                void Write(int64 value);
                void Write(uint64 value);
                void Write(float value);
                void Write(const char* value);
                void Write(const char* value, int length);
                void Write(const String& value);
                void Write(Color value);
                void Write(Vector2 value);
                void Write(Vector3 value);
                void Write(Vector4 value);

                inline Stream* GetSource() const;

                BinaryWriter& operator = (const BinaryWriter& right);
                inline bool operator == (const BinaryWriter& right) const;
                inline bool operator != (const BinaryWriter& right) const;

                static inline void From(byte* buffer, bool value);
                static inline void From(byte* buffer, int8 value);
                static inline void From(byte* buffer, uint8 value);
                static inline void From(byte* buffer, int16 value);
                static inline void From(byte* buffer, uint16 value);
                static inline void From(byte* buffer, int32 value);
                static inline void From(byte* buffer, uint32 value);
                static inline void From(byte* buffer, int64 value);
                static inline void From(byte* buffer, uint64 value);
                static inline void From(byte* buffer, float value);
                static inline void From(byte* buffer, Color value);
                static inline void From(byte* buffer, Vector2 value);
                static inline void From(byte* buffer, Vector3 value);
                static inline void From(byte* buffer, Vector4 value);

            private:
                template <typename T> inline void WriteTemplate(T value);

            private:
                StreamPtr sourceStream;
        };
    }

#   include <Bibim/BinaryWriter.inl>

#endif