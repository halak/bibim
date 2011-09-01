#include <Bibim/PCH.h>
#include <Bibim/BatchCommand.h>
#include <Bibim/Assert.h>
#include <Bibim/CloningContext.h>
#include <Bibim/Delete.h>

namespace Bibim
{
    BatchCommand::BatchCommand(const CommandCollection commands)
    {
        SetCommands(commands);
    }

    BatchCommand::BatchCommand(const BatchCommand& original, CloningContext& context)
    {
        commands.reserve(original.commands.size());
        for (CommandCollection::const_iterator it = original.commands.begin(); it != original.commands.end(); it++)
            commands.push_back(context.Clone(*it));

        restorableCommands.reserve(original.restorableCommands.size());
        for (RestorableCommandCollection::const_iterator it = original.restorableCommands.begin(); it != original.restorableCommands.end(); it++)
            restorableCommands.push_back(context.Clone(*it));
    }

    BatchCommand::~BatchCommand()
    {
        restorableCommands.clear();
        DeleteAll(commands);
    }

    BatchCommand* BatchCommand::CloneWith(CloningContext& context) const
    {
        return new BatchCommand(*this, context);
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
                restorableCommands.push_back(static_cast<RestorableCommand*>(*it));
        }
    }
}