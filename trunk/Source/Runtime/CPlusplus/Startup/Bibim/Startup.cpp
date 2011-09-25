#include <Bibim/Startup.h>
#include <Bibim/All.h>

namespace Bibim
{
    void Startup::All()
    {
        GameAssetFactory::AddEntry<SourceTexture2D>();
        GameAssetFactory::AddEntry<UILayout>();
        GameAssetFactory::SortEntries();
    }
}