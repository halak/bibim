#include <Bibim/Config.h>
#include <Bibim/IPEndPoint.h>
#include <Bibim/Assert.h>
#include <Bibim/Numerics.h>
#include <Bibim/String.h>

#if defined(BIBIM_PLATFORM_WINDOWS)
#   include <winsock2.h>
#else
#   include <arpa/inet.h>
#endif

namespace Bibim
{
    const uint IPEndPoint::Localhost = 0x0100007F;
    const int  IPEndPoint::HttpPort = 80;

    IPEndPoint::IPEndPoint(const char* address, int port)
        : value(Compose(inet_addr(address), port))
    {
    }

    IPEndPoint::IPEndPoint(const String& address, int port)
        : value(Compose(inet_addr(address.CStr()), port))
    {
    }

    String IPEndPoint::GetAddressString() const
    {
        const in_addr address = { GetAddress() };
        return String(inet_ntoa(address));
    }

    String IPEndPoint::ToString() const
    {
        const in_addr address = { GetAddress() };
        return String::CFormat("%s:%d", address, GetPort());
    }

    uint64 IPEndPoint::Compose(uint address, int port)
    {
        BBAssert(0 < port && port < 0xFFFF);
        return (static_cast<uint64>(address) << 32) | static_cast<uint64>(port);
    }
}