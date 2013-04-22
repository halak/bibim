#include <Bibim/Config.h>
#include <Bibim/TypingContext.h>
#include <Bibim/Assert.h>
#include <Bibim/Font.h>
#include <Bibim/FontString.h>
#include <Bibim/Glyph.h>
#include <Bibim/GlyphTable.h>
#include <Bibim/String.h>
#include <utf8.h>

namespace Bibim
{
    TypingContext::TypingContext(Font* font, const String& text, float boundary)
        : fontString(new FontString(font, text)),
          fontStringLocalAllocated(true),
          boundary(boundary)
    {
        Reset();
    }

    TypingContext::TypingContext(const FontString& string, float boundary)
        : fontString(&string),
          fontStringLocalAllocated(false),
          boundary(boundary)
    {
        Reset();
    }

    TypingContext::~TypingContext()
    {
        if (fontStringLocalAllocated)
            delete fontString;
    }

    void TypingContext::Reset()
    {
        const Font* font = fontString->GetFont();
        currentPosition.X = font->GetStrokeSize();
        currentPosition.Y = 0.0f;
        currentGlyph = nullptr;
        currentStrokedGlyph = nullptr;
        currentIndex = 0;
        currentIndexFromOriginalText = 0;
        lineNumber = 0;
    }

    int TypingContext::GetLength(int code)
    {
        const wchar_t wideCharacter = static_cast<wchar_t>(code);
        return utf8::utf8_length(wideCharacter);
    }

    bool TypingContext::MoveNext()
    {
        const Font* font = fontString->GetFont();
        const float spacing = font->GetSpacing();
        const float lineHeight = font->GetLineHeight();

        if (currentGlyph)
        {
            currentPosition += currentGlyph->GetAdvance() * spacing;
            currentIndexFromOriginalText += GetLength(GetCode());
        }

        if (currentIndex >= static_cast<int>(fontString->GetRegularGlyphs().size()))
            return false;

        if (GetCode() == L'\n')
        {
            currentPosition.X = 0.0f;
            currentPosition.Y += lineHeight;
            lineNumber++;
        }

        currentGlyph = fontString->GetRegularGlyphs()[currentIndex];

        if (fontString->GetFont()->GetStrokeSize() > 0)
            currentStrokedGlyph = fontString->GetStrokedGlyphs()[currentIndex];
        else
            currentStrokedGlyph = nullptr;

        currentIndex++;

        const float advanceX = currentGlyph->GetAdvance().X;
        if (currentPosition.X + (advanceX * spacing) + font->GetStrokeSize() > boundary)
        {
            currentPosition.X = 0.0f;
            currentPosition.Y += lineHeight;
            lineNumber++;
        }

        return true;
    }
}