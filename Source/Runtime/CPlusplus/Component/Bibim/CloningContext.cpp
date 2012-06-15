#include <Bibim/PCH.h>
#include <Bibim/CloningContext.h>
#include <Bibim/Assert.h>
#include <Bibim/GameComponent.h>

namespace Bibim
{
    CloningContext::CloningContext()
    {
    }

    CloningContext::~CloningContext()
    {
    }

    void CloningContext::Store(const GameComponent* original, GameComponent* clone)
    {
        BBAssertDebug(originalCloneMap.find(original) == originalCloneMap.end());
        originalCloneMap.insert(ComponentMap::value_type(original, clone));
    }

    GameComponent* CloningContext::CloneComponent(const GameComponent* original)
    {
        if (original == nullptr)
            return nullptr;

        ComponentMap::const_iterator it = originalCloneMap.find(original);
        if (it != originalCloneMap.end())
            return (*it).second;
        else
        {
            GameComponent* clone = original->Clone(*this);
            BBAssertDebug(clone != nullptr);
            BBAssertDebug(original == clone || originalCloneMap.find(original) != originalCloneMap.end());
            return clone;
        }
    }
}