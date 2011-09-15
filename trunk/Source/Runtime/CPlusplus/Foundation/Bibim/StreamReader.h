#pragma once
#ifndef __BIBIM_STREAMREADER_H__
#define __BIBIM_STREAMREADER_H__

#   include <Bibim/FWD.h>

    namespace Bibim
    {
        class StreamReader
        {
            public:
                explicit StreamReader(Stream* sourceStream);
                StreamReader(const StreamReader& original);
                ~StreamReader();

                bool ReadBool();
                int ReadInt();
                float ReadFloat();
                String ReadString();

                inline Stream* GetSource() const;

                StreamReader& operator = (const StreamReader& right);
                inline bool operator == (const StreamReader& right) const;
                inline bool operator != (const StreamReader& right) const;

            private:
                template <typename T> inline T ReadTemplate();

            private:
                StreamPtr sourceStream;
        };
    }

#   include <Bibim/StreamReader.inl>

#endif