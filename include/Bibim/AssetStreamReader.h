#pragma once
#ifndef __BIBIM_ASSETSTREAMREADER_H__
#define __BIBIM_ASSETSTREAMREADER_H__

#include <Bibim/FWD.h>
#include <Bibim/BinaryReader.h>
#include <Bibim/GameAssetStorage.h>

namespace Bibim
{
    class AssetStreamReader : public BinaryReader
    {
        public:
            AssetStreamReader(const String& name, Stream* sourceStream, GameAssetStorage* storage);
            AssetStreamReader(const String& name, Stream* sourceStream, GameAssetStorage* storage, bool isPriority);
            AssetStreamReader(const AssetStreamReader& original);
            ~AssetStreamReader();

            void ReadAsync(AssetLoadingTask* task);

            GameModule* ReadModule();
            GameModule* ReadModule(int defaultModuleClassID);

            GameAsset* ReadAsset();
            
            using BinaryReader::Read;
            inline void Read(GameAssetPtr& outValue);

            GameModule* FindModuleByClassID(int classID);

            inline const String& GetName() const;
            inline GameModuleTree* GetModules() const;
            inline GameAssetStorage* GetStorage() const;
            inline bool IsPriority() const;

            AssetStreamReader& operator = (const AssetStreamReader& right);

        private:
            String name;
            GameAssetStorage* storage;
            GameModuleTree* modules;
            bool isPriority;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    void AssetStreamReader::Read(GameAssetPtr& outValue)
    {
        outValue = ReadAsset();
    }

    const String& AssetStreamReader::GetName() const
    {
        return name;
    }

    GameModuleTree* AssetStreamReader::GetModules() const
    {
        return modules;
    }

    GameAssetStorage* AssetStreamReader::GetStorage() const
    {
        return storage;
    }

    bool AssetStreamReader::IsPriority() const
    {
        return isPriority;
    }
}

#endif