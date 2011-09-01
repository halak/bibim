#pragma once
#ifndef __BIBIM_FONT_H__
#define __BIBIM_FONT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Asset.h>
#   include <Bibim/Color.h>
#   include <map>
#   include <vector>

    namespace Bibim
    {
        class Font : public Asset
        {
            public:
                typedef std::map<uint32, const Glyph*> GlyphDictionary;

            public:
                Font();
                Font(FontLibrary* library);
                Font(const Font& original);
                virtual ~Font();

                Vector2 Measure(const String& text);
                Vector2 Measure(const String& text, float boundary);
                Vector2 Measure(const FontString& fontString);
                Vector2 Measure(const FontString& fontString, float boundary);
                
                inline FontLibrary* GetLibrary() const;
                void SetLibrary(FontLibrary* value);

                const String& GetFace() const;
                void SetFace(const String& value);

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

                int GetGlowSize() const;
                void SetGlowSize(int value);

                float GetGlowSpread() const;
                void  SetGlowSpread(float value);

                float GetGlowThickness() const;
                void  SetGlowThickness(float value);

                float GetScale() const;
                void  SetScale(float value);

                bool GetHinting() const;
                void SetHinting(bool value);

                bool GetIgnoreBitmap() const;
                void SetIgnoreBitmap(bool value);

                inline Color GetColor() const;
                void SetColor(Color value);

                inline Color GetStrokeColor() const;
                void SetStrokeColor(Color value);

                inline Color GetGlowColor() const;
                void SetGlowColor(Color value);

                inline float GetSpacing() const;
                void SetSpacing(float value);

                const Glyph* GetRegularGlyph(uint32 code) const;
                const Glyph* GetStrokedGlyph(uint32 code) const;
                const Glyph* GetGlowGlyph(uint32 code) const;

                float GetAscender() const;
                float GetDescender() const;
                float GetLineHeight() const;

                inline uint GetRevision() const;

                const GlyphDictionary& GetCachedRegularGlyphs() const;
                const GlyphDictionary& GetCachedStrokedGlyphs() const;
                const GlyphDictionary& GetCachedGlowGlyphs() const;

            private:
                FontCache* GetCache() const;

            private:
                FontLibrary* library;
                unsigned int revision;

                float spacing;
                Color color;
                Color strokeColor;
                Color glowColor;
                FontCacheParameters* parametersPointer;
                FontCacheParameters& parameters;
                mutable FontCachePtr cache;

                static const GlyphDictionary EmptyGlyphs;

            private:
                Font& operator = (const Font&);
        };
    }

#   include <Bibim/Font.inl>

#endif