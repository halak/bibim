namespace Bibim
{
    Stream* StreamReader::GetSource() const
    {
        return sourceStream;
    }

    bool StreamReader::operator == (const StreamReader& right) const
    {
        return sourceStream == right.sourceStream;
    }

    bool StreamReader::operator != (const StreamReader& right) const
    {
        return !operator == (right);
    }
}