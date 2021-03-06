﻿#include <Bibim/Config.h>
#include <Bibim/FontLibrary.h>
#include <Bibim/Assert.h>
#include <Bibim/Font.h>
#include <Bibim/FontCache.h>
#include <vector>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace Bibim
{
    FontLibrary::FontLibrary(GraphicsDevice* graphicsDevice)
        : graphicsDevice(graphicsDevice),
          assetStorage(nullptr),
          ftLibrary(nullptr),
          globalScale(1.0f)
    {
        Construct();

        if (GetGraphicsDevice())
            GetGraphicsDevice()->AddLostEventListener(this);
    }

    FontLibrary::~FontLibrary()
    {
        caches.clear();
        FT_Done_FreeType(static_cast<FT_Library>(ftLibrary));

        if (GetGraphicsDevice())
            GetGraphicsDevice()->RemoveLostEventListener(this);
    }

    void FontLibrary::CollectGarbage()
    {
        for (CacheCollection::iterator it = caches.begin(); it != caches.end();)
        {
            if ((*it).second.GetReferenceCount() == 1)
                it = caches.erase(it);
            else
                ++it;
        }
    }

    FontCache* FontLibrary::GetCache(const FontCacheParameters& parameters)
    {
        const unsigned int hashCode = parameters.GetHashCode();
        for (CacheCollection::iterator it = caches.begin(); it != caches.end(); ++it)
        {
            if ((*it).first == hashCode &&
                (*it).second->GetParameters() == parameters)
                return (*it).second;
        }

        caches.push_back(CachePair(hashCode, new FontCache(this, parameters)));
        return caches.back().second;
    }

    void FontLibrary::SetGlobalScale(float value)
    {
        globalScale = value;
        for (FontCollection::iterator it = fonts.begin(); it != fonts.end(); ++it)
            (*it)->SetScale(value);
    }

    void FontLibrary::Construct()
    {
        FT_Library library = nullptr;
        FT_Init_FreeType(&library);
        ftLibrary = static_cast<void*>(library);
    }

    void FontLibrary::Add(Font* font)
    {
        fonts.insert(font);
        font->SetScale(globalScale);
    }

    void FontLibrary::Remove(Font* font)
    {
        fonts.erase(font);
    }

    void FontLibrary::OnGraphicsDeviceLost(GraphicsDeviceBase* g)
    {
        BBAssert(GetGraphicsDevice() == g);

        for (FontCollection::iterator it = fonts.begin(); it != fonts.end(); ++it)
            (*it)->IncreaseRevision();
        
        for (CacheCollection::iterator it = caches.begin(); it != caches.end(); ++it)
            (*it).second->Clear();
    }
}