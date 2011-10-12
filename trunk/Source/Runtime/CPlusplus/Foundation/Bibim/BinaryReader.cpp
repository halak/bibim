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

    int8 BinaryReader::ReadInt8()
    {
        return ReadTemplate<int8>();
    }

    uint8 BinaryReader::ReadUInt8()
    {
        return ReadTemplate<uint8>();
    }

    int16 BinaryReader::ReadInt16()
    {
        return ReadTemplate<int16>();
    }

    uint16 BinaryReader::ReadUInt16()
    {
        return ReadTemplate<uint16>();
    }

    int32 BinaryReader::ReadInt32()
    {
        return ReadTemplate<int32>();
    }

    uint32 BinaryReader::ReadUInt32()
    {
        return ReadTemplate<uint32>();
    }

    int64 BinaryReader::ReadInt64()
    {
        return ReadTemplate<int64>();
    }

    uint64 BinaryReader::ReadUInt64()
    {
        return ReadTemplate<uint64>();
    }

    float BinaryReader::ReadFloat()
    {
        return ReadTemplate<float>();
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
        BBStaticAssert(sizeof(Color) == 4);
        return ReadTemplate<Color>();
    }

    Rect BinaryReader::ReadRect()
    {
        BBStaticAssert(sizeof(Rect) == 16);
        return ReadTemplate<Rect>();
    }

    RectF BinaryReader::ReadRectF()
    {
        BBStaticAssert(sizeof(RectF) == 16);
        return ReadTemplate<RectF>();
    }

    Vector2 BinaryReader::ReadVector2()
    {
        BBStaticAssert(sizeof(Vector2) == 8);
        return ReadTemplate<Vector2>();
    }

    Vector3 BinaryReader::ReadVector3()
    {
        BBStaticAssert(sizeof(Vector3) == 12);
        return ReadTemplate<Vector3>();
    }

    Vector4 BinaryReader::ReadVector4()
    {
        BBStaticAssert(sizeof(Vector4) == 16);
        return ReadTemplate<Vector4>();
    }

    BinaryReader& BinaryReader::operator = (const BinaryReader& right)
    {
        sourceStream = right.sourceStream;
        return *this;
    }
}