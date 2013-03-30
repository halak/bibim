namespace Bibim
{
    IME* UIEditText::GetIME() const
    {
        return ime;
    }

    IME::TextFormat UIEditText::GetFormat() const
    {
        return format;
    }

    const String& UIEditText::GetPlaceholder() const
    {
        return placeholder;
    }

    void UIEditText::SetPlaceholder(const String& value)
    {
        placeholder = value;
    }

    int UIEditText::GetMaxLength() const
    {
        return maxLength;
    }

    bool UIEditText::GetFrozen() const
    {
        return frozen;
    }

    void UIEditText::SetFrozen(bool value)
    {
        frozen = value;
    }

    const String& UIEditText::GetEditorTitle() const
    {
        return editorTitle;
    }

    void UIEditText::SetEditorTitle(const String& value)
    {
        editorTitle = value;
    }

    const String& UIEditText::GetEditorDescription() const
    {
        return editorDescription;
    }

    void UIEditText::SetEditorDescription(const String& value)
    {
        editorDescription = value;
    }
}