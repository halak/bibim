#pragma once
#ifndef __BIBIM_SOCKET_H__
#define __BIBIM_SOCKET_H__

#   include <Bibim/FWD.h>
#   include <Bibim/SharedObject.h>
#   include <Bibim/String.h>

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
                Socket(const char* ipAddress, int port);
                ~Socket();

                bool Connect();
                void Disconnect();

                bool TryConnect();

                int Send(const void* buffer, int size);
                int Receive(void* buffer, int size);

                inline bool IsConnected() const;
                bool CanSend() const;
                bool CanReceive() const;

            private:
                bool Preconnect();
                bool ConnectActually();
                bool SetNonBlockingIOMode(bool value);

            private:
#               if (defined(BIBIM_PLATFORM_WINDOWS))
                    typedef uint HANDLE;
#               else
                    typedef int HANDLE;
                    static const int INVALID_SOCKET = -1;
#               endif

                HANDLE handle;
                String hostname;
                int port;
                Status status;
        };

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        bool Socket::IsConnected() const
        {
            return status == Socket::Connected;
        }
    }

#endif