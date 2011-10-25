#pragma once
#ifndef __BIBIM_DUMPSTREAM_H__
#define __BIBIM_DUMPSTREAM_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Stream.h>

    namespace Bibim
    {
        class DumpStream : public Stream
        {
            public:
                DumpStream(Stream* baseStream, Stream* outputStream);
                virtual ~DumpStream();

                virtual int Read(void* buffer, int size);
                virtual int Write(const void* buffer, int size);
                virtual void Flush();
                virtual int Seek(int offset, SeekOrigin origin);

                virtual int GetPosition();
                virtual int GetLength();

                virtual bool CanRead() const;
                virtual bool CanWrite() const;
                virtual bool CanSeek() const;

                inline Stream* GetBaseStream() const;
                inline Stream* GetOutputStream() const;

            private:
                StreamPtr baseStream;
                StreamPtr outputStream;
        };
    }

#   include <Bibim/DumpStream.inl>

#endif