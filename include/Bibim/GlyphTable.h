#pragma once
#ifndef __BIBIM_GLYPHTABLE_H__
#define __BIBIM_GLYPHTABLE_H__

#include <Bibim/FWD.h>
#include <Bibim/GlyphSurface.h>
#include <Bibim/Point2.h>
#include <Bibim/Vector2.h>
#include <map>
#include <vector>

namespace Bibim
{
    class GlyphTable
    {
        public:
            typedef std::map<int, const Glyph*> GlyphDictionary;

        public:
            GlyphTable();
            ~GlyphTable();

            const Glyph* Add(int code, Vector2 advance);
            const Glyph* Add(int code, Vector2 advance, Vector2 bitmapOffset, Vector2 bitmapSize, GlyphSurface* surface, GlyphSurface::Slot slot);

            bool Remove(int code);
            void Clear();

            const Glyph* Find(int code) const;

            inline const GlyphDictionary& GetGlyphs() const;

        private:
            inline const Glyph* Add(int code, const Glyph* glyph);

        private:
            GlyphDictionary glyphs;

        private:
            GlyphTable(const GlyphTable&);
            GlyphTable& operator = (const GlyphTable&);
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    const GlyphTable::GlyphDictionary& GlyphTable::GetGlyphs() const
    {
        return glyphs;
    }
}

#endif