#pragma once
#ifndef __BIBIM_SPRITE_H__
#define __BIBIM_SPRITE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Rectangle.h>
#   include <Bibim/Vector2.h>

    namespace Bibim
    {
        class Sprite
        {
            public:
                Sprite();
                Sprite(Texture2DPtr texture);
                Sprite(Texture2DPtr texture, const Rectangle& clippingRectangle);
                Sprite(Texture2DPtr texture, const Rectangle& clippingRectangle, Vector2 origin);
                Sprite(Texture2DPtr texture, Vector2 origin);
                Sprite(const Sprite& original);

                inline Texture2DPtr GetTexture() const;
                inline const Rectangle& GetClippingRectangle() const;
                inline Vector2 GetOrigin() const;

                Sprite& operator = (const Sprite& original);
                
                bool operator == (const Sprite& right) const;
                bool operator != (const Sprite& right) const;

            private:
                Texture2DPtr texture;
                Rectangle clippingRectangle;
                Vector2 origin;
        };
    }

#   include <Bibim/Sprite.inl>

#endif