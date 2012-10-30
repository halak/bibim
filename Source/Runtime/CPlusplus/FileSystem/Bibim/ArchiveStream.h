#pragma once
#ifndef __BIBIM_ARCHIVESTREAM_H__
#define __BIBIM_ARCHIVESTREAM_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Stream.h>
#   include <Bibim/String.h>
#   include <vector>

    namespace Bibim
    {
        class ArchiveStream : public Stream
        {
            public:
                ArchiveStream();
                virtual ~ArchiveStream();

                void Close();

                virtual int Read(void* buffer, int size);
                virtual int Write(const void* buffer, int size);
                virtual void Flush();
                virtual int Seek(int offset, SeekOrigin origin);

                virtual int GetPosition();
                virtual int GetLength();

                virtual bool CanRead() const;
                virtual bool CanWrite() const;
                virtual bool CanSeek() const;
        };
    }

#   include <Bibim/ArchiveStream.inl>

#endif