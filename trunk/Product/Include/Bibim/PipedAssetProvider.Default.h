#pragma once
#ifndef __BIBIM_PIPEDASSETPROVIDER_DEFAULT_H__
#define __BIBIM_PIPEDASSETPROVIDER_DEFAULT_H__

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
                static const int LoadAssetPacketID = 1000;
                static const int ChangeClientNamePacketID = 1001;
                static const int ChangeWorkingDirectoryPacketID = 1002;

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

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        const String& PipedAssetProvider::GetClientName() const
        {
            return clientName;
        }

        const String& PipedAssetProvider::GetServerName() const
        {
            return serverName;
        }

        const String& PipedAssetProvider::GetPipeName() const
        {
            return pipeName;
        }

        const String& PipedAssetProvider::GetWorkingDirectory() const
        {
            return workingDirectory;
        }

        bool PipedAssetProvider::GetDumpCacheEnabled() const
        {
            return dumpCacheEnabled;
        }

        void PipedAssetProvider::SetDumpCacheEnabled(bool value)
        {
            dumpCacheEnabled = value;
        }
    }

#endif