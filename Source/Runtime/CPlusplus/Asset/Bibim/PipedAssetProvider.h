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
            BBModuleClass(PipedAssetProvider, AssetProvider, 'P', 'A', 'S', 'P');
            public:
                static const uint32 LoadAssetPacketID = 1000;
                static const uint32 ChangeClientNamePacketID = 1001;
                static const uint32 ChangeWorkingDirectoryPacketID = 1002;

            public:
                PipedAssetProvider();
                PipedAssetProvider(GameAssetStorage* storage);
                PipedAssetProvider(GameAssetStorage* storage, const String& pipeName, const String& clientName);
                PipedAssetProvider(GameAssetStorage* storage, const String& serverName, const String& pipeName, const String& clientName);
                virtual ~PipedAssetProvider();

                virtual bool Preload(const String& name);
                virtual GameAsset* Load(const String& name);

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

            private:
                bool BeginLoad(const String& name, String& outPipeName);
                bool TryConnectToServer();

            private:
                String serverName;
                String pipeName;
                String clientName;
                String workingDirectory;     
                PipeClientStreamPtr queryStream;
                bool dumpCacheEnabled;
        };
    }

#   include <Bibim/PipedAssetProvider.inl>

#endif