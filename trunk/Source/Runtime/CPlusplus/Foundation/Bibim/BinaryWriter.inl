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

    template <typename T> void BinaryWriter::FromTemplate(byte* buffer, T value)
    {
        *(reinterpret_cast<T*>(buffer)) = value;
    }

    void BinaryWriter::From(byte* buffer, bool value)
    {
        (*buffer) = value ? 1 : 0;
    }

    void BinaryWriter::From(byte* buffer, byte value)
    {
        FromTemplate(buffer, value);
    }

    void BinaryWriter::From(byte* buffer, short value)
    {
        FromTemplate(buffer, value);
    }

    void BinaryWriter::From(byte* buffer, int value)
    {
        FromTemplate(buffer, value);
    }

    void BinaryWriter::From(byte* buffer, longint value)
    {
        FromTemplate(buffer, value);
    }

    void BinaryWriter::From(byte* buffer, float value)
    {
        FromTemplate(buffer, value);
    }

    void BinaryWriter::From(byte* buffer, double value)
    {
        FromTemplate(buffer, value);
    }

    void BinaryWriter::From(byte* buffer, Color value)
    {
        FromTemplate(buffer, value);
    }

    void BinaryWriter::From(byte* buffer, Point2 value)
    {
        FromTemplate(buffer, value);
    }

    void BinaryWriter::From(byte* buffer, Point3 value)
    {
        FromTemplate(buffer, value);
    }

    void BinaryWriter::From(byte* buffer, Point4 value)
    {
        FromTemplate(buffer, value);
    }

    void BinaryWriter::From(byte* buffer, Rect value)
    {
        FromTemplate(buffer, value);
    }

    void BinaryWriter::From(byte* buffer, RectF value)
    {
        FromTemplate(buffer, value);
    }

    void BinaryWriter::From(byte* buffer, Vector2 value)
    {
        FromTemplate(buffer, value);
    }

    void BinaryWriter::From(byte* buffer, Vector3 value)
    {
        FromTemplate(buffer, value);
    }

    void BinaryWriter::From(byte* buffer, Vector4 value)
    {
        FromTemplate(buffer, value);
    }
}