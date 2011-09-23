#include <Bibim/PCH.h>
#include <Bibim/PipedAssetProvider.h>
#include <Bibim/AssetStreamReader.h>
#include <Bibim/BinaryWriter.h>
#include <BIbim/GameAssetFactory.h>
#include <BIbim/GameAssetStorage.h>
#include <Bibim/PipeClientStream.h>

namespace Bibim
{
    PipedAssetProvider::PipedAssetProvider()
    {
    }

    PipedAssetProvider::PipedAssetProvider(GameAssetStorage* storage)
        : AssetProvider(storage)
    {
    }

    PipedAssetProvider::PipedAssetProvider(GameAssetStorage* storage, const String& pipeName)
        : AssetProvider(storage),
          pipeName(pipeName)
    {
    }

    PipedAssetProvider::PipedAssetProvider(GameAssetStorage* storage, const String& serverName, const String& pipeName)
        : AssetProvider(storage),
          serverName(serverName),
          pipeName(pipeName)
    {
    }

    PipedAssetProvider::~PipedAssetProvider()
    {
        if (queryStream && queryStream->IsConnected())
            queryStream->Disconnect();
    }

    GameAsset* PipedAssetProvider::Load(const String& name)
    {
        BBAssertDebug(GetStorage() != nullptr);

        if (queryStream == nullptr && pipeName.IsEmpty() == false)
        {
            queryStream = new PipeClientStream(serverName, pipeName, PipeStream::ReadAndWrite);
            queryStream->Connect();
        }

        if (queryStream == nullptr || queryStream->IsConnected() == false)
            return nullptr;

        BinaryWriter writer(queryStream);
        writer.Write(static_cast<uint32>(1000));
        writer.Write(name);

        PipeClientStreamPtr assetStream = new PipeClientStream(serverName, pipeName + "_" + "ASSET", PipeStream::ReadOnly);
        do
        {
            assetStream->Connect();
        } while (assetStream->IsConnected() == false);

        AssetStreamReader reader(name, assetStream, GetStorage());
        return GameAssetFactory::Create(reader);
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
}