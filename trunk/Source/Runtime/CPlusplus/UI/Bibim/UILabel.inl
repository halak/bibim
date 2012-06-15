namespace Bibim
{
    const String& UILabel::GetText() const
    {
        return text;
    }

    void UILabel::SetTextByChars(const char* value)
    {
        if (value)
            SetText(value);
    }

    Font* UILabel::GetFont() const
    {
        return font;
    }

    bool UILabel::GetAutoResize() const
    {
        return autoResize;
    }
}