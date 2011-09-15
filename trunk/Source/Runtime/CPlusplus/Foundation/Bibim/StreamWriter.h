#pragma once
#ifndef __BIBIM_STREAMWRITER_H__
#define __BIBIM_STREAMWRITER_H__

#   include <Bibim/FWD.h>

    namespace Bibim
    {
        class StreamWriter
        {
            public:
                explicit StreamWriter(Stream* sourceStream);
                StreamWriter(const StreamWriter& original);
                ~StreamWriter();

                void Write(bool value);
                void Write(int32 value);
                void Write(uint32 value);
                void Write(float value);
                void Write(const char* value);
                void Write(const char* value, int length);
                void Write(const String& value);

                inline Stream* GetSource() const;

                StreamWriter& operator = (const StreamWriter& right);
                inline bool operator == (const StreamWriter& right) const;
                inline bool operator != (const StreamWriter& right) const;

            private:
                template <typename T> inline void WriteTemplate(T value);

            private:
                StreamPtr sourceStream;
        };
    }

#   include <Bibim/StreamWriter.inl>

#endif