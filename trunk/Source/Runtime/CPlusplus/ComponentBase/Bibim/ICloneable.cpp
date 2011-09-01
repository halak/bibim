#include <Bibim/PCH.h>
#include <Bibim/ICloneable.h>
#include <Bibim/CloningContext.h>

namespace Bibim
{
    ICloneable::ICloneable()
    {
    }

    ICloneable::ICloneable(CloningContext& /*context*/)
    {
    }

    ICloneable* ICloneable::Clone() const
    {
        CloningContext context;
        return CloneWith(context);
    }
}