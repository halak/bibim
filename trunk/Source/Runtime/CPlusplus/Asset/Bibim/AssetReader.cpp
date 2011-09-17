#include <Bibim/AssetReader.h>
#include <Bibim/Assert.h>
#include <Bibim/GameAssetStorage.h>
#include <Bibim/GameModule.h>
#include <Bibim/GameModuleNode.h>
#include <Bibim/GameModuleTree.h>

namespace Bibim
{
    AssetReader::AssetReader(Stream* sourceStream, GameAssetStorage* storage)
        : BinaryReader(sourceStream),
          storage(storage),
          modules(storage->GetModules())
    {
        BBAssert(storage);
        BBAssert(modules);
    }

    AssetReader::AssetReader(const AssetReader& original)
        : BinaryReader(original),
          storage(original.storage),
          modules(original.modules)
    {
    }

    AssetReader::~AssetReader()
    {
    }

    void AssetReader::ReadAsync(GameAssetLoadingTask* task)
    {
        BBAssertDebug(task);
        storage->Add(task);
    }

    GameModule* AssetReader::ReadModule()
    {
        if (modules == nullptr)
            return nullptr;

        const uint32 id = ReadUInt32();
        if (id != 0x00000000)
            return modules->Find(id);
        else
            return nullptr;
    }

    GameModule* AssetReader::ReadModule(uint32 defaultModuleClassID)
    {
        if (GameModule* module = ReadModule())
            return module;
        else
            return FindModuleByClassID(defaultModuleClassID);
    }

    GameModule* AssetReader::FindModuleByClassID(uint32 classID)
    {
        if (modules)
            return modules->GetRoot()->FindChildByClassID(classID);
        else
            return nullptr;
    }

    AssetReader& AssetReader::operator = (const AssetReader& right)
    {
        BinaryReader::operator = (right);
        storage = right.storage;
        modules = right.modules;
        return *this;
    }
}