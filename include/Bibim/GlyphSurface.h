#pragma once
#ifndef __BIBIM_GLYPHSURFACE_H__
#define __BIBIM_GLYPHSURFACE_H__

#include <Bibim/FWD.h>
#include <Bibim/Rect.h>
#include <Bibim/DynamicTexture2D.h>
#include <Bibim/RectStorage.h>

namespace Bibim
{
    class GlyphSurface
    {
        public:
            struct Slot
            {
                Rect ClippingRect;

                inline Slot();
                inline explicit Slot(Rect clippingRect);
                inline Slot(const Slot& original);

                inline Slot& operator = (const Slot& right);
                inline bool operator == (const Slot& right) const;
                inline bool operator != (const Slot& right) const;
            };

        public:
            Slot Allocate(const void* buffer, int width, int height, int pitch);
            void Deallocate(const Slot& Rect);

            inline Texture2D* GetTexture() const;

        private:
            GlyphSurface(GraphicsDevice* graphicsDevice, int width, int height);
            ~GlyphSurface();

        private:
            RectStorage storage;
            DynamicTexture2DPtr texture;

            friend class FontCache;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    Texture2D* GlyphSurface::GetTexture() const
    {
        return StaticCast<Texture2D>(texture);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    GlyphSurface::Slot::Slot()
        : ClippingRect(Rect::Empty)
    {
    }

    GlyphSurface::Slot::Slot(Rect clippingRect)
        : ClippingRect(clippingRect)
    {
    }

    GlyphSurface::Slot::Slot(const Slot& original)
        : ClippingRect(original.ClippingRect)
    {
    }

    GlyphSurface::Slot& GlyphSurface::Slot::operator = (const Slot& right)
    {
        ClippingRect = right.ClippingRect;
        return *this;
    }

    bool GlyphSurface::Slot::operator == (const Slot& right) const
    {
        return ClippingRect == right.ClippingRect;
    }

    bool GlyphSurface::Slot::operator != (const Slot& right) const
    {
        return !operator == (right);
    }
}

#endif  