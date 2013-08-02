#pragma once
#ifndef __BIBIM_NETWORKSTREAM_H__
#define __BIBIM_NETWORKSTREAM_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Stream.h>

    namespace Bibim
    {
        class NetworkStream : public Stream
        {
            public:
                NetworkStream(Socket* socket);
                virtual ~NetworkStream();

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
                SocketPtr socket;
        };
    }

#endif