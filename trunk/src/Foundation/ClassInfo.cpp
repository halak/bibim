#include <Bibim/Config.h>
#include <Bibim/ClassInfo.h>
#include <Bibim/ClassHierarchy.h>

namespace Bibim
{
    ClassInfo::ClassInfo()
        : id(0),
          base(nullptr)
    {
    }

    ClassInfo::ClassInfo(int id)
        : id(id),
          base(nullptr)
    {
    }

    ClassInfo::ClassInfo(ClassInfo* base)
        : id(0),
          base(base)
    {
    }

    ClassInfo::ClassInfo(int id, ClassInfo* base)
        : id(id),
          base(base)
    {
    }

    ClassInfo::~ClassInfo()
    {
    }

    bool ClassInfo::IsInstanceOf(const ClassInfo* other) const
    {
        const ClassInfo* current = this;
        while (current && current != other)
            current = current->GetBase();

        return current ? true : false;
    }
}