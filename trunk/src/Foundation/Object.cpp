#include <Bibim/Config.h>
#include <Bibim/Object.h>

namespace Bibim
{
    const ClassInfo Object::Class;

    Object::Object()
    {
    }

    const ClassInfo& Object::GetClass() const
    {
        return Class;
    }

    int Object::GetClassID() const
    {
        return 0;
    }
}