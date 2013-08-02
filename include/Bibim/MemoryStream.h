#pragma once
#ifndef __BIBIM_MEMORYSTREAM_H__
#define __BIBIM_MEMORYSTREAM_H__

#include <Bibim/FWD.h>
#include <Bibim/Stream.h>

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

            static inline MemoryStream* NewReadableStream(const byte* buffer, int length);
            static inline MemoryStream* NewReadableStream(const byte* buffer, int length, bool deleteOnClose);
            static inline MemoryStream* NewWritableStream(int capacity, bool deleteOnClose);
            static inline MemoryStream* NewWritableStream(int capacity, bool deleteOnClose, bool fillZero);

        private:
            MemoryStream(const byte* buffer, int length, bool deleteOnClose);
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

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    byte* MemoryStream::GetBuffer()
    {
        return buffer;
    }

    const byte* MemoryStream::GetBuffer() const
    {
        return buffer;
    }

    int MemoryStream::GetCapacity() const
    {
        return capacity;
    }

    MemoryStream* MemoryStream::NewReadableStream(const byte* buffer, int length)
    {
        return new MemoryStream(buffer, length, false);
    }

    MemoryStream* MemoryStream::NewReadableStream(const byte* buffer, int length, bool deleteOnClose)
    {
        return new MemoryStream(buffer, length, deleteOnClose);
    }

    MemoryStream* MemoryStream::NewWritableStream(int capacity, bool deleteOnClose)
    {
        return new MemoryStream(capacity, deleteOnClose, false);
    }

    MemoryStream* MemoryStream::NewWritableStream(int capacity, bool deleteOnClose, bool fillZero)
    {
        return new MemoryStream(capacity, deleteOnClose, fillZero);
    }
}

#endif