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

    HANDLE PipeStream::GetHandle() const
    {
        return handle;
    }

    void PipeStream::SetHandle(HANDLE value)
    {
        handle = value;
    }
}