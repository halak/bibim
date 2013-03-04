#include <Bibim/PCH.h>
#include <Bibim/PNGReader.h>
#include <Bibim/AssetStreamReader.h>
#include <Bibim/GameAsset.h>
#include <png.h>
#include <pngstruct.h>
#include <zlib.h>

namespace Bibim
{
    static void ReadPNGData(png_structp pngReader, png_bytep data, png_size_t length)
    {
        AssetStreamReader* reader = ((AssetStreamReader*)pngReader->io_ptr);
        if (reader->Read(data, length) == nullptr)
            png_error(pngReader, "Read Error");
    }

    bool PNGReader::Read(AssetStreamReader& reader, byte* destination, int destinationPitch)
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

        BBAssert(static_cast<int>(pitch) == destinationPitch);

        png_bytep* rows = BBStackAlloc(png_bytep, height);
        for (png_uint_32 i = 0; i < height; i++)
            rows[i] = &destination[destinationPitch * i];

        png_read_image(pngReader, rows);

        png_read_end(pngReader, nullptr);

        png_destroy_read_struct(&pngReader, &pngInfo, nullptr);

        BBStackFree(rows);

        return true;
    }
}