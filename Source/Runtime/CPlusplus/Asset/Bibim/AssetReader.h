#pragma once
#ifndef __BIBIM_ASSETREADER_H__
#define __BIBIM_ASSETREADER_H__

#   include <Bibim/FWD.h>
#   include <Bibim/BinaryReader.h>
#   include <Bibim/GameAssetStorage.h>

    namespace Bibim
    {
        class AssetReader : public BinaryReader
        {
            public:
                AssetReader(Stream* sourceStream, GameAssetStorage* storage);
                AssetReader(const AssetReader& original);
                ~AssetReader();

                void ReadAsync(AssetLoadingTask* task);

                GameModule* ReadModule();
                GameModule* ReadModule(uint32 defaultModuleClassID);

                GameModule* FindModuleByClassID(uint32 classID);
                inline GameModuleTree* GetModules() const;

                AssetReader& operator = (const AssetReader& right);
                inline bool operator == (const AssetReader& right) const;
                inline bool operator != (const AssetReader& right) const;

            private:
                GameAssetStorage* storage;
                GameModuleTree* modules;
        };
    }

#   include <Bibim/AssetReader.inl>

#endif