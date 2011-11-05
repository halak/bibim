#include <Bibim/PCH.h>
#include <Bibim/GameModule.h>
#include <Bibim/Assert.h>
#include <Bibim/GameModuleNode.h>
#include <Bibim/GameModuleTree.h>

namespace Bibim
{
    const int GameModule::UnspecifiedID = -1;

    GameModule::GameModule()
        : node(nullptr),
          id(UnspecifiedID),
          alive(true),
          active(true)
    {
    }

    GameModule::GameModule(int id)
        : node(nullptr),
          id(id),
          alive(true),
          active(true)
    {
    }

    GameModule::~GameModule()
    {
        if (node)
            node->OnModuleDestructed();
    }

    void GameModule::SetID(int value)
    {
        if (id != value)
        {
            // GameStructure���� ���� ID�� GameComponent�� �� �� �̻� ������ �� �����ϴ�.
            BBAssertDebug(value != UnspecifiedID &&
                          node && node->GetTree() && node->GetTree()->Find(value) != nullptr);

            const int oldID = id;

            id = value;

            if (node && node->GetTree())
                node->GetTree()->OnModuleIDChanged(this, oldID);
        }
    }

    void GameModule::SetAlive(bool value)
    {
        if (alive != value)
        {
            const Status old = GetStatus();

            alive = value;

            BBAssertDebug(GetStatus() != old); // Alive�� �ٲ�� Status�� �ݵ�� �ٲ�ϴ�.

            OnStatusChanged(old);

            if (node)
                node->OnModuleAliveChanged();
        }
    }
    
    void GameModule::SetActive(bool value)
    {
        if (active != value)
        {
            const Status old = GetStatus();

            active = value;

            // DeadStatus���� Active�� �ٲ� Status�� �ٲ��� �ʵ�
            // Active�� Status�� ������������ ������ ���� �ʽ��ϴ�.
            if (alive)
                OnStatusChanged(old);
        }
    }

    void* GameModule::QueryClass(int /*classID*/)
    {
        return nullptr;
    }

    void GameModule::OnStatusChanged(Status /*old*/)
    {
    }
}