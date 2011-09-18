#include <Bibim/PCH.h>
#include <Bibim/FileAssetProvider.h>

namespace Bibim
{
    FileAssetProvider::FileAssetProvider()
    {
    }

    FileAssetProvider::FileAssetProvider(GameAssetStorage* storage)
        : AssetProvider(storage)
    {
    }

    FileAssetProvider::FileAssetProvider(GameAssetStorage* storage, const String& directory)
        : AssetProvider(storage),
          directory(directory)
    {
    }

    FileAssetProvider::~FileAssetProvider()
    {
    }

    GameAsset* FileAssetProvider::Load(const String& name)
    {
        return nullptr;
    }

    void FileAssetProvider::SetDirectory(const String& value)
    {
        directory = value;

        if (directory.GetLength() > 0)
        {
            const char last = directory[directory.GetLength() - 1];
            if (last != '\\')
                directory.Append("\\");
        }
    }
}