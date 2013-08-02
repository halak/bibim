#include <Bibim/ManualLocker.h>
#include <Bibim/Assert.h>

namespace Bibim
{
    ManualLocker::~ManualLocker()
    {
        BBAssert(lockCount == 0);
    }
}