#pragma once
#ifndef __BIBIM_SOCKET_NULL_H__
#define __BIBIM_SOCKET_NULL_H__

#include <Bibim/FWD.h>
#if (defined(BIBIM_PLATFORM_EMSCRIPTEN))

#include <Bibim/SharedObject.h>
#include <Bibim/IPEndPoint.h>

namespace Bibim
{
    class Socket : public SharedObject
    {
        public:
            enum Status
            {
                Disconnected,
                Connected,
            };
            
        public:
            explicit inline Socket(IPEndPoint endPoint);
            inline ~Socket();

            inline bool Connect();
            inline void Disconnect();

            inline bool TryConnect();

            inline int Send(const void* buffer, int size);
            inline int Receive(void* buffer, int size);

            inline bool IsConnected() const;
            inline bool CanSend() const;
            inline bool CanReceive() const;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    Socket::Socket(IPEndPoint /*endPoint*/)
    {
    }

    Socket::~Socket()
    {
    }

    bool Socket::Connect()
    {
        return false;
    }

    void Socket::Disconnect()
    {
    }

    bool Socket::TryConnect()
    {
        return false;
    }

    int Socket::Send(const void* /*buffer*/, int /*size*/)
    {
        return 0;
    }

    int Socket::Receive(void* /*buffer*/, int /*size*/)
    {
        return 0;
    }

    bool Socket::IsConnected() const
    {
        return false;
    }

    bool Socket::CanSend() const
    {
        return false;
    }

    bool Socket::CanReceive() const
    {
        return false;
    }
}

#endif
#endif