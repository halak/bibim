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
                AssetStreamReader(const AssetStreamReader& original);
                ~AssetStreamReader();

                void ReadAsync(AssetLoadingTask* task);

                GameModule* ReadModule();
                GameModule* ReadModule(uint32 defaultModuleClassID);

                GameModule* FindModuleByClassID(uint32 classID);

                inline const String& GetName() const;
                inline GameModuleTree* GetModules() const;

                AssetStreamReader& operator = (const AssetStreamReader& right);
                inline bool operator == (const AssetStreamReader& right) const;
                inline bool operator != (const AssetStreamReader& right) const;

            private:
                String name;
                GameAssetStorage* storage;
                GameModuleTree* modules;
        };
    }

#   include <Bibim/AssetStreamReader.inl>

#endif