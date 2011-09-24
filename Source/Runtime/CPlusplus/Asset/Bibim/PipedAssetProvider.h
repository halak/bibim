#pragma once
#ifndef __BIBIM_PIPEDASSETPROVIDER_H__
#define __BIBIM_PIPEDASSETPROVIDER_H__

#   include <Bibim/FWD.h>
#   include <Bibim/AssetProvider.h>
#   include <Bibim/String.h>

    namespace Bibim
    {
        class PipedAssetProvider : public AssetProvider
        {
            BBGameModuleClass('P', 'A', 'S', 'P');
            public:
                PipedAssetProvider();
                PipedAssetProvider(GameAssetStorage* storage);
                PipedAssetProvider(GameAssetStorage* storage, const String& pipeName, const String& clientName);
                PipedAssetProvider(GameAssetStorage* storage, const String& serverName, const String& pipeName, const String& clientName);
                virtual ~PipedAssetProvider();

                virtual GameAsset* Load(const String& name);

                inline const String& GetServerName() const;
                void SetServerName(const String& value);

                inline const String& GetPipeName() const;
                void SetPipeName(const String& value);

                inline const String& GetClientName() const;
                void SetClientName(const String& value);

            private:
                String serverName;
                String pipeName;
                String clientName;
                PipeClientStreamPtr queryStream;
        };
    }

#   include <Bibim/PipedAssetProvider.inl>

#endif