namespace Bibim
{
    Stream* BinaryWriter::GetSource() const
    {
        return sourceStream;
    }

    bool BinaryWriter::operator == (const BinaryWriter& right) const
    {
        return sourceStream == right.sourceStream;
    }

    bool BinaryWriter::operator != (const BinaryWriter& right) const
    {
        return !operator == (right);
    }
}