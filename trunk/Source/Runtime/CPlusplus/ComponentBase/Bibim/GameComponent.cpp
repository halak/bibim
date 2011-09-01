#include <Bibim/PCH.h>
#include <Bibim/GameComponent.h>
#include <Bibim/Assert.h>
#include <Bibim/Exception.h>
#include <Bibim/GameNode.h>
#include <Bibim/GameStructure.h>
#include <Bibim/ICloneable.h>
#include <Bibim/IUpdateable.h>

namespace Bibim
{
    const uint GameComponent::UnspecifiedID = 0xFFFFFFFF;

    GameComponent::GameComponent()
        : node(nullptr),
          id(UnspecifiedID),
          alive(true),
          active(true)
    {
    }

    GameComponent::GameComponent(uint32 id)
        : node(nullptr),
          id(id),
          alive(true),
          active(true)
    {
    }

    GameComponent::~GameComponent()
    {
        if (node)
            node->OnComponentDestructed();
    }

    void GameComponent::SetID(uint32 value)
    {
        if (id != value)
        {
            // GameStructure내에 같은 ID의 GameComponent가 두 개 이상 존재할 수 없습니다.
            if (value != UnspecifiedID && node && node->GetStructure())
                BBIfThrow(node->GetStructure()->Find(value), Exception("value"));

            const uint oldID = id;

            id = value;

            if (node && node->GetStructure())
                node->GetStructure()->OnComponentIDChanged(this, oldID);
        }
    }

    void GameComponent::SetAlive(bool value)
    {
        if (alive != value)
        {
            const Status old = GetStatus();

            alive = value;

            BBAssertDebug(GetStatus() != old); // Alive가 바뀌면 Status도 반드시 바뀝니다.

            OnStatusChanged(old);

            if (node)
                node->OnComponentAliveChanged();
        }
    }
    
    void GameComponent::SetActive(bool value)
    {
        if (active != value)
        {
            const Status old = GetStatus();

            active = value;

            // DeadStatus에선 Active가 바뀌어도 Status가 바뀌지 않듯
            // Active는 Status에 무조건적으로 영향을 주지 않습니다.
            if (GetStatus() != old)
                OnStatusChanged(old);
        }
    }

    ICloneable* GameComponent::QueryCloneableInterface()
    {
        return nullptr;
    }

    const ICloneable* GameComponent::QueryCloneableInterface() const
    {
        return const_cast<GameComponent*>(this)->QueryCloneableInterface();
    }

    IUpdateable* GameComponent::QueryUpdateableInterface()
    {
        return nullptr;
    }

    const IUpdateable* GameComponent::QueryUpdateableInterface() const
    {
        return const_cast<GameComponent*>(this)->QueryUpdateableInterface();
    }

    void* GameComponent::QueryClass(uint32 classID)
    {
        switch (classID)
        {
            case ICloneable::ClassID:
                return QueryCloneableInterface();
            case IUpdateable::ClassID:
                return QueryUpdateableInterface();
            default:
                return nullptr;
        }
    }

    void GameComponent::OnStatusChanged(Status /*old*/)
    {
    }
}