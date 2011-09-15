namespace Bibim
{
    Stream* StreamWriter::GetSource() const
    {
        return sourceStream;
    }

    bool StreamWriter::operator == (const StreamWriter& right) const
    {
        return sourceStream == right.sourceStream;
    }

    bool StreamWriter::operator != (const StreamWriter& right) const
    {
        return !operator == (right);
    }
}