#pragma once
#ifndef __BIBIM_GLYPHTABLE_H__
#define __BIBIM_GLYPHTABLE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Point2.h>
#   include <Bibim/Vector2.h>
#   include <map>
#   include <vector>

    namespace Bibim
    {
        class GlyphTable
        {
            public:
                typedef std::map<int, const Glyph*> GlyphDictionary;
                typedef std::vector<GlyphSurface*> SurfaceCollection;

            public:
                GlyphTable(GraphicsDevice* graphicsDevice);
                ~GlyphTable();

                const Glyph* Add(int code, Vector2 advance, Vector2 bitmapOffset, Vector2 bitmapSize, const void* buffer, int width, int height, int pitch);

                bool Remove(int code);

                void Clear();

                const Glyph* Find(int code) const;

                inline const GlyphDictionary& GetGlyphs() const;
                inline const SurfaceCollection& GetSurfaces() const;

            private:
                std::pair<GlyphSurface*, Rect> AllocateSurface(const void* buffer, int width, int height, int pitch);
                static Point2 GetAdaptiveSurfaceSize(int numberOfExisting, int width, int height);

            private:
                GraphicsDevice* graphicsDevice;
                GlyphDictionary glyphs;
                SurfaceCollection surfaces;

            private:
                GlyphTable(const GlyphTable&);
                GlyphTable& operator = (const GlyphTable&);
        };

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        const GlyphTable::GlyphDictionary& GlyphTable::GetGlyphs() const
        {
            return glyphs;
        }

        const GlyphTable::SurfaceCollection& GlyphTable::GetSurfaces() const
        {
            return surfaces;
        }
    }

#endif