#include <Bibim/PCH.h>
#include <Bibim/UIDrawingContext.h>
#include <Bibim/Assert.h>
#include <Bibim/Font.h>
#include <Bibim/FontString.h>
#include <Bibim/GraphicsCapabilities.h>
#include <Bibim/GraphicsDevice.h>
#include <Bibim/Image.h>
#include <Bibim/UIRenderer.h>
#include <Bibim/UIEffectStack.h>
#include <Bibim/UIVisual.h>
#include <Bibim/Texture2D.h>
#include <Bibim/TypingContext.h>

namespace Bibim
{
    UIDrawingContext::UIDrawingContext(UIRenderer* renderer)
        : UIVisualVisitor(renderer->GetViewTransform(), renderer->GetInversedViewTransform(), renderer->GetProjectionTransform(), true),
          renderer(renderer),
          isDrawing(false)
    {
        effectStack = new UIEffectStack(renderer->GetGraphicsDevice()->GetCapabilities().IsShaderSupported());
    }
    
    UIDrawingContext::~UIDrawingContext()
    {
    }

    void UIDrawingContext::Draw(UIVisual* target)
    {
        BBAssert(isDrawing == false);

        isDrawing = true;
        renderer->Begin();
        OnBegan();

        Visit(target);

        OnEnded();
        renderer->End();
        isDrawing = false;
    }

    void UIDrawingContext::Draw(const RectF& bounds, const RectF& clippedBounds, Image* image, bool horizontalFlip, bool verticalFlip)
    {
        BBAssertDebug(image && image->GetTexture() && renderer);
        if (image->GetStatus() != GameAsset::CompletedStatus ||
            image->GetTexture()->GetStatus() != GameAsset::CompletedStatus)
            return;

        if (currentMask &&
            currentMask->GetStatus() == GameAsset::CompletedStatus &&
            currentMask->GetTexture()->GetStatus() == GameAsset::CompletedStatus)
        {
            Draw(bounds, clippedBounds, image, currentMask, horizontalFlip, verticalFlip);
            return;
        }

        const float boundsClippedLeft   = (clippedBounds.GetLeft() - bounds.GetLeft()) / bounds.Width;
        const float boundsClippedTop    = (clippedBounds.GetTop() - bounds.GetTop()) / bounds.Height;
        const float boundsClippedRight  = (bounds.GetRight() - clippedBounds.GetRight()) / bounds.Width;
        const float boundsClippedBottom = (bounds.GetBottom() - clippedBounds.GetBottom()) / bounds.Height;

        RectF clippingRect = image->GetNormalizedClippingRect();
        float clippingLeft   = clippingRect.GetLeft();
        float clippingTop    = clippingRect.GetTop();
        float clippingRight  = clippingRect.GetRight();
        float clippingBottom = clippingRect.GetBottom();

        switch (image->GetAppliedTransform())
        {
            case Image::Identity:
                clippingLeft   += clippingRect.Width * boundsClippedLeft;
                clippingTop    += clippingRect.Height * boundsClippedTop;
                clippingRight  -= clippingRect.Width * boundsClippedRight;
                clippingBottom -= clippingRect.Height * boundsClippedBottom;
                break;
            case Image::RotateCW90:
                clippingLeft   += clippingRect.Height * boundsClippedBottom;
                clippingTop    += clippingRect.Width * boundsClippedLeft;
                clippingRight  -= clippingRect.Height * boundsClippedTop;
                clippingBottom -= clippingRect.Width * boundsClippedRight;
                break;
        }

        clippingRect.X = clippingLeft;
        clippingRect.Y = clippingTop;
        clippingRect.Width  = (horizontalFlip == false) ? clippingRight - clippingLeft : clippingLeft - clippingRight;
        clippingRect.Height = (verticalFlip   == false) ? clippingBottom - clippingTop : clippingTop - clippingBottom;

        const Vector2 points[] =
        {
            Vector2(clippedBounds.GetLeft()  - 0.5f, clippedBounds.GetTop() - 0.5f),
            Vector2(clippedBounds.GetRight() - 0.5f, clippedBounds.GetTop() - 0.5f),
            Vector2(clippedBounds.GetLeft()  - 0.5f, clippedBounds.GetBottom() - 0.5f),
            Vector2(clippedBounds.GetRight() - 0.5f, clippedBounds.GetBottom() - 0.5f),
        };

        Vector2 uv[4];
        switch (image->GetAppliedTransform())
        {
            case Image::Identity:
                uv[0] = Vector2(clippingRect.GetLeft(), clippingRect.GetTop());
                uv[1] = Vector2(clippingRect.GetRight(), clippingRect.GetTop());
                uv[2] = Vector2(clippingRect.GetLeft(), clippingRect.GetBottom());
                uv[3] = Vector2(clippingRect.GetRight(), clippingRect.GetBottom());
                break;
            case Image::RotateCW90:
                uv[0] = Vector2(clippingRect.GetRight(), clippingRect.GetTop());
                uv[1] = Vector2(clippingRect.GetRight(), clippingRect.GetBottom());
                uv[2] = Vector2(clippingRect.GetLeft(), clippingRect.GetTop());
                uv[3] = Vector2(clippingRect.GetLeft(), clippingRect.GetBottom());
                break;
        }

        const Color color = Color(Vector4(1.0f, 1.0f, 1.0f, GetCurrentOpacity()));
        renderer->DrawQuad(points, color, uv, image->GetTexture());
    }

    void UIDrawingContext::Draw(const RectF& bounds, const RectF& clippedBounds, Image* image, Image* maskImage, bool horizontalFlip, bool verticalFlip)
    {
        BBAssertDebug(image && image->GetTexture() && renderer);
        if (image->GetStatus() != GameAsset::CompletedStatus ||
            image->GetTexture()->GetStatus() != GameAsset::CompletedStatus)
            return;
        if (maskImage->GetStatus() != GameAsset::CompletedStatus ||
            maskImage->GetTexture()->GetStatus() != GameAsset::CompletedStatus)
            return Draw(bounds, clippedBounds, image, horizontalFlip, verticalFlip);

        const float boundsClippedLeft   = (clippedBounds.GetLeft() - bounds.GetLeft()) / bounds.Width;
        const float boundsClippedTop    = (clippedBounds.GetTop() - bounds.GetTop()) / bounds.Height;
        const float boundsClippedRight  = (bounds.GetRight() - clippedBounds.GetRight()) / bounds.Width;
        const float boundsClippedBottom = (bounds.GetBottom() - clippedBounds.GetBottom()) / bounds.Height;

        RectF clippingRect = image->GetNormalizedClippingRect();
        float clippingLeft   = clippingRect.GetLeft();
        float clippingTop    = clippingRect.GetTop();
        float clippingRight  = clippingRect.GetRight();
        float clippingBottom = clippingRect.GetBottom();

        RectF maskClippingRect = maskImage->GetNormalizedClippingRect();
        float maskClippingLeft   = maskClippingRect.GetLeft();
        float maskClippingTop    = maskClippingRect.GetTop();
        float maskClippingRight  = maskClippingRect.GetRight();
        float maskClippingBottom = maskClippingRect.GetBottom();

        switch (image->GetAppliedTransform())
        {
            case Image::Identity:
                clippingLeft   += boundsClippedLeft;
                clippingTop    += boundsClippedTop;
                clippingRight  -= boundsClippedRight;
                clippingBottom -= boundsClippedBottom;
                break;
            case Image::RotateCW90:
                clippingLeft   += boundsClippedBottom;
                clippingTop    += boundsClippedLeft;
                clippingRight  -= boundsClippedTop;
                clippingBottom -= boundsClippedRight;
                break;
        }

        switch (maskImage->GetAppliedTransform())
        {
            case Image::Identity:
                maskClippingLeft   += boundsClippedLeft;
                maskClippingTop    += boundsClippedTop;
                maskClippingRight  -= boundsClippedRight;
                maskClippingBottom -= boundsClippedBottom;
                break;
            case Image::RotateCW90:
                maskClippingLeft   += boundsClippedBottom;
                maskClippingTop    += boundsClippedLeft;
                maskClippingRight  -= boundsClippedTop;
                maskClippingBottom -= boundsClippedRight;
                break;
        }

        clippingRect.X = clippingLeft;
        clippingRect.Y = clippingTop;
        clippingRect.Width  = (horizontalFlip == false) ? clippingRight - clippingLeft : clippingLeft - clippingRight;
        clippingRect.Height = (verticalFlip   == false) ? clippingBottom - clippingTop : clippingTop - clippingBottom;

        maskClippingRect.X = maskClippingLeft;
        maskClippingRect.Y = maskClippingTop;
        maskClippingRect.Width  = (horizontalFlip == false) ? maskClippingRight - maskClippingLeft : maskClippingLeft - maskClippingRight;
        maskClippingRect.Height = (verticalFlip   == false) ? maskClippingBottom - maskClippingTop : maskClippingTop - maskClippingBottom;

        const Vector2 points[] =
        {
            Vector2(clippedBounds.GetLeft()  - 0.5f, clippedBounds.GetTop() - 0.5f),
            Vector2(clippedBounds.GetRight() - 0.5f, clippedBounds.GetTop() - 0.5f),
            Vector2(clippedBounds.GetLeft()  - 0.5f, clippedBounds.GetBottom() - 0.5f),
            Vector2(clippedBounds.GetRight() - 0.5f, clippedBounds.GetBottom() - 0.5f),
        };

        Vector2 uv1[4];
        switch (image->GetAppliedTransform())
        {
            case Image::Identity:
                uv1[0] = Vector2(clippingRect.GetLeft(), clippingRect.GetTop());
                uv1[1] = Vector2(clippingRect.GetRight(), clippingRect.GetTop());
                uv1[2] = Vector2(clippingRect.GetLeft(), clippingRect.GetBottom());
                uv1[3] = Vector2(clippingRect.GetRight(), clippingRect.GetBottom());
                break;
            case Image::RotateCW90:
                uv1[0] = Vector2(clippingRect.GetRight(), clippingRect.GetTop());
                uv1[1] = Vector2(clippingRect.GetRight(), clippingRect.GetBottom());
                uv1[2] = Vector2(clippingRect.GetLeft(), clippingRect.GetTop());
                uv1[3] = Vector2(clippingRect.GetLeft(), clippingRect.GetBottom());
                break;
        }

        Vector2 uv2[4];
        switch (image->GetAppliedTransform())
        {
            case Image::Identity:
                uv2[0] = Vector2(maskClippingRect.GetLeft(), maskClippingRect.GetTop());
                uv2[1] = Vector2(maskClippingRect.GetRight(), maskClippingRect.GetTop());
                uv2[2] = Vector2(maskClippingRect.GetLeft(), maskClippingRect.GetBottom());
                uv2[3] = Vector2(maskClippingRect.GetRight(), maskClippingRect.GetBottom());
                break;
            case Image::RotateCW90:
                uv2[0] = Vector2(maskClippingRect.GetRight(), maskClippingRect.GetTop());
                uv2[1] = Vector2(maskClippingRect.GetRight(), maskClippingRect.GetBottom());
                uv2[2] = Vector2(maskClippingRect.GetLeft(), maskClippingRect.GetTop());
                uv2[3] = Vector2(maskClippingRect.GetLeft(), maskClippingRect.GetBottom());
                break;
        }

        const Color color = Color(Vector4(1.0f, 1.0f, 1.0f, GetCurrentOpacity()));
        renderer->DrawQuad(points, color, uv1, image->GetTexture(), uv2, maskImage->GetTexture());
    }

    void UIDrawingContext::Draw(Vector2 position, Texture2D* texture)
    {
        BBAssertDebug(texture && renderer);

        const RectF drawingRect = RectF(position.X,
                                        position.Y,
                                        static_cast<float>(texture->GetWidth()),
                                        static_cast<float>(texture->GetHeight()));

        const Vector2 points[] =
        {
            Vector2(drawingRect.GetLeft()  - 0.5f, drawingRect.GetTop() - 0.5f),
            Vector2(drawingRect.GetRight() - 0.5f, drawingRect.GetTop() - 0.5f),
            Vector2(drawingRect.GetLeft()  - 0.5f, drawingRect.GetBottom() - 0.5f),
            Vector2(drawingRect.GetRight() - 0.5f, drawingRect.GetBottom() - 0.5f),
        };
        const Color color = Color(Vector4(1.0f, 1.0f, 1.0f, GetCurrentOpacity()));
        renderer->DrawQuad(points, color, RectF(0.0f, 0.0f, 1.0f, 1.0f), texture);
    }

    void UIDrawingContext::DrawString(const RectF& bounds, const RectF& clippedBounds, Font* font, const String& text)
    {
        DrawString(bounds, clippedBounds, FontString(font, text));
    }

    void UIDrawingContext::DrawString(const RectF& bounds, const RectF& clippedBounds, const FontString& fontString)
    {
        BBAssertDebug(renderer);

        if (fontString.GetText().IsEmpty())
            return;

        TypingContext context(fontString, bounds.Width);

        struct DrawGlyphs
        {
            static void Do(UIDrawingContext* self, TypingContext& context, UIRenderer* renderer, const RectF& bounds, const RectF& clippedBounds, const FontString::GlyphCollection& glyphs, Color color)
            {
                while (context.MoveNext())
                {
                    const Glyph* glyph = glyphs[context.GetGlyphIndex()];
                    if (glyph->GetTexture() == nullptr)
                        continue;

                    const float tw = 1.0f / static_cast<float>(glyph->GetTexture()->GetWidth());
                    const float th = 1.0f / static_cast<float>(glyph->GetTexture()->GetHeight());
                    RectF clippingRect = RectF(glyph->GetClippingRect().X,
                                               glyph->GetClippingRect().Y,
                                               glyph->GetClippingRect().Width,
                                               glyph->GetClippingRect().Height);
                    clippingRect.X *= tw;
                    clippingRect.Y *= th;
                    clippingRect.Width  *= tw;
                    clippingRect.Height *= th;

                    const RectF drawingRect = RectF(bounds.X + context.GetPosition().X + glyph->GetBitmapOffset().X,
                                                    bounds.Y + context.GetPosition().Y + glyph->GetBitmapOffset().Y,
                                                    glyph->GetBitmapSize().X,
                                                    glyph->GetBitmapSize().Y);
                    const Vector2 points[4] = 
                    {
                        Vector2(drawingRect.GetLeft()  - 0.5f, drawingRect.GetTop() - 0.5f),
                        Vector2(drawingRect.GetRight() - 0.5f, drawingRect.GetTop() - 0.5f),
                        Vector2(drawingRect.GetLeft()  - 0.5f, drawingRect.GetBottom() - 0.5f),
                        Vector2(drawingRect.GetRight() - 0.5f, drawingRect.GetBottom() - 0.5f),
                    };
                    renderer->DrawQuad(points, color, clippingRect, glyph->GetTexture());
                }
            }
        };

        renderer->BeginBatch();

        if (fontString.GetFont()->GetGlowSize() > 0)
        {
            DrawGlyphs::Do(this, context, renderer, bounds, clippedBounds, fontString.GetGlowGlyphs(), fontString.GetFont()->GetGlowColor());
            context.Reset();
        }

        if (fontString.GetFont()->GetStrokeSize() > 0.0f)
        {
            DrawGlyphs::Do(this, context, renderer, bounds, clippedBounds, fontString.GetStrokedGlyphs(), fontString.GetFont()->GetStrokeColor());
            context.Reset();
        }

        DrawGlyphs::Do(this, context, renderer, bounds, clippedBounds, fontString.GetRegularGlyphs(), fontString.GetFont()->GetColor());
        renderer->EndBatch();
    }

    void UIDrawingContext::DrawRect(const RectF& bounds, float width, Color color)
    {
        color.A = static_cast<byte>(static_cast<float>(color.A) * GetCurrentOpacity());
    }

    void UIDrawingContext::FillRect(const RectF& bounds, float width, Color color)
    {
        color.A = static_cast<byte>(static_cast<float>(color.A) * GetCurrentOpacity());
    }

    void UIDrawingContext::OnBegan()
    {
    }

    void UIDrawingContext::OnEnded()
    {
    }

    void UIDrawingContext::OnVisit()
    {
        ImagePtr oldMask = currentMask;

        if (GetCurrentVisual()->GetEffectMap())
        {
            if (effectStack->Push(GetCurrentVisual()->GetEffectMap(), currentMask))
                renderer->Setup(effectStack->GetTopEffectors());
        }

        renderer->Setup(GetCurrentTransform());
        GetCurrentVisual()->OnDraw(*this);
        renderer->Setup(GetCurrentTransform());

        if (GetCurrentVisual()->GetEffectMap())
        {
            if (effectStack->Pop())
            {
                currentMask = oldMask;
                renderer->Setup(effectStack->GetTopEffectors());
            }
        }
    }
}