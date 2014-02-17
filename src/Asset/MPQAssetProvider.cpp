#include <Bibim/Config.h>
#if (defined(BIBIM_PLATFORM_WINDOWS))

#include <Bibim/MPQAssetProvider.h>
#include <Bibim/AssetLoadingTask.h>
#include <Bibim/AssetStreamReader.h>
#include <Bibim/BinaryWriter.h>
#include <Bibim/MPQ.h>
#include <Bibim/MPQStream.h>
#include <Bibim/GameAssetFactory.h>
#include <Bibim/GameAssetStorage.h>
#include <StormLib.h>

namespace Bibim
{
    class MPQAssetPreloadingTask : public AssetPreloadingTask
    {
        public:
            MPQAssetPreloadingTask(const String& name, GameAssetStorage* storage, MPQ* mpq)
                : AssetPreloadingTask(name, storage),
                  mpq(mpq)
            {
            }

            virtual ~MPQAssetPreloadingTask()
            {
            }

            virtual void Execute()
            {
                if (GameAsset* result = MPQAssetProvider::LoadActually(GetStorage(), mpq, GetName(), true))
                    Register(result);
            }

        private:
            MPQ* mpq;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    MPQAssetProvider::MPQAssetProvider()
    {
    }

    MPQAssetProvider::MPQAssetProvider(GameAssetStorage* storage)
        : AssetProvider(storage)
    {
    }

    MPQAssetProvider::MPQAssetProvider(GameAssetStorage* storage, MPQ* mpq)
        : AssetProvider(storage),
          mpq(mpq)
    {
    }

    MPQAssetProvider::~MPQAssetProvider()
    {
    }

    Stream* MPQAssetProvider::Open(const String& name)
    {
        return OpenActually(mpq, name);
    }

    bool MPQAssetProvider::Preload(const String& name)
    {
        BBAssertDebug(GetStorage() != nullptr && mpq != nullptr);
        Add(new MPQAssetPreloadingTask(name, GetStorage(), mpq));
        return true;
    }

    GameAsset* MPQAssetProvider::Load(const String& name)
    {
        BBAssertDebug(mpq != nullptr);
        return LoadActually(GetStorage(), mpq, name, false);
    }

    bool MPQAssetProvider::Restore(const String& /*name*/, GameAsset* /*asset*/)
    {
        return false;
    }

    void MPQAssetProvider::SetMPQ(MPQ* value)
    {
        mpq = value;
    }

    Stream* MPQAssetProvider::OpenActually(MPQ* mpq, const String& name)
    {
        const int nl = name.GetLength();
        const int totalLength = nl + 3 + 1;
        char* filename = BBStackAlloc(char, totalLength);
        String::CopyChars(&filename[0],  name.CStr());
        String::CopyChars(&filename[nl], ".ab");
        filename[totalLength - 1] = '\0';

        Stream* stream = nullptr;
        if (mpq->Has(filename))
            stream = new MPQStream(mpq, filename);

        BBStackFree(filename);

        return stream;
    }

    GameAsset* MPQAssetProvider::LoadActually(GameAssetStorage* storage,
                                               MPQ* mpq,
                                               const String& name,
                                               bool isPriority)
    {
        BBAssertDebug(storage != nullptr);

        StreamPtr stream = OpenActually(mpq, name);
        if (stream && stream->CanRead())
        {
            AssetStreamReader reader(name, stream, storage, isPriority);
            return GameAssetFactory::Create(reader);
        }
        else
            return nullptr;
    }
}

#endif