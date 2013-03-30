namespace Bibim
{
    Stream* DumpStream::GetBaseStream() const
    {
        return baseStream;
    }

    Stream* DumpStream::GetOutputStream() const
    {
        return outputStream;
    }
}