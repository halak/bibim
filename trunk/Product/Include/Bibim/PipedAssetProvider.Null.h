#pragma once
#ifndef __BIBIM_PIPEDASSETPROVIDER_NULL_H__
#define __BIBIM_PIPEDASSETPROVIDER_NULL_H__

#   include <Bibim/FWD.h>
#   include <Bibim/AssetProvider.h>
#   include <Bibim/String.h>

    namespace Bibim
    {
        class PipedAssetProvider : public AssetProvider
        {
            BBModuleClass(PipedAssetProvider, AssetProvider, 'P', 'A', 'S', 'P');
            public:
                static const String DefaultPipeName;

            public:
                PipedAssetProvider();
                PipedAssetProvider(GameAssetStorage* storage);
                PipedAssetProvider(GameAssetStorage* storage, const String& pipeName, const String& clientName);
                PipedAssetProvider(GameAssetStorage* storage, const String& serverName, const String& pipeName, const String& clientName);
                virtual ~PipedAssetProvider();

                virtual bool Preload(const String& name);
                virtual GameAsset* Load(const String& name);
                virtual bool Restore(const String& name, GameAsset* asset);

                inline const String& GetServerName() const;
                void SetServerName(const String& value);

                inline const String& GetPipeName() const;
                void SetPipeName(const String& value);

                inline const String& GetClientName() const;
                void SetClientName(const String& value);

                inline const String& GetWorkingDirectory() const;
                void SetWorkingDirectory(const String& value);

                inline bool GetDumpCacheEnabled() const;
                inline void SetDumpCacheEnabled(bool value);
        };
    }

#endif