#include <Bibim/AssetStreamReader.h>
#include <Bibim/Assert.h>
#include <Bibim/GameAsset.h>
#include <Bibim/GameAssetStorage.h>
#include <Bibim/GameModule.h>
#include <Bibim/GameModuleNode.h>
#include <Bibim/GameModuleTree.h>

namespace Bibim
{
    AssetStreamReader::AssetStreamReader(const String& name, Stream* sourceStream, GameAssetStorage* storage)
        : BinaryReader(sourceStream),
          name(name),
          storage(storage),
          modules(storage->GetModules()),
          isPriority(false)
    {
        BBAssert(storage);
        BBAssert(modules);
    }

    AssetStreamReader::AssetStreamReader(const String& name, Stream* sourceStream, GameAssetStorage* storage, bool isPriority)
        : BinaryReader(sourceStream),
          name(name),
          storage(storage),
          modules(storage->GetModules()),
          isPriority(isPriority)
    {
        BBAssert(storage);
        BBAssert(modules);
    }

    AssetStreamReader::AssetStreamReader(const AssetStreamReader& original)
        : BinaryReader(original),
          name(original.name),
          storage(original.storage),
          modules(original.modules),
          isPriority(original.isPriority)
    {
    }

    AssetStreamReader::~AssetStreamReader()
    {
    }

    void AssetStreamReader::ReadAsync(AssetLoadingTask* task)
    {
        BBAssertDebug(task);
        if (isPriority)
            storage->AddFirst(task);
        else
            storage->AddLast(task);
    }

    GameModule* AssetStreamReader::ReadModule()
    {
        if (modules == nullptr)
            return nullptr;

        const int id = ReadInt();
        if (id != 0x00000000)
            return modules->Find(id);
        else
            return nullptr;
    }

    GameModule* AssetStreamReader::ReadModule(int defaultModuleClassID)
    {
        if (GameModule* module = ReadModule())
            return module;
        else
            return FindModuleByClassID(defaultModuleClassID);
    }

    GameAsset* AssetStreamReader::ReadAsset()
    {
        const String assetName = ReadString();
        if (assetName.IsEmpty())
            return nullptr;

        return storage->Load(assetName);
    }

    GameModule* AssetStreamReader::FindModuleByClassID(int classID)
    {
        if (modules)
            return modules->GetRoot()->FindChildByClassID(classID);
        else
            return nullptr;
    }

    AssetStreamReader& AssetStreamReader::operator = (const AssetStreamReader& right)
    {
        BinaryReader::operator = (right);
        name = right.name;
        storage = right.storage;
        modules = right.modules;
        isPriority = right.isPriority;
        return *this;
    }
}