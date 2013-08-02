#include <Bibim/MemoryStream.h>
#include <Bibim/Assert.h>
#include <Bibim/Math.h>
#include <Bibim/Memory.h>

namespace Bibim
{
    MemoryStream::MemoryStream(const byte* buffer, int length, bool deleteOnClose)
        : buffer(const_cast<byte*>(buffer)),
          length(length),
          capacity(length),
          position(0),
          deleteOnClose(deleteOnClose),
          canRead(true),
          canWrite(false)
    {
    }

    MemoryStream::MemoryStream(int capacity, bool deleteOnClose, bool fillZero)
        : buffer(capacity > 0 ? new byte[capacity] : nullptr),
          length(0),
          capacity(capacity > 0 ? capacity : 0),
          position(0),
          deleteOnClose(deleteOnClose),
          canRead(false),
          canWrite(true)
    {
        if (fillZero)
            Memory::Fill(buffer, capacity);
    }

    MemoryStream::~MemoryStream()
    {
        if (deleteOnClose)
            delete [] buffer;
    }

    int MemoryStream::Read(void* buffer, int size)
    {
        if (this->position + size < this->length)
        {
            Memory::Copy(buffer, size, &this->buffer[this->position], size);
            this->position += size;
            return size;
        }
        else
        {
            const int readBytes = this->length - this->position;
            Memory::Copy(buffer, size, &this->buffer[this->position], readBytes);
            this->position = this->length;
            return readBytes;
        }
    }

    int MemoryStream::Write(const void* buffer, int size)
    {
        if (this->position + size < this->length)
        {
            Memory::Copy(&this->buffer[this->position], this->capacity - this->position, buffer, size);
            this->position += size;
            return size;
        }
        else
        {
            const int newPosition = this->position + size;
            if (newPosition >= this->capacity)
            {
                this->capacity = newPosition * 2;
                byte* newBuffer = new byte [this->capacity];
                byte* oldBuffer = this->buffer;
                Memory::Copy(newBuffer, this->capacity, oldBuffer, this->length);
                this->buffer = newBuffer;
                delete [] oldBuffer;
            }

            Memory::Copy(&this->buffer[this->position], this->capacity - this->position, buffer, size);
            this->position = newPosition;
            this->length = newPosition;
            return size;
        }
    }

    void MemoryStream::Flush()
    {
    }

    int MemoryStream::Seek(int offset, SeekOrigin origin)
    {
        int newPosition = 0;
        switch (origin)
        {
            case FromBegin:
                newPosition = offset;
                break;
            case FromEnd:
                newPosition = length + offset;
                break;
            case FromCurrent:
                newPosition = position + offset;
                break;
            default:
                BBBreak();
                break;
        }

        position = Math::Min(newPosition, length);

        return position;
    }

    int MemoryStream::GetPosition()
    {
        return position;
    }

    int MemoryStream::GetLength()
    {
        return length;
    }

    bool MemoryStream::CanRead() const
    {
        return canRead;
    }

    bool MemoryStream::CanWrite() const
    {
        return canWrite;
    }

    bool MemoryStream::CanSeek() const
    {
        return true;
    }
}