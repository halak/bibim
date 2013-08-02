#pragma once
#ifndef __BIBIM_IPENDPOINT_H__
#define __BIBIM_IPENDPOINT_H__

#   include <Bibim/FWD.h>

    namespace Bibim
    {
        class IPEndPoint
        {
            public:
                inline IPEndPoint();
                IPEndPoint(const char* address, int port);
                IPEndPoint(const String& address, int port);
                inline IPEndPoint(uint address, int port);
                inline IPEndPoint(const IPEndPoint& original);

                inline uint GetAddress() const;
                inline int GetPort() const;

                String GetAddressString() const;
                String ToString() const;

                inline bool IsValid() const;
                inline bool IsLocalhost() const;

                inline IPEndPoint& operator = (const IPEndPoint& right);
                inline bool operator == (const IPEndPoint& right) const;
                inline bool operator != (const IPEndPoint& right) const;

                static const uint Localhost;
                static const int  HttpPort;

            private:
                uint64 Compose(uint address, int port);

            private:
                uint64 value;
        };

        IPEndPoint::IPEndPoint()
            : value(0)
        {
        }

        IPEndPoint::IPEndPoint(uint address, int port)
            : value(Compose(address, port))
        {
        }

        IPEndPoint::IPEndPoint(const IPEndPoint& original)
            : value(original.value)
        {
        }

        uint IPEndPoint::GetAddress() const
        {
            return static_cast<uint>(value >> 32);
        }

        int IPEndPoint::GetPort() const
        {
            return (value & 0xFFFF);
        }

        bool IPEndPoint::IsValid() const
        {
            return value != 0;
        }

        bool IPEndPoint::IsLocalhost() const
        {
            return GetAddress() == Localhost;
        }

        IPEndPoint& IPEndPoint::operator = (const IPEndPoint& right)
        {
            value = right.value;
            return *this;
        }

        bool IPEndPoint::operator == (const IPEndPoint& right) const
        {
            return value == right.value;
        }

        bool IPEndPoint::operator != (const IPEndPoint& right) const
        {
            return !operator == (right);
        }
    }

#endif