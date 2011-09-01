#pragma once
#ifndef __BIBIM_SPRITE_INL__
#define __BIBIM_SPRITE_INL__

    namespace Bibim
    {
        Texture2DPtr Sprite::GetTexture() const
        {
            return texture;
        }

        const Rectangle& Sprite::GetClippingRectangle() const
        {
            return clippingRectangle;
        }

        Vector2 Sprite::GetOrigin() const
        {
            return origin;
        }
    }

#endif