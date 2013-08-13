#include <Bibim/Config.h>
#include <Bibim/Glyph.h>
#include <Bibim/GlyphSurface.h>
#include <Bibim/Texture2D.h>

namespace Bibim
{
    Glyph::Glyph(int code, Vector2 advance)
        : code(code),
          advance(advance),
          bitmapOffset(Vector2::Zero),
          bitmapSize(Vector2::Zero),
          surface(nullptr)
    {
    }

    Glyph::Glyph(int code, Vector2 advance, Vector2 bitmapOffset, Vector2 bitmapSize, GlyphSurface* surface, GlyphSurface::Slot slot)
        : code(code),
          advance(advance),
          bitmapOffset(bitmapOffset),
          bitmapSize(bitmapSize),
          surface(surface),
          slot(slot)
    {
    }

    Glyph::~Glyph()
    {
        if (surface)
            surface->Deallocate(slot);
    }
}