#include <Bibim/PCH.h>
#include <Bibim/PipedAssetProvider.h>
#include <Bibim/AssetLoadingTask.h>
#include <Bibim/AssetStreamReader.h>
#include <Bibim/BinaryWriter.h>
#include <Bibim/DumpStream.h>
#include <Bibim/FileStream.h>
#include <Bibim/Environment.h>
#include <BIbim/GameAssetFactory.h>
#include <BIbim/GameAssetStorage.h>
#include <Bibim/PipeClientStream.h>

namespace Bibim
{
    class PipedAssetPreloadingTask : public AssetPreloadingTask
    {
        public:
            PipedAssetPreloadingTask(const String& name, GameAssetStorage* storage, const String& serverName, const String& assetPipeName, bool dumpCacheEnabled)
                : AssetPreloadingTask(name, storage),
                  serverName(serverName),
                  assetPipeName(assetPipeName),
                  dumpCacheEnabled(dumpCacheEnabled),
                  cancelled(false)
            {
            }

            virtual ~PipedAssetPreloadingTask()
            {
            }

            virtual void Execute()
            {
                PipeClientStreamPtr pipeStream = new PipeClientStream(serverName, assetPipeName, PipeStream::ReadOnly);
                do
                {
                    pipeStream->Connect();
                } while (pipeStream->IsConnected() == false && cancelled == false);

                if (cancelled == false)
                {
                    StreamPtr assetStream = nullptr;
                    if (dumpCacheEnabled)
                        assetStream = new DumpStream(pipeStream, new FileStream(GetName() + ".ab", FileStream::WriteOnly));
                    else
                        assetStream = pipeStream;

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
            bool dumpCacheEnabled;
            bool cancelled;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    const String PipedAssetProvider::DefaultPipeName = "BibimAssetPipe";

    PipedAssetProvider::PipedAssetProvider()
        : dumpCacheEnabled(false)
    {
    }

    PipedAssetProvider::PipedAssetProvider(GameAssetStorage* storage)
        : AssetProvider(storage),
          dumpCacheEnabled(false)
    {
    }

    PipedAssetProvider::PipedAssetProvider(GameAssetStorage* storage, const String& pipeName, const String& clientName)
        : AssetProvider(storage),
          pipeName(pipeName),
          clientName(clientName),
          dumpCacheEnabled(false)
    {
    }

    PipedAssetProvider::PipedAssetProvider(GameAssetStorage* storage, const String& serverName, const String& pipeName, const String& clientName)
        : AssetProvider(storage),
          serverName(serverName),
          pipeName(pipeName),
          clientName(clientName),
          dumpCacheEnabled(false)
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
            Add(new PipedAssetPreloadingTask(name, GetStorage(), serverName, assetPipeName, dumpCacheEnabled));
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
            PipeClientStreamPtr pipeStream = new PipeClientStream(serverName, assetPipeName, PipeStream::ReadOnly);
            do
            {
                pipeStream->Connect();
            } while (pipeStream->IsConnected() == false);

            StreamPtr assetStream = nullptr;
            if (dumpCacheEnabled)
                assetStream = new DumpStream(pipeStream, new FileStream(name + ".ab", FileStream::WriteOnly));
            else
                assetStream = pipeStream;

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

    void PipedAssetProvider::SetWorkingDirectory(const String& value)
    {
        if (workingDirectory != value)
        {
            workingDirectory = value;

            if (TryConnectToServer())
            {
                BinaryWriter queryWriter(queryStream);
                queryWriter.Write(ChangeWorkingDirectoryPacketID);
                queryWriter.Write(workingDirectory);
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
                if (workingDirectory.IsEmpty() == false)
                    writer.Write(workingDirectory);
                else
                    writer.Write(Environment::GetWorkingDirectory());
                writer.Write(GetClientName());
            }
        }

        return queryStream &&queryStream->IsConnected();
    }
}