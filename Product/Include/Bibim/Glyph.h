#pragma once
#ifndef __BIBIM_GLYPH_H__
#define __BIBIM_GLYPH_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Rect.h>
#   include <Bibim/Vector2.h>

    namespace Bibim
    {
        class Glyph
        {
            BBThisIsNoncopyableClass(Glyph);
            public:
                inline int GetCode() const;
                inline Vector2 GetAdvance() const;
                inline Vector2 GetBitmapOffset() const;
                inline Vector2 GetBitmapSize() const;
                inline GlyphSurface* GetSurface() const;
                inline Texture2D* GetTexture() const;
                inline Rect GetClippingRect() const;

            private:
                Glyph(int code, Vector2 advance);
                Glyph(int code, Vector2 advance, Vector2 bitmapOffset, Vector2 bitmapSize, GlyphSurface* surface, Rect clippingRect);
                ~Glyph();

            private:
                int code;
                Vector2 advance;
                Vector2 bitmapOffset;
                Vector2 bitmapSize;
                GlyphSurface* surface;
                Texture2DPtr texture;
                Rect clippingRect;

                friend class GlyphTable;
        };
    }

#   include <Bibim/Glyph.inl>

#endif