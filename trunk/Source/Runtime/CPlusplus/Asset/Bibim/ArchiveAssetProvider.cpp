#include <Bibim/PCH.h>
#include <Bibim/ArchiveAssetProvider.h>
#include <Bibim/AssetLoadingTask.h>
#include <Bibim/AssetStreamReader.h>
#include <Bibim/BinaryWriter.h>
#include <Bibim/FileStream.h>
#include <BIbim/GameAssetFactory.h>
#include <BIbim/GameAssetStorage.h>

namespace Bibim
{
    class ArchiveAssetPreloadingTask : public AssetPreloadingTask
    {
        public:
            ArchiveAssetPreloadingTask(const String& name, GameAssetStorage* storage, Archive* archive)
                : AssetPreloadingTask(name, storage),
                  archive(archive)
            {
            }

            virtual ~ArchiveAssetPreloadingTask()
            {
            }

            virtual void Execute()
            {
                /*
                const int dl = directory.GetLength();
                const int nl = GetName().GetLength();
                const int totalLength = dl + nl + 3 + 1;
                char* filename = BBStackAlloc(char, totalLength);
                String::CopyChars(&filename[0],       directory.CStr());
                String::CopyChars(&filename[dl],      GetName().CStr());
                String::CopyChars(&filename[dl + nl], ".ab");
                filename[totalLength - 1] = '\0';

                FileStreamPtr assetStream = new FileStream(filename, FileStream::ReadOnly);
                AssetStreamReader reader(GetName(), assetStream, GetStorage(), true);
                GameAsset* result = GameAssetFactory::Create(reader);
                Register(result);

                BBStackFree(filename);
                */
            }

        private:
            Archive* archive;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    ArchiveAssetProvider::ArchiveAssetProvider()
        : archive(nullptr)
    {
    }

    ArchiveAssetProvider::ArchiveAssetProvider(GameAssetStorage* storage)
        : AssetProvider(storage),
          archive(nullptr)
    {
    }

    ArchiveAssetProvider::ArchiveAssetProvider(GameAssetStorage* storage, Archive* archive)
        : AssetProvider(storage),
          archive(nullptr)
    {
        SetArchive(archive);
    }

    ArchiveAssetProvider::~ArchiveAssetProvider()
    {
    }

    bool ArchiveAssetProvider::Preload(const String& name)
    {
        BBAssertDebug(GetStorage() != nullptr);
        Add(new ArchiveAssetPreloadingTask(name, GetStorage(), archive));
        return true;
    }

    GameAsset* ArchiveAssetProvider::Load(const String& name)
    {
        BBAssertDebug(GetStorage() != nullptr);

        /*
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
        */

        return nullptr;
    }

    void ArchiveAssetProvider::SetArchive(Archive* value)
    {
        archive = value;
    }
}