#include <Bibim/PCH.h>
#include <Bibim/UIDrawingContext.h>
#include <Bibim/Assert.h>
#include <Bibim/Font.h>
#include <Bibim/FontString.h>
#include <Bibim/UIImage.h>
#include <Bibim/UIRenderer.h>
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

    void UIDrawingContext::Draw(const RectF& bounds, const RectF& clippedBounds, UIImage* image, bool horizontalFlip, bool verticalFlip)
    {
        BBAssertDebug(image && image->GetRealTexture() && renderer);

        const float boundsClippedLeft   = (clippedBounds.GetLeft() - bounds.GetLeft()) / bounds.Width;
        const float boundsClippedTop    = (clippedBounds.GetTop() - bounds.GetTop()) / bounds.Height;
        const float boundsClippedRight  = (bounds.GetRight() - clippedBounds.GetRight()) / bounds.Width;
        const float boundsClippedBottom = (bounds.GetBottom() - clippedBounds.GetBottom()) / bounds.Height;

        RectF clippingRect = image->GetNormalizedRealClippingRect();
        const float clippingLeft   = clippingRect.GetLeft() + boundsClippedLeft;
        const float clippingTop    = clippingRect.GetTop() + boundsClippedTop;
        const float clippingRight  = clippingRect.GetRight() - boundsClippedRight;
        const float clippingBottom = clippingRect.GetBottom() - boundsClippedBottom;

        clippingRect.X = clippingLeft;
        clippingRect.Y = clippingTop;
        clippingRect.Width  = (horizontalFlip == false) ? clippingRight - clippingLeft : clippingLeft - clippingRight;
        clippingRect.Height = (verticalFlip   == false) ? clippingBottom - clippingTop : clippingTop - clippingBottom;

        Vector2 points[] =
        {
            Vector2(clippedBounds.GetLeft()  - 0.5f, clippedBounds.GetTop() - 0.5f),
            Vector2(clippedBounds.GetRight() - 0.5f, clippedBounds.GetTop() - 0.5f),
            Vector2(clippedBounds.GetLeft()  - 0.5f, clippedBounds.GetBottom() - 0.5f),
            Vector2(clippedBounds.GetRight() - 0.5f, clippedBounds.GetBottom() - 0.5f),
        };
        Project(points[0], points[1], points[2], points[3]);

        renderer->Draw(points[0], points[1], points[2], points[3], clippingRect, image->GetRealTexture(), Color(Vector4(1.0f, 1.0f, 1.0f, GetCurrentOpacity())));
    }

    void UIDrawingContext::Draw(Vector2 position, Texture2D* texture)
    {
        BBAssertDebug(texture && renderer);

        const RectF drawingRect = RectF(position.X,
                                                       position.Y,
                                                       static_cast<float>(texture->GetWidth()),
                                                       static_cast<float>(texture->GetHeight()));

        Vector2 points[] =
        {
            Vector2(drawingRect.GetLeft()  - 0.5f, drawingRect.GetTop() - 0.5f),
            Vector2(drawingRect.GetRight() - 0.5f, drawingRect.GetTop() - 0.5f),
            Vector2(drawingRect.GetLeft()  - 0.5f, drawingRect.GetBottom() - 0.5f),
            Vector2(drawingRect.GetRight() - 0.5f, drawingRect.GetBottom() - 0.5f),
        };
        Project(points[0], points[1], points[2], points[3]);

        renderer->Draw(points[0], points[1], points[2], points[3], RectF(0.0f, 0.0f, 1.0f, 1.0f), texture, Color(Vector4(1.0f, 1.0f, 1.0f, GetCurrentOpacity())));
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

        renderer->EnterStringRenderMode();

        TypingContext context(fontString, bounds.Width);

        struct DrawGlyphs
        {
            static void Do(UIDrawingContext* self, TypingContext& context, UIRenderer* renderer, const RectF& bounds, const RectF& clippedBounds, const FontString::GlyphCollection& glyphs, Color color)
            {
                while (context.MoveNext())
                {
                    const Glyph* glyph = glyphs[context.GetGlyphIndex()];

                    const float tw = 1.0f / static_cast<float>(glyph->GetTexture()->GetWidth());
                    const float th = 1.0f / static_cast<float>(glyph->GetTexture()->GetHeight());
                    RectF clippingRect = RectF(glyph->GetClippingRect().X, glyph->GetClippingRect().Y, glyph->GetClippingRect().Width, glyph->GetClippingRect().Height);
                    clippingRect.X *= tw;
                    clippingRect.Y *= th;
                    clippingRect.Width  *= tw;
                    clippingRect.Height *= th;

                    const RectF drawingRect = RectF(bounds.X + context.GetPosition().X + glyph->GetBitmapOffset().X,
                                                                   bounds.Y + context.GetPosition().Y + glyph->GetBitmapOffset().Y,
                                                                   glyph->GetBitmapSize().X,
                                                                   glyph->GetBitmapSize().Y);
                    Vector2 points[4] = 
                    {
                        Vector2(drawingRect.GetLeft()  - 0.5f, drawingRect.GetTop() - 0.5f),
                        Vector2(drawingRect.GetRight() - 0.5f, drawingRect.GetTop() - 0.5f),
                        Vector2(drawingRect.GetLeft()  - 0.5f, drawingRect.GetBottom() - 0.5f),
                        Vector2(drawingRect.GetRight() - 0.5f, drawingRect.GetBottom() - 0.5f),
                    };
                    self->Project(points[0], points[1], points[2], points[3]);
                    renderer->Draw(points[0], points[1], points[2], points[3], clippingRect, glyph->GetTexture(), color);
                }
            }
        };

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

        renderer->LeaveStringRenderMode();
    }

    void UIDrawingContext::DrawRect(const RectF& bounds, float width, Color color)
    {
        color.A = static_cast<byte>(static_cast<float>(color.A) * GetCurrentOpacity());
        //renderer->DrawRect(bounds, color);
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
        GetCurrentVisual()->OnDraw(*this);
    }
}