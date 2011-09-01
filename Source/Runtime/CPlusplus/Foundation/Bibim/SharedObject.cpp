#include <Bibim/PCH.h>
#include <Bibim/SharedObject.h>
#include <Bibim/SharedObjectLife.h>

namespace Bibim
{
    SharedObject::SharedObject()
        : life(0)
    {
    }

    SharedObject::SharedObject(const SharedObject& /*original*/)
        : life(0)
    {
    }

    SharedObject::~SharedObject()
    {
    }
}