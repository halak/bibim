#include <Bibim/PCH.h>
#include <Bibim/SharedObject.h>
#include <Bibim/Atomic.h>

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

    void SharedObject::IncreaseReferenceCount()
    {
        Atomic::Increment(referenceCount);
    }

    void SharedObject::DecreaseReferenceCount()
    {
        Atomic::Decrement(referenceCount);
        if (referenceCount == 0)
            delete this;
    }
}