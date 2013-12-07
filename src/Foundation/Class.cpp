#include <Bibim/Config.h>
#include <Bibim/Class.h>
#include <Bibim/ClassHierarchy.h>

namespace Bibim
{
    Class::Class(int id)
        : id(id),
          base(nullptr),
          baseID(0)
    {
    }

    Class::Class(int id, int baseID)
        : id(id),
          base(nullptr),
          baseID(baseID)
    {
        ClassHierarchy::Add(this);
    }

    Class::~Class()
    {
    }

    const Class* Class::GetBase() const
    {
        if (base == nullptr && baseID != 0)
            base = ClassHierarchy::Find(baseID);
        
        return base;
    }

    bool Class::IsInstanceOf(const Class* other) const
    {
        return IsInstanceOf(other->GetID());
    }

    bool Class::IsInstanceOf(int id) const
    {
        const Class* current = this;
        while (current && current->GetID() != id)
            current = current->GetBase();

        return current ? true : false;
    }
}