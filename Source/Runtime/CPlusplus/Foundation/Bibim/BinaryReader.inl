namespace Bibim
{
    Stream* BinaryReader::GetSource() const
    {
        return sourceStream;
    }

    bool BinaryReader::operator == (const BinaryReader& right) const
    {
        return sourceStream == right.sourceStream;
    }

    bool BinaryReader::operator != (const BinaryReader& right) const
    {
        return !operator == (right);
    }
}