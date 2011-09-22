#include <Bibim/AssetStreamReader.h>
#include <Bibim/Assert.h>
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
          modules(storage->GetModules())
    {
        BBAssert(storage);
        BBAssert(modules);
    }

    AssetStreamReader::AssetStreamReader(const AssetStreamReader& original)
        : BinaryReader(original),
          name(original.name),
          storage(original.storage),
          modules(original.modules)
    {
    }

    AssetStreamReader::~AssetStreamReader()
    {
    }

    void AssetStreamReader::ReadAsync(AssetLoadingTask* task)
    {
        BBAssertDebug(task);
        storage->Add(task);
    }

    GameModule* AssetStreamReader::ReadModule()
    {
        if (modules == nullptr)
            return nullptr;

        const uint32 id = ReadUInt32();
        if (id != 0x00000000)
            return modules->Find(id);
        else
            return nullptr;
    }

    GameModule* AssetStreamReader::ReadModule(uint32 defaultModuleClassID)
    {
        if (GameModule* module = ReadModule())
            return module;
        else
            return FindModuleByClassID(defaultModuleClassID);
    }

    GameModule* AssetStreamReader::FindModuleByClassID(uint32 classID)
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
        return *this;
    }
}