#include <Bibim/PCH.h>
#include <Bibim/SharedObject.h>

namespace Bibim
{
    SharedObject::SharedObject()
        : referenceCount(0)
    {
    }

    SharedObject::SharedObject(const SharedObject& /*original*/)
        : referenceCount(0)
    {
    }

    SharedObject::~SharedObject()
    {
    }
}