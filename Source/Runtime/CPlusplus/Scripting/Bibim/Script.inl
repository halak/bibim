namespace Bibim
{
    const Script::Buffer& Script::GetBuffer() const
    {
        return buffer;
    }

    const Script::StringCollection& Script::GetStringTable() const
    {
        return stringTable;
    }
}