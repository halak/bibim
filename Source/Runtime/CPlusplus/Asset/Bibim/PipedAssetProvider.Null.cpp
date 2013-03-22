#include <Bibim/PCH.h>
#include <Bibim/PipedAssetProvider.Null.h>

namespace Bibim
{
    const String PipedAssetProvider::DefaultPipeName = "BibimAssetPipe";

    PipedAssetProvider::PipedAssetProvider()
    {
    }

    PipedAssetProvider::PipedAssetProvider(GameAssetStorage* /*storage*/)
    {
    }

    PipedAssetProvider::PipedAssetProvider(GameAssetStorage* /*storage*/, const String& /*pipeName*/, const String& /*clientName*/)
    {
    }

    PipedAssetProvider::PipedAssetProvider(GameAssetStorage* /*storage*/, const String& /*serverName*/, const String& /*pipeName*/, const String& /*clientName*/)
    {
    }

    PipedAssetProvider::~PipedAssetProvider()
    {
    }
    
    bool PipedAssetProvider::Preload(const String& /*name*/)
    {
        return false;
    }

    GameAsset* PipedAssetProvider::Load(const String& /*name*/)
    {
        return nullptr;
    }

    bool PipedAssetProvider::Restore(const String& /*name*/, GameAsset* /*asset*/)
    {
        return false;
    }
    
    const String& PipedAssetProvider::GetServerName() const
    {
        return String::Empty;
    }

    void PipedAssetProvider::SetServerName(const String& /*value*/)
    {
    }

    const String& PipedAssetProvider::GetPipeName() const
    {
        return String::Empty;
    }

    void PipedAssetProvider::SetPipeName(const String& /*value*/)
    {
    }
    
    const String& PipedAssetProvider::GetClientName() const
    {
        return String::Empty;
    }

    void PipedAssetProvider::SetClientName(const String& /*value*/)
    {
    }
    
    const String& PipedAssetProvider::GetWorkingDirectory() const
    {
        return String::Empty;
    }

    void PipedAssetProvider::SetWorkingDirectory(const String& /*value*/)
    {
    }
    
    bool PipedAssetProvider::GetDumpCacheEnabled() const
    {
        return false;
    }

    void PipedAssetProvider::SetDumpCacheEnabled(bool /*value*/)
    {
    }
}