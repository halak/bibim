#include <Bibim/PCH.h>
#include <Bibim/UpdateableGameComponent.h>

namespace Bibim
{
    UpdateableGameComponent::UpdateableGameComponent()
        : lastTimestamp(-1)
    {
    }

    UpdateableGameComponent::~UpdateableGameComponent()
    {
    }

    void UpdateableGameComponent::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
    }
    
    void UpdateableGameComponent::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
    }
}