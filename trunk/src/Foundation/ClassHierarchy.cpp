#include <Bibim/Config.h>
#include <Bibim/Class.h>
#include <Bibim/ClassHierarchy.h>
#include <vector>

namespace Bibim
{
    static std::vector<const Class*> registeredClasses;

    const Class* ClassHierarchy::Find(int id)
    {
        // TODO: 최적화 여지 있음
        for (std::vector<const Class*>::const_iterator it = registeredClasses.begin(); it != registeredClasses.end(); it++)
        {
            if ((*it)->GetID() == id)
                return (*it);
        }

        // 상식적으로 일어날 수 없음
        return nullptr;
    }

    void ClassHierarchy::Add(const Class* item)
    {
        registeredClasses.push_back(item);
    }
}