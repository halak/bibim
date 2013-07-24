namespace Bibim
{
    void UIGeometryEffect::BeginDraw(UIDrawingContext& /*context*/, UIVisual* /*visual*/)
    {
    }

    void UIGeometryEffect::EndDraw(UIDrawingContext& /*context*/, UIVisual* /*visual*/)
    {
    }

    void UIGeometryEffect::DrawLines(UIRenderer* renderer, int count, Vector2* p, Color color)
    {
        renderer->DrawLines(count, p, color);
    }

    void UIGeometryEffect::DrawLines(UIRenderer* renderer, int count, Vector2* p, Color* c)
    {
        renderer->DrawLines(count, p, c);
    }

    void UIGeometryEffect::DrawDebugLines(UIRenderer* renderer, int count, Vector2* p, Color color)
    {
        renderer->DrawLines(count, p, color);
    }

    void UIGeometryEffect::DrawDebugLines(UIRenderer* renderer, int count, Vector2* p, Color* c)
    {
        renderer->DrawLines(count, p, c);
    }

    void UIGeometryEffect::DrawTriangles(UIRenderer* renderer, int count, Vector2* p, Color color)
    {
        renderer->DrawTriangles(count, p, color);
    }

    void UIGeometryEffect::DrawQuad(UIRenderer* renderer, Vector2* p, Color color)
    {
        renderer->DrawQuad(p, color);
    }

    void UIGeometryEffect::DrawQuad(UIRenderer* renderer, Vector2* p, Color color, Vector2* uv,  Texture2D* texture)
    {
        renderer->DrawQuad(p, color, uv, texture);
    }

    void UIGeometryEffect::DrawQuad(UIRenderer* renderer, Vector2* p, Color color, Vector2* uv1, Texture2D* texture1, Vector2* uv2, Texture2D* texture2)
    {
        renderer->DrawQuad(p, color, uv1, texture1, uv2, texture2);
    }

    void UIGeometryEffect::DrawQuad(UIRenderer* renderer, Vector2* p, Color color, RectF clippingRect, Texture2D* texture)
    {
        renderer->DrawQuad(p, color, clippingRect, texture);
    }

    void UIGeometryEffect::DrawQuad(UIRenderer* renderer, Vector2* p, Color color, RectF clippingRect, Texture2D* texture1, Vector2* uv2, Texture2D* texture2)
    {
        renderer->DrawQuad(p, color, clippingRect, texture1, uv2, texture2);
    }

    void UIGeometryEffect::DrawQuad(UIRenderer* renderer, Vector2* p, Color* c)
    {
        renderer->DrawQuad(p, c);
    }

    void UIGeometryEffect::DrawQuad(UIRenderer* renderer, Vector2* p, Color* c, Vector2* uv,  Texture2D* texture)
    {
        renderer->DrawQuad(p, c, uv, texture);
    }

    void UIGeometryEffect::DrawQuad(UIRenderer* renderer, Vector2* p, Color* c, Vector2* uv1, Texture2D* texture1, Vector2* uv2, Texture2D* texture2)
    {
        renderer->DrawQuad(p, c, uv1, texture1, uv2, texture2);
    }

    void UIGeometryEffect::DrawQuad(UIRenderer* renderer, Vector3* p, Color color)
    {
        renderer->DrawQuad(p, color);
    }

    void UIGeometryEffect::DrawQuad(UIRenderer* renderer, Vector3* p, Color color, Vector2* uv,  Texture2D* texture)
    {
        renderer->DrawQuad(p, color, uv, texture);
    }

    void UIGeometryEffect::DrawQuad(UIRenderer* renderer, Vector3* p, Color color, Vector2* uv1, Texture2D* texture1, Vector2* uv2, Texture2D* texture2)
    {
        renderer->DrawQuad(p, color, uv1, texture1, uv2, texture2);
    }
}