#include <Bibim/PCH.h>
#include <Bibim/Asset.h>

namespace Bibim
{
    Asset::Asset()
        : uri(URI::Empty)
    {
    }

    Asset::Asset(const URI& uri)
        : uri(uri)
    {
    }

    Asset::~Asset()
    {
    }
}