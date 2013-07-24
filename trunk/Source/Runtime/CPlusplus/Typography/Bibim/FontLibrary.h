﻿#pragma once
#ifndef __BIBIM_FONTLIBRARY_H__
#define __BIBIM_FONTLIBRARY_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameModule.h>
#   include <Bibim/GraphicsDevice.h>
#   include <Bibim/String.h>
#   include <set>
#   include <vector>

    namespace Bibim
    {
        class FontLibrary : public GameModule, public GraphicsDevice::LostEventListener
        {
            BBModuleClass(FontLibrary, GameModule, 'F', 'T', 'L', 'B');
            public:
                typedef std::pair<unsigned int, FontCachePtr> CachePair;
                typedef std::vector<CachePair> CacheCollection;
                typedef std::set<Font*> FontCollection;

            public:
                FontLibrary(GraphicsDevice* graphicsDevice);
                virtual ~FontLibrary();

                inline GraphicsDevice* GetGraphicsDevice() const;

                inline const String& GetOSFontDirectory() const;

                inline const String& GetAlternativeFace() const;

                FontCache* GetCache(const FontCacheParameters& parameters);

                void SetGlobalScale(float value);

                // ResultType: FT_Library
                inline void* GetFTLibrary() const;

            private:
                void Construct();

                void Add(Font* font);
                void Remove(Font* font);

                virtual void OnGraphicsDeviceLost(GraphicsDeviceBase* g);

            private:
                GraphicsDevice* graphicsDevice;
                String osFontDirectory;
                String alternativeFace;
                CacheCollection caches;
                FontCollection fonts;
                void* ftLibrary;
                float globalScale;

                friend class Font;
        };
    }

#endif