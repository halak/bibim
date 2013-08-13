#pragma once
#ifndef __BIBIM_GLYPH_H__
#define __BIBIM_GLYPH_H__

#include <Bibim/FWD.h>
#include <Bibim/GlyphSurface.h>
#include <Bibim/Vector2.h>

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
            inline GlyphSurface::Slot GetSlot() const;

        private:
            Glyph(int code, Vector2 advance);
            Glyph(int code, Vector2 advance, Vector2 bitmapOffset, Vector2 bitmapSize, GlyphSurface* surface, GlyphSurface::Slot slot);
            ~Glyph();

        private:
            int code;
            Vector2 advance;
            Vector2 bitmapOffset;
            Vector2 bitmapSize;
            GlyphSurface* surface;
            GlyphSurface::Slot slot;

            friend class GlyphTable;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    int Glyph::GetCode() const
    {
        return code;
    }

    Vector2 Glyph::GetAdvance() const
    {
        return advance;
    }

    Vector2 Glyph::GetBitmapOffset() const
    {
        return bitmapOffset;
    }

    Vector2 Glyph::GetBitmapSize() const
    {
        return bitmapSize;
    }

     GlyphSurface* Glyph::GetSurface() const
     {
         return surface;
     }

    Texture2D* Glyph::GetTexture() const
    {
        return surface ? surface->GetTexture() : nullptr;
    }

    GlyphSurface::Slot Glyph::GetSlot() const
    {
        return slot;
    }
}

#endif