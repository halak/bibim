namespace Bibim
{
    const String& UIMarkupText::GetOriginalText() const
    {
        return originalText;
    }

    const String& UIMarkupText::GetDisplayText() const
    {
        return displayText;
    }

    const UIMarkupText::PhraseCollection& UIMarkupText::GetPhrases() const
    {
        return phrases;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    UIMarkupText::PhraseType UIMarkupText::Phrase::GetType() const
    {
        return type;
    }

    int UIMarkupText::Phrase::GetIndex() const
    {
        return index;
    }

    int UIMarkupText::Phrase::GetLength() const
    {
        return length;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    Color UIMarkupText::ColorPhrase::GetColor() const
    {
        return color;
    }

    bool UIMarkupText::ColorPhrase::HasColor() const
    {
        return hasColor;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    const String& UIMarkupText::ContentPhrase::GetContentType() const
    {
        return contentType;
    }

    const String& UIMarkupText::ContentPhrase::GetContentName() const
    {
        return contentName;
    }

    const SequenceDictionary& UIMarkupText::ContentPhrase::GetAttributes() const
    {
        return attributes;
    }
}