#include <Bibim/PCH.h>
#include <Bibim/BitMask.h>
#include <Bibim/AssetStreamReader.h>
#include <Bibim/Math.h>

namespace Bibim
{
    BitMask::BitMask(int width, int height, int pitch, std::vector<byte>& buffer)
        : width(width),
          height(height),
          pitch(pitch)
    {
        this->buffer.swap(buffer);
    }

    BitMask::~BitMask()
    {
    }

    bool BitMask::GetPixel(int x, int y)
    {
        x = Math::Clamp(x, 0, width - 1);
        y = Math::Clamp(y, 0, height - 1);
        const int index = static_cast<int>(x / BitsPerByte) + (y * pitch);
        return (buffer[index] & (0x80 >> (x % BitsPerByte))) != 0;
    }

    void BitMask::SetPixel(int x, int y, bool value)
    {
        x = Math::Clamp(x, 0, width - 1);
        y = Math::Clamp(y, 0, height - 1);
        const int index = static_cast<int>(x / BitsPerByte) + (y * pitch);

        if (value)
            buffer[index] |= (0x80 >> (x % BitsPerByte));
        else
            buffer[index] &= ~(0x80 >> (x % BitsPerByte));
    }

    GameAsset* BitMask::Create(StreamReader& reader, GameAsset* /*existingInstance*/)
    {
        const int width = static_cast<int>(reader.ReadShortInt());
        const int height = static_cast<int>(reader.ReadShortInt());
        const int pitch = static_cast<int>(reader.ReadShortInt());
        if (width == 0 || height == 0 || pitch == 0)
            return nullptr;

        std::vector<byte> buffer;
        buffer.resize(pitch * height);
        reader.Read(&buffer[0], static_cast<int>(buffer.size()));

        return new BitMask(width, height, pitch, buffer);
    }
}