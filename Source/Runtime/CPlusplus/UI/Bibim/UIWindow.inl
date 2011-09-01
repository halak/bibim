namespace Bibim
{
    void UIWindow::AddChild(UIVisual* item)
    {
        Add(item);
    }

    void UIWindow::InsertChild(int index, UIVisual* item)
    {
        Insert(index, item);
    }

    bool UIWindow::RemoveChild(UIVisual* item)
    {
        return Remove(item);
    }

    bool UIWindow::RemoveChildAt(int index)
    {
        return RemoveAt(index);
    }

    void UIWindow::RemoveAllChildren()
    {
        RemoveAll();
    }

    Vector2 UIWindow::GetFixedSize() const
    {
        return fixedSize;
    }

    void UIWindow::SetFixedSize(Vector2 value)
    {
        fixedSize = value;
    }

    bool UIWindow::GetFixedSizeUsed() const
    {
        return fixedSizeUsed;
    }

    void UIWindow::SetFixedSizeUsed(bool value)
    {
        fixedSizeUsed = value;
    }
}