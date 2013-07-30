#include <Bibim/Config.h>
#include <Bibim/NetworkAssetProvider.h>
#include <Bibim/AssetLoadingTask.h>
#include <Bibim/AssetStreamReader.h>
#include <Bibim/BinaryWriter.h>
#include <Bibim/DumpStream.h>
#include <Bibim/FileStream.h>
#include <Bibim/Environment.h>
#include <Bibim/GameAssetFactory.h>
#include <Bibim/GameAssetStorage.h>
#include <Bibim/Log.h>
#include <Bibim/Socket.h>
#include <Bibim/NetworkStream.h>

namespace Bibim
{
    class NetworkAssetPreloadingTask : public AssetPreloadingTask
    {
        public:
            NetworkAssetPreloadingTask(const String& name, GameAssetStorage* storage, Stream* stream, bool dumpCacheEnabled)
                : AssetPreloadingTask(name, storage),
                  stream(stream),
                  dumpCacheEnabled(dumpCacheEnabled),
                  cancelled(false)
            {
            }

            virtual ~NetworkAssetPreloadingTask()
            {
            }

            virtual void Execute()
            {
                if (cancelled == false)
                {
                    StreamPtr assetStream = nullptr;
                    if (dumpCacheEnabled)
                        assetStream = new DumpStream(stream, new FileStream(GetName() + ".ab", FileStream::WriteOnly));
                    else
                        assetStream = stream;

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
            StreamPtr stream;
            GameAssetStorage* storage;
            bool dumpCacheEnabled;
            bool cancelled;
    };
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    NetworkAssetProvider::NetworkAssetProvider()
        : dumpCacheEnabled(false)
    {
    }

    NetworkAssetProvider::NetworkAssetProvider(GameAssetStorage* storage)
        : AssetProvider(storage),
          dumpCacheEnabled(false)
    {
    }

    NetworkAssetProvider::NetworkAssetProvider(GameAssetStorage* storage, const IPEndPoint& endPoint, const String& clientName)
        : AssetProvider(storage),
          endPoint(endPoint),
          clientName(clientName),
          dumpCacheEnabled(false)
    {
    }

    NetworkAssetProvider::~NetworkAssetProvider()
    {
    }

    bool NetworkAssetProvider::Preload(const String& name)
    {
        StreamPtr stream;
        if (BeginLoad(name, stream))
        {
            Add(new NetworkAssetPreloadingTask(name, GetStorage(), stream, dumpCacheEnabled));
            return true;
        }
        else
            return false;
    }

    GameAsset* NetworkAssetProvider::Load(const String& name)
    {
        StreamPtr stream;
        if (BeginLoad(name, stream))
        {
            StreamPtr assetStream = nullptr;
            if (dumpCacheEnabled)
                assetStream = new DumpStream(stream, new FileStream(name + ".ab", FileStream::WriteOnly));
            else
                assetStream = stream;

            AssetStreamReader reader(name, assetStream, GetStorage());
            return GameAssetFactory::Create(reader);
        }
        else
            return nullptr;
    }

    bool NetworkAssetProvider::Restore(const String& /*name*/, GameAsset* /*asset*/)
    {
        return false;
    }

    void NetworkAssetProvider::SetEndPoint(IPEndPoint value)
    {
        if (endPoint != value)
        {
            endPoint = value;

            if (endPoint.GetPort() == 0)
                endPoint = IPEndPoint(endPoint.GetAddress(), DefaultPort);
        }
    }

    bool NetworkAssetProvider::BeginLoad(const String& name, StreamPtr& outStream)
    {
        BBAssertDebug(GetStorage() != nullptr);

        SocketPtr socket = new Socket(GetEndPoint());
        if (socket->TryConnect())
        {
            StreamPtr stream = new NetworkStream(socket);

            BinaryWriter writer(stream);
            writer.Write(clientName);
            if (workingDirectory.IsEmpty() == false)
                writer.Write(workingDirectory);
            else
                writer.Write(Environment::GetWorkingDirectory());
            writer.Write(name);

            outStream = stream;

            return true;
        }
        else
            return false;
    }
}