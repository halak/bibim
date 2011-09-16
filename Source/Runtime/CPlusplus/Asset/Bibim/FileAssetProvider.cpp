#include <Bibim/PCH.h>
#include <Bibim/FileAssetProvider.h>

namespace Bibim
{
    FileAssetProvider::FileAssetProvider()
    {
    }

    FileAssetProvider::~FileAssetProvider()
    {
    }

    GameAsset* FileAssetProvider::Load(const String& /*name*/)
    {
        return nullptr;
    }
}