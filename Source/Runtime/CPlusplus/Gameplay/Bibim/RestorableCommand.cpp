#include <Bibim/PCH.h>
#include <Bibim/RestorableCommand.h>

namespace Bibim
{
    RestorableCommand::RestorableCommand()
    {
    }

    RestorableCommand::~RestorableCommand()
    {
    }

    void RestorableCommand::Redo()
    {
        Execute();
    }

    bool RestorableCommand::CanUndo() const
    {
        return true;
    }

    bool RestorableCommand::CanRedo() const
    {
        return true;
    }

    bool RestorableCommand::IsRestorable() const
    {
        return true;
    }
}