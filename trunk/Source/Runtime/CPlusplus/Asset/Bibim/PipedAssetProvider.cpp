#include <Bibim/PCH.h>
#include <Bibim/PipedAssetProvider.h>
#include <Bibim/AssetStreamReader.h>
#include <Bibim/BinaryWriter.h>
#include <Bibim/Environment.h>
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

    GameAsset* PipedAssetProvider::Load(const String& name)
    {
        BBAssertDebug(GetStorage() != nullptr);

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

        if (queryStream == nullptr || queryStream->IsConnected() == false)
            return nullptr;

        BinaryWriter queryWriter(queryStream);
        queryWriter.Write(static_cast<uint32>(1000));
        queryWriter.Write(name);

        BinaryReader queryReader(queryStream);
        const String assetPipeName = queryReader.ReadString();

        PipeClientStreamPtr assetStream = new PipeClientStream(serverName, assetPipeName, PipeStream::ReadOnly);
        do
        {
            assetStream->Connect();
        } while (assetStream->IsConnected() == false);

        AssetStreamReader reader(name, assetStream, GetStorage());
        return GameAssetFactory::Create(reader);
    }

    void PipedAssetProvider::SetClientName(const String& value)
    {
        if (clientName != value)
        {
            clientName = value;
        }
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