#include <Bibim/PCH.h>
#include <Bibim/IClassQueryable.h>

namespace Bibim
{
    const void* IClassQueryable::QueryClass(uint32 classID) const
    {
        return const_cast<IClassQueryable*>(this)->QueryClass(classID);
    }
}