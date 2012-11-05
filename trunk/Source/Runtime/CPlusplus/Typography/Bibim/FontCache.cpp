#include <Bibim/PCH.h>
#include <Bibim/FontCache.h>
#include <Bibim/FontLibrary.h>
#include <Bibim/Glyph.h>
#include <Bibim/GlyphTable.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_STROKER_H
#include FT_BITMAP_H
#include <windows.h>

namespace Bibim
{
    static FT_Vector ZeroVector = { 0, 0 };

    // library 26.6 실수계와 C++ float 좌표계를 상호 변환한다.
    // http://library.sourceforge.net/library2/docs/glyphs/glyphs-3.html
    static inline float F26D6ToFloat(FT_F26Dot6 value)
    {
        return static_cast<float>(value) / 64.0f;
    }

    static inline FT_F26Dot6 FloatToF26D6(float value)
    {
        return static_cast<FT_F26Dot6>(value * 64.0f);
    }

    static inline float F16D16ToFloat(FT_Fixed value)
    {
        return static_cast<float>(value) / 65536.0f;
    }

    static inline FT_Fixed FloatToF16D16(float value)
    {
        return static_cast<FT_F26Dot6>(value * 65536.0f);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    FontCacheParameters::FontCacheParameters()
        : FontSize(10.0f),
          StrokeSize(0.0f),
          Weights(0.0f),
          Shear(0.0f),
          GlowSize(0),
          GlowSpread(0.0f),
          GlowThickness(0.0f),
          Scale(1.0f),
          Hinting(true),
          IgnoreBitmap(false)
    {
    }

    FontCacheParameters::FontCacheParameters(const String& faceURI, float fontSize, float strokeSize, float weights, float shear, 
                                             int glowSize, float glowSpread, float glowThickness,
                                             float scale, bool hinting, bool ignoreBitmap)
        : FaceURI(faceURI),
          FontSize(fontSize),
          StrokeSize(strokeSize),
          Weights(weights),
          Shear(shear),
          GlowSize(glowSize),
          GlowSpread(glowSpread),
          GlowThickness(glowThickness),
          Scale(scale),
          Hinting(hinting),
          IgnoreBitmap(ignoreBitmap)
    {
    }

    FontCacheParameters::FontCacheParameters(const FontCacheParameters& original)
        : FaceURI(original.FaceURI),
          FontSize(original.FontSize),
          StrokeSize(original.StrokeSize),
          Weights(original.Weights),
          Shear(original.Shear),
          GlowSize(original.GlowSize),
          GlowSpread(original.GlowSpread),
          GlowThickness(original.GlowThickness),
          Scale(original.Scale),
          Hinting(original.Hinting),
          IgnoreBitmap(original.IgnoreBitmap)
    {
    }

    unsigned int FontCacheParameters::GetHashCode() const
    {
        unsigned int result = 0;
        result += static_cast<unsigned int>(FaceURI.GetLength() * 65536);
        result += static_cast<unsigned int>(FloatToF26D6(FontSize));
        result += static_cast<unsigned int>(FloatToF26D6(StrokeSize));
        result += static_cast<unsigned int>(FloatToF26D6(Weights));
        result += static_cast<unsigned int>(FloatToF16D16(Shear));
        result += static_cast<unsigned int>(GlowSize);
        result += static_cast<unsigned int>(GlowSpread * 100.0f);
        result += static_cast<unsigned int>(GlowThickness * 100.0f);
        result += static_cast<unsigned int>(Scale * 100.0f);
        result += static_cast<unsigned int>(Hinting ? 0x08000000 : 0x00000000);
        result += static_cast<unsigned int>(IgnoreBitmap ? 0x00800000 : 0x00000000);
        return result;
    }

    FontCacheParameters& FontCacheParameters::operator = (const FontCacheParameters& right)
    {
        FaceURI = right.FaceURI;
        FontSize = right.FontSize;
        StrokeSize = right.StrokeSize;
        Weights = right.Weights;
        Shear = right.Shear;
        GlowSize = right.GlowSize;
        GlowSpread = right.GlowSpread;
        GlowThickness = right.GlowThickness;
        Scale = right.Scale;
        Hinting = right.Hinting;
        IgnoreBitmap = right.IgnoreBitmap;
        return *this;
    }

    bool FontCacheParameters::operator == (const FontCacheParameters& right) const
    {
        if (GlowSize > 0 && right.GlowSize > 0)
        {
            return (FaceURI                  == right.FaceURI &&
                    FloatToF26D6(FontSize)   == FloatToF26D6(right.FontSize) &&
                    FloatToF26D6(StrokeSize) == FloatToF26D6(right.StrokeSize) &&
                    FloatToF26D6(Weights)    == FloatToF26D6(right.Weights) &&
                    FloatToF16D16(Shear)     == FloatToF16D16(right.Shear) &&
                    GlowSize                 == right.GlowSize &&
                    GlowSpread               == right.GlowSpread &&
                    GlowThickness            == right.GlowThickness &&
                    FloatToF26D6(Scale)      == FloatToF26D6(right.Scale) &&
                    Hinting                  == right.Hinting &&
                    IgnoreBitmap             == right.IgnoreBitmap);
        }
        else if (GlowSize == 0 && right.GlowSize == 0)
        {
            return (FaceURI                  == right.FaceURI &&
                    FloatToF26D6(FontSize)   == FloatToF26D6(right.FontSize) &&
                    FloatToF26D6(StrokeSize) == FloatToF26D6(right.StrokeSize) &&
                    FloatToF26D6(Weights)    == FloatToF26D6(right.Weights) &&
                    FloatToF16D16(Shear)     == FloatToF16D16(right.Shear) &&
                    FloatToF26D6(Scale)      == FloatToF26D6(right.Scale) &&
                    Hinting                  == right.Hinting &&
                    IgnoreBitmap             == right.IgnoreBitmap);
        }
        else
            return false;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    FontCache::FontCache(FontLibrary* library, const FontCacheParameters& parameters)
        : library(library),
          parameters(parameters),
          primaryFace(nullptr),
          alternativeFace(nullptr),
          stroker(nullptr),
          ascender(0.0f),
          descender(0.0f),
          lineHeight(0.0f),
          regularGlyphTable(nullptr),
          strokedGlyphTable(nullptr),
          glowGlyphTable(nullptr)
    {
        String faceFilename = parameters.FaceURI;
        int    faceIndex    = 0; // *.ttc 파일일 경우 폰트가 존재하는 위치 (TTC = TrueTypeCollection)

        int separatorIndex = parameters.FaceURI.ReverseFind('?');
        if (separatorIndex != -1)
        {
            faceFilename = parameters.FaceURI.Substring(0, separatorIndex);
            faceIndex    = atoi(parameters.FaceURI.Substring(separatorIndex + 1).CStr());
        }

        if (FT_Error error = FT_New_Face(static_cast<FT_Library>(library->GetFTLibrary()), faceFilename.CStr(), faceIndex, &primaryFace))
        {
            const String newFaceFilepath = library->GetOSFontDirectory() + faceFilename;
            if (FT_New_Face(static_cast<FT_Library>(library->GetFTLibrary()), newFaceFilepath.CStr(), faceIndex, &primaryFace))
            {
                // ERROR 처리 (return하지는 않음)
            }
        }

        if (FT_Error error = FT_New_Face(static_cast<FT_Library>(library->GetFTLibrary()), library->GetAlternativeFace().CStr(), 0, &alternativeFace))
        {
            // ERROR 처리 (return하지는 않음)
        }

        const FT_F26Dot6 scaledFontSize = FloatToF26D6(parameters.FontSize * parameters.Scale);

        if (primaryFace)
            FT_Set_Char_Size(primaryFace, 0, scaledFontSize, 96, 96);
        if (alternativeFace)
            FT_Set_Char_Size(alternativeFace, 0, scaledFontSize, 96, 96);

        if (parameters.StrokeSize > 0.0f)
        {
            if (FT_Error error = FT_Stroker_New(static_cast<FT_Library>(library->GetFTLibrary()), &stroker))
            {
                // ERROR 처리
            }

            const FT_F26Dot6 scaledStrokeSize = FloatToF26D6(parameters.StrokeSize * parameters.Scale);

            if (stroker)
                FT_Stroker_Set(stroker, scaledStrokeSize, FT_STROKER_LINECAP_BUTT, FT_STROKER_LINEJOIN_ROUND, 0);
        }

        transform[0][0] = FloatToF16D16(1.0f);
        transform[0][1] = FloatToF16D16(parameters.Shear);
        transform[1][0] = FloatToF16D16(0.0f);
        transform[1][1] = FloatToF16D16(1.0f);

        const FT_Face metricsFont = primaryFace ? primaryFace : alternativeFace;
        const FT_Size_Metrics& metrics = metricsFont->size->metrics;
        ascender   = F26D6ToFloat(metrics.ascender) / parameters.Scale;
        descender  = F26D6ToFloat(metrics.descender) / parameters.Scale;
        lineHeight = F26D6ToFloat(metrics.height) / parameters.Scale;

        regularGlyphTable = new GlyphTable(library->GetGraphicsDevice());

        if (stroker)
            strokedGlyphTable = new GlyphTable(library->GetGraphicsDevice());
    }

    FontCache::~FontCache()
    {
        delete glowGlyphTable;
        delete strokedGlyphTable;
        delete regularGlyphTable;

        if (stroker)
            FT_Stroker_Done(stroker);
        if (alternativeFace)
            FT_Done_Face(alternativeFace);
        if (primaryFace)
            FT_Done_Face(primaryFace);
    }

    const Glyph* FontCache::GetGlyph(int code)
    {
        if (const Glyph* result = regularGlyphTable->Find(code))
            return result;
        else
        {
            if (code == '\t')
            {
                static const float TabSize = 4.0f;
                const Glyph* regularGlyph = GetGlyph(' ');

                if (parameters.StrokeSize > 0.0f)
                {
                    if (const Glyph* strokedGlyph = strokedGlyphTable->Find(' '))
                    {
                        const Vector2 advance = strokedGlyph->GetAdvance();
                        strokedGlyphTable->Add('\t',
                                               Vector2(advance.X * TabSize, advance.Y),
                                               Vector2::Zero,
                                               Vector2::Zero,
                                               nullptr, 0, 0, 0);
                    }
                }

                const Vector2 advance = regularGlyph->GetAdvance();
                return regularGlyphTable->Add('\t',
                                              Vector2(advance.X * TabSize, advance.Y),
                                              Vector2::Zero,
                                              Vector2::Zero,
                                              nullptr, 0, 0, 0);
            }

            struct SelectFace
            {
                // 두 Face에서 Code를 찾아서 반환합니다.
                static std::pair<FT_Face, unsigned int> Do(FT_Face primary, FT_Face alternative, int code)
                {
                    if (primary)
                    {
                        const unsigned int index = FT_Get_Char_Index(primary, code);
                        if (index != 0)
                            return std::pair<FT_Face, unsigned int>(primary, index);
                    }

                    if (alternative)
                    {
                        const unsigned int index = FT_Get_Char_Index(alternative, code);
                        if (index != 0)
                            return std::pair<FT_Face, unsigned int>(alternative, index);
                    }

                    return std::pair<FT_Face, unsigned int>(nullptr, 0);
                }
            };

            // Grayscale을 보장하는 Bitmap 구조체.
            // 원본 Bitmap이 8bpp라면 그대로 보관하고,
            // 만약 8pp가 아니라면 8pp로 변환합니다.
            // 새로이 생성된 Bitmap은 자동으로 삭제됩니다.
            struct GrayscaleBitmap
            {
                FT_Library Library;
                FT_Bitmap* Bitmap;
                bool isNewBitmap;

                GrayscaleBitmap(FT_Library library, FT_Bitmap& source)
                    : Library(library)
                {
                    if (source.pixel_mode == FT_PIXEL_MODE_GRAY)
                    {
                        Bitmap = &source;
                        isNewBitmap = false;
                    }
                    else
                    {
                        Bitmap = new FT_Bitmap();
                        FT_Bitmap_Convert(Library, &source, Bitmap, 8);
                        isNewBitmap = true;

                        const byte scale = static_cast<byte>(255 / (Bitmap->num_grays - 1));
                        byte* destination = static_cast<byte*>(Bitmap->buffer);
                        for (int y = 0; y < Bitmap->rows; y++)
                        {
                            for (int x = 0; x < Bitmap->width; x++)
                            {
                                destination[x] *= scale;
                            }
                            destination += Bitmap->pitch;
                        }
                    }
                }

                ~GrayscaleBitmap()
                {
                    if (isNewBitmap)
                    {
                        FT_Bitmap_Done(Library, Bitmap);
                        delete Bitmap;
                    }
                }
            };

            std::pair<FT_Face, unsigned int> faceGlyphIndex = SelectFace::Do(primaryFace, alternativeFace, code);
            if (faceGlyphIndex.first == nullptr)
                faceGlyphIndex = SelectFace::Do(primaryFace, alternativeFace, L'?');

            FT_Int32 loadFlags = FT_LOAD_DEFAULT;
            if (parameters.IgnoreBitmap)
                loadFlags |= FT_LOAD_NO_BITMAP;
            if (parameters.Hinting == false)
                loadFlags |= FT_LOAD_NO_HINTING;

            FT_Matrix ftTransform = 
            {
                transform[0][0], transform[0][1],
                transform[1][0], transform[1][1],
            };
            FT_Set_Transform(faceGlyphIndex.first, &ftTransform, &ZeroVector);

            if (parameters.StrokeSize > 0.0f)
            {
                FT_Error result = 0;
                FT_Glyph strokedGlyph = nullptr;
                FT_Load_Glyph(faceGlyphIndex.first, faceGlyphIndex.second, loadFlags | FT_LOAD_NO_BITMAP);
                FT_Get_Glyph(faceGlyphIndex.first->glyph, &strokedGlyph);
                if (FT_Glyph_Stroke(&strokedGlyph, stroker, 1) == 0)
                {
                    result = FT_Glyph_To_Bitmap(&strokedGlyph, FT_RENDER_MODE_NORMAL, nullptr, 1);

                    FT_BitmapGlyph strokedGlyphBitmap = reinterpret_cast<FT_BitmapGlyph>(strokedGlyph);

                    if (parameters.Weights > 0.0f)
                        FT_Bitmap_Embolden(static_cast<FT_Library>(library->GetFTLibrary()), &strokedGlyphBitmap->bitmap, FloatToF26D6(parameters.Weights), 0);

                    GrayscaleBitmap glyphBitmap(static_cast<FT_Library>(library->GetFTLibrary()), strokedGlyphBitmap->bitmap);

                    const Vector2 advance = Vector2(F16D16ToFloat(strokedGlyph->advance.x), F16D16ToFloat(strokedGlyph->advance.y));
                    const Vector2 bitmapOffset = Vector2(static_cast<float>(strokedGlyphBitmap->left), GetAscender() - static_cast<float>(strokedGlyphBitmap->top));
                    const Vector2 bitmapSize   = Vector2(glyphBitmap.Bitmap->width, glyphBitmap.Bitmap->rows);
                    strokedGlyphTable->Add(code,
                                           advance, bitmapOffset / parameters.Scale, bitmapSize / parameters.Scale,
                                           glyphBitmap.Bitmap->buffer,
                                           glyphBitmap.Bitmap->width,
                                           glyphBitmap.Bitmap->rows,
                                           glyphBitmap.Bitmap->pitch);
                }
                FT_Done_Glyph(strokedGlyph);
            }

            FT_Load_Glyph(faceGlyphIndex.first, faceGlyphIndex.second, loadFlags);
            FT_Render_Glyph(faceGlyphIndex.first->glyph, FT_RENDER_MODE_NORMAL);

            if (parameters.Weights > 0.0f)
                FT_Bitmap_Embolden(static_cast<FT_Library>(library->GetFTLibrary()), &faceGlyphIndex.first->glyph->bitmap, FloatToF26D6(parameters.Weights), 0);

            GrayscaleBitmap glyphBitmap(static_cast<FT_Library>(library->GetFTLibrary()), faceGlyphIndex.first->glyph->bitmap);

            FT_GlyphSlot renderedGlyph = faceGlyphIndex.first->glyph;
            const Vector2 advance = Vector2(F26D6ToFloat(renderedGlyph->advance.x), F26D6ToFloat(renderedGlyph->advance.y));
            const Vector2 bitmapOffset = Vector2(static_cast<float>(renderedGlyph->bitmap_left), GetAscender() - static_cast<float>(renderedGlyph->bitmap_top));
            const Vector2 bitmapSize   = Vector2(glyphBitmap.Bitmap->width, glyphBitmap.Bitmap->rows);

            return regularGlyphTable->Add(code,
                                          advance / parameters.Scale, bitmapOffset / parameters.Scale, bitmapSize / parameters.Scale,
                                          glyphBitmap.Bitmap->buffer,
                                          glyphBitmap.Bitmap->width,
                                          glyphBitmap.Bitmap->rows,
                                          glyphBitmap.Bitmap->pitch);
        }
    }
}