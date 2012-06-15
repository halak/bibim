#include <Bibim/PCH.h>
#include <Bibim/FontLibrary.h>
#include <Bibim/FontCache.h>
#include <vector>
#include <windows.h>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace Bibim
{
    FontLibrary::FontLibrary()
        : graphicsDevice(nullptr),
          ftLibrary(nullptr)
    {
        Construct();
    }

    FontLibrary::FontLibrary(GraphicsDevice* graphicsDevice)
        : graphicsDevice(graphicsDevice),
          ftLibrary(nullptr)
    {
        Construct();
    }

    FontLibrary::~FontLibrary()
    {
        caches.clear();
        FT_Done_FreeType(static_cast<FT_Library>(ftLibrary));
    }

    FontCache* FontLibrary::GetCache(const FontCacheParameters& parameters)
    {
        const unsigned int hashCode = parameters.GetHashCode();
        for (CacheCollection::iterator it = caches.begin(); it != caches.end(); it++)
        {
            if ((*it).first == hashCode &&
                (*it).second->GetParameters() == parameters)
                return (*it).second;
        }

        caches.push_back(CachePair(hashCode, new FontCache(this, parameters)));
        return caches.back().second;
    }

    void FontLibrary::Construct()
    {
        FT_Library library = nullptr;
        FT_Init_FreeType(&library);
        ftLibrary = static_cast<void*>(library);

        // TODO: 글꼴 폴더 / 기본 글꼴
        std::vector<char> windowsDirectory;
        windowsDirectory.resize(GetWindowsDirectory(nullptr, 0) + 1, '\0');
        GetWindowsDirectory(&windowsDirectory[0], windowsDirectory.size());
        osFontDirectory = &windowsDirectory[0];
        osFontDirectory += "\\Fonts\\";

        alternativeFace = osFontDirectory + "gulim.ttc";
    }
}