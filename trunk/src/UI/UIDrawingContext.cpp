#include <Bibim/Config.h>
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
    namespace
    {
        static inline float cm(float v)
        {
            return static_cast<float>(static_cast<int>(v)) - 0.5f;
        }

        static inline Vector2 cm(Vector2 v)
        {
            return Vector2(cm(v.X), cm(v.Y));
        }
    }

    UIDrawingContext::UIDrawingContext(UIRenderer* renderer)
        : UIVisualVisitor(renderer->GetGraphicsDevice()->GetViewportSize(),
                          renderer->GetViewTransform(),
                          renderer->GetInversedViewTransform(),
                          renderer->GetProjectionTransform(), true),
          renderer(renderer),
          isDrawing(false)
    {
        effectStack = new UIEffectStack(renderer->GetGraphicsDevice()->GetCapabilities().IsShaderSupported());
    }

    UIDrawingContext::UIDrawingContext(UIRenderer* renderer, Point2 size)
        : UIVisualVisitor(size,
                          renderer->GetViewTransform(),
                          renderer->GetInversedViewTransform(),
                          renderer->GetProjectionTransform(), true),
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
        OnBegan(target);

        Ready(target);
        Visit(target);

        OnEnded(target);
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
                clippingLeft   += clippingRect.Width * boundsClippedBottom;
                clippingTop    += clippingRect.Height * boundsClippedLeft;
                clippingRight  -= clippingRect.Width * boundsClippedTop;
                clippingBottom -= clippingRect.Height * boundsClippedRight;
                break;
        }

        clippingRect.X = (horizontalFlip == false) ? clippingLeft : clippingRight;
        clippingRect.Y = (verticalFlip == false)   ? clippingTop  : clippingBottom;
        clippingRect.Width  = (horizontalFlip == false) ? clippingRight - clippingLeft : clippingLeft - clippingRight;
        clippingRect.Height = (verticalFlip   == false) ? clippingBottom - clippingTop : clippingTop - clippingBottom;

        Vector2 points[] =
        {
            Vector2(cm(clippedBounds.GetLeft()),  cm(clippedBounds.GetTop())),
            Vector2(cm(clippedBounds.GetRight()), cm(clippedBounds.GetTop())),
            Vector2(cm(clippedBounds.GetLeft()),  cm(clippedBounds.GetBottom())),
            Vector2(cm(clippedBounds.GetRight()), cm(clippedBounds.GetBottom())),
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
                clippingLeft   += clippingRect.Width * boundsClippedLeft;
                clippingTop    += clippingRect.Height * boundsClippedTop;
                clippingRight  -= clippingRect.Width * boundsClippedRight;
                clippingBottom -= clippingRect.Height * boundsClippedBottom;
                break;
            case Image::RotateCW90:
                clippingLeft   += clippingRect.Width * boundsClippedBottom;
                clippingTop    += clippingRect.Height * boundsClippedLeft;
                clippingRight  -= clippingRect.Width * boundsClippedTop;
                clippingBottom -= clippingRect.Height * boundsClippedRight;
                break;
        }

        switch (maskImage->GetAppliedTransform())
        {
            case Image::Identity:
                maskClippingLeft   += maskClippingRect.Width * boundsClippedLeft;
                maskClippingTop    += maskClippingRect.Height * boundsClippedTop;
                maskClippingRight  -= maskClippingRect.Width * boundsClippedRight;
                maskClippingBottom -= maskClippingRect.Height * boundsClippedBottom;
                break;
            case Image::RotateCW90:
                maskClippingLeft   += maskClippingRect.Width * boundsClippedBottom;
                maskClippingTop    += maskClippingRect.Height * boundsClippedLeft;
                maskClippingRight  -= maskClippingRect.Width * boundsClippedTop;
                maskClippingBottom -= maskClippingRect.Height * boundsClippedRight;
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
            Vector2(cm(clippedBounds.GetLeft()),  cm(clippedBounds.GetTop())),
            Vector2(cm(clippedBounds.GetRight()), cm(clippedBounds.GetTop())),
            Vector2(cm(clippedBounds.GetLeft()),  cm(clippedBounds.GetBottom())),
            Vector2(cm(clippedBounds.GetRight()), cm(clippedBounds.GetBottom())),
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
        switch (maskImage->GetAppliedTransform())
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
                VisibleVertices(Vector2 origin)
                    : origin(origin)
                {
                }

                virtual ~VisibleVertices() { }

                virtual void Append(Vector2 p0)
                {
                    data.push_back(origin + p0);
                }

                virtual void Append(Vector2 p0, Vector2 p1)
                {
                    data.push_back(origin + p0);
                    data.push_back(origin + p1);
                }

                virtual void Append(Vector2 p0, Vector2 p1, Vector2 p2)
                {
                    data.push_back(origin + p0);
                    data.push_back(origin + p1);
                    data.push_back(origin + p2);
                }

                virtual void Append(Vector2 p0, Vector2 p1, Vector2 p2, Vector2 p3)
                {
                    data.push_back(origin + p0);
                    data.push_back(origin + p1);
                    data.push_back(origin + p2);
                    data.push_back(origin + p3);
                }

                virtual void Append(const std::vector<Vector2>& p)
                { 
                    data.reserve(data.size() + p.size());
                    for (std::vector<Vector2>::const_iterator it = p.begin(); it != p.end(); ++it)
                        data.push_back(origin + (*it));
                }

            public:
                Vector2 origin;
                std::vector<Vector2> data;
        };

        VisibleVertices v(GetOffset());
        shape->Build(v);

        if (v.data.empty() == false)
        {
            v.data.push_back(v.data[0]);
            DrawLines(static_cast<int>(v.data.size()), &v.data[0], color);
        }
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
            Vector2(cm(drawingRect.GetLeft()),  cm(drawingRect.GetTop())),
            Vector2(cm(drawingRect.GetRight()), cm(drawingRect.GetTop())),
            Vector2(cm(drawingRect.GetLeft()),  cm(drawingRect.GetBottom())),
            Vector2(cm(drawingRect.GetRight()), cm(drawingRect.GetBottom())),
        };
        const Color color = Color(Vector4(1.0f, 1.0f, 1.0f, GetCurrentOpacity()));
        const RectF clippingRect = RectF(0.0f,
                                         0.0f,
                                         static_cast<float>(texture->GetWidth())  / texture->GetSurfaceWidth(),
                                         static_cast<float>(texture->GetHeight()) / texture->GetSurfaceHeight());
        
        if (currentGeomEffect)
            currentGeomEffect->DrawQuad(renderer, points, color, clippingRect, texture);
        else
            renderer->DrawQuad(points, color, clippingRect, texture);
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

    void UIDrawingContext::DrawUnclipped(Vector2 position, float rotation, Vector2 rotationCenter, Vector2 scale, Image* image, Color color)
    {
        BBAssertDebug(image && image->GetTexture() && renderer);
        if (image->GetStatus() != GameAsset::CompletedStatus ||
            image->GetTexture()->GetStatus() != GameAsset::CompletedStatus)
            return;

        const Vector2 size = Vector2(static_cast<float>(image->GetClippingRect().Width) * scale.X,
                                     static_cast<float>(image->GetClippingRect().Height) * scale.Y);
        rotationCenter.X *= size.X;
        rotationCenter.Y *= size.Y; 

        Vector2 points[] =
        {
            Vector2(0.0f   - rotationCenter.X, 0.0f   - rotationCenter.Y),
            Vector2(size.X - rotationCenter.X, 0.0f   - rotationCenter.Y),
            Vector2(0.0f   - rotationCenter.X, size.Y - rotationCenter.Y),
            Vector2(size.X - rotationCenter.X, size.Y - rotationCenter.Y),
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

    void UIDrawingContext::DrawString(RectF bounds, Font* font, const String& text)
    {
        static const RectF BigRect = RectF(-10000.0f, -10000.0f, 20000.0f, 20000.0f);
        DrawString(bounds, BigRect, FontString(font, text));
    }

    void UIDrawingContext::DrawString(const RectF& bounds, const RectF& clippedBounds, const FontString& fontString)
    {
        BBAssertDebug(renderer);

        if (fontString.GetText().IsEmpty())
            return;

        struct DrawGlyphs
        {
            static void Do(UIGeometryEffect* geomEffect,
                           TypingContext& context,
                           UIRenderer* renderer,
                           const RectF& bounds,
                           const RectF& clippedBounds,
                           const FontString::GlyphCollection& glyphs,
                           Color color,
                           Vector2 offset)
            {
                renderer->BeginBatch();
                while (context.MoveNext())
                {
                    const Glyph* glyph = glyphs[context.GetGlyphIndex()];
                    if (glyph->GetTexture() == nullptr)
                        continue;

                    const Vector2 bitmapSize = glyph->GetBitmapSize();
                    RectF drawingRect = RectF(bounds.X + context.GetPosition().X + glyph->GetBitmapOffset().X + offset.X,
                                              bounds.Y + context.GetPosition().Y + glyph->GetBitmapOffset().Y + offset.Y,
                                              bitmapSize.X,
                                              bitmapSize.Y);

                    const float clippedLeft = Math::Max(clippedBounds.GetLeft() - drawingRect.GetLeft(), 0.0f);
                    const float clippedTop = Math::Max(clippedBounds.GetTop() - drawingRect.GetTop(), 0.0f);
                    const float clippedRight = Math::Max(drawingRect.GetRight() - clippedBounds.GetRight(), 0.0f);
                    const float clippedBottom = Math::Max(drawingRect.GetBottom() - clippedBounds.GetBottom(), 0.0f);
                    drawingRect.X += clippedLeft;
                    drawingRect.Y += clippedTop;
                    drawingRect.Width -= clippedRight + clippedLeft;
                    drawingRect.Height -= clippedBottom + clippedTop;

                    if (drawingRect.Width <= 0.0f || drawingRect.Height <= 0.0f)
                        continue;

                    const float tw = 1.0f / static_cast<float>(glyph->GetTexture()->GetWidth());
                    const float th = 1.0f / static_cast<float>(glyph->GetTexture()->GetHeight());
                    RectF clippingRect = RectF(glyph->GetSlot().ClippingRect.X,
                                               glyph->GetSlot().ClippingRect.Y,
                                               glyph->GetSlot().ClippingRect.Width,
                                               glyph->GetSlot().ClippingRect.Height);
                    clippingRect.X *= tw;
                    clippingRect.Y *= th;
                    clippingRect.Width  *= tw;
                    clippingRect.Height *= th;

                    clippingRect.X += clippedLeft * tw;
                    clippingRect.Y += clippedTop * th;
                    clippingRect.Width -= (clippedRight + clippedLeft) * tw;
                    clippingRect.Height -= (clippedBottom + clippedTop) * th;

                    Vector2 points[4] = 
                    {
                        Vector2(cm(drawingRect.GetLeft()),  cm(drawingRect.GetTop())),
                        Vector2(cm(drawingRect.GetRight()), cm(drawingRect.GetTop())),
                        Vector2(cm(drawingRect.GetLeft()),  cm(drawingRect.GetBottom())),
                        Vector2(cm(drawingRect.GetRight()), cm(drawingRect.GetBottom())),
                    };

                    if (geomEffect)
                        geomEffect->DrawQuad(renderer, points, color, clippingRect, glyph->GetTexture());
                    else
                        renderer->DrawQuad(points, color, clippingRect, glyph->GetTexture());
                }
                renderer->EndBatch();
            }
        };

        TypingContext context(fontString, bounds.Width);

        if (fontString.GetFont()->GetShadowSize() > 0)
        {
            Color shadowColor = fontString.GetFont()->GetShadowColor();
            shadowColor.A = static_cast<byte>(static_cast<float>(shadowColor.A) * GetCurrentOpacity());
            DrawGlyphs::Do(currentGeomEffect, context, renderer, bounds, clippedBounds, fontString.GetShadowGlyphs(), shadowColor, fontString.GetFont()->GetShadowOffset());
            context.Reset();
        }

        if (fontString.GetFont()->GetStrokeSize() > 0.0f)
        {
            Color strokeColor = fontString.GetFont()->GetStrokeColor();
            strokeColor.A = static_cast<byte>(static_cast<float>(strokeColor.A) * GetCurrentOpacity());
            DrawGlyphs::Do(currentGeomEffect, context, renderer, bounds, clippedBounds, fontString.GetStrokedGlyphs(), strokeColor, Vector2::Zero);
            context.Reset();
        }

        Color color = fontString.GetFont()->GetColor();
        color.A = static_cast<byte>(static_cast<float>(color.A) * GetCurrentOpacity());
        DrawGlyphs::Do(currentGeomEffect, context, renderer, bounds, clippedBounds, fontString.GetRegularGlyphs(), color, Vector2::Zero);
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
            Vector2(cm(bounds.GetLeft()),  cm(bounds.GetTop())),
            Vector2(cm(bounds.GetRight()), cm(bounds.GetTop())),
            Vector2(cm(bounds.GetRight()), cm(bounds.GetBottom())),
            Vector2(cm(bounds.GetLeft()),  cm(bounds.GetBottom())),
            Vector2(cm(bounds.GetLeft()),  cm(bounds.GetTop()))
        };

        color.A = static_cast<byte>(static_cast<float>(color.A) * GetCurrentOpacity());
        if (currentGeomEffect)
            currentGeomEffect->DrawLines(renderer, sizeof(p) / sizeof(p[0]), p, color);
        else
            renderer->DrawLines(sizeof(p) / sizeof(p[0]), p, color);
    }

    void UIDrawingContext::DrawCircle(Vector2 center, float radius, Color color)
    {
        DrawEllipse(center, radius, radius, color);
    }

    void UIDrawingContext::DrawEllipse(const RectF& bounds, Color color)
    {
        DrawEllipse(bounds.GetCenterPoint(),
                    bounds.Width * 0.5f,
                    bounds.Height * 0.5f,
                    color);
    }

    void UIDrawingContext::DrawEllipse(Vector2 center, float xRadius, float yRadius, Color color)
    {
        center = cm(center);

        int count = 32;
        Vector2* p = BBStackAlloc(Vector2, count + 1);

        float r = 0.0f;
        const float increment = Math::TwoPi / static_cast<float>(count);
        for (int i = 0; i < count; i++, r += increment)
        {
            p[i] = Vector2(center.X + (xRadius * Math::Sin(r)),
                           center.Y + (yRadius * Math::Cos(r)));
        }

        p[count] = p[0];

        color.A = static_cast<byte>(static_cast<float>(color.A) * GetCurrentOpacity());
        if (currentGeomEffect)
            currentGeomEffect->DrawLines(renderer, count + 1, p, color);
        else
            renderer->DrawLines(count + 1, p, color);

        BBStackFree(p);
    }

    void UIDrawingContext::DrawRoundedRect(RectF bounds, float radius, Color color)
    {
        DrawRoundedRect(bounds, radius, radius, radius, radius, color);
    }

    void UIDrawingContext::DrawRoundedRect(RectF bounds, float leftTopRadius, float rightTopRadius, float leftBottomRadius, float rightBottomRadius, Color color)
    {
        bounds.X = cm(bounds.X);
        bounds.Y = cm(bounds.Y);

        const float maxRadius = Math::Min(bounds.Width, bounds.Height) * 0.5f;
        leftTopRadius = Math::Clamp(leftTopRadius, 0.0f, maxRadius);
        rightTopRadius = Math::Clamp(rightTopRadius, 0.0f, maxRadius);
        leftBottomRadius = Math::Clamp(leftBottomRadius, 0.0f, maxRadius);
        rightBottomRadius = Math::Clamp(rightBottomRadius, 0.0f, maxRadius);

        struct Rotator
        {
            float r;
            float increment;
            int count;

            Rotator(float r, int count)
                : r(r),
                  increment(-Math::PiOver2 / static_cast<float>(count)),
                  count(count)
            {
            }

            Vector2* Rotate(Vector2* p, Vector2 center, float radius)
            {
                for (int i = 0; i < count; i++, r += increment)
                {
                    (*p++) = Vector2(center.X + (radius * Math::Sin(r)),
                                     center.Y + (radius * Math::Cos(r)));
                }

                return p;
            }
        };

        Rotator rotator(Math::Pi, 8);

        int count = 8 * 4 + 6;
        Vector2* p = BBStackAlloc(Vector2, count);

        Vector2* current = p;

        (*current++) = bounds.GetLeftTop() + Vector2(leftTopRadius, 0.0f);
        (*current++) = bounds.GetRightTop() - Vector2(rightTopRadius, 0.0f);

        current = rotator.Rotate(current,
                                 bounds.GetRightTop() + Vector2(-rightTopRadius, +rightTopRadius),
                                 rightTopRadius);

        (*current++) = bounds.GetRightBottom() - Vector2(0.0f, rightBottomRadius);

        current = rotator.Rotate(current,
                                 bounds.GetRightBottom() + Vector2(-rightBottomRadius, -rightBottomRadius),
                                 rightBottomRadius);

        (*current++) = bounds.GetLeftBottom() + Vector2(leftBottomRadius, 0.0f);

        current = rotator.Rotate(current,
                                 bounds.GetLeftBottom() + Vector2(+leftBottomRadius, -leftBottomRadius),
                                 leftBottomRadius);

        (*current++) = bounds.GetLeftTop() + Vector2(0.0f, leftTopRadius);

        current = rotator.Rotate(current,
                                 bounds.GetLeftTop() + Vector2(+leftTopRadius, +leftTopRadius),
                                 leftTopRadius);

        (*current++) = (*p);

        BBAssert(static_cast<int>(current - p) == count);

        color.A = static_cast<byte>(static_cast<float>(color.A) * GetCurrentOpacity());
        if (currentGeomEffect)
            currentGeomEffect->DrawLines(renderer, current - p, p, color);
        else
            renderer->DrawLines(current - p, p, color);

        BBStackFree(p);
    }

    void UIDrawingContext::DrawDebugLine(Vector2 p0, Vector2 p1, Color color)
    {
        Vector2 p[] = { p0, p1 };
        color.A = static_cast<byte>(static_cast<float>(color.A) * GetCurrentOpacity());
        if (currentGeomEffect)
            currentGeomEffect->DrawDebugLines(renderer, sizeof(p) / sizeof(p[0]), p, color);
        else
            renderer->DrawDebugLines(sizeof(p) / sizeof(p[0]), p, color);
    }

    void UIDrawingContext::DrawDebugLines(int count, Vector2* p, Color color)
    {
        if (count <= 1)
            return;

        color.A = static_cast<byte>(static_cast<float>(color.A) * GetCurrentOpacity());
        if (currentGeomEffect)
            currentGeomEffect->DrawDebugLines(renderer, count, p, color);
        else
            renderer->DrawDebugLines(count, p, color);
    }

    void UIDrawingContext::DrawDebugRect(const RectF& bounds, Color color)
    {
        Vector2 p[] =
        {
            Vector2(cm(bounds.GetLeft()),  cm(bounds.GetTop())),
            Vector2(cm(bounds.GetRight()), cm(bounds.GetTop())),
            Vector2(cm(bounds.GetRight()), cm(bounds.GetBottom())),
            Vector2(cm(bounds.GetLeft()),  cm(bounds.GetBottom())),
            Vector2(cm(bounds.GetLeft()),  cm(bounds.GetTop()))
        };

        color.A = static_cast<byte>(static_cast<float>(color.A) * GetCurrentOpacity());
        if (currentGeomEffect)
            currentGeomEffect->DrawDebugLines(renderer, sizeof(p) / sizeof(p[0]), p, color);
        else
            renderer->DrawDebugLines(sizeof(p) / sizeof(p[0]), p, color);
    }

    void UIDrawingContext::FillRect(const RectF& bounds, Color color)
    {
        Vector2 p[] = 
        {
            Vector2(cm(bounds.GetLeft()),  cm(bounds.GetTop())),
            Vector2(cm(bounds.GetRight()), cm(bounds.GetTop())),
            Vector2(cm(bounds.GetLeft()),  cm(bounds.GetBottom())),

            Vector2(cm(bounds.GetLeft()),  cm(bounds.GetBottom())),
            Vector2(cm(bounds.GetRight()), cm(bounds.GetTop())),
            Vector2(cm(bounds.GetRight()), cm(bounds.GetBottom())),
        };
        
        color.A = static_cast<byte>(static_cast<float>(color.A) * GetCurrentOpacity());
        if (currentGeomEffect)
            currentGeomEffect->DrawTriangles(renderer, sizeof(p) / sizeof(p[0]), p, color);
        else
            renderer->DrawTriangles(sizeof(p) / sizeof(p[0]), p, color);
    }

    void UIDrawingContext::FillCircle(Vector2 center, float radius, Color color)
    {
        FillEllipse(center, radius, radius, color);
    }

    void UIDrawingContext::FillEllipse(const RectF& bounds, Color color)
    {
        FillEllipse(bounds.GetCenterPoint(),
                    bounds.Width * 0.5f,
                    bounds.Height * 0.5f,
                    color);
    }

    void UIDrawingContext::FillEllipse(Vector2 center, float xRadius, float yRadius, Color color)
    {
        center = cm(center);

        int count = 32 * 3;
        Vector2* p = BBStackAlloc(Vector2, count);

        float r = 0.0f;
        const float increment = Math::TwoPi / static_cast<float>(count / 3);
        for (int i = 0; i < count; i += 3, r += increment)
        {
            p[i + 0] = center;
            p[i + 1] = Vector2(center.X + (xRadius * Math::Sin(r + increment)),
                               center.Y + (yRadius * Math::Cos(r + increment)));
            p[i + 2] = Vector2(center.X + (xRadius * Math::Sin(r)),
                               center.Y + (yRadius * Math::Cos(r)));
        }

        color.A = static_cast<byte>(static_cast<float>(color.A) * GetCurrentOpacity());
        if (currentGeomEffect)
            currentGeomEffect->DrawTriangles(renderer, count, p, color);
        else
            renderer->DrawTriangles(count, p, color);

        BBStackFree(p);
    }

    void UIDrawingContext::FillRoundedRect(RectF bounds, float radius, Color color)
    {
        FillRoundedRect(bounds, radius, radius, radius, radius, color);
    }

    void UIDrawingContext::FillRoundedRect(RectF bounds, float leftTopRadius, float rightTopRadius, float leftBottomRadius, float rightBottomRadius, Color color)
    {
        bounds.X = cm(bounds.X);
        bounds.Y = cm(bounds.Y);

        const Vector2 boundsCenter = bounds.GetCenterPoint();

        const float maxRadius = Math::Min(bounds.Width, bounds.Height) * 0.5f;
        leftTopRadius = Math::Clamp(leftTopRadius, 0.0f, maxRadius);
        rightTopRadius = Math::Clamp(rightTopRadius, 0.0f, maxRadius);
        leftBottomRadius = Math::Clamp(leftBottomRadius, 0.0f, maxRadius);
        rightBottomRadius = Math::Clamp(rightBottomRadius, 0.0f, maxRadius);

        struct Rotator
        {
            float r;
            float increment;
            int count;
            Vector2 boundsCenter;

            Rotator(float r, int count, Vector2 boundsCenter)
                : r(r),
                  increment(-Math::PiOver2 / static_cast<float>(count)),
                  count(count),
                  boundsCenter(boundsCenter)
            {
            }

            Vector2* Rotate(Vector2* p, Vector2 center, float radius)
            {
                for (int i = 0; i < count; i++, r += increment)
                {
                    (*p++) = boundsCenter;
                    (*p++) = Vector2(center.X + (radius * Math::Sin(r)),
                                     center.Y + (radius * Math::Cos(r)));
                    (*p++) = Vector2(center.X + (radius * Math::Sin(r + increment)),
                                     center.Y + (radius * Math::Cos(r + increment)));
                }

                return p;
            }
        };

        Rotator rotator(Math::Pi, 8, boundsCenter);

        int count = (8 * 4 + 4) * 3;
        Vector2* p = BBStackAlloc(Vector2, count);

        Vector2* current = p;

        (*current++) = boundsCenter;
        (*current++) = bounds.GetLeftTop() + Vector2(leftTopRadius, 0.0f);
        (*current++) = bounds.GetRightTop() - Vector2(rightTopRadius, 0.0f);

        current = rotator.Rotate(current,
                                 bounds.GetRightTop() + Vector2(-rightTopRadius, +rightTopRadius),
                                 rightTopRadius);

        (*current++) = boundsCenter;
        (*current++) = bounds.GetRightTop() + Vector2(0.0f, rightTopRadius);
        (*current++) = bounds.GetRightBottom() - Vector2(0.0f, rightBottomRadius);

        current = rotator.Rotate(current,
                                 bounds.GetRightBottom() + Vector2(-rightBottomRadius, -rightBottomRadius),
                                 rightBottomRadius);

        (*current++) = boundsCenter;
        (*current++) = bounds.GetRightBottom() - Vector2(rightBottomRadius, 0.0f);
        (*current++) = bounds.GetLeftBottom() + Vector2(leftBottomRadius, 0.0f);

        current = rotator.Rotate(current,
                                 bounds.GetLeftBottom() + Vector2(+leftBottomRadius, -leftBottomRadius),
                                 leftBottomRadius);

        (*current++) = boundsCenter;
        (*current++) = bounds.GetLeftBottom() - Vector2(0.0f, leftBottomRadius);
        (*current++) = bounds.GetLeftTop() + Vector2(0.0f, leftTopRadius);

        current = rotator.Rotate(current,
                                 bounds.GetLeftTop() + Vector2(+leftTopRadius, +leftTopRadius),
                                 leftTopRadius);

        BBAssert(static_cast<int>(current - p) == count);

        color.A = static_cast<byte>(static_cast<float>(color.A) * GetCurrentOpacity());
        if (currentGeomEffect)
            currentGeomEffect->DrawTriangles(renderer, current - p, p, color);
        else
            renderer->DrawTriangles(current - p, p, color);

        BBStackFree(p);
    }

    void UIDrawingContext::FillTriangles(int count, Vector2* p, Color color)
    {
        color.A = static_cast<byte>(static_cast<float>(color.A) * GetCurrentOpacity());
        if (currentGeomEffect)
            currentGeomEffect->DrawTriangles(renderer, count, p, color);
        else
            renderer->DrawTriangles(count, p, color);
    }

    void UIDrawingContext::FillTriangles(int count, Vector2* p, Vector2* uv, Color* color, Texture2D* texture)
    {
        const float opacity = GetCurrentOpacity();
        for (int i = 0; i < count; i++)
            color[i].A = static_cast<byte>(static_cast<float>(color[i].A) * opacity);

        if (currentGeomEffect)
            currentGeomEffect->DrawTriangles(renderer, count, p, uv, color, texture);
        else
            renderer->DrawTriangles(count, p, uv, color, texture);
    }

    void UIDrawingContext::OnBegan(UIVisual* /*target*/)
    {
    }

    void UIDrawingContext::OnEnded(UIVisual* /*target*/)
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