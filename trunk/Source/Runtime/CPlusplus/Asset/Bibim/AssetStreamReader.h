#pragma once
#ifndef __BIBIM_ASSETSTREAMREADER_H__
#define __BIBIM_ASSETSTREAMREADER_H__

#   include <Bibim/FWD.h>
#   include <Bibim/BinaryReader.h>
#   include <Bibim/GameAssetStorage.h>

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
    }

#   include <Bibim/AssetStreamReader.inl>

#endif