#include <Bibim/Config.h>
#include <Bibim/FileAssetProviderBase.h>
#include <Bibim/AssetLoadingTask.h>
#include <Bibim/AssetStreamReader.h>
#include <Bibim/BinaryWriter.h>
#include <Bibim/FileStream.h>
#include <Bibim/Log.h>
#include <Bibim/GameAssetFactory.h>
#include <Bibim/GameAssetStorage.h>

namespace Bibim
{
    class FileAssetPreloadingTask : public AssetPreloadingTask
    {
        public:
            FileAssetPreloadingTask(FileAssetProviderBase* owner, const String& name, GameAssetStorage* storage, const String& directory)
                : AssetPreloadingTask(name, storage),
                  owner(owner),
                  directory(directory)
            {
            }

            virtual ~FileAssetPreloadingTask()
            {
            }

            virtual void Execute()
            {
                if (GameAsset* result = owner->LoadActually(GetStorage(), directory, GetName(), true, nullptr))
                    Register(result);
            }

        private:
            FileAssetProviderBase* owner;
            String directory;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    FileAssetProviderBase::FileAssetProviderBase()
    {
    }

    FileAssetProviderBase::FileAssetProviderBase(GameAssetStorage* storage)
        : AssetProvider(storage)
    {
    }

    FileAssetProviderBase::FileAssetProviderBase(GameAssetStorage* storage, const String& directory)
        : AssetProvider(storage)
    {
        SetDirectory(directory);
    }

    FileAssetProviderBase::~FileAssetProviderBase()
    {
    }

    Stream* FileAssetProviderBase::Open(const String& name)
    {
        return OpenActually(directory, name);
    }

    bool FileAssetProviderBase::Preload(const String& name)
    {
        BBAssertDebug(GetStorage() != nullptr);
        Add(new FileAssetPreloadingTask(this, name, GetStorage(), directory));
        return true;
    }

    GameAsset* FileAssetProviderBase::Load(const String& name)
    {
        return LoadActually(GetStorage(), directory, name, false, nullptr);
    }

    bool FileAssetProviderBase::Restore(const String& name, GameAsset* asset)
    {
        return LoadActually(GetStorage(), directory, name, false, asset) == asset;
    }

    void FileAssetProviderBase::SetDirectory(const String& value)
    {
        directory = value;

        if (directory.GetLength() > 0)
        {
            const char last = directory[directory.GetLength() - 1];
            if (last != '/')
                directory.Append("/");
        }
    }

    Stream* FileAssetProviderBase::OpenActually(const String& directory, const String& name)
    {
        const int dl = directory.GetLength();
        const int nl = name.GetLength();
        const int totalLength = dl + nl + 3 + 1;
        char* filename = BBStackAlloc(char, totalLength);
        String::CopyChars(&filename[0],       directory.CStr());
        String::CopyChars(&filename[dl],      name.CStr());
        String::CopyChars(&filename[dl + nl], ".ab");
        filename[totalLength - 1] = '\0';

        Stream* stream = new FileStream(filename, FileStream::ReadOnly);

        BBStackFree(filename);

        if (stream->CanRead())
            return stream;
        else
        {
            StreamPtr streamPointer = stream;
            return nullptr;
        }
    }

    GameAsset* FileAssetProviderBase::LoadActually(GameAssetStorage* storage,
                                                   const String& directory,
                                                   const String& name,
                                                   bool isPriority,
                                                   GameAsset* existingInstance)
    {
        BBAssertDebug(storage != nullptr);

        StreamPtr stream = OpenActually(directory, name);
        if (stream && stream->CanRead())
        {
            AssetStreamReader reader(name, stream, storage, isPriority);
            return GameAssetFactory::Create(reader, existingInstance);
        }
        else
            return nullptr;
    }
}