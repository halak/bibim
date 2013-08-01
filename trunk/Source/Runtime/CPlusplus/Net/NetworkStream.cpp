#include <Bibim/Config.h>
#include <Bibim/NetworkStream.h>
#include <Bibim/Assert.h>
#include <Bibim/Socket.h>

namespace Bibim
{
    NetworkStream::NetworkStream(Socket* socket)
        : socket(socket)
    {
        BBAssert(socket);
    }

    NetworkStream::~NetworkStream()
    {
    }

    int NetworkStream::Read(void* buffer, int size)
    {
        return socket->Receive(buffer, size);
    }

    int NetworkStream::Write(const void* buffer, int size)
    {
        return socket->Send(buffer, size);
    }

    void NetworkStream::Flush()
    {
    }

    int NetworkStream::Seek(int offset, SeekOrigin origin)
    {
        return 0;
    }

    int NetworkStream::GetPosition()
    {
        return 0;
    }

    int NetworkStream::GetLength()
    {
        return 0;
    }

    bool NetworkStream::CanRead() const
    {
        return socket->CanReceive();
    }

    bool NetworkStream::CanWrite() const
    {
        return socket->CanSend();
    }

    bool NetworkStream::CanSeek() const
    {
        return false;
    }
}