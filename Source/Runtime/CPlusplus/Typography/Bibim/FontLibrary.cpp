#include <Bibim/PCH.h>
#include <Bibim/FontLibrary.h>
#include <Bibim/FontCache.h>
#include <vector>
#include <windows.h>

namespace Bibim
{
    struct FontLibrary::Fields
    {
        FT_Library library;
    };

    FontLibrary::FontLibrary()
        : graphicsDevice(nullptr),
          m(new Fields())
    {
        Construct();
    }

    FontLibrary::FontLibrary(GraphicsDevice* graphicsDevice)
        : graphicsDevice(graphicsDevice),
          m(new Fields())
    {
        Construct();
    }

    FontLibrary::~FontLibrary()
    {
        caches.clear();
        FT_Done_FreeType(m->library);
        delete m;
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

    void* FontLibrary::GetFTLibrary() const
    {
        return static_cast<void*>(m->library);
    }

    void FontLibrary::Construct()
    {
        FT_Init_FreeType(&m->library);

        // TODO: 글꼴 폴더 / 기본 글꼴
        std::vector<char> windowsDirectory;
        windowsDirectory.resize(GetWindowsDirectory(NULL, 0) + 1, '\0');
        GetWindowsDirectory(&windowsDirectory[0], windowsDirectory.size());
        osFontDirectory = &windowsDirectory[0];
        osFontDirectory += "\\Fonts\\";

        alternativeFace = osFontDirectory + "gulim.ttc";
    }
}