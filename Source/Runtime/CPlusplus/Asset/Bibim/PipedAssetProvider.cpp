#include <Bibim/PCH.h>
#include <Bibim/PipedAssetProvider.h>
#include <Bibim/StreamWriter.h>

namespace Bibim
{
    PipedAssetProvider::PipedAssetProvider()
    {
    }

    PipedAssetProvider::~PipedAssetProvider()
    {
        if (queryStream && queryStream->IsConnected())
            queryStream->Disconnect();
    }

    GameAsset* PipedAssetProvider::Load(const String& name)
    {
        if (queryStream == nullptr && pipeName.IsEmpty() == false)
        {
            queryStream = new PipeClientStream(serverName, pipeName, PipeStream::ReadAndWrite);
            queryStream->Connect();
        }

        if (queryStream == nullptr || queryStream->IsConnected() == false)
            return false;

        StreamWriter writer(queryStream);
        writer.Write("Request Asset Stream");
        writer.Write(name);

        PipeClientStreamPtr assetStream = new PipeClientStream();
        do
        {
            assetStream->Connect();
        } while (assetStream->IsConnected());

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
}