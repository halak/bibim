#include <Bibim/Config.h>
#include <Bibim/Socket.h>
#include <Bibim/Log.h>
#include <Bibim/Thread.h>

#if defined(BIBIM_PLATFORM_WINDOWS)
#   include <winsock2.h>
#elif defined(BIBIM_PLATFORM_APPLE)
#   include <sys/socket.h>
#   include <sys/select.h>
#   include <sys/filio.h>
#   include <sys/ioctl.h>
#   include <arpa/inet.h>
#   include <unistd.h>
#else
#   include <sys/socket.h>
#   include <sys/select.h>
#   include <asm/ioctls.h>
#   include <arpa/inet.h>
#   include <linux/tcp.h>
#   include <unistd.h>
#endif

#pragma warning(push)
#pragma warning(disable:4127)

namespace Bibim
{
    Socket::Socket(IPEndPoint endPoint)
        : handle(INVALID_SOCKET),
          endPoint(endPoint),
          status(Disconnected)
    {
    #   if (defined(BIBIM_PLATFORM_WINDOWS))
        static struct Winsock
        {
            WSADATA data;
            bool isInitialized;

            Winsock()  { isInitialized = WSAStartup(MAKEWORD(2, 2), &data) != 0; }
            ~Winsock() { WSACleanup(); }
        } winsock;

        if (winsock.isInitialized == false)
            return;
    #   endif
    }

    Socket::~Socket()
    {
        Disconnect();
    }

    bool Socket::Connect()
    {
        if (Preconnect())
            return ConnectActually();
        else
            return false;
    }

    void Socket::Disconnect()
    {
        if (handle != INVALID_SOCKET)
        {
    #       if (defined(BIBIM_PLATFORM_WINDOWS))
                closesocket(handle);
    #       else
                close(handle);
    #       endif

            handle = INVALID_SOCKET;
        }
    }

    bool Socket::TryConnect()
    {
        if (Preconnect())
        {
            if (SetNonBlockingIOMode(true) == false)
            {
                Disconnect();
                return false;
            }

            ConnectActually();

            if (SetNonBlockingIOMode(false) == false)
            {
                Disconnect();
                return false;
            }

            if (status == Connected)
                return true;
            else
            {
                fd_set rset;
                fd_set wset;
                FD_ZERO(&rset);
                FD_ZERO(&wset);
                FD_SET(handle, &rset);
                FD_SET(handle, &wset);

                struct timeval timeoutObject;
                timeoutObject.tv_sec = 0;
                timeoutObject.tv_usec = 1;
                if (select(2, &rset, &wset, nullptr, &timeoutObject) > 0)
                {
                    status = Connected;
                    return true;
                }
                else
                    return false;
            }
        }
        else
            return false;
    }

    bool Socket::Preconnect()
    {
        if (handle != INVALID_SOCKET)
            return true;

        handle = socket(AF_INET, SOCK_STREAM, 0);
        if (handle != INVALID_SOCKET)
        {
            const int value = 1;
            setsockopt(handle,
                       SOL_SOCKET,
                       0,
                       reinterpret_cast<const char*>(&value),
                       sizeof(value));
            return true;
        }
        else
            return false;
    }

    bool Socket::ConnectActually()
    {
        struct sockaddr_in addr = { 0, };
        addr.sin_family = AF_INET;
        addr.sin_port = htons(static_cast<u_short>(endPoint.GetPort()));
        addr.sin_addr.s_addr = endPoint.GetAddress();
        const int result = connect(handle, reinterpret_cast<const sockaddr*>(&addr), sizeof(addr));
        if (result == 0)
        {
            status = Connected;
            return true;
        }
        else
            return false;
    }

    bool Socket::SetNonBlockingIOMode(bool value)
    {
#       if (defined(BIBIM_PLATFORM_WINDOWS))
            unsigned long mode = value ? 1 : 0;
            return ioctlsocket(handle, FIONBIO, &mode) == 0;
#       else
            // return ioctl(handle, FIONBIO, &mode) == 0;
            return true;
#       endif
    }

    int Socket::Send(const void* buffer, int size)
    {
        if (status == Connected)
            return send(handle, static_cast<const char*>(buffer), size, 0);
        else
            return 0;
    }

    int Socket::Receive(void* buffer, int size)
    {
        if (status != Connected)
            return 0;

        int index = 0;
        while (index < size)
        {
            const int received = recv(handle, static_cast<char*>(buffer) + index, size - index, 0);
            if (received > 0)
                index += received;
            else if (received == 0)
            {
                // gracefully closed;
                break;
            }
            else
            {
#if (defined(BIBIM_PLATFORM_WINDOWS))
                const int error = WSAGetLastError();

#define XXX(val) if (error == val) { Log::Information(#val); }
                XXX(WSANOTINITIALISED);
                XXX(WSAENETDOWN);
                XXX(WSAEFAULT);
                XXX(WSAENOTCONN);
                XXX(WSAEINTR);
                XXX(WSAEINPROGRESS);
                XXX(WSAENETRESET);
                XXX(WSAENOTSOCK);
                XXX(WSAEOPNOTSUPP);
                XXX(WSAESHUTDOWN);
                XXX(WSAEWOULDBLOCK);
                XXX(WSAEMSGSIZE);
                XXX(WSAEINVAL);
                XXX(WSAECONNABORTED);
                XXX(WSAETIMEDOUT);
                XXX(WSAECONNRESET);
#undef XXX
#endif
                break;
            }
        }

        return index;
    }

    bool Socket::CanSend() const
    {
        if (status != Connected)
            return false;

        fd_set test;
        FD_ZERO(&test);
        FD_SET(handle, &test);
        
        struct timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = 1;

        return select(2, nullptr, &test, nullptr, &timeout) > 0;
    }

    bool Socket::CanReceive() const
    {
        if (status != Connected)
            return false;

        fd_set test;
        FD_ZERO(&test);
        FD_SET(handle, &test);
        
        struct timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = 1;

        return select(2, &test, nullptr, nullptr, &timeout) > 0;
    }
}

#pragma warning(pop)