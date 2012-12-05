namespace Bibim
{
    UIVisual* UIPanel::GetChildAt(int index) const
    {
        if (0 <= index && index < static_cast<int>(children.size()))
            return children[index];
        else
            return nullptr;
    }

    int UIPanel::GetNumberOfChildren() const
    {
        return static_cast<int>(children.size());
    }

    const UIPanel::VisualCollection& UIPanel::GetChildren() const
    {
        return children;
    }
}