#include <Bibim/PCH.h>
#include <Bibim/FileAssetProvider.Default.h>

namespace Bibim
{
    FileAssetProvider::FileAssetProvider()
    {
    }

    FileAssetProvider::FileAssetProvider(GameAssetStorage* storage)
        : Base(storage)
    {
    }

    FileAssetProvider::FileAssetProvider(GameAssetStorage* storage, const String& directory)
        : Base(storage, directory)
    {
    }

    FileAssetProvider::~FileAssetProvider()
    {
    }
}