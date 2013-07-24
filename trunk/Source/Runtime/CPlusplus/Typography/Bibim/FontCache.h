﻿#pragma once
#ifndef __BIBIM_FONTCACHE_H__
#define __BIBIM_FONTCACHE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameAsset.h>
#   include <Bibim/String.h>
#   include <vector>

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
                virtual ~FontCache();

                const Glyph* GetGlyph(int code);

                inline FontLibrary* GetLibrary() const;
                inline const FontCacheParameters& GetParameters() const;
                inline float GetAscender() const;
                inline float GetDescender() const;
                inline float GetLineHeight() const;

                inline const GlyphTable* GetRegularGlyphTable() const;
                inline const GlyphTable* GetStrokedGlyphTable() const;
                inline const GlyphTable* GetShadowGlyphTable() const;

            private:
                FontCache(FontLibrary* library, const FontCacheParameters& parameters);

                void Clear();

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

                friend class FontLibrary;
        };
    }

#endif