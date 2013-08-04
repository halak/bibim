#pragma once
#ifndef __BIBIM_FORKSTREAM_H__
#define __BIBIM_FORKSTREAM_H__

#include <Bibim/FWD.h>
#include <Bibim/Stream.h>
#include <vector>

namespace Bibim
{
    class ForkStream : public Stream
    {
        public:
            typedef std::vector<StreamPtr> StreamCollection;

        public:
            ForkStream(Stream* stream1 = nullptr,
                       Stream* stream2 = nullptr,
                       Stream* stream3 = nullptr,
                       Stream* stream4 = nullptr);
            virtual ~ForkStream();

            virtual int Read(void* buffer, int size);
            virtual int Write(const void* buffer, int size);
            virtual void Flush();
            virtual int Seek(int offset, SeekOrigin origin);

            virtual int GetPosition();
            virtual int GetLength();

            virtual bool CanRead() const;
            virtual bool CanWrite() const;
            virtual bool CanSeek() const;

            inline const StreamCollection& GetStreams() const;

        private:
            StreamCollection streams;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    const ForkStream::StreamCollection& ForkStream::GetStreams() const
    {
        return streams;
    }
}

#endif