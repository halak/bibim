namespace Bibim
{
    const String& UIDocument::GetText() const
    {
        return text;
    }

    UIDocument::StyleSheet* UIDocument::GetStyleSheet() const
    {
        return stylesheet;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    UIDocument::StyleSheet::Content::~Content()
    {
    }

    Vector2 UIDocument::StyleSheet::Content::GetOrigin() const
    {
        return origin;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    UIDocument::StyleSheet::Decoration::~Decoration()
    {
    }

    Font* UIDocument::StyleSheet::Decoration::GetFont() const
    {
        return font;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    void UIDocument::StyleSheet::AddContent(const String& name, Image* image)
    {
        AddContent(name, image, Vector2(0.5f, 0.5f));
    }

    void UIDocument::StyleSheet::AddContentXY(const String& name, Image* image, float originX, float originY)
    {
        AddContent(name, image, Vector2(originX, originY));
    }

    const UIDocument::StyleSheet::Content* UIDocument::StyleSheet::GetContent(const String& name) const
    {
        std::map<String, Content>::const_iterator it = contents.find(name);
        if (it != contents.end())
            return &(*it).second;
        else
            return nullptr;
    }

    const UIDocument::StyleSheet::Decoration* UIDocument::StyleSheet::GetDecoration(const String& name) const
    {
        std::map<String, Decoration>::const_iterator it = decorations.find(name);
        if (it != decorations.end())
            return &(*it).second;
        else
            return nullptr;
    }
}