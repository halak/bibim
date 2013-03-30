namespace Bibim
{
    int TypingContext::GetCode() const
    {
        return currentGlyph ? currentGlyph->GetCode() : '\0';
    }

    Vector2 TypingContext::GetPosition() const
    {
        return currentPosition;
    }
    const Glyph* TypingContext::GetRegularGlyph() const
    {
        return currentGlyph;
    }

    const Glyph* TypingContext::GetStrokedGlyph() const
    {
        return currentStrokedGlyph;
    }

    int TypingContext::GetIndex() const
    {
        return currentIndexFromOriginalText;
    }

    int TypingContext::GetGlyphIndex() const
    {
        return currentIndex - 1;
    }

    int TypingContext::GetLineNumber() const
    {
        return lineNumber;
    }
}