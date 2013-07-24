#pragma once
#ifndef __BIBIM_FONT_H__
#define __BIBIM_FONT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameAsset.h>
#   include <Bibim/Color.h>
#   include <Bibim/String.h>
#   include <map>
#   include <vector>

    namespace Bibim
    {
        class Font : public GameAsset
        {
            BBSerializableAssetClass(Font, GameAsset, 'F', 'O', 'N', 'T');
            public:
                typedef std::map<int, const Glyph*> GlyphDictionary;

                struct Metric
                {
                    static const Metric Empty;

                    Vector2 Size;
                    Vector2 EndPosition;
                    int LineCount;

                    inline Metric(Vector2 size, Vector2 endPosition, int lineCount)
                        : Size(size),
                          EndPosition(endPosition),
                          LineCount(lineCount)
                    {
                    }
                };

            public:
                Font();
                Font(FontLibrary* library);
                Font(const Font& original);
                virtual ~Font();

                Font* Clone() const;
                void Prepare(const String& text);

                Metric Measure(const String& text);
                Metric Measure(const String& text, float boundary);
                Metric Measure(const FontString& fontString);
                Metric Measure(const FontString& fontString, float boundary);

                inline FontLibrary* GetLibrary() const;
                void SetLibrary(FontLibrary* value);

                const String& GetFaceURI() const;
                void SetFaceURI(const String& value);
                void SetFace(const byte* data, int length);

                float GetSize() const;
                void  SetSize(float value);

                float GetStrokeSize() const;
                void  SetStrokeSize(float value);

                float GetWeights() const;
                void  SetWeights(float value);

                bool GetBold() const;
                void SetBold(bool value);

                float GetShear() const;
                void  SetShear(float value);

                bool GetItalic() const;
                void SetItalic(bool value);

                int GetShadowSize() const;
                void SetShadowSize(int value);

                float GetShadowSpread() const;
                void  SetShadowSpread(float value);

                float GetShadowThickness() const;
                void  SetShadowThickness(float value);

                Vector2 GetShadowOffset() const;
                void SetShadowOffset(Vector2 value);
                inline void SetShadowOffsetXY(float x, float y);

                float GetScale() const;
                void  SetScale(float value);

                bool GetHinting() const;
                void SetHinting(bool value);

                bool GetIgnoreBitmap() const;
                void SetIgnoreBitmap(bool value);

                inline Color GetColor() const;
                void SetColor(Color value);
                inline void SetColorRGB(byte r, byte g, byte b);

                inline Color GetStrokeColor() const;
                void SetStrokeColor(Color value);
                inline void SetStrokeColorRGB(byte r, byte g, byte b);

                inline Color GetShadowColor() const;
                void SetShadowColor(Color value);
                inline void SetShadowColorRGB(byte r, byte g, byte b);

                inline float GetSpacing() const;
                void SetSpacing(float value);

                const Glyph* GetRegularGlyph(int code) const;
                const Glyph* GetStrokedGlyph(int code) const;
                const Glyph* GetShadowGlyph(int code) const;

                float GetAscender() const;
                float GetDescender() const;
                float GetLineHeight() const;

                const GlyphDictionary& GetCachedRegularGlyphs() const;
                const GlyphDictionary& GetCachedStrokedGlyphs() const;
                const GlyphDictionary& GetCachedShadowGlyphs() const;

            private:
                FontCache* GetCache() const;

            private:
                FontLibrary* library;

                Vector2 shadowOffset;
                float spacing;
                Color color;
                Color strokeColor;
                Color shadowColor;
                FontCacheParameters* parametersPointer;
                FontCacheParameters& parameters;
                mutable FontCachePtr cache;

                static const GlyphDictionary EmptyGlyphs;

                friend class FontLibrary;
        };
    }

#endif