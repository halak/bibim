#include <Bibim/PCH.h>
#include <Bibim/UITintEffect.h>
#include <Bibim/ComponentStreamReader.h>

namespace Bibim
{
    BBImplementsComponent(UITintEffect);

    UITintEffect::UITintEffect()
        : value(1.0f, 1.0f, 1.0f, 0.0f)
    {
    }

    UITintEffect::UITintEffect(Vector4 value)
        : value(value)
    {
    }

    UITintEffect::~UITintEffect()
    {
    }

    void UITintEffect::DrawLines(UIRenderer* renderer, int count, Vector2* p, Color color)
    {
        color *= value;
        Base::DrawLines(renderer, count, p, color);
    }

    void UITintEffect::DrawLines(UIRenderer* renderer, int count, Vector2* p, Color* c)
    {
        for (int i = 0; i < count; i++)
            c[i] *= value;
        Base::DrawLines(renderer, count, p, c);
    }

    void UITintEffect::DrawTriangles(UIRenderer* renderer, int count, Vector2* p, Color color)
    {
        color *= value;
        Base::DrawTriangles(renderer, count, p, color);
    }

    void UITintEffect::DrawQuad(UIRenderer* renderer, Vector2* p, Color color)
    {
        color *= value;
        Base::DrawQuad(renderer, p, color);
    }

    void UITintEffect::DrawQuad(UIRenderer* renderer, Vector2* p, Color color, Vector2* uv,  Texture2D* texture)
    {
        color *= value;
        Base::DrawQuad(renderer, p, color, uv, texture);
    }

    void UITintEffect::DrawQuad(UIRenderer* renderer, Vector2* p, Color color, Vector2* uv1, Texture2D* texture1, Vector2* uv2, Texture2D* texture2)
    {
        color *= value;
        Base::DrawQuad(renderer, p, color, uv1, texture1, uv2, texture2);
    }

    void UITintEffect::DrawQuad(UIRenderer* renderer, Vector2* p, Color color, RectF clippingRect, Texture2D* texture)
    {
        color *= value;
        Base::DrawQuad(renderer, p, color, clippingRect, texture);
    }

    void UITintEffect::DrawQuad(UIRenderer* renderer, Vector2* p, Color color, RectF clippingRect, Texture2D* texture1, Vector2* uv2, Texture2D* texture2)
    {
        color *= value;
        Base::DrawQuad(renderer, p, color, clippingRect, texture1, uv2, texture2);
    }

    void UITintEffect::DrawQuad(UIRenderer* renderer, Vector2* p, Color* c)
    {
        c[0] *= value;
        c[1] *= value;
        c[2] *= value;
        c[3] *= value;
        Base::DrawQuad(renderer, p, c);
    }

    void UITintEffect::DrawQuad(UIRenderer* renderer, Vector2* p, Color* c, Vector2* uv,  Texture2D* texture)
    {
        c[0] *= value;
        c[1] *= value;
        c[2] *= value;
        c[3] *= value;
        Base::DrawQuad(renderer, p, c, uv, texture);
    }

    void UITintEffect::DrawQuad(UIRenderer* renderer, Vector2* p, Color* c, Vector2* uv1, Texture2D* texture1, Vector2* uv2, Texture2D* texture2)
    {
        c[0] *= value;
        c[1] *= value;
        c[2] *= value;
        c[3] *= value;
        Base::DrawQuad(renderer, p, c, uv1, texture1, uv2, texture2);
    }

    void UITintEffect::DrawQuad(UIRenderer* renderer, Vector3* p, Color color)
    {
        color *= value;
        Base::DrawQuad(renderer, p, color);
    }

    void UITintEffect::DrawQuad(UIRenderer* renderer, Vector3* p, Color color, Vector2* uv,  Texture2D* texture)
    {
        color *= value;
        Base::DrawQuad(renderer, p, color, uv, texture);
    }

    void UITintEffect::DrawQuad(UIRenderer* renderer, Vector3* p, Color color, Vector2* uv1, Texture2D* texture1, Vector2* uv2, Texture2D* texture2)
    {
        color *= value;
        Base::DrawQuad(renderer, p, color, uv1, texture1, uv2, texture2);
    }

    void UITintEffect::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        value = reader.ReadVector4();
    }

    void UITintEffect::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        value = o->value;
    }
}