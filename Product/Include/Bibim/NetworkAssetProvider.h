#pragma once
#ifndef __BIBIM_NETWORKASSETPROVIDER_DEFAULT_H__
#define __BIBIM_NETWORKASSETPROVIDER_DEFAULT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/AssetProvider.h>
#   include <Bibim/IPEndPoint.h>
#   include <Bibim/String.h>

    namespace Bibim
    {
        class NetworkAssetProvider : public AssetProvider
        {
            BBModuleClass(NetworkAssetProvider, AssetProvider, 'N', 'A', 'S', 'P');
            public:
                static const int DefaultPort = 51894;

            public:
                NetworkAssetProvider();
                NetworkAssetProvider(GameAssetStorage* storage);
                NetworkAssetProvider(GameAssetStorage* storage, const IPEndPoint& endPoint, const String& clientName);
                virtual ~NetworkAssetProvider();

                virtual bool Preload(const String& name);
                virtual GameAsset* Load(const String& name);
                virtual bool Restore(const String& name, GameAsset* asset);

                inline IPEndPoint GetEndPoint() const;
                void SetEndPoint(IPEndPoint value);

                inline const String& GetClientName() const;
                inline void SetClientName(const String& value);

                inline const String& GetWorkingDirectory() const;
                inline void SetWorkingDirectory(const String& value);

                inline bool GetDumpCacheEnabled() const;
                inline void SetDumpCacheEnabled(bool value);

            private:
                bool BeginLoad(const String& name, StreamPtr& outStream);

            private:
                IPEndPoint endPoint;
                String clientName;
                String workingDirectory;
                bool dumpCacheEnabled;
        };

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        IPEndPoint NetworkAssetProvider::GetEndPoint() const
        {
            return endPoint;
        }

        const String& NetworkAssetProvider::GetClientName() const
        {
            return clientName;
        }

        void NetworkAssetProvider::SetClientName(const String& value)
        {
            clientName = value;
        }

        const String& NetworkAssetProvider::GetWorkingDirectory() const
        {
            return workingDirectory;
        }

        void NetworkAssetProvider::SetWorkingDirectory(const String& value)
        {
            workingDirectory = value;
        }

        bool NetworkAssetProvider::GetDumpCacheEnabled() const
        {
            return dumpCacheEnabled;
        }

        void NetworkAssetProvider::SetDumpCacheEnabled(bool value)
        {
            dumpCacheEnabled = value;
        }
    }

#endif