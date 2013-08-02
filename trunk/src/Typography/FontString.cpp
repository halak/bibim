#include <Bibim/Config.h>
#include <Bibim/FontString.h>
#include <Bibim/Assert.h>
#include <Bibim/Font.h>
#include <Bibim/Glyph.h>
#include <Bibim/Math.h>
#include <utf8.h>

namespace Bibim
{
    const FontString FontString::Empty;

    FontString::FontString()
        : text(String::Empty),
          font(nullptr),
          size(Vector2::Zero)
    {
    }

    FontString::FontString(Font* font, const char* text)
        : text(text),
          font(font),
          size(Vector2::Zero)
    {
        FillGlyphs();
    }

    FontString::FontString(Font* font, const String& text)
        : text(text),
          font(font),
          size(Vector2::Zero)
    {
        FillGlyphs();
    }

    FontString::FontString(const FontString& original)
        : text(original.text),
          font(original.font),
          size(original.size),
          regularGlyphs(original.regularGlyphs),
          strokedGlyphs(original.strokedGlyphs),
          shadowGlyphs(original.shadowGlyphs)
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
        size = Vector2::Zero;
        regularGlyphs.clear();
        strokedGlyphs.clear();
        shadowGlyphs.clear();

        if (font->GetLibrary() == nullptr || text.GetLength() == 0)
            return;

        std::vector<wchar_t> wideCharacters;
        wideCharacters.reserve(text.GetLength());
        utf8::utf8to16(&text.CStr()[0], &text.CStr()[text.GetLength()], std::back_inserter(wideCharacters));
        
        int lineCount = 1;
        float lineWidth = 0.0f;
        class Measurer
        {
            public:
                Measurer()
                    : lastCode(L'\0'),
                      lineWidth(0.0f),
                      lineCount(1),
                      maxLineWidth(0.0f)
                {
                }

                void Step(float width)
                {
                    lineWidth += width;
                }

                void Step(wchar_t code, float width)
                {
                    Step(width);

                    if ((code == L'\r') || 
                        (code == L'\n' && lastCode != L'\r'))
                    {
                        maxLineWidth = Math::Max(maxLineWidth, lineWidth);
                        lineWidth = 0.0f;
                        lineCount++;
                    }
                
                    lastCode = code;
                }

                float GetMaxLineWidth() const
                {
                    return Math::Max(maxLineWidth, lineWidth);
                }

                int GetLineCount() const { return lineCount; }

            private:
                wchar_t lastCode;
                float lineWidth;
                int lineCount;
                float maxLineWidth;
        } measurer;

        const float spacing = font->GetSpacing();
        regularGlyphs.reserve(wideCharacters.size());
        if (font->GetStrokeSize() > 0.0f)
        {
            measurer.Step(font->GetStrokeSize() * 2.0f);
            strokedGlyphs.reserve(wideCharacters.size());
            if (font->GetShadowSize() > 0)
            {
                shadowGlyphs.reserve(wideCharacters.size());
                for (std::vector<wchar_t>::const_iterator it = wideCharacters.begin(); it != wideCharacters.end(); it++)
                {
                    regularGlyphs.push_back(font->GetRegularGlyph(*it));
                    strokedGlyphs.push_back(font->GetStrokedGlyph(*it));
                    shadowGlyphs.push_back(font->GetShadowGlyph(*it));
                    measurer.Step(*it, shadowGlyphs.back()->GetAdvance().X * spacing);
                }
            }
            else
            {
                for (std::vector<wchar_t>::const_iterator it = wideCharacters.begin(); it != wideCharacters.end(); it++)
                {
                    regularGlyphs.push_back(font->GetRegularGlyph(*it));
                    strokedGlyphs.push_back(font->GetStrokedGlyph(*it));
                    measurer.Step(*it, strokedGlyphs.back()->GetAdvance().X * spacing);
                }
            }
        }
        else
        {
            if (font->GetShadowSize() > 0)
            {
                shadowGlyphs.reserve(wideCharacters.size());
                for (std::vector<wchar_t>::const_iterator it = wideCharacters.begin(); it != wideCharacters.end(); it++)
                {
                    regularGlyphs.push_back(font->GetRegularGlyph(*it));
                    shadowGlyphs.push_back(font->GetShadowGlyph(*it));
                    measurer.Step(*it, shadowGlyphs.back()->GetAdvance().X * spacing);
                }
            }
            else
            {
                for (std::vector<wchar_t>::const_iterator it = wideCharacters.begin(); it != wideCharacters.end(); it++)
                {
                    regularGlyphs.push_back(font->GetRegularGlyph(*it));
                    measurer.Step(*it, regularGlyphs.back()->GetAdvance().X * spacing);
                }
            }
        }

        size.X = measurer.GetMaxLineWidth();
        size.Y = static_cast<float>(measurer.GetLineCount()) * font->GetLineHeight();
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
        size = original.size;
        regularGlyphs = original.regularGlyphs;
        strokedGlyphs = original.strokedGlyphs;
        shadowGlyphs = original.shadowGlyphs;
        return *this;
    }
}