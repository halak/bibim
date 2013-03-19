#include <Bibim/PCH.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/GameAsset.h>
#include <Bibim/GameAssetStorage.h>
#include <Bibim/GameComponent.h>
#include <Bibim/GameComponentFactory.h>
#include <Bibim/GameModuleNode.h>
#include <Bibim/GameModuleTree.h>

namespace Bibim
{
    ComponentStreamReader::ComponentStreamReader(Stream* sourceStream, GameModuleTree* modules)
        : BinaryReader(sourceStream),
          modules(modules),
          storage(nullptr)
    {
        
    }

    ComponentStreamReader::~ComponentStreamReader()
    {
    }

    GameAssetStorage* ComponentStreamReader::GetStorage()
    {
        if (storage == nullptr)
            storage = static_cast<GameAssetStorage*>(FindModuleByClassID(GameAssetStorage::ClassID));

        return storage;
    }

    GameModule* ComponentStreamReader::ReadModule()
    {
        if (modules == nullptr)
            return nullptr;

        const int id= ReadInt();
        if (id != 0)
            return modules->Find(id);
        else
            return nullptr;
    }

    GameModule* ComponentStreamReader::ReadModule(int defaultModuleClassID)
    {
        if (GameModule* module = ReadModule())
            return module;
        else
            return FindModuleByClassID(defaultModuleClassID);
    }

    GameModule* ComponentStreamReader::FindModuleByClassID(int classID)
    {
        if (modules)
            return modules->GetRoot()->FindChildByClassID(classID);
        else
            return nullptr;
    }

    GameAsset* ComponentStreamReader::ReadAsset()
    {
        const String assetName = ReadString();
        if (assetName.IsEmpty())
            return nullptr;

        return GetStorage()->Load(assetName);
    }

    GameComponent* ComponentStreamReader::ReadComponent()
    {
        const int index = ReadInt();
        if (index == -1)
            return nullptr;

        BBAssert(0 <= index);

        if (index >= static_cast<int>(localComponents.size()))
            localComponents.resize(index + 1);

        if (localComponents[index])
            return localComponents[index];

        const int classID = ReadInt();
        if (classID == 0)
            return nullptr;

        if (GameComponent* o = GameComponentFactory::Create(classID))
        {
            localComponents[index] = o;
            o->OnRead(*this);
            return o;
        }
        else
            return nullptr;
    }

    void ComponentStreamReader::Read(GameAssetPtr& outValue)
    {
        outValue = ReadAsset();
    }

    void ComponentStreamReader::Read(GameComponentPtr& outValue)
    {
        outValue = ReadComponent();
    }
}