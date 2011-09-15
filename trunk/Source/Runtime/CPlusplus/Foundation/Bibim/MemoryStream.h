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
                MemoryStream();
                MemoryStream(int length);
                MemoryStream(byte* buffer, int length);
                virtual ~MemoryStream();

                virtual int Read(void* buffer, int size);
                virtual int Write(const void* buffer, int size);
                virtual void Flush();
                virtual int Seek(int offset, SeekOrigin origin);

                virtual int GetPosition();
                virtual int GetLength();

                virtual bool CanRead() const;
                virtual bool CanWrite() const;
                virtual bool CanSeek() const;

            private:
                byte* buffer;
                int length;
                int position;

                // allocator
                // capacity
        };
    }

#endif