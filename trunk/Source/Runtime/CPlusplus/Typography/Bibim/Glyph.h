#pragma once
#ifndef __BIBIM_GLYPH_H__
#define __BIBIM_GLYPH_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Rectangle.h>
#   include <Bibim/Vector2.h>

    namespace Bibim
    {
        class Glyph
        {
            public:
                inline uint32 GetCode() const;
                inline Vector2 GetAdvance() const;
                inline Vector2 GetBitmapOffset() const;
                inline Vector2 GetBitmapSize() const;
                inline GlyphSurface* GetSurface() const;
                inline Texture2D* GetTexture() const;
                inline Rectangle GetClippingRectangle() const;

            private:
                Glyph(uint32 code, Vector2 advance);
                Glyph(uint32 code, Vector2 advance, Vector2 bitmapOffset, Vector2 bitmapSize, GlyphSurface* surface, Rectangle clippingRectangle);
                ~Glyph();

            private:
                uint32 code;
                Vector2 advance;
                Vector2 bitmapOffset;
                Vector2 bitmapSize;
                GlyphSurface* surface;
                Texture2DPtr texture;
                Rectangle clippingRectangle;

            private:
                Glyph(const Glyph&);
                Glyph& operator = (const Glyph&);

                friend class GlyphTable;
        };
    }

#   include <Bibim/Glyph.inl>

#endif