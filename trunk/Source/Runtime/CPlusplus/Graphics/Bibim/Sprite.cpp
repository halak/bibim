#include <Bibim/PCH.h>
#include <Bibim/Sprite.h>
#include <Bibim/Texture2D.h>

namespace Bibim
{
    Sprite::Sprite()
        : texture(),
          clippingRectangle(Rectangle::Empty),
          origin(Vector2::Zero)
    {
    }

    Sprite::Sprite(Texture2DPtr texture)
        : texture(texture),
          clippingRectangle(0, 0, texture->GetWidth(), texture->GetHeight()),
          origin(Vector2::Zero)
    {
    }

    Sprite::Sprite(Texture2DPtr texture, const Rectangle& clippingRectangle)
        : texture(texture),
          clippingRectangle(clippingRectangle),
          origin(Vector2::Zero)
    {
    }

    Sprite::Sprite(Texture2DPtr texture, Vector2 origin)
        : texture(texture),
          clippingRectangle(0, 0, texture->GetWidth(), texture->GetHeight()),
          origin(origin)
    {
    }

    Sprite::Sprite(Texture2DPtr texture, const Rectangle& clippingRectangle, Vector2 origin)
        : texture(texture),
          clippingRectangle(clippingRectangle),
          origin(origin)
    {
    }

    Sprite::Sprite(const Sprite& original)
        : texture(original.texture),
          clippingRectangle(original.clippingRectangle),
          origin(original.origin)              
    {
    }

    Sprite& Sprite::operator = (const Sprite& original)
    {
        texture = original.texture;
        clippingRectangle = original.clippingRectangle;
        origin = original.origin;
        return *this;
    }
                
    bool Sprite::operator == (const Sprite& right) const
    {
        return (texture == right.texture && 
                clippingRectangle == right.clippingRectangle && 
                origin == right.origin);
    }

    bool Sprite::operator != (const Sprite& right) const
    {
        return !operator == (right);
    }
}