namespace Bibim
{
    const String& UILabel::GetText() const
    {
        return text;
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