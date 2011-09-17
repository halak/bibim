#include <Bibim/PCH.h>
#include <Bibim/GameAsset.h>

namespace Bibim
{
    GameAsset::GameAsset()
        : status(EmptyStatus),
          revision(0)
    {
    }

    GameAsset::~GameAsset()
    {
    }
}