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
                int Depth;
                Rect ClippingRect;

                inline Slot();
                inline Slot(int depth, Rect clippingRect);
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
            Slot Allocate(int depth, int component, const void* buffer, int width, int height, int pitch);

        private:
            GlyphSurface(GraphicsDevice* graphicsDevice, int width, int height);
            ~GlyphSurface();

        private:
            RectStorage storages[4];
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
        : Depth(0),
          ClippingRect(Rect::Empty)
    {
    }

    GlyphSurface::Slot::Slot(int depth, Rect clippingRect)
        : Depth(depth),
          ClippingRect(clippingRect)
    {
    }

    GlyphSurface::Slot::Slot(const Slot& original)
        : Depth(original.Depth),
          ClippingRect(original.ClippingRect)
    {
    }

    GlyphSurface::Slot& GlyphSurface::Slot::operator = (const Slot& right)
    {
        Depth = right.Depth;
        ClippingRect = right.ClippingRect;
        return *this;
    }

    bool GlyphSurface::Slot::operator == (const Slot& right) const
    {
        return Depth == right.Depth && ClippingRect == right.ClippingRect;
    }

    bool GlyphSurface::Slot::operator != (const Slot& right) const
    {
        return !operator == (right);
    }
}

#endif  