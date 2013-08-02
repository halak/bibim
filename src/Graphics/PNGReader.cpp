#include <Bibim/Config.h>
#include <Bibim/PNGReader.h>
#include <Bibim/AssetStreamReader.h>
#include <Bibim/GameAsset.h>
#include <png.h>
#include <pngstruct.h>

namespace Bibim
{
    static void ReadPNGData(png_structp pngReader, png_bytep data, png_size_t length)
    {
        AssetStreamReader* reader = ((AssetStreamReader*)pngReader->io_ptr);
        if (reader->Read(data, length) == nullptr)
            png_error(pngReader, "Read Error");
    }

    bool PNGReader::Read(AssetStreamReader& reader,
                         byte* destination,
                         int destinationPitch,
                         bool swapRedBlue)
    {
        byte signature[8];
        reader.Read(signature, sizeof(signature) / sizeof(signature[0]));
        if (png_sig_cmp(signature, 0, sizeof(signature) / sizeof(signature[0])))
            return false;

        png_structp pngReader = png_create_read_struct(PNG_LIBPNG_VER_STRING,
                                                       nullptr,
                                                       nullptr,
                                                       nullptr);
        if (pngReader == nullptr)
            return false;

        png_infop pngInfo = png_create_info_struct(pngReader);
        if (pngInfo == nullptr)
        {
            png_destroy_read_struct(&pngReader, nullptr, nullptr);
            return false;
        }

        png_set_read_fn(pngReader, (png_voidp)&reader, ReadPNGData);

        png_set_sig_bytes(pngReader, 8);

        png_read_info(pngReader, pngInfo);

        png_uint_32 width = 0;
        png_uint_32 height = 0;
        int bitDepth = 0;
        int colorType = 0;
        png_get_IHDR(pngReader, pngInfo, &width, &height, &bitDepth, &colorType, NULL, NULL, NULL);

        png_size_t pitch = png_get_rowbytes(pngReader, pngInfo);
        // png_size_t channels = png_get_channels(pngReader, pngInfo);

        if (colorType == PNG_COLOR_TYPE_RGB_ALPHA)
        {
            BBAssert(static_cast<int>(pitch) == destinationPitch);
        }
        else if (colorType == PNG_COLOR_TYPE_RGB)
        {
            // RGBA가 아니라 RGB 3byte로 저장되어있기 때문에 표면 pitch의 3/4의 크기여야합니다.
            BBAssert(static_cast<int>(pitch) == destinationPitch * 3 / 4);
        }

        png_bytep* rows = BBStackAlloc(png_bytep, height);
        for (png_uint_32 i = 0; i < height; i++)
            rows[i] = &destination[destinationPitch * i];

        png_read_image(pngReader, rows);

        png_read_end(pngReader, nullptr);

        png_destroy_read_struct(&pngReader, &pngInfo, nullptr);

        if (colorType == PNG_COLOR_TYPE_RGB)
        {
            const int RED   = swapRedBlue == false ? 0 : 2;
            const int GREEN = 1;
            const int BLUE  = swapRedBlue == false ? 2 : 0;

            for (png_uint_32 i = 0; i < height; i++)
            {
                png_bytep row = rows[i];
                for (int k = static_cast<int>(width - 1); k >= 0; k--)
                {
                    const int a = k * 4;
                    const int b = k * 3;
                    row[a + 0] = row[b + RED];
                    row[a + 1] = row[b + GREEN];
                    row[a + 2] = row[b + BLUE];
                    row[a + 3] = 0xff;
                }
            }
        }
        else if (colorType == PNG_COLOR_TYPE_RGBA)
        {
            if (swapRedBlue)
            {
                for (png_uint_32 y = 0; y < height; y++)
                {
                    png_bytep row = rows[y];
                    for (png_uint_32 x = 0; x < width; x++, row+=4)
                    {
                        const png_byte temporary = row[0];
                        row[0] = row[2];
                        row[2] = temporary;
                    }
                }
            }
        }

        BBStackFree(rows);

        return true;
    }
}