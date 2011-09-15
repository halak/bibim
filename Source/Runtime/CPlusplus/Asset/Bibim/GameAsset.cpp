#include <Bibim/PCH.h>
#include <Bibim/GameAsset.h>

namespace Bibim
{
    GameAsset::GameAsset()
        : uri(URI::Empty)
    {
    }

    GameAsset::GameAsset(const URI& uri)
        : uri(uri)
    {
    }

    GameAsset::~GameAsset()
    {
    }
}