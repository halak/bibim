#include <Bibim/PCH.h>
#include <Bibim/UIAfterImageEffect.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/Math.h>
#include <Bibim/UIDrawingContext.h>

namespace Bibim
{
    BBImplementsComponent(UIAfterImageEffect);

    UIAfterImageEffect::UIAfterImageEffect()
        : skippedFrames(1),
          totalFrames(10),
          currentAfterImages(nullptr)
    {
    }

    UIAfterImageEffect::~UIAfterImageEffect()
    {
        currentAfterImages = nullptr;

        AIDictionary temporaryAfterImages;
        temporaryAfterImages.swap(afterImages);

        for (AIDictionary::const_iterator it = temporaryAfterImages.begin(); it != temporaryAfterImages.end(); it++)
        {
            const AICollection& items = *(*it).second;
            for (AICollection::const_iterator itItem = items.begin(); itItem != items.end(); itItem++)
            {
            }

            delete (*it).second;
        }
    }

    void UIAfterImageEffect::SetSkippedFrames(int value)
    {
        skippedFrames = Math::Max(value, 0);
    }

    void UIAfterImageEffect::SetTotalFrames(int value)
    {
        totalFrames = Math::Max(value, 1);
    }

    void UIAfterImageEffect::BeginDraw(UIDrawingContext& context, UIVisual* visual)
    {
        AIDictionary::iterator it = afterImages.find(visual);
        if (it != afterImages.end())
            currentAfterImages = (*it).second;
        else
        {
            currentAfterImages = new AICollection();
            afterImages.insert(AIDictionary::value_type(visual, currentAfterImages));
        }

        currentTransform = context.GetCurrentTransform();
    }

    void UIAfterImageEffect::EndDraw(UIDrawingContext& /*context*/, UIVisual* /*visual*/)
    {
        currentAfterImages = nullptr;
    }

    void UIAfterImageEffect::DrawLines(UIRenderer* renderer, int count, Vector2* p, Color color)
    {
        Base::DrawLines(renderer, count, p, color);
    }

    void UIAfterImageEffect::DrawLines(UIRenderer* renderer, int count, Vector2* p, Color* c)
    {
        Base::DrawLines(renderer, count, p, c);
    }

    void UIAfterImageEffect::DrawTriangles(UIRenderer* renderer, int count, Vector2* p, Color color)
    {
        Base::DrawTriangles(renderer, count, p, color);
    }

    void UIAfterImageEffect::DrawQuad(UIRenderer* renderer, Vector2* p, Color color)
    {
        Base::DrawQuad(renderer, p, color);
    }

    void UIAfterImageEffect::DrawQuad(UIRenderer* renderer, Vector2* p, Color color, Vector2* uv,  Texture2D* texture)
    {
        Base::DrawQuad(renderer, p, color, uv, texture);
    }

    void UIAfterImageEffect::DrawQuad(UIRenderer* renderer, Vector2* p, Color color, Vector2* uv1, Texture2D* texture1, Vector2* uv2, Texture2D* texture2)
    {
        Base::DrawQuad(renderer, p, color, uv1, texture1, uv2, texture2);
    }

    void UIAfterImageEffect::DrawQuad(UIRenderer* renderer, Vector2* p, Color color, RectF clippingRect, Texture2D* texture)
    {
        Base::DrawQuad(renderer, p, color, clippingRect, texture);
    }

    void UIAfterImageEffect::DrawQuad(UIRenderer* renderer, Vector2* p, Color color, RectF clippingRect, Texture2D* texture1, Vector2* uv2, Texture2D* texture2)
    {
        Base::DrawQuad(renderer, p, color, clippingRect, texture1, uv2, texture2);
    }

    void UIAfterImageEffect::DrawQuad(UIRenderer* renderer, Vector2* p, Color* c)
    {
        Base::DrawQuad(renderer, p, c);
    }

    void UIAfterImageEffect::DrawQuad(UIRenderer* renderer, Vector2* p, Color* c, Vector2* uv,  Texture2D* texture)
    {
        Base::DrawQuad(renderer, p, c, uv, texture);
    }

    void UIAfterImageEffect::DrawQuad(UIRenderer* renderer, Vector2* p, Color* c, Vector2* uv1, Texture2D* texture1, Vector2* uv2, Texture2D* texture2)
    {
        Base::DrawQuad(renderer, p, c, uv1, texture1, uv2, texture2);
    }

    void UIAfterImageEffect::DrawQuad(UIRenderer* renderer, Vector3* p, Color color)
    {
        Base::DrawQuad(renderer, p, color);
    }

    void UIAfterImageEffect::DrawQuad(UIRenderer* renderer, Vector3* p, Color color, Vector2* uv,  Texture2D* texture)
    {
        Base::DrawQuad(renderer, p, color, uv, texture);
    }

    void UIAfterImageEffect::DrawQuad(UIRenderer* renderer, Vector3* p, Color color, Vector2* uv1, Texture2D* texture1, Vector2* uv2, Texture2D* texture2)
    {
        Base::DrawQuad(renderer, p, color, uv1, texture1, uv2, texture2);
    }

    void UIAfterImageEffect::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        skippedFrames = static_cast<int>(reader.ReadShortInt());
        totalFrames = static_cast<int>(reader.ReadShortInt());
    }

    void UIAfterImageEffect::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        skippedFrames = o->skippedFrames;
        totalFrames = o->totalFrames;
    }
}