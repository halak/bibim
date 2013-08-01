#include <Bibim/Config.h>
#include <Bibim/UIAfterImageEffect.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/Math.h>
#include <Bibim/Texture2D.h>
#include <Bibim/UIDrawingContext.h>

namespace Bibim
{
    BBImplementsComponent(UIAfterImageEffect);

    UIAfterImageEffect::UIAfterImageEffect()
        : skippedFrames(2),
          totalFrames(20),
          active(true),
          currentAfterImage(nullptr)
    {
    }

    UIAfterImageEffect::~UIAfterImageEffect()
    {
        currentAfterImage = nullptr;

        AfterImageDictionary temporaryAfterImages;
        temporaryAfterImages.swap(afterImages);

        for (AfterImageDictionary::const_iterator it = temporaryAfterImages.begin(); it != temporaryAfterImages.end(); it++)
            delete (*it).second;
    }

    byte UIAfterImageEffect::GetOpacityDecrement() const
    {
        return Math::Max(static_cast<byte>(255.0f / static_cast<float>((skippedFrames + 1) * totalFrames)), static_cast<byte>(1));
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
        currentTransform = context.GetCurrentTransform();

        AfterImageDictionary::iterator it = afterImages.find(visual);
        if (it != afterImages.end())
        {
            currentAfterImage = (*it).second;

            const byte opacityDecrement = GetOpacityDecrement();
            UIRenderer* renderer = context.GetRenderer();
            std::deque<Frame>& frames = currentAfterImage->Frames;
            for (std::deque<Frame>::iterator it = frames.begin(); it != frames.end(); it++)
            {
                Frame& item = (*it);

                if (item.color.A > opacityDecrement)
                    item.color.A -= opacityDecrement;
                else
                    item.color.A = 0;

                renderer->Setup(item.transform);
                renderer->DrawQuad(item.positions, item.color, item.uv, item.texture);
            }

            while (static_cast<int>(currentAfterImage->Frames.size()) > totalFrames)
                currentAfterImage->Frames.pop_front();

            currentAfterImage->SkippedFrames++;
        }
        else
        {
            currentAfterImage = new AfterImage();
            currentAfterImage->SkippedFrames = skippedFrames + 1;
            afterImages.insert(AfterImageDictionary::value_type(visual, currentAfterImage));
        }
    }

    void UIAfterImageEffect::EndDraw(UIDrawingContext& /*context*/, UIVisual* /*visual*/)
    {
        if (currentAfterImage && currentAfterImage->SkippedFrames > skippedFrames)
        {
            currentAfterImage->SkippedFrames = 0;
            currentAfterImage = nullptr;
        }
    }

    void UIAfterImageEffect::DrawQuad(UIRenderer* renderer, Vector2* p, Color color)
    {
        Base::DrawQuad(renderer, p, color);
    }

    void UIAfterImageEffect::DrawQuad(UIRenderer* renderer, Vector2* p, Color color, Vector2* uv,  Texture2D* texture)
    {
        if (active && currentAfterImage->SkippedFrames > skippedFrames)
            currentAfterImage->Frames.push_back(Frame(currentTransform, p, color, uv, texture));

        Base::DrawQuad(renderer, p, color, uv, texture);
    }

    void UIAfterImageEffect::DrawQuad(UIRenderer* renderer, Vector2* p, Color color, Vector2* uv1, Texture2D* texture1, Vector2* uv2, Texture2D* texture2)
    {
        Base::DrawQuad(renderer, p, color, uv1, texture1, uv2, texture2);
    }

    void UIAfterImageEffect::DrawQuad(UIRenderer* renderer, Vector2* p, Color color, RectF clippingRect, Texture2D* texture)
    {
        if (active && currentAfterImage->SkippedFrames > skippedFrames)
            currentAfterImage->Frames.push_back(Frame(currentTransform, p, color, clippingRect, texture));

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
        active = static_cast<bool>(reader.ReadBool());
    }

    void UIAfterImageEffect::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        skippedFrames = o->skippedFrames;
        totalFrames = o->totalFrames;
        active = o->active;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    UIAfterImageEffect::Frame::Frame(const Matrix4& transform, Vector2* p4, Color c, Vector2* uv4, Texture2D* texture)
        : transform(transform),
          color(c),
          texture(texture)
    {
        positions[0] = p4[0];
        positions[1] = p4[1];
        positions[2] = p4[2];
        positions[3] = p4[3];
        uv[0] = uv4[0];
        uv[1] = uv4[1];
        uv[2] = uv4[2];
        uv[3] = uv4[3];
    }

    UIAfterImageEffect::Frame::Frame(const Matrix4& transform, Vector2* p4, Color c, RectF clippingRect, Texture2D* texture)
        : transform(transform),
          color(c),
          texture(texture)
    {
        positions[0] = p4[0];
        positions[1] = p4[1];
        positions[2] = p4[2];
        positions[3] = p4[3];
        uv[0] = Vector2(clippingRect.GetLeft(),  clippingRect.GetTop());
        uv[1] = Vector2(clippingRect.GetRight(), clippingRect.GetTop());
        uv[2] = Vector2(clippingRect.GetLeft(),  clippingRect.GetBottom());
        uv[3] = Vector2(clippingRect.GetRight(), clippingRect.GetBottom());
    }
}