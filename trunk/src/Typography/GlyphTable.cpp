#include <Bibim/Config.h>
#include <Bibim/GlyphTable.h>
#include <Bibim/Assert.h>
#include <Bibim/Glyph.h>
#include <Bibim/GlyphSurface.h>
#include <Bibim/Math.h>

namespace Bibim
{
    GlyphTable::GlyphTable()
    {
        glyphs.insert(GlyphDictionary::value_type('\0', new Glyph('\0', Vector2(1.0f, 0.0f))));
        glyphs.insert(GlyphDictionary::value_type('\r', new Glyph('\r', Vector2(1.0f, 0.0f))));
        glyphs.insert(GlyphDictionary::value_type('\n', new Glyph('\n', Vector2(1.0f, 0.0f))));
    }

    GlyphTable::~GlyphTable()
    {
        Clear();
    }

    const Glyph* GlyphTable::Add(int code, const Glyph* glyph)
    {
        GlyphDictionary::iterator it = glyphs.find(code);
        if (it != glyphs.end())
        {
            const Glyph* oldGlyph = (*it).second;
            (*it).second = glyph;
            delete oldGlyph;
        }
        else
        {
            if (glyphs.insert(GlyphDictionary::value_type(code, glyph)).second == false)
            {
                delete glyph;
                glyph = nullptr;
            }
        }

        return glyph;
    }

    const Glyph* GlyphTable::Add(int code, Vector2 advance)
    {
        return Add(code, new Glyph(code, advance));
    }

    const Glyph* GlyphTable::Add(int code, Vector2 advance, Vector2 bitmapOffset, Vector2 bitmapSize, GlyphSurface* surface, GlyphSurface::Slot slot)
    {
        return Add(code, new Glyph(code, advance, bitmapOffset, bitmapSize, surface, slot));
    }

    bool GlyphTable::Remove(int code)
    {
        GlyphDictionary::const_iterator it = glyphs.find(code);
        if (it != glyphs.end())
        {
            const Glyph* glyph = (*it).second;
            glyphs.erase((*it).first);
            delete glyph;
            return true;
        }
        else
            return false;
    }

    void GlyphTable::Clear()
    {
        GlyphDictionary deletingGlyphs;
        deletingGlyphs.swap(glyphs);

        for (GlyphDictionary::iterator it = deletingGlyphs.begin(); it != deletingGlyphs.end(); it++)
            delete (*it).second;
    }

    const Glyph* GlyphTable::Find(int code) const
    {
        GlyphDictionary::const_iterator it = glyphs.find(code);
        if (it != glyphs.end())
            return (*it).second;
        else
            return nullptr;
    }
}