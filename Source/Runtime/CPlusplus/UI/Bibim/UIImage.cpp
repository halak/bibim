#include <Bibim/PCH.h>
#include <Bibim/UIImage.h>
#include <Bibim/Texture2D.h>

namespace Bibim
{
    UIImage::UIImage(const URI& textureURI, const Rectangle& clippingRectangle)
        : textureURI(textureURI),
          clippingRectangle(clippingRectangle),
          revision(1)
    {
    }

    UIImage::~UIImage()
    {
    }

    void UIImage::SetRealTextureData(Texture2D* texture)
    {
        if (realTexture != texture || realClippingRectangle != clippingRectangle)
        {
            realTexture = texture;
            
            if (texture)
            {
                realClippingRectangle = Rectangle(0, 0, texture->GetWidth(), texture->GetHeight());
                normalizedRealClippingRectangle = RectangleF(0.0f, 0.0f, 1.0f, 1.0f);
            }
            else
            {
                realClippingRectangle = Rectangle::Empty;
                normalizedRealClippingRectangle = RectangleF::Empty;
            }

            revision++;
        }
    }

    void UIImage::SetRealTextureData(Texture2D* texture, const Rectangle& clippingRectangle)
    {
        if (realTexture != texture || realClippingRectangle != clippingRectangle)
        {
            realTexture = texture;
            realClippingRectangle = clippingRectangle;
            
            if (texture)
            {
                const float textureWidth  = static_cast<float>(texture->GetWidth());
                const float textureHeight = static_cast<float>(texture->GetHeight());
                const float left   = static_cast<float>(clippingRectangle.GetLeft()) / textureWidth;
                const float top    = static_cast<float>(clippingRectangle.GetTop()) / textureHeight;
                const float right  = static_cast<float>(clippingRectangle.GetRight()) / textureWidth;
                const float bottom = static_cast<float>(clippingRectangle.GetBottom()) / textureHeight;
                normalizedRealClippingRectangle = RectangleF(left, top, right - left, bottom - top);
            }
            else
                normalizedRealClippingRectangle = RectangleF::Empty;

            revision++;
        }
    }
}