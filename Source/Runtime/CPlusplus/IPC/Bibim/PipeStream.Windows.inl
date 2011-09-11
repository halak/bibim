namespace Bibim
{
    const String& PipeStream::GetName() const
    {
        return name;
    }

    PipeStream::AccessMode PipeStream::GetAccessMode() const
    {
        return accessMode;
    }

    bool PipeStream::IsOpen() const
    {
        return handle != INVALID_HANDLE_VALUE;
    }

    HANDLE PipeStream::GetHandle() const
    {
        return handle;
    }
}