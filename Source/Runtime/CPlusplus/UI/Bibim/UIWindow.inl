namespace Bibim
{
    void UIWindow::AddChild(UIVisual* item)
    {
        Add(item);
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
}