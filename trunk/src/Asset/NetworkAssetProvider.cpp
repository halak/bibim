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
                  storage(storage),
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

    Stream* NetworkAssetProvider::Open(const String& name)
    {
        Stream* stream = nullptr;
        if (BeginLoad(name, stream))
        {
            if (dumpCacheEnabled)
                return new DumpStream(stream, new FileStream(name + ".ab", FileStream::WriteOnly));
            else
                return stream;
        }
        else
            return nullptr;
    }

    bool NetworkAssetProvider::Preload(const String& name)
    {
        Stream* stream = nullptr;
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
        if (Stream* stream = Open(name))
        {
            AssetStreamReader reader(name, stream, GetStorage());
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

    bool NetworkAssetProvider::BeginLoad(const String& name, Stream*& outStream)
    {
        BBAssertDebug(GetStorage() != nullptr);

        SocketPtr socket = new Socket(GetEndPoint());
        if (socket->TryConnect())
        {
            Stream* stream = new NetworkStream(socket);

            BinaryWriter::WriteTo(stream, clientName);
            if (workingDirectory.IsEmpty() == false)
                BinaryWriter::WriteTo(stream, workingDirectory);
            else
                BinaryWriter::WriteTo(stream, Environment::GetWorkingDirectory());
            BinaryWriter::WriteTo(stream, name);

            outStream = stream;

            return true;
        }
        else
            return false;
    }
}