#include <Bibim/PCH.h>
#include <Bibim/GameComponent.h>
#include <Bibim/CloningContext.h>
#include <Bibim/ComponentStreamReader.h>

namespace Bibim
{
    GameComponent::GameComponent()
        : id(UnspecifiedID)
    {
    }

    GameComponent::GameComponent(uint id)
        : id(id)
    {
    }

    GameComponent::~GameComponent()
    {
    }

    GameComponent* GameComponent::Clone() const
    {
        CloningContext context;
        return Clone(context);
    }

    void GameComponent::OnRead(ComponentStreamReader& reader)
    {
        id = reader.ReadUInt32();
    }

    void GameComponent::OnCopy(const GameComponent* original, CloningContext& /*context*/)
    {
        id = original->id;
    }
}