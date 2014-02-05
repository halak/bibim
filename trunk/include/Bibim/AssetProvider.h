#pragma once
#ifndef __BIBIM_ASSETPROVIDER_H__
#define __BIBIM_ASSETPROVIDER_H__

#include <Bibim/FWD.h>
#include <Bibim/GameModule.h>
#include <Bibim/String.h>

namespace Bibim
{
    class AssetProvider : public GameModule
    {
        BBAbstractModuleClass(AssetProvider, GameModule);
        public:
            static const int DefaultPriority = 100;

        public:
            AssetProvider();
            AssetProvider(GameAssetStorage* storage);
            virtual ~AssetProvider();

            virtual Stream* Open(const String& name) = 0;
            virtual bool Preload(const String& name) = 0;
            virtual GameAsset* Load(const String& name) = 0;
            virtual bool Restore(const String& name, GameAsset* asset) = 0;

            inline GameAssetStorage* GetStorage() const;
            void SetStorage(GameAssetStorage* value);
            inline int GetPriority() const;
            void SetPriority(int value);

        protected:
            void Add(AssetPreloadingTask* item);

        private:
            GameAssetStorage* storage;
            int priority;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    GameAssetStorage* AssetProvider::GetStorage() const
    {
        return storage;
    }

    int AssetProvider::GetPriority() const
    {
        return priority;
    }
}

#endif