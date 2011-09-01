#include <Bibim/PCH.h>
#include <Bibim/GameModule.h>

namespace Bibim
{
    GameModule::GameModule()
    {
    }

    GameModule::GameModule(uint32 id)
        : GameComponent(id)
    {
    }

    GameModule::GameModule(const GameModule& original, CloningContext& context)
        : GameComponent(),
          ICloneable(context),
          name(original.name),
          filename(original.filename),
          description(original.description)
    {
    }

    GameModule::~GameModule()
    {
    }

    GameModule* GameModule::CloneWith(CloningContext& context) const
    {
        return new GameModule(*this, context);
    }

    ICloneable* GameModule::QueryCloneableInterface()
    {
        return this;
    }
}