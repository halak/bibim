﻿#pragma once
#ifndef __BIBIM_FONTSTRING_H__
#define __BIBIM_FONTSTRING_H__

#include <Bibim/FWD.h>
#include <Bibim/String.h>
#include <Bibim/Vector2.h>
#include <vector>

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
            /// Glyphs에 Index에 대응하는 Original Text로부터의 Index를 가져옵니다.
            /// 예) "가나다"의 '나'부분은 Glyphs Index는 1이지만 Original Text로부터의 Index는 2입니다.
            int ConvertToOriginalIndex(int index) const;

            inline const String& GetText() const;
            inline Font* GetFont() const;
            inline Vector2 GetSize() const;
            inline const GlyphCollection& GetRegularGlyphs() const;
            inline const GlyphCollection& GetStrokedGlyphs() const;
            inline const GlyphCollection& GetShadowGlyphs() const;

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
            Vector2 size;
            GlyphCollection regularGlyphs;
            GlyphCollection strokedGlyphs;
            GlyphCollection shadowGlyphs;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    const String& FontString::GetText() const
    {
        return text;
    }

    Font* FontString::GetFont() const
    {
        return font;
    }

    Vector2 FontString::GetSize() const
    {
        return size;
    }

    const FontString::GlyphCollection& FontString::GetRegularGlyphs() const
    {
        return regularGlyphs;
    }

    const FontString::GlyphCollection& FontString::GetStrokedGlyphs() const
    {
        return strokedGlyphs;
    }

    const FontString::GlyphCollection& FontString::GetShadowGlyphs() const
    {
        return shadowGlyphs;
    }
}

#endif