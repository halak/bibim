#include <Bibim/Config.h>
#include <Bibim/JPEG.h>
#include <Bibim/AssetStreamReader.h>
#include <Bibim/GameAsset.h>
#include <Bibim/Memory.h>
#include <Bibim/Stream.h>
#include <stdio.h>
#include <jpeglib.h>

namespace Bibim
{
    static const int JpegSourceBufferSize = 4096;
    struct JpegSource
    {
        struct jpeg_source_mgr pub;
        Stream* stream;
        byte* buffer;
    };

    static void JpegSourceInit(j_decompress_ptr /*cinfo*/)
    {
    }

    static boolean JpegSourceFillBuffer(j_decompress_ptr cinfo)
    {
        JpegSource* source = reinterpret_cast<JpegSource*>(cinfo->src);
        Stream* stream = source->stream;
        int bytesRead = stream->Read(source->buffer, JpegSourceBufferSize);
        if (bytesRead <= 0)
        {
            // INSERT FAKE END OF IMAGE MARKER
            source->buffer[0] = static_cast<JOCTET>(0xFF);
            source->buffer[1] = static_cast<JOCTET>(JPEG_EOI);
            bytesRead = 2;
        }

        source->pub.next_input_byte = source->buffer;
        source->pub.bytes_in_buffer = bytesRead;

        return TRUE;
    }

    static void JpegSourceSkip(j_decompress_ptr cinfo, long nbytes)
    {
        if (nbytes <= 0)
            return;

        struct jpeg_source_mgr* source = reinterpret_cast<struct jpeg_source_mgr*>(cinfo->src);

        while (nbytes > static_cast<long>(source->bytes_in_buffer))
        {
            nbytes -= static_cast<long>(source->bytes_in_buffer);
            JpegSourceFillBuffer(cinfo);
        }

        source->next_input_byte += (size_t)nbytes;
        source->bytes_in_buffer -= (size_t)nbytes;
    }

    static void JpegSourceTerm(j_decompress_ptr /*cinfo*/)
    {
    }

    bool JPEG::Read(AssetStreamReader& reader,
                    byte* destination,
                    int destinationPitch,
                    bool swapRedBlue)
    {
        const int RED  = swapRedBlue ? 2 : 0;
        const int BLUE = swapRedBlue ? 0 : 2;

        struct jpeg_error_mgr errorManager;
        struct jpeg_decompress_struct jpegReader;

        jpegReader.err = jpeg_std_error(&errorManager);
        jpeg_create_decompress(&jpegReader);

        byte buffer[JpegSourceBufferSize];
        void* sourceMemory = (*jpegReader.mem->alloc_small)((j_common_ptr)&jpegReader,
                                                            JPOOL_PERMANENT,
                                                            sizeof(JpegSource));
        JpegSource* jpegSource = reinterpret_cast<JpegSource*>(sourceMemory);
        jpegSource->pub.init_source = &JpegSourceInit;
        jpegSource->pub.fill_input_buffer = &JpegSourceFillBuffer;
        jpegSource->pub.skip_input_data = &JpegSourceSkip;
        jpegSource->pub.resync_to_restart = &jpeg_resync_to_restart;
        jpegSource->pub.term_source = &JpegSourceTerm;
        jpegSource->pub.bytes_in_buffer = 0;
        jpegSource->pub.next_input_byte = NULL;
        jpegSource->stream = reader.GetSource();
        jpegSource->buffer = buffer;
        jpegReader.src = reinterpret_cast<struct jpeg_source_mgr*>(jpegSource);

        jpeg_read_header(&jpegReader, TRUE);

        jpeg_start_decompress(&jpegReader);

        const int rowStride = jpegReader.output_width * jpegReader.output_components;
        JSAMPARRAY source = (*jpegReader.mem->alloc_sarray)((j_common_ptr)&jpegReader, JPOOL_IMAGE, rowStride, 1);

        while (jpegReader.output_scanline < jpegReader.output_height)
        {
            jpeg_read_scanlines(&jpegReader, source, 1);
            for (unsigned int i = 0, x1 = 0, x2 = 0; i < jpegReader.output_width; i++, x1 += 4, x2 += 3)
            {
                destination[x1 + 0] = source[0][x2 + RED];
                destination[x1 + 1] = source[0][x2 + 1];
                destination[x1 + 2] = source[0][x2 + BLUE];
                destination[x1 + 3] = 0xFF;
            }
            destination += destinationPitch;
        }

        jpeg_finish_decompress(&jpegReader);

        jpeg_destroy_decompress(&jpegReader);

        /*
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
        */

        return true;
    }
}