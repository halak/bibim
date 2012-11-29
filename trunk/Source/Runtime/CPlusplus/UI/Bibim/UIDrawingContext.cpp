#include <Bibim/PCH.h>
#include <Bibim/UIDrawingContext.h>
#include <Bibim/Assert.h>
#include <Bibim/Font.h>
#include <Bibim/FontString.h>
#include <Bibim/GraphicsCapabilities.h>
#include <Bibim/GraphicsDevice.h>
#include <Bibim/Image.h>
#include <Bibim/Math.h>
#include <Bibim/Shape2D.h>
#include <Bibim/UIGeometryEffect.h>
#include <Bibim/UIEffectMap.h>
#include <Bibim/UIEffectStack.h>
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

        clippingRect.X = (horizontalFlip == false) ? clippingLeft : clippingRight;
        clippingRect.Y = (verticalFlip == false)   ? clippingTop  : clippingBottom;
        clippingRect.Width  = (horizontalFlip == false) ? clippingRight - clippingLeft : clippingLeft - clippingRight;
        clippingRect.Height = (verticalFlip   == false) ? clippingBottom - clippingTop : clippingTop - clippingBottom;

        Vector2 points[] =
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
        if (currentGeomEffect)
            currentGeomEffect->DrawQuad(renderer, points, color, uv, image->GetTexture());
        else
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

        Vector2 points[] =
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
        if (currentGeomEffect)
            currentGeomEffect->DrawQuad(renderer, points, color, uv1, image->GetTexture(), uv2, maskImage->GetTexture());
        else
            renderer->DrawQuad(points, color, uv1, image->GetTexture(), uv2, maskImage->GetTexture());
    }

    void UIDrawingContext::Draw(Shape2D* shape, Color color)
    {
        if (shape == nullptr)
            return;

        class VisibleVertices : public Shape2D::Vertices
        {
            public:
                VisibleVertices() { }
                virtual ~VisibleVertices() { }

                virtual void Append(Vector2 p0)
                {
                    data.push_back(p0);
                }

                virtual void Append(Vector2 p0, Vector2 p1)
                {
                    data.push_back(p0);
                    data.push_back(p1);
                }

                virtual void Append(Vector2 p0, Vector2 p1, Vector2 p2)
                {
                    data.push_back(p0);
                    data.push_back(p1);
                    data.push_back(p2);
                }

                virtual void Append(Vector2 p0, Vector2 p1, Vector2 p2, Vector2 p3)
                {
                    data.push_back(p0);
                    data.push_back(p1);
                    data.push_back(p2);
                    data.push_back(p3);
                }

                virtual void Append(const std::vector<Vector2>& p)
                { 
                    data.insert(data.end(), p.begin(), p.end());
                }

            public:
                std::vector<Vector2> data;
        };

        VisibleVertices v;
        shape->Build(v);

        if (v.data.empty() == false)
            DrawLines(static_cast<int>(v.data.size()), &v.data[0], color);
    }

    void UIDrawingContext::DrawUnclipped(Vector2 position, Texture2D* texture)
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
        const Color color = Color(Vector4(1.0f, 1.0f, 1.0f, GetCurrentOpacity()));
        if (currentGeomEffect)
            currentGeomEffect->DrawQuad(renderer, points, color, RectF(0.0f, 0.0f, 1.0f, 1.0f), texture);
        else
            renderer->DrawQuad(points, color, RectF(0.0f, 0.0f, 1.0f, 1.0f), texture);
    }

    void UIDrawingContext::DrawUnclipped(Vector2 position, float rotation, Image* image)
    {
        DrawUnclipped(position, rotation, 1.0f, image, Color(255, 255, 255));
    }

    void UIDrawingContext::DrawUnclipped(Vector2 position, float rotation, Image* image, Color color)
    {
        DrawUnclipped(position, rotation, 1.0f, image, color);
    }

    void UIDrawingContext::DrawUnclipped(Vector2 position, float rotation, float scale, Image* image, Color color)
    {
        BBAssertDebug(image && image->GetTexture() && renderer);
        if (image->GetStatus() != GameAsset::CompletedStatus ||
            image->GetTexture()->GetStatus() != GameAsset::CompletedStatus)
            return;

        const float halfWidth  = static_cast<float>(image->GetClippingRect().Width) * 0.5f * scale;
        const float halfHeight = static_cast<float>(image->GetClippingRect().Height) * 0.5f * scale;

        Vector2 points[] =
        {
            Vector2(-halfWidth, -halfHeight),
            Vector2(+halfWidth, -halfHeight),
            Vector2(-halfWidth, +halfHeight),
            Vector2(+halfWidth, +halfHeight),
        };
        if (rotation != 0.0f)
        {
            const float sin = Math::Sin(rotation);
            const float cos = Math::Cos(rotation);
            points[0].Rotate(sin, cos);
            points[1].Rotate(sin, cos);
            points[2].Rotate(sin, cos);
            points[3].Rotate(sin, cos);
        }
        points[0] += position;
        points[1] += position;
        points[2] += position;
        points[3] += position;

        const RectF clippingRect = image->GetNormalizedClippingRect();
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

        color.A = static_cast<byte>(static_cast<float>(color.A) * GetCurrentOpacity());
        if (currentGeomEffect)
            currentGeomEffect->DrawQuad(renderer, points, color, uv, image->GetTexture());
        else
            renderer->DrawQuad(points, color, uv, image->GetTexture());
    }

    void UIDrawingContext::DrawUnclipped(Vector2 position, float rotation, Vector3 rotationAxis, float scale, Image* image, Color color)
    {
        BBAssertDebug(image && image->GetTexture() && renderer);
        if (image->GetStatus() != GameAsset::CompletedStatus ||
            image->GetTexture()->GetStatus() != GameAsset::CompletedStatus)
            return;

        const float halfWidth  = static_cast<float>(image->GetClippingRect().Width) * 0.5f * scale;
        const float halfHeight = static_cast<float>(image->GetClippingRect().Height) * 0.5f * scale;

        Vector3 points[] =
        {
            Vector3(-halfWidth, -halfHeight, 0.0f),
            Vector3(+halfWidth, -halfHeight, 0.0f),
            Vector3(-halfWidth, +halfHeight, 0.0f),
            Vector3(+halfWidth, +halfHeight, 0.0f),
        };
        if (rotation != 0.0f)
        {
            const float sin = Math::Sin(rotation);
            const float cos = Math::Cos(rotation);
            
            points[0].Rotate(rotationAxis, sin, cos);
            points[1].Rotate(rotationAxis, sin, cos);
            points[2].Rotate(rotationAxis, sin, cos);
            points[3].Rotate(rotationAxis, sin, cos);
        }
        points[0].X += position.X;
        points[0].Y += position.Y;
        points[1].X += position.X;
        points[1].Y += position.Y;
        points[2].X += position.X;
        points[2].Y += position.Y;
        points[3].X += position.X;
        points[3].Y += position.Y;

        const RectF clippingRect = image->GetNormalizedClippingRect();
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

        color.A = static_cast<byte>(static_cast<float>(color.A) * GetCurrentOpacity());
        if (currentGeomEffect)
            currentGeomEffect->DrawQuad(renderer, points, color, uv, image->GetTexture());
        else
            renderer->DrawQuad(points, color, uv, image->GetTexture());
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
            static void Do(UIGeometryEffect* geomEffect, TypingContext& context, UIRenderer* renderer, const RectF& bounds, const RectF& /*clippedBounds*/, const FontString::GlyphCollection& glyphs, Color color)
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
                    Vector2 points[4] = 
                    {
                        Vector2(drawingRect.GetLeft()  - 0.5f, drawingRect.GetTop() - 0.5f),
                        Vector2(drawingRect.GetRight() - 0.5f, drawingRect.GetTop() - 0.5f),
                        Vector2(drawingRect.GetLeft()  - 0.5f, drawingRect.GetBottom() - 0.5f),
                        Vector2(drawingRect.GetRight() - 0.5f, drawingRect.GetBottom() - 0.5f),
                    };

                    if (geomEffect)
                        geomEffect->DrawQuad(renderer, points, color, clippingRect, glyph->GetTexture());
                    else
                        renderer->DrawQuad(points, color, clippingRect, glyph->GetTexture());
                }
            }
        };

        renderer->BeginBatch();

        if (fontString.GetFont()->GetGlowSize() > 0)
        {
            Color glowColor = fontString.GetFont()->GetGlowColor();
            glowColor.A = static_cast<byte>(static_cast<float>(glowColor.A) * GetCurrentOpacity());
            DrawGlyphs::Do(currentGeomEffect, context, renderer, bounds, clippedBounds, fontString.GetGlowGlyphs(), glowColor);
            context.Reset();
        }

        if (fontString.GetFont()->GetStrokeSize() > 0.0f)
        {
            Color strokeColor = fontString.GetFont()->GetStrokeColor();
            strokeColor.A = static_cast<byte>(static_cast<float>(strokeColor.A) * GetCurrentOpacity());
            DrawGlyphs::Do(currentGeomEffect, context, renderer, bounds, clippedBounds, fontString.GetStrokedGlyphs(), strokeColor);
            context.Reset();
        }

        Color color = fontString.GetFont()->GetColor();
        color.A = static_cast<byte>(static_cast<float>(color.A) * GetCurrentOpacity());
        DrawGlyphs::Do(currentGeomEffect, context, renderer, bounds, clippedBounds, fontString.GetRegularGlyphs(), color);

        renderer->EndBatch();
    }

    void UIDrawingContext::DrawLine(Vector2 p0, Vector2 p1, Color color)
    {
        Vector2 p[] = { p0, p1 };
        color.A = static_cast<byte>(static_cast<float>(color.A) * GetCurrentOpacity());
        if (currentGeomEffect)
            currentGeomEffect->DrawLines(renderer, sizeof(p) / sizeof(p[0]), p, color);
        else
            renderer->DrawLines(sizeof(p) / sizeof(p[0]), p, color);
    }

    void UIDrawingContext::DrawLines(int count, Vector2* p, Color color)
    {
        if (count <= 1)
            return;

        color.A = static_cast<byte>(static_cast<float>(color.A) * GetCurrentOpacity());
        if (currentGeomEffect)
            currentGeomEffect->DrawLines(renderer, count, p, color);
        else
            renderer->DrawLines(count, p, color);
    }

    void UIDrawingContext::DrawRect(const RectF& bounds, Color color)
    {
        Vector2 p[] =
        {
            Vector2(bounds.GetLeft(),  bounds.GetTop()),
            Vector2(bounds.GetRight(), bounds.GetTop()),
            Vector2(bounds.GetRight(), bounds.GetBottom()),
            Vector2(bounds.GetLeft(),  bounds.GetBottom()),
            Vector2(bounds.GetLeft(),  bounds.GetTop())
        };

        color.A = static_cast<byte>(static_cast<float>(color.A) * GetCurrentOpacity());
        if (currentGeomEffect)
            currentGeomEffect->DrawLines(renderer, sizeof(p) / sizeof(p[0]), p, color);
        else
            renderer->DrawLines(sizeof(p) / sizeof(p[0]), p, color);
    }

    void UIDrawingContext::DrawCircle(Vector2 center, float radius, Color color)
    {
        int count = 32;
        Vector2* p = BBStackAlloc(Vector2, count + 1);

        float r = 0.0f;
        const float increment = Math::TwoPi / static_cast<float>(count);
        for (int i = 0; i < count; i++, r += increment)
        {
            p[i] = Vector2(center.X + (radius * Math::Sin(r)),
                           center.Y + (radius * Math::Cos(r)));
        }

        p[count] = p[0];

        color.A = static_cast<byte>(static_cast<float>(color.A) * GetCurrentOpacity());
        if (currentGeomEffect)
            currentGeomEffect->DrawLines(renderer, count + 1, p, color);
        else
            renderer->DrawLines(count + 1, p, color);

        BBStackFree(p);
    }

    void UIDrawingContext::FillRect(const RectF& bounds, Color color)
    {
        Vector2 p[] = 
        {
            Vector2(bounds.GetLeft(),  bounds.GetTop()),
            Vector2(bounds.GetRight(), bounds.GetTop()),
            Vector2(bounds.GetLeft(),  bounds.GetBottom()),

            Vector2(bounds.GetLeft(),  bounds.GetBottom()),
            Vector2(bounds.GetRight(), bounds.GetTop()),
            Vector2(bounds.GetRight(), bounds.GetBottom()),
        };
        
        color.A = static_cast<byte>(static_cast<float>(color.A) * GetCurrentOpacity());
        if (currentGeomEffect)
            currentGeomEffect->DrawTriangles(renderer, sizeof(p) / sizeof(p[0]), p, color);
        else
            renderer->DrawTriangles(sizeof(p) / sizeof(p[0]), p, color);
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
        UIGeometryEffectPtr oldGeomEffect = currentGeomEffect;

        UIEffectMap* effectMap = GetCurrentVisual()->GetEffectMap();

        if (effectMap)
        {
            if (effectStack->Push(effectMap, currentMask))
                renderer->Setup(effectStack->GetTopEffectors());

            if (effectMap->GetGeometryEffect())
                currentGeomEffect = effectMap->GetGeometryEffect();
        }

        renderer->Setup(GetCurrentTransform());
        if (currentGeomEffect)
            currentGeomEffect->BeginDraw(*this, GetCurrentVisual());
        GetCurrentVisual()->OnDraw(*this);
        if (currentGeomEffect)
            currentGeomEffect->EndDraw(*this, GetCurrentVisual());
        renderer->Setup(GetCurrentTransform());

        if (effectMap)
        {
            if (effectStack->Pop())
            {
                currentMask = oldMask;
                renderer->Setup(effectStack->GetTopEffectors());
            }

            currentGeomEffect = oldGeomEffect;
        }
    }
}