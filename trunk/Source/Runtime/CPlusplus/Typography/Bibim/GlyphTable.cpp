﻿#include <Bibim/PCH.h>
#include <Bibim/GlyphTable.h>
#include <Bibim/Assert.h>
#include <Bibim/Glyph.h>
#include <Bibim/GlyphSurface.h>
#include <Bibim/Math.h>

namespace Bibim
{
    GlyphTable::GlyphTable(GraphicsDevice* graphicsDevice)
        : graphicsDevice(graphicsDevice)
    {
        glyphs.insert(GlyphDictionary::value_type('\0', new Glyph('\0', Vector2(1.0f, 0.0f))));
        glyphs.insert(GlyphDictionary::value_type('\r', new Glyph('\r', Vector2(1.0f, 0.0f))));
        glyphs.insert(GlyphDictionary::value_type('\n', new Glyph('\n', Vector2(1.0f, 0.0f))));
    }

    GlyphTable::~GlyphTable()
    {
        Clear();
    }

    const Glyph* GlyphTable::Add(int code, Vector2 advance, Vector2 bitmapOffset, Vector2 bitmapSize, const void* buffer, int width, int height, int pitch)
    {
        std::pair<GlyphSurface*, Rect> allocated = AllocateSurface(buffer, width, height, pitch);
        Glyph* newGlyph = nullptr;
        if (allocated.first)
            newGlyph = new Glyph(code, advance, bitmapOffset, bitmapSize, allocated.first, allocated.second);
        else
            newGlyph = new Glyph(code, advance);

        GlyphDictionary::iterator it = glyphs.find(code);
        if (it != glyphs.end())
        {
            const Glyph* oldGlyph = (*it).second;
            (*it).second = newGlyph;
            delete oldGlyph;
        }
        else
        {
            if (glyphs.insert(GlyphDictionary::value_type(code, newGlyph)).second == false)
            {
                delete newGlyph;
                newGlyph = nullptr;
            }
        }

        return newGlyph;
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

        SurfaceCollection deletingSurfaces;
        deletingSurfaces.swap(surfaces);

        for (SurfaceCollection::iterator it = deletingSurfaces.begin(); it != deletingSurfaces.end(); it++)
            delete (*it);
    }

    const Glyph* GlyphTable::Find(int code) const
    {
        GlyphDictionary::const_iterator it = glyphs.find(code);
        if (it != glyphs.end())
            return (*it).second;
        else
            return nullptr;
    }

    std::pair<GlyphSurface*, Rect> GlyphTable::AllocateSurface(const void* buffer, int width, int height, int pitch)
    {
        if (buffer == nullptr || width <= 0 || height <= 0)
            return std::pair<GlyphSurface*, Rect>(nullptr, Rect::Empty);

        for (SurfaceCollection::iterator it = surfaces.begin(); it != surfaces.end(); ++it)
        {
            Rect allocated = (*it)->Allocate(buffer, width, height, pitch);
            if (allocated != Rect::Empty)
                return std::pair<GlyphSurface*, Rect>(*it, allocated);
        }

        const Point2 surfaceSize = GetAdaptiveSurfaceSize(surfaces.size(), width, height);
        BBAssert(surfaceSize != Point2::Zero);

        GlyphSurface* glyphSurface = new GlyphSurface(graphicsDevice, surfaceSize.X, surfaceSize.Y);
        Rect allocated = glyphSurface->Allocate(buffer, width, height, pitch);
        BBAssert(allocated != Rect::Empty);

        surfaces.push_back(glyphSurface);

        return std::pair<GlyphSurface*, Rect>(glyphSurface, allocated);
    }

    Point2 GlyphTable::GetAdaptiveSurfaceSize(int numberOfExisting, int width, int height)
    {
        static const Point2 textureSizes[] =
        {
            Point2(128, 128),
            Point2(256, 256),
            Point2(256, 256),
            Point2(512, 512),
            Point2(512, 512),
            Point2(1024, 512),
            Point2(1024, 1024)
        };
        static const int lastTextureSizeIndex = sizeof(textureSizes) / sizeof(textureSizes[0]) - 1;

        const int   index = Math::Min(numberOfExisting, lastTextureSizeIndex);
        const Point2 selectedSize = textureSizes[index];
        if (selectedSize.X >= width && selectedSize.Y >= height)
            return selectedSize;
        else
        {
            // 만약 할당하려는 텍스쳐의 크기가 글리프 크기보다 작으면,
            // 다음 텍스쳐의 크기를 할당한다. 만약 최고 텍스쳐 크기보다 크다면 Point2::Zero를 반환한다. (예외 상황임)
            if (numberOfExisting < lastTextureSizeIndex)
                return GetAdaptiveSurfaceSize(numberOfExisting + 1, width, height);
            else
                return Point2::Zero;
        }
    }
}