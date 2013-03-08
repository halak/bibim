#include <Bibim/PCH.h>
#include <Bibim/FontString.h>
#include <Bibim/Assert.h>
#include <Bibim/Font.h>
#include <Bibim/Glyph.h>
#include <utf8.h>

namespace Bibim
{
    const FontString FontString::Empty;

    FontString::FontString()
        : text(String::Empty),
          font(nullptr),
          totalWidth(0.0f)
    {
    }

    FontString::FontString(Font* font, const char* text)
        : text(text),
          font(font),
          totalWidth(0.0f)
    {
        FillGlyphs();
    }

    FontString::FontString(Font* font, const String& text)
        : text(text),
          font(font),
          totalWidth(0.0f)
    {
        FillGlyphs();
    }

    FontString::FontString(const FontString& original)
        : text(original.text),
          font(original.font),
          totalWidth(original.totalWidth),
          regularGlyphs(original.regularGlyphs),
          strokedGlyphs(original.strokedGlyphs),
          glowGlyphs(original.glowGlyphs)
    {
    }

    FontString::~FontString()
    {
    }

    int FontString::ConvertToOriginalIndex(int index) const
    {
        int result = 0;
        for (int i = 0; i < index; i++)
        {
            const int code = regularGlyphs[i]->GetCode();
            const wchar_t wideCharacter = static_cast<wchar_t>(code);
            result += utf8::utf8_length(wideCharacter);
        }

        return result;
    }

    void FontString::FillGlyphs()
    {
        totalWidth = 0.0f;
        regularGlyphs.clear();
        strokedGlyphs.clear();
        glowGlyphs.clear();

        if (font->GetLibrary() == nullptr || text.GetLength() == 0)
            return;

        std::vector<wchar_t> wideCharacters;
        wideCharacters.reserve(text.GetLength());
        utf8::utf8to16(&text.CStr()[0], &text.CStr()[text.GetLength()], std::back_inserter(wideCharacters));

        const float spacing = font->GetSpacing();
        regularGlyphs.reserve(wideCharacters.size());
        if (font->GetStrokeSize() > 0.0f)
        {
            strokedGlyphs.reserve(wideCharacters.size());
            if (font->GetGlowSize() > 0)
            {
                glowGlyphs.reserve(wideCharacters.size());
                for (std::vector<wchar_t>::const_iterator it = wideCharacters.begin(); it != wideCharacters.end(); it++)
                {
                    regularGlyphs.push_back(font->GetRegularGlyph(*it));
                    strokedGlyphs.push_back(font->GetStrokedGlyph(*it));
                    glowGlyphs.push_back(font->GetGlowGlyph(*it));
                    totalWidth += glowGlyphs.back()->GetAdvance().X * spacing;
                }
            }
            else
            {
                for (std::vector<wchar_t>::const_iterator it = wideCharacters.begin(); it != wideCharacters.end(); it++)
                {
                    regularGlyphs.push_back(font->GetRegularGlyph(*it));
                    strokedGlyphs.push_back(font->GetStrokedGlyph(*it));
                    totalWidth += strokedGlyphs.back()->GetAdvance().X * spacing;
                }
            }
        }
        else
        {
            if (font->GetGlowSize() > 0)
            {
                glowGlyphs.reserve(wideCharacters.size());
                for (std::vector<wchar_t>::const_iterator it = wideCharacters.begin(); it != wideCharacters.end(); it++)
                {
                    regularGlyphs.push_back(font->GetRegularGlyph(*it));
                    glowGlyphs.push_back(font->GetGlowGlyph(*it));
                    totalWidth += glowGlyphs.back()->GetAdvance().X * spacing;
                }
            }
            else
            {
                for (std::vector<wchar_t>::const_iterator it = wideCharacters.begin(); it != wideCharacters.end(); it++)
                {
                    regularGlyphs.push_back(font->GetRegularGlyph(*it));
                    totalWidth += regularGlyphs.back()->GetAdvance().X * spacing;
                }
            }
        }
    }

    FontString& FontString::operator = (const char* text)
    {
        this->text = text;
        FillGlyphs();
        return *this;
    }

    FontString& FontString::operator = (const String& text)
    {
        this->text = text;
        FillGlyphs();
        return *this;
    }

    FontString& FontString::operator = (const FontString& original)
    {
        text = original.text;
        font = original.font;
        totalWidth = original.totalWidth;
        regularGlyphs = original.regularGlyphs;
        strokedGlyphs = original.strokedGlyphs;
        glowGlyphs = original.glowGlyphs;
        return *this;
    }
}