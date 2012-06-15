#include <Bibim/PCH.h>
#include <Bibim/BatchCommand.h>
#include <Bibim/Assert.h>
#include <Bibim/Delete.h>

namespace Bibim
{
    BatchCommand::BatchCommand()
    {
    }

    BatchCommand::BatchCommand(const CommandCollection commands)
    {
        SetCommands(commands);
    }

    BatchCommand::~BatchCommand()
    {
        restorableCommands.clear();
        DeleteAll(commands);
    }

    void BatchCommand::Execute()
    {
        for (CommandCollection::iterator it = commands.begin(); it != commands.end(); it++)
            (*it)->Execute();
    }

    void BatchCommand::Undo()
    {
        BBAssertDebug(CanUndo());

        for (RestorableCommandCollection::reverse_iterator it = restorableCommands.rbegin(); it != restorableCommands.rend(); it++)
            (*it)->Undo();
    }

    void BatchCommand::Redo()
    {
        BBAssertDebug(CanRedo());

        for (RestorableCommandCollection::iterator it = restorableCommands.begin(); it != restorableCommands.end(); it++)
            (*it)->Redo();
    }

    bool BatchCommand::CanUndo() const
    {
        if (commands.size() != restorableCommands.size())
            return false;

        for (RestorableCommandCollection::const_reverse_iterator it = restorableCommands.rbegin(); it != restorableCommands.rend(); it++)
        {
            if ((*it)->CanUndo() == false)
                return false;
        }
        
        return true;
    }

    bool BatchCommand::CanRedo() const
    {
        if (commands.size() != restorableCommands.size())
            return false;

        for (RestorableCommandCollection::const_iterator it = restorableCommands.begin(); it != restorableCommands.end(); it++)
        {
            if ((*it)->CanRedo() == false)
                return false;
        }

        return true;
    }

    void BatchCommand::SetCommands(const CommandCollection& value)
    {
        restorableCommands.clear();
        restorableCommands.reserve(value.size());
        DeleteAll(commands);
        commands = value;

        for (CommandCollection::iterator it = commands.begin(); it != commands.end(); it++)
        {
            if ((*it)->IsRestorable())
                restorableCommands.push_back(StaticCast<RestorableCommand>(*it));
        }
    }
}