namespace Bibim
{
    void BinaryReader::Read(bool& outValue)
    {
        outValue = ReadBool();
    }

    void BinaryReader::Read(byte& outValue)
    {
        outValue = ReadByte();
    }

    void BinaryReader::Read(short& outValue)
    {
        outValue = ReadShortInt();
    }

    void BinaryReader::Read(int& outValue)
    {
        outValue = ReadInt();
    }

    void BinaryReader::Read(longint& outValue)
    {
        outValue = ReadLongInt();
    }

    void BinaryReader::Read(float& outValue)
    {
        outValue = ReadFloat();
    }

    void BinaryReader::Read(double& outValue)
    {
        outValue = ReadDouble();
    }

    void BinaryReader::Read(String& outValue)
    {
        outValue = ReadString();
    }

    void BinaryReader::Read(Color& outValue)
    {
        outValue = ReadColor();
    }

    void BinaryReader::Read(Point2& outValue)
    {
        outValue = ReadPoint2();
    }

    void BinaryReader::Read(Point3& outValue)
    {
        outValue = ReadPoint3();
    }

    void BinaryReader::Read(Point4& outValue)
    {
        outValue = ReadPoint4();
    }

    void BinaryReader::Read(Rect& outValue)
    {
        outValue = ReadRect();
    }

    void BinaryReader::Read(RectF& outValue)
    {
        outValue = ReadRectF();
    }

    void BinaryReader::Read(Vector2& outValue)
    {
        outValue = ReadVector2();
    }

    void BinaryReader::Read(Vector3& outValue)
    {
        outValue = ReadVector3();
    }

    void BinaryReader::Read(Vector4& outValue)
    {
        outValue = ReadVector4();
    }

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

    template <typename T> T BinaryReader::ToTemplate(const byte* buffer)
    {
        return *reinterpret_cast<const T*>(buffer);
    }

    bool BinaryReader::ToBool(const byte* buffer)
    {
        return (*buffer) != 0;
    }

    byte BinaryReader::ToByte(const byte* buffer)
    {
        return ToTemplate<byte>(buffer);
    }

    short BinaryReader::ToShortInt(const byte* buffer)
    {
        return ToTemplate<short>(buffer);
    }

    int BinaryReader::ToInt(const byte* buffer)
    {
        return ToTemplate<int>(buffer);
    }

    longint BinaryReader::ToLongInt(const byte* buffer)
    {
        return ToTemplate<longint>(buffer);
    }

    float BinaryReader::ToFloat(const byte* buffer)
    {
        return ToTemplate<float>(buffer);
    }

    double BinaryReader::ToDouble(const byte* buffer)
    {
        return ToTemplate<double>(buffer);
    }

    Color BinaryReader::ToColor(const byte* buffer)
    {
        return ToTemplate<Color>(buffer);
    }

    Point2 BinaryReader::ToPoint2(const byte* buffer)
    {
        return ToTemplate<Point2>(buffer);
    }

    Point3 BinaryReader::ToPoint3(const byte* buffer)
    {
        return ToTemplate<Point3>(buffer);
    }

    Point4 BinaryReader::ToPoint4(const byte* buffer)
    {
        return ToTemplate<Point4>(buffer);
    }

    Rect BinaryReader::ToRect(const byte* buffer)
    {
        return ToTemplate<Rect>(buffer);
    }

    RectF BinaryReader::ToRectF(const byte* buffer)
    {
        return ToTemplate<RectF>(buffer);
    }

    Vector2 BinaryReader::ToVector2(const byte* buffer)
    {
        return ToTemplate<Vector2>(buffer);
    }

    Vector3 BinaryReader::ToVector3(const byte* buffer)
    {
        return ToTemplate<Vector3>(buffer);
    }

    Vector4 BinaryReader::ToVector4(const byte* buffer)
    {
        return ToTemplate<Vector4>(buffer);
    }
}