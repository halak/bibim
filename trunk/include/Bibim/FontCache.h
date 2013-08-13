#pragma once
#ifndef __BIBIM_FONTCACHE_H__
#define __BIBIM_FONTCACHE_H__

#include <Bibim/FWD.h>
#include <Bibim/GameAsset.h>
#include <Bibim/GlyphSurface.h>
#include <Bibim/String.h>
#include <vector>

// Freetype2 Forward Declaration
struct FT_FaceRec_;
struct FT_StrokerRec_;
typedef struct FT_FaceRec_*  FT_Face;
typedef struct FT_StrokerRec_*  FT_Stroker;

namespace Bibim
{
    struct FontCacheParameters
    {
        String FaceURI;
        float FontSize;
        float StrokeSize;
        float Weights;
        float Shear;
        int ShadowSize;
        float ShadowSpread;
        float ShadowThickness;
        float Scale;
        bool Hinting;
        bool IgnoreBitmap;
        std::vector<byte> FaceData;

        FontCacheParameters();
        FontCacheParameters(const String& faceURI, float fontSize, float strokeSize, float weights, float shear, 
                            int shadowSize, float shadowSpread, float shadowThickness,
                            float scale, bool hinting, bool ignoreBitmap);
        FontCacheParameters(const FontCacheParameters& original);

        unsigned int GetHashCode() const;

        FontCacheParameters& operator = (const FontCacheParameters& right);
        bool operator == (const FontCacheParameters& right) const;
        inline bool operator != (const FontCacheParameters& right) const;
    };

    class FontCache : public GameAsset
    {
        BBAssetClass(FontCache, GameAsset, 'F', 'N', 'T', 'C');
        public:
            typedef std::vector<GlyphSurface*> SurfaceCollection;

        public:
            virtual ~FontCache();

            const Glyph* GetGlyph(int code);

            inline FontLibrary* GetLibrary() const;
            inline const FontCacheParameters& GetParameters() const;
            inline float GetAscender() const;
            inline float GetDescender() const;
            inline float GetLineHeight() const;
            inline const SurfaceCollection& GetSurfaces() const;

            inline const GlyphTable* GetRegularGlyphTable() const;
            inline const GlyphTable* GetStrokedGlyphTable() const;
            inline const GlyphTable* GetShadowGlyphTable() const;

        private:
            FontCache(FontLibrary* library, const FontCacheParameters& parameters);

            void Clear();

            const Glyph* Add(GlyphTable* glyphTable, int code, Vector2 advance, Vector2 bitmapOffset, Vector2 bitmapSize, const void* buffer, int width, int height, int pitch);
            
            std::pair<GlyphSurface*, GlyphSurface::Slot> AllocateSurface(const void* buffer, int width, int height, int pitch);

            static Point2 GetAdaptiveSurfaceSize(int numberOfExisting, int width, int height);

        private:
            FontLibrary* library;
            FontCacheParameters parameters;

            FT_Face primaryFace;
            FT_Face alternativeFace;
            FT_Stroker stroker;
            int transform[2][2];

            float ascender;
            float descender;
            float lineHeight;

            GlyphTable* regularGlyphTable;
            GlyphTable* strokedGlyphTable;
            GlyphTable* shadowGlyphTable;
            SurfaceCollection surfaces;

            friend class FontLibrary;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    bool FontCacheParameters::operator != (const FontCacheParameters& right) const
    {
        return !operator == (right);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    FontLibrary* FontCache::GetLibrary() const
    {
        return library;
    }

    const FontCacheParameters& FontCache::GetParameters() const
    {
        return parameters;
    }

    float FontCache::GetAscender() const
    {
        return ascender;
    }

    float FontCache::GetDescender() const
    {
        return descender;
    }

    float FontCache::GetLineHeight() const
    {
        return lineHeight;
    }

    const FontCache::SurfaceCollection& FontCache::GetSurfaces() const
    {
        return surfaces;
    }

    const GlyphTable* FontCache::GetRegularGlyphTable() const
    {
        return regularGlyphTable;
    }

    const GlyphTable* FontCache::GetStrokedGlyphTable() const
    {
        return strokedGlyphTable;
    }

    const GlyphTable* FontCache::GetShadowGlyphTable() const
    {
        return shadowGlyphTable;
    }
}

#endif