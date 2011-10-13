namespace Bibim
{
    void UIDrawingContext::Draw(Image* image)
    {
        Draw(GetCurrentBounds(), GetCurrentClippedBounds(), image, false, false);
    }

    void UIDrawingContext::Draw(Image* image, bool horizontalFlip, bool verticalFlip)
    {
        Draw(GetCurrentBounds(), GetCurrentClippedBounds(), image, horizontalFlip, verticalFlip);
    }

    void UIDrawingContext::DrawString(Font* font, const String& text)
    {
        DrawString(GetCurrentBounds(), GetCurrentClippedBounds(), font, text);
    }

    void UIDrawingContext::DrawString(const FontString& fontString)
    {
        DrawString(GetCurrentBounds(), GetCurrentClippedBounds(), fontString);
    }

    void UIDrawingContext::DrawString(Vector2 position, Font* font, const String& text)
    {
        DrawString(RectF(position.X, position.Y, 10000.0f, 10000.0f), RectF(-10000.0f, -10000.0f, 20000.0f, 20000.0f), font, text);
    }

    void UIDrawingContext::DrawChild(UIVisual* target)
    {
        Visit(target);
    }
}