#include <Bibim/PCH.h>
#include <Bibim/FileAssetProvider.h>
#include <Bibim/AssetReader.h>
#include <Bibim/BinaryWriter.h>
#include <Bibim/FileStream.h>
#include <BIbim/GameAssetFactory.h>
#include <BIbim/GameAssetStorage.h>

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
        : AssetProvider(storage)
    {
        SetDirectory(directory);
    }

    FileAssetProvider::~FileAssetProvider()
    {
    }

    GameAsset* FileAssetProvider::Load(const String& name)
    {
        BBAssertDebug(GetStorage() != nullptr);

        FileStreamPtr assetStream = new FileStream(directory + name, FileStream::ReadOnly);
        AssetReader reader(name, assetStream, GetStorage());
        return GameAssetFactory::Create(reader);
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