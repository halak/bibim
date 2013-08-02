#pragma once
#ifndef __BIBIM_MPQSTREAM_H__
#define __BIBIM_MPQSTREAM_H__

#include <Bibim/FWD.h>
#if (defined(BIBIM_PLATFORM_WINDOWS))

#include <Bibim/Stream.h>
#include <Bibim/String.h>
#include <vector>

namespace Bibim
{
    class MPQStream : public Stream
    {
        public:
            MPQStream(MPQ* mpq, const String& path);
            virtual ~MPQStream();

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

        private:
            void* handle;
    };
}

#endif
#endif