namespace Bibim
{
    Window* IMEBase::GetWindow() const
    {
        return window;
    }

    void IMEBase::SetWindow(Window* value)
    {
        window = value;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    int IMEBase::Request::GetID() const
    {
        return id;
    }

    const String& IMEBase::Request::GetText() const
    {
        return text;
    }

    const String& IMEBase::Request::GetTitle() const
    {
        return title;
    }

    const String& IMEBase::Request::GetDescription() const
    {
        return description;
    }

    IMEBase::TextFormat IMEBase::Request::GetFormat() const
    {
        return format;
    }

    int IMEBase::Request::GetMaxLength() const
    {
        return maxLength;
    }
}