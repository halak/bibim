#include <Bibim/PCH.h>
#include <Bibim/UIImage.h>
#include <Bibim/Texture2D.h>

namespace Bibim
{
    UIImage::UIImage(const URI& textureURI, const Rect& clippingRect)
        : textureURI(textureURI),
          clippingRect(clippingRect),
          revision(1)
    {
    }

    UIImage::~UIImage()
    {
    }

    void UIImage::SetRealTextureData(Texture2D* texture)
    {
        if (realTexture != texture || realClippingRect != clippingRect)
        {
            realTexture = texture;
            
            if (texture)
            {
                realClippingRect = Rect(0, 0, texture->GetWidth(), texture->GetHeight());
                normalizedRealClippingRect = RectF(0.0f, 0.0f, 1.0f, 1.0f);
            }
            else
            {
                realClippingRect = Rect::Empty;
                normalizedRealClippingRect = RectF::Empty;
            }

            revision++;
        }
    }

    void UIImage::SetRealTextureData(Texture2D* texture, const Rect& clippingRect)
    {
        if (realTexture != texture || realClippingRect != clippingRect)
        {
            realTexture = texture;
            realClippingRect = clippingRect;
            
            if (texture)
            {
                const float textureWidth  = static_cast<float>(texture->GetWidth());
                const float textureHeight = static_cast<float>(texture->GetHeight());
                const float left   = static_cast<float>(clippingRect.GetLeft()) / textureWidth;
                const float top    = static_cast<float>(clippingRect.GetTop()) / textureHeight;
                const float right  = static_cast<float>(clippingRect.GetRight()) / textureWidth;
                const float bottom = static_cast<float>(clippingRect.GetBottom()) / textureHeight;
                normalizedRealClippingRect = RectF(left, top, right - left, bottom - top);
            }
            else
                normalizedRealClippingRect = RectF::Empty;

            revision++;
        }
    }

    UIElement* UIImage::Create(StreamReader& /*reader*/, UIElement* /*existingInstance*/)
    {
        return nullptr;
    }
}