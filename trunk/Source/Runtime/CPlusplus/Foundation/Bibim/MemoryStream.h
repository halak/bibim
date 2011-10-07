#pragma once
#ifndef __BIBIM_MEMORYSTREAM_H__
#define __BIBIM_MEMORYSTREAM_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Stream.h>

    namespace Bibim
    {
        class MemoryStream : public Stream
        {
            public:
                virtual ~MemoryStream();

                virtual int Read(void* buffer, int size);
                virtual int Write(const void* buffer, int size);
                virtual void Flush();
                virtual int Seek(int offset, SeekOrigin origin);

                inline byte* GetBuffer();
                inline const byte* GetBuffer() const;
                virtual int GetPosition();
                virtual int GetLength();
                inline  int GetCapacity() const;

                virtual bool CanRead() const;
                virtual bool CanWrite() const;
                virtual bool CanSeek() const;

                static MemoryStream* NewReadableStream(const byte* buffer, int length);
                static MemoryStream* NewWritableStream(int capacity, bool deleteOnClose, bool fillZero);

            private:
                MemoryStream(const byte* buffer, int length);
                MemoryStream(int capacity, bool deleteOnClose, bool fillZero);

            private:
                byte* buffer;
                int length;
                int capacity;
                int position;
                bool deleteOnClose;
                bool canRead;
                bool canWrite;
        };
    }

#endif