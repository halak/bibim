#pragma once
#ifndef __BIBIM_FONTSTRING_H__
#define __BIBIM_FONTSTRING_H__

#   include <Bibim/FWD.h>
#   include <Bibim/String.h>
#   include <vector>

    namespace Bibim
    {
        class FontString
        {
            public:
                typedef std::vector<const Glyph*> GlyphCollection;

            public:
                FontString();
                FontString(Font* font, const char* text);
                FontString(Font* font, const String& text);
                FontString(const FontString& original);
                ~FontString();

                /// Summary:
                /// Glyphs�� Index�� �����ϴ� Original Text�κ����� Index�� �����ɴϴ�.
                /// ��) "������"�� '��'�κ��� Glyphs Index�� 1������ Original Text�κ����� Index�� 2�Դϴ�.
                int ConvertToOriginalIndex(int index) const;

                inline const String& GetText() const;
                inline Font* GetFont() const;
                inline const GlyphCollection& GetRegularGlyphs() const;
                inline const GlyphCollection& GetStrokedGlyphs() const;
                inline const GlyphCollection& GetGlowGlyphs() const;

                FontString& operator = (const char* text);
                FontString& operator = (const String& text);
                FontString& operator = (const FontString& original);

            public:
                static const FontString Empty;

            private:
                void FillGlyphs();

            private:
                String  text;
                FontPtr font;
                GlyphCollection regularGlyphs;
                GlyphCollection strokedGlyphs;
                GlyphCollection glowGlyphs;
        };
    }

#    include <Bibim/FontString.inl>

#endif