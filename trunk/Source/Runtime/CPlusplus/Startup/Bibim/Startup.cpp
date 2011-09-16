#include <Bibim/Startup.h>
#include <Bibim/GameAssetFactory.h>
#include <Bibim/GameModuleFactory.h>
#include <Bibim/SourceTexture2D.h>
#include <Bibim/All.h>

namespace Bibim
{
    void Startup::All()
    {
        GameAssetFactory::AddEntry<SourceTexture2D>();
        GameAssetFactory::SortEntries();
    }
}