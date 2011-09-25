#include <Bibim/PCH.h>
#include <Bibim/PipedAssetProvider.h>
#include <Bibim/AssetLoadingTask.h>
#include <Bibim/AssetStreamReader.h>
#include <Bibim/BinaryWriter.h>
#include <Bibim/Environment.h>
#include <BIbim/GameAssetFactory.h>
#include <BIbim/GameAssetStorage.h>
#include <Bibim/PipeClientStream.h>

namespace Bibim
{
    class PipedAssetPreloadingTask : public AssetPreloadingTask
    {
        public:
            PipedAssetPreloadingTask(const String& name, GameAssetStorage* storage, const String& serverName, const String& assetPipeName)
                : AssetPreloadingTask(name, storage),
                  serverName(serverName),
                  assetPipeName(assetPipeName),
                  cancelled(false)
            {
            }

            virtual ~PipedAssetPreloadingTask()
            {
            }

            virtual void Execute()
            {
                PipeClientStreamPtr assetStream = new PipeClientStream(serverName, assetPipeName, PipeStream::ReadOnly);
                do
                {
                    assetStream->Connect();
                } while (assetStream->IsConnected() == false && cancelled == false);

                if (cancelled == false)
                {
                    AssetStreamReader reader(GetName(), assetStream, GetStorage(), true);
                    Register(GameAssetFactory::Create(reader));
                }
                else
                    Unregister();
            }

            virtual void Cancel()
            {
                cancelled = true;
            }

        private:
            String serverName;
            String assetPipeName;
            GameAssetStorage* storage;
            bool cancelled;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    PipedAssetProvider::PipedAssetProvider()
    {
    }

    PipedAssetProvider::PipedAssetProvider(GameAssetStorage* storage)
        : AssetProvider(storage)
    {
    }

    PipedAssetProvider::PipedAssetProvider(GameAssetStorage* storage, const String& pipeName, const String& clientName)
        : AssetProvider(storage),
          pipeName(pipeName),
          clientName(clientName)
    {
    }

    PipedAssetProvider::PipedAssetProvider(GameAssetStorage* storage, const String& serverName, const String& pipeName, const String& clientName)
        : AssetProvider(storage),
          serverName(serverName),
          pipeName(pipeName),
          clientName(clientName)
    {
    }

    PipedAssetProvider::~PipedAssetProvider()
    {
        if (queryStream && queryStream->IsConnected())
            queryStream->Disconnect();
    }

    bool PipedAssetProvider::Preload(const String& name)
    {
        String assetPipeName;
        if (BeginLoad(name, assetPipeName))
        {
            Add(new PipedAssetPreloadingTask(name, GetStorage(), serverName, assetPipeName));
            return true;
        }
        else
            return false;
    }

    GameAsset* PipedAssetProvider::Load(const String& name)
    {
        String assetPipeName;
        if (BeginLoad(name, assetPipeName))
        {
            PipeClientStreamPtr assetStream = new PipeClientStream(serverName, assetPipeName, PipeStream::ReadOnly);
            do
            {
                assetStream->Connect();
            } while (assetStream->IsConnected() == false);

            AssetStreamReader reader(name, assetStream, GetStorage());
            return GameAssetFactory::Create(reader);
        }
        else
            return nullptr;
    }

    void PipedAssetProvider::SetServerName(const String& value)
    {
        if (serverName != value)
        {
            serverName = value;

            if (queryStream && queryStream->IsConnected())
                queryStream->Disconnect();

            queryStream.Reset();
        }
    }

    void PipedAssetProvider::SetPipeName(const String& value)
    {
        if (pipeName != value)
        {
            pipeName = value;
            
            if (queryStream && queryStream->IsConnected())
                queryStream->Disconnect();

            queryStream.Reset();
        }
    }

    void PipedAssetProvider::SetClientName(const String& value)
    {
        if (clientName != value)
        {
            clientName = value;

            if (TryConnectToServer())
            {
                BinaryWriter queryWriter(queryStream);
                queryWriter.Write(ChangeClientNamePacketID);
                queryWriter.Write(clientName);
            }
        }
    }

    bool PipedAssetProvider::BeginLoad(const String& name, String& outPipeName)
    {
        BBAssertDebug(GetStorage() != nullptr);

        if (TryConnectToServer())
        {
            BinaryWriter queryWriter(queryStream);
            queryWriter.Write(LoadAssetPacketID);
            queryWriter.Write(name);

            BinaryReader queryReader(queryStream);
            outPipeName = queryReader.ReadString();

            return true;
        }
        else
            return false;
    }

    bool PipedAssetProvider::TryConnectToServer()
    {
        if (queryStream == nullptr && pipeName.IsEmpty() == false)
        {
            queryStream = new PipeClientStream(serverName, pipeName, PipeStream::ReadAndWrite);
            queryStream->Connect();

            if (queryStream->IsConnected())
            {
                BinaryWriter writer(queryStream);
                writer.Write(Environment::GetWorkingDirectory());
                writer.Write(GetClientName());
            }
        }

        return queryStream &&queryStream->IsConnected();
    }
}