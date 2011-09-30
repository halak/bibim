namespace Bibim
{
    const Script::Buffer& Script::GetBuffer() const
    {
        return buffer;
    }

    uint Script::GetEntryPoint() const
    {
        return entryPoint;
    }
}