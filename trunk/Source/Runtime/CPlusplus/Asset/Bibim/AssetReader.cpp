#include <Bibim/AssetReader.h>
#include <Bibim/Assert.h>
#include <Bibim/GameModule.h>
#include <Bibim/GameModuleTree.h>

namespace Bibim
{
    AssetReader::AssetReader(Stream* sourceStream, GameModuleTree* modules)
        : StreamReader(sourceStream),
          modules(modules)
    {
        BBAssert(modules);
    }

    AssetReader::AssetReader(const AssetReader& original)
        : StreamReader(original),
          modules(original.modules)
    {
    }

    AssetReader::~AssetReader()
    {
    }

    GameModule* AssetReader::ReadModule()
    {
        return nullptr;
    }

    AssetReader& AssetReader::operator = (const AssetReader& right)
    {
        StreamReader::operator = (right);
        modules = right.modules;
        return *this;
    }
}