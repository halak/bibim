#include <Bibim/PCH.h>
#include <Bibim/FileAssetProvider.h>
#include <Bibim/AssetStreamReader.h>
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

    bool FileAssetProvider::Preload(const String& name)
    {
        return false;
    }

    GameAsset* FileAssetProvider::Load(const String& name)
    {
        BBAssertDebug(GetStorage() != nullptr);

        const int dl = directory.GetLength();
        const int nl = name.GetLength();
        const int totalLength = dl + nl + 3 + 1;
        char* filename = BBStackAlloc(char, totalLength);
        String::CopyChars(&filename[0],       directory.CStr());
        String::CopyChars(&filename[dl],      name.CStr());
        String::CopyChars(&filename[dl + nl], ".ab");
        filename[totalLength - 1] = '\0';

        FileStreamPtr assetStream = new FileStream(filename, FileStream::ReadOnly);
        AssetStreamReader reader(name, assetStream, GetStorage());
        GameAsset* result = GameAssetFactory::Create(reader);

        BBStackFree(filename);

        return result;
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