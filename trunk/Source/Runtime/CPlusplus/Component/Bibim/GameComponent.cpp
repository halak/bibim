#include <Bibim/PCH.h>
#include <Bibim/GameComponent.h>
#include <Bibim/ComponentStreamReader.h>

namespace Bibim
{
    const int GameComponent::UnspecifiedID = -1;

    GameComponent::GameComponent()
        : id(UnspecifiedID)
    {
    }

    GameComponent::GameComponent(int id)
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
        id = reader.ReadInt();
    }

    void GameComponent::OnCopy(const GameComponent* original, CloningContext& /*context*/)
    {
        id = original->id;
    }
}