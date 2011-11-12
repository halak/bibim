#include <Bibim/PCH.h>
#include <Bibim/GameComponent.h>
#include <Bibim/ComponentStreamReader.h>

namespace Bibim
{
    GameComponent::GameComponent()
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
    }

    void GameComponent::OnCopy(const GameComponent* original, CloningContext& /*context*/)
    {
    }
}