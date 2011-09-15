#pragma once
#ifndef __BIBIM_ASSETREADER_H__
#define __BIBIM_ASSETREADER_H__

#   include <Bibim/FWD.h>
#   include <Bibim/StreamReader.h>

    namespace Bibim
    {
        class AssetReader : public StreamReader
        {
            public:
                AssetReader(Stream* sourceStream, GameModuleTree* modules);
                AssetReader(const AssetReader& original);
                ~AssetReader();

                GameModule* ReadModule();

                inline GameModuleTree* GetModules() const;

                AssetReader& operator = (const AssetReader& right);
                inline bool operator == (const AssetReader& right) const;
                inline bool operator != (const AssetReader& right) const;

            private:
                GameModuleTree* modules;
        };
    }

#   include <Bibim/AssetReader.inl>

#endif