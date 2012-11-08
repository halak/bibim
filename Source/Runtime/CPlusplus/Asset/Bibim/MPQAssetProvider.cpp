#include <Bibim/PCH.h>
#include <Bibim/MPQAssetProvider.h>
#include <Bibim/AssetLoadingTask.h>
#include <Bibim/AssetStreamReader.h>
#include <Bibim/BinaryWriter.h>
#include <Bibim/FileStream.h>
#include <BIbim/GameAssetFactory.h>
#include <BIbim/GameAssetStorage.h>

namespace Bibim
{
    class MPQAssetPreloadingTask : public AssetPreloadingTask
    {
        public:
            MPQAssetPreloadingTask(const String& name, GameAssetStorage* storage, const String& directory)
                : AssetPreloadingTask(name, storage),
                  directory(directory)
            {
            }

            virtual ~MPQAssetPreloadingTask()
            {
            }

            virtual void Execute()
            {
                if (GameAsset* result = MPQAssetProvider::LoadActually(GetStorage(), directory, GetName(), true))
                    Register(result);
            }

        private:
            String directory;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    MPQAssetProvider::MPQAssetProvider()
    {
    }

    MPQAssetProvider::MPQAssetProvider(GameAssetStorage* storage)
        : AssetProvider(storage)
    {
    }

    MPQAssetProvider::MPQAssetProvider(GameAssetStorage* storage, const String& directory)
        : AssetProvider(storage)
    {
        SetDirectory(directory);
    }

    MPQAssetProvider::~MPQAssetProvider()
    {
    }

    bool MPQAssetProvider::Preload(const String& name)
    {
        BBAssertDebug(GetStorage() != nullptr);
        Add(new MPQAssetPreloadingTask(name, GetStorage(), directory));
        return true;
    }

    GameAsset* MPQAssetProvider::Load(const String& name)
    {
        return LoadActually(GetStorage(), directory, name, false);
    }

    void MPQAssetProvider::SetDirectory(const String& value)
    {
        directory = value;

        if (directory.GetLength() > 0)
        {
            const char last = directory[directory.GetLength() - 1];
            if (last != '\\')
                directory.Append("\\");
        }
    }

    GameAsset* MPQAssetProvider::LoadActually(GameAssetStorage* storage,
                                               const String& directory,
                                               const String& name,
                                               bool isPriority)
    {
        BBAssertDebug(storage != nullptr);

        const int dl = directory.GetLength();
        const int nl = name.GetLength();
        const int totalLength = dl + nl + 3 + 1;
        char* filename = BBStackAlloc(char, totalLength);
        String::CopyChars(&filename[0],       directory.CStr());
        String::CopyChars(&filename[dl],      name.CStr());
        String::CopyChars(&filename[dl + nl], ".ab");
        filename[totalLength - 1] = '\0';

        FileStreamPtr assetStream = new FileStream(filename, FileStream::ReadOnly);
        AssetStreamReader reader(name, assetStream, storage, isPriority);
        GameAsset* result = GameAssetFactory::Create(reader);

        BBStackFree(filename);

        return result;
    }
}