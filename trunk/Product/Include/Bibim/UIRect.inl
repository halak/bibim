namespace Bibim
{
    Color UIRect::GetFillColor() const
    {
        return fillColor;
    }

    void UIRect::SetFillColor(Color value)
    {
        fillColor = value;
    }

    float UIRect::GetFillColorR() const
    {
        return fillColor.GetR();
    }

    float UIRect::GetFillColorG() const
    {
        return fillColor.GetG();
    }

    float UIRect::GetFillColorB() const
    {
        return fillColor.GetB();
    }

    void UIRect::SetFillColorRGB(float r, float g, float b)
    {
        SetFillColor(Color(Vector3(r, g, b)));
    }
}