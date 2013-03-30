#pragma once
#ifndef __BIBIM_STREAMWRITER_H__
#define __BIBIM_STREAMWRITER_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Color.h>
#   include <Bibim/Point2.h>
#   include <Bibim/Point3.h>
#   include <Bibim/Point4.h>
#   include <Bibim/Rect.h>
#   include <Bibim/RectF.h>
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
                void Write(byte value);
                void Write(short value);
                void Write(int value);
                void Write(longint value);
                void Write(float value);
                void Write(double value);
                void Write(const char* value);
                void Write(const char* value, int length);
                void Write(const String& value);
                void Write(Color value);
                void Write(Point2 value);
                void Write(Point3 value);
                void Write(Point4 value);
                void Write(Rect value);
                void Write(RectF value);
                void Write(Vector2 value);
                void Write(Vector3 value);
                void Write(Vector4 value);

                inline Stream* GetSource() const;

                BinaryWriter& operator = (const BinaryWriter& right);
                inline bool operator == (const BinaryWriter& right) const;
                inline bool operator != (const BinaryWriter& right) const;

                static inline void From(byte* buffer, bool value);
                static inline void From(byte* buffer, byte value);
                static inline void From(byte* buffer, short value);
                static inline void From(byte* buffer, int value);
                static inline void From(byte* buffer, longint value);
                static inline void From(byte* buffer, float value);
                static inline void From(byte* buffer, double value);
                static inline void From(byte* buffer, Color value);
                static inline void From(byte* buffer, Point2 value);
                static inline void From(byte* buffer, Point3 value);
                static inline void From(byte* buffer, Point4 value);
                static inline void From(byte* buffer, Rect value);
                static inline void From(byte* buffer, RectF value);
                static inline void From(byte* buffer, Vector2 value);
                static inline void From(byte* buffer, Vector3 value);
                static inline void From(byte* buffer, Vector4 value);

            private:
                template <typename T> inline void WriteTemplate(T value);
                template <typename T> static inline void FromTemplate(byte* buffer, T value);

            private:
                StreamPtr sourceStream;
        };
    }

#   include <Bibim/BinaryWriter.inl>

#endif