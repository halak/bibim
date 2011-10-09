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

    bool BinaryReader::ToBool(const byte* buffer)
    {
        return *buffer != 0;
    }

    int8 BinaryReader::ToInt8(const byte* buffer)
    {
        return *reinterpret_cast<const int8*>(buffer);
    }

    uint8 BinaryReader::ToUInt8(const byte* buffer)
    {
        return *reinterpret_cast<const uint8*>(buffer);
    }

    int16 BinaryReader::ToInt16(const byte* buffer)
    {
        return *reinterpret_cast<const int16*>(buffer);
    }

    uint16 BinaryReader::ToUInt16(const byte* buffer)
    {
        return *reinterpret_cast<const uint16*>(buffer);
    }

    int32 BinaryReader::ToInt32(const byte* buffer)
    {
        return *reinterpret_cast<const int32*>(buffer);
    }

    uint32 BinaryReader::ToUInt32(const byte* buffer)
    {
        return *reinterpret_cast<const uint32*>(buffer);
    }

    int64 BinaryReader::ToInt64(const byte* buffer)
    {
        return *reinterpret_cast<const int64*>(buffer);
    }

    uint64 BinaryReader::ToUInt64(const byte* buffer)
    {
        return *reinterpret_cast<const uint64*>(buffer);
    }

    float BinaryReader::ToFloat(const byte* buffer)
    {
        return *reinterpret_cast<const float*>(buffer);
    }

    Color BinaryReader::ToColor(const byte* buffer)
    {
        return Color(buffer[0], buffer[1], buffer[2], buffer[3]);
    }
}