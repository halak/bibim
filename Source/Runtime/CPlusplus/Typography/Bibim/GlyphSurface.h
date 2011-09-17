#pragma once
#ifndef __BIBIM_GLYPHSURFACE_H__
#define __BIBIM_GLYPHSURFACE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Rectangle.h>
#   include <Bibim/DynamicTexture2D.h>

    namespace Bibim
    {
        class GlyphSurface
        {
            public:
                Rectangle Allocate(const void* buffer, int width, int height, int pitch);
                void Deallocate(const Rectangle& rectangle);

                inline const RectangleStorage& GetStorage() const;
                inline Texture2D* GetTexture() const;

            private:
                GlyphSurface(GraphicsDevice* graphicsDevice, int width, int height);
                ~GlyphSurface();

            private:
                RectangleStorage* storage;
                DynamicTexture2DPtr texture;

                friend class GlyphTable;
        };
    }

#   include <Bibim/GlyphSurface.inl>

#endif  