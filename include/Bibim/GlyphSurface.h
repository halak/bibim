#pragma once
#ifndef __BIBIM_GLYPHSURFACE_H__
#define __BIBIM_GLYPHSURFACE_H__

#include <Bibim/FWD.h>
#include <Bibim/Rect.h>
#include <Bibim/DynamicTexture2D.h>

namespace Bibim
{
    class GlyphSurface
    {
        public:
            Rect Allocate(const void* buffer, int width, int height, int pitch);
            void Deallocate(const Rect& Rect);

            inline const RectStorage& GetStorage() const;
            inline Texture2D* GetTexture() const;

        private:
            GlyphSurface(GraphicsDevice* graphicsDevice, int width, int height);
            ~GlyphSurface();

        private:
            RectStorage* storage;
            DynamicTexture2DPtr texture;

            friend class GlyphTable;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    const RectStorage& GlyphSurface::GetStorage() const
    {
        return *storage;
    }

    Texture2D* GlyphSurface::GetTexture() const
    {
        return StaticCast<Texture2D>(texture);
    }
}

#endif  