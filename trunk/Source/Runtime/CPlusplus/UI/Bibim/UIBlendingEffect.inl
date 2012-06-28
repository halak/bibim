namespace Bibim
{
    BlendMode UIBlendingEffect::GetMode() const
    {
        return mode;
    }

    void UIBlendingEffect::SetMode(BlendMode value)
    {
        mode = value;
    }

    const char* UIBlendingEffect::GetModeAsChars() const
    {
        return ConvertFromBlendModeToString(GetMode());
    }

    void UIBlendingEffect::SetModeByChars(const char* value)
    {
        if (value)
            SetMode(ConvertFromStringToBlendMode(value));
    }
}