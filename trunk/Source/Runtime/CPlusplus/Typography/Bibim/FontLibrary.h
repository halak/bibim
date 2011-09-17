#pragma once
#ifndef __BIBIM_FONTLIBRARY_H__
#define __BIBIM_FONTLIBRARY_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameModule.h>
#   include <Bibim/String.h>
#   include <vector>

    namespace Bibim
    {
        class FontLibrary : public GameModule
        {
            BBGameModuleClass('F', 'T', 'L', 'B');
            public:
                typedef std::pair<unsigned int, FontCachePtr> CachePair;
                typedef std::vector<CachePair> CacheCollection;

            public:
                FontLibrary();
                FontLibrary(GraphicsDevice* graphicsDevice);
                virtual ~FontLibrary();

                inline GraphicsDevice* GetGraphicsDevice() const;
                void SetGraphicsDevice(GraphicsDevice* value);

                inline const String& GetOSFontDirectory() const;

                inline const String& GetAlternativeFace() const;

                FontCache* GetCache(const FontCacheParameters& parameters);

                // ResultType: FT_Library
                inline void* GetFTLibrary() const;

            private:
                void Construct();

            private:
                GraphicsDevice* graphicsDevice;
                String osFontDirectory;
                String alternativeFace;
                CacheCollection caches;
                void* ftLibrary;
        };
    }

#   include <Bibim/FontLibrary.inl>

#endif