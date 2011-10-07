namespace Bibim
{
    byte* MemoryStream::GetBuffer()
    {
        return buffer;
    }

    const byte* MemoryStream::GetBuffer() const
    {
        return buffer;
    }
    
    int MemoryStream::GetCapacity() const
    {
        return capacity;
    }

    MemoryStream* MemoryStream::NewReadableStream(const byte* buffer, int length)
    {
        return new MemoryStream(buffer, length);
    }

    MemoryStream* MemoryStream::NewWritableStream(int capacity, bool deleteOnClose)
    {
        return new MemoryStream(capacity, deleteOnClose, false);
    }

    MemoryStream* MemoryStream::NewWritableStream(int capacity, bool deleteOnClose, bool fillZero)
    {
        return new MemoryStream(capacity, deleteOnClose, fillZero);
    }
}