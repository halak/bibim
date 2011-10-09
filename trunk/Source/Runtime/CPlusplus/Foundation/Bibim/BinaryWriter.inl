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
    
    void BinaryWriter::From(byte* buffer, bool value)
    {
        *buffer = value ? 1 : 0;
    }

    void BinaryWriter::From(byte* buffer, int8 value)
    {
        *(reinterpret_cast<int8*>(buffer)) = value;
    }

    void BinaryWriter::From(byte* buffer, uint8 value)
    {
        *(reinterpret_cast<uint8*>(buffer)) = value;
    }

    void BinaryWriter::From(byte* buffer, int16 value)
    {
        *(reinterpret_cast<int16*>(buffer)) = value;
    }

    void BinaryWriter::From(byte* buffer, uint16 value)
    {
        *(reinterpret_cast<uint16*>(buffer)) = value;
    }

    void BinaryWriter::From(byte* buffer, int32 value)
    {
        *(reinterpret_cast<int32*>(buffer)) = value;
    }

    void BinaryWriter::From(byte* buffer, uint32 value)
    {
        *(reinterpret_cast<uint32*>(buffer)) = value;
    }

    void BinaryWriter::From(byte* buffer, int64 value)
    {
        *(reinterpret_cast<int64*>(buffer)) = value;
    }

    void BinaryWriter::From(byte* buffer, uint64 value)
    {
        *(reinterpret_cast<uint64*>(buffer)) = value;
    }

    void BinaryWriter::From(byte* buffer, float value)
    {
        *(reinterpret_cast<float*>(buffer)) = value;
    }
}