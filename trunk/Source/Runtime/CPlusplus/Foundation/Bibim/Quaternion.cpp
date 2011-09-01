#include <Bibim/PCH.h>
#include <Bibim/Quaternion.h>

namespace Bibim
{  
    const Quaternion Quaternion::Zero     = Quaternion(0.0f, 0.0f, 0.0f, 0.0f);
    const Quaternion Quaternion::Identity = Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
}