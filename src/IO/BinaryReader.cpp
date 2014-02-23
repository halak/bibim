#include <Bibim/Config.h>
#include <Bibim/BinaryReader.h>
#include <Bibim/Log.h>
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

    void* BinaryReader::ReadFrom(Stream* stream, void* buffer, int length)
    {
        BBAssertDebug(stream != nullptr);
        stream->Read(buffer, length);
        return buffer;        
    }

    template <typename T> T BinaryReader::ReadFromTemplate(Stream* stream)
    {
        BBAssertDebug(stream != nullptr);

        T result;
        if (stream->Read(&result, sizeof(T)) == sizeof(T))
            return result;
        else
        {
            Log::Error("BinaryWriter::ReadFromTemplate Error");
            return T();
        }
    }

    bool BinaryReader::ReadBoolFrom(Stream* stream)
    {
        return ReadFromTemplate<bool>(stream);
    }

    byte BinaryReader::ReadByteFrom(Stream* stream)
    {
        return ReadFromTemplate<byte>(stream);
    }

    short BinaryReader::ReadShortIntFrom(Stream* stream)
    {
        return ReadFromTemplate<short>(stream);
    }

    int BinaryReader::ReadIntFrom(Stream* stream)
    {
        return ReadFromTemplate<int>(stream);
    }

    longint BinaryReader::ReadLongIntFrom(Stream* stream)
    {
        return ReadFromTemplate<longint>(stream);
    }

    float BinaryReader::ReadFloatFrom(Stream* stream)
    {
        return ReadFromTemplate<float>(stream);
    }

    double BinaryReader::ReadDoubleFrom(Stream* stream)
    {
        return ReadFromTemplate<double>(stream);
    }

    String BinaryReader::ReadStringFrom(Stream* stream)
    {
        BBAssertDebug(stream != nullptr);

        int readSize = 0;
        int length = 0;
        
        readSize = stream->Read(&length, sizeof(length));
        BBAssert(readSize == sizeof(length));

        if (length > 0)
        {
            char* buffer = BBStackAlloc(char, length);
            readSize = stream->Read(buffer, length);
            BBAssert(readSize == length);
            
            const String result = String(buffer, 0, length);
            
            BBStackFree(buffer);

            return result;
        }
        else
            return String::Empty;
    }

    Color BinaryReader::ReadColorFrom(Stream* stream)
    {
        return ReadFromTemplate<Color>(stream);
    }

    Point2 BinaryReader::ReadPoint2From(Stream* stream)
    {
        return ReadFromTemplate<Point2>(stream);
    }

    Point3 BinaryReader::ReadPoint3From(Stream* stream)
    {
        return ReadFromTemplate<Point3>(stream);
    }

    Point4 BinaryReader::ReadPoint4From(Stream* stream)
    {
        return ReadFromTemplate<Point4>(stream);
    }

    Rect BinaryReader::ReadRectFrom(Stream* stream)
    {
        return ReadFromTemplate<Rect>(stream);
    }

    RectF BinaryReader::ReadRectFFrom(Stream* stream)
    {
        return ReadFromTemplate<RectF>(stream);
    }

    Vector2 BinaryReader::ReadVector2From(Stream* stream)
    {
        return ReadFromTemplate<Vector2>(stream);
    }

    Vector3 BinaryReader::ReadVector3From(Stream* stream)
    {
        return ReadFromTemplate<Vector3>(stream);
    }

    Vector4 BinaryReader::ReadVector4From(Stream* stream)
    {
        return ReadFromTemplate<Vector4>(stream);
    }

    BinaryReader& BinaryReader::operator = (const BinaryReader& right)
    {
        sourceStream = right.sourceStream;
        return *this;
    }
}