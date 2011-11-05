#include <Bibim/PCH.h>
#include <Bibim/BinaryReader.h>
#include <Bibim/Memory.h>
#include <Bibim/Stream.h>

namespace Bibim
{
    BinaryReader::BinaryReader(Stream* sourceStream)
        : sourceStream(sourceStream)
    {
    }

    BinaryReader::BinaryReader(const BinaryReader& original)
        : sourceStream(original.sourceStream)
    {
    }

    BinaryReader::~BinaryReader()
    {
    }

    template <typename T> T BinaryReader::ReadTemplate()
    {
        BBAssertDebug(sourceStream != nullptr);

        T result;
        if (sourceStream->Read(&result, sizeof(T)) == sizeof(T))
            return result;
        else
        {
            // TODO: ERROR
            return T();
        }
    }

    void* BinaryReader::Read(void* buffer, int length)
    {
        BBAssertDebug(sourceStream != nullptr);

        if (sourceStream->Read(buffer, length) == length)
            return buffer;
        else
            return nullptr;
    }

    bool BinaryReader::ReadBool()
    {
        return ReadTemplate<bool>();
    }

    byte BinaryReader::ReadByte()
    {
        return ReadTemplate<byte>();
    }

    short BinaryReader::ReadShortInt()
    {
        return ReadTemplate<short>();
    }

    int BinaryReader::ReadInt()
    {
        return ReadTemplate<int>();
    }

    longint BinaryReader::ReadLongInt()
    {
        return ReadTemplate<longint>();
    }

    float BinaryReader::ReadFloat()
    {
        return ReadTemplate<float>();
    }

    double BinaryReader::ReadDouble()
    {
        return ReadTemplate<double>();
    }

    String BinaryReader::ReadString()
    {
        BBAssertDebug(sourceStream != nullptr);

        int readSize = 0;
        int length = 0;
        
        readSize = sourceStream->Read(&length, sizeof(length));
        BBAssert(readSize == sizeof(length));

        if (length > 0)
        {
            char* buffer = BBStackAlloc(char, length);
            readSize = sourceStream->Read(buffer, length);
            BBAssert(readSize == length);
            
            const String result = String(buffer, 0, length);
            
            BBStackFree(buffer);

            return result;
        }
        else
            return String::Empty;
    }

    Color BinaryReader::ReadColor()
    {
        return ReadTemplate<Color>();
    }

    Point2 BinaryReader::ReadPoint2()
    {
        return ReadTemplate<Point2>();
    }

    Point3 BinaryReader::ReadPoint3()
    {
        return ReadTemplate<Point3>();
    }

    Point4 BinaryReader::ReadPoint4()
    {
        return ReadTemplate<Point4>();
    }

    Rect BinaryReader::ReadRect()
    {
        return ReadTemplate<Rect>();
    }

    RectF BinaryReader::ReadRectF()
    {
        return ReadTemplate<RectF>();
    }

    Vector2 BinaryReader::ReadVector2()
    {
        return ReadTemplate<Vector2>();
    }

    Vector3 BinaryReader::ReadVector3()
    {
        return ReadTemplate<Vector3>();
    }

    Vector4 BinaryReader::ReadVector4()
    {
        return ReadTemplate<Vector4>();
    }

    BinaryReader& BinaryReader::operator = (const BinaryReader& right)
    {
        sourceStream = right.sourceStream;
        return *this;
    }
}