#include <Bibim/Config.h>
#include <Bibim/ClassInfo.h>
#include <Bibim/ClassHierarchy.h>
#include <vector>

namespace Bibim
{
    static std::vector<const ClassInfo*> registeredClasses;

    const ClassInfo* ClassHierarchy::Find(int id)
    {
        // TODO: ����ȭ ���� ����
        for (std::vector<const ClassInfo*>::const_iterator it = registeredClasses.begin(); it != registeredClasses.end(); it++)
        {
            if ((*it)->GetID() == id)
                return (*it);
        }

        // ��������� �Ͼ �� ����
        return nullptr;
    }

    void ClassHierarchy::Add(const ClassInfo* item)
    {
        registeredClasses.push_back(item);
    }
}