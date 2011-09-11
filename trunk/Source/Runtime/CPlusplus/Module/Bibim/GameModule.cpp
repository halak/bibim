#include <Bibim/PCH.h>
#include <Bibim/GameModule.h>
#include <Bibim/Assert.h>
#include <Bibim/GameModuleNode.h>
#include <Bibim/GameModuleTree.h>

namespace Bibim
{
    const uint GameModule::UnspecifiedID = 0xFFFFFFFF;

    GameModule::GameModule()
        : node(nullptr),
          id(UnspecifiedID),
          alive(true),
          active(true)
    {
    }

    GameModule::GameModule(uint32 id)
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

    void GameModule::SetID(uint32 value)
    {
        if (id != value)
        {
            // GameStructure내에 같은 ID의 GameComponent가 두 개 이상 존재할 수 없습니다.
            BBAssertDebug(value != UnspecifiedID &&
                          node && node->GetTree() && node->GetTree()->Find(value) != nullptr);

            const uint oldID = id;

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

            BBAssertDebug(GetStatus() != old); // Alive가 바뀌면 Status도 반드시 바뀝니다.

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

            // DeadStatus에선 Active가 바뀌어도 Status가 바뀌지 않듯
            // Active는 Status에 무조건적으로 영향을 주지 않습니다.
            if (alive)
                OnStatusChanged(old);
        }
    }

    void* GameModule::QueryClass(uint32 /*classID*/)
    {
        return nullptr;
    }

    void GameModule::OnStatusChanged(Status /*old*/)
    {
    }
}