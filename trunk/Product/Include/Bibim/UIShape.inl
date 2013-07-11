namespace Bibim
{
    Color UIShape::GetFillColor() const
    {
        return fillColor;
    }

    void UIShape::SetFillColor(Color value)
    {
        fillColor = value;
    }

    float UIShape::GetFillColorR() const
    {
        return fillColor.GetR();
    }

    float UIShape::GetFillColorG() const
    {
        return fillColor.GetG();
    }

    float UIShape::GetFillColorB() const
    {
        return fillColor.GetB();
    }

    void UIShape::SetFillColorRGB(float r, float g, float b)
    {
        SetFillColor(Color(Vector3(r, g, b)));
    }

    Color UIShape::GetLineColor() const
    {
        return lineColor;
    }

    void UIShape::SetLineColor(Color value)
    {
        lineColor = value;
    }

    float UIShape::GetLineColorR() const
    {
        return lineColor.GetR();
    }

    float UIShape::GetLineColorG() const
    {
        return lineColor.GetG();
    }

    float UIShape::GetLineColorB() const
    {
        return lineColor.GetB();
    }

    void UIShape::SetLineColorRGB(float r, float g, float b)
    {
        SetLineColor(Color(Vector3(r, g, b)));
    }
}